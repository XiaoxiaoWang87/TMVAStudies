#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>


#include <TF1.h>
#include <TH1.h>
#include <TLegend.h>
#include <TFile.h>
#include <TDirectory.h>
#include <TTree.h>
#include <TEnv.h>
#include "THStack.h"
#include "TFile.h"
#include "TTree.h"
#include "TKey.h"
#include "TCanvas.h"
#include <TStyle.h>
#include "TLatex.h"
#include "TImage.h"
#include "TLine.h"
#include "TColor.h"
#include "TROOT.h"
#include "TH2F.h"
#include "TMath.h"
#include "TPaveText.h"
#include "TSystem.h"

#include "../1LStopBoosted/usefull.h"

#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/IMethod.h"

#include "../1LStopBoosted/PlottingTools.h"
#include "../1LStopBoosted/readparameters.h"
#include "../1LStopBoosted/CrossSections.h"
#include "../1LStopBoosted/HistoHandler.h"
#include "../1LStopBoosted/selection.h"
#include "Train.h"


int main(int argc, char *argv[]){

    std::string outdir = "";
    std::string lumi = "10";
    std::string train = "False";
    std::string evaluate = "False";

    if(argc < 2){
      cout<<"no config file - do you know what you are doing?"<<endl;
      exit(1);
    }
    std::string globcfg = argv[1];
    readparameters rp(globcfg.c_str());
    outdir = rp.get<string>("_OUTDIR");    
    gSystem->mkdir(outdir.c_str());	

    train = rp.get<string>("_TRAIN");
    evaluate = rp.get<string>("_EVALUATE"); 
    lumi = rp.get<string>("_LUMI");

    Train* t = new Train(outdir,train,evaluate, lumi);   
	
    t->run();
   
    delete t;
    
    return 0;
}
Train::Train(){
    _outdir = "";
}

Train::Train(std::string outdir, std::string train, std::string evaluate,  std::string lumi){
    _outdir = outdir;
    _train = train;
    _evaluate = evaluate;
    _lumi = lumi;
}

Train::~Train(){
}


void Train::run(){
    
    xsec = new CrossSections("Files.txt");
    xsec->Setup();
    p = new PlottingTools(_outdir);    
    p->AtlasStyle();
   
    std::vector<std::string> filenames = xsec->GetFilenames();

        //initOutput(filenames[i]);
        //writeOutput();
        

    readTrainFile();
 

    // define methods here
    Use["Cuts"]            = 0;
    Use["Likelihood"]      = 0;
    Use["PDERS"]           = 0;
    Use["KNN"]             = 0;
    Use["Fisher"]          = 0;
    Use["HMatrix"]         = 0;
    Use["MLP"]             = 0;
    Use["SVM"]             = 0;
    Use["BDT"]             = 1;
    Use["BDTG"]            = 0;
    Use["RuleFit"]         = 0;


    // setup variables, pt bins and jet type here
    setup();


    // Training
    std::string train_output = "";

    std::map<std::string, std::string>::iterator fIter_t = pt_bin.begin();
    std::map<std::string, std::string>::iterator lIter_t = pt_bin.end();

    for(;fIter_t!=lIter_t;++fIter_t){

        // copy for plotting (tmva internal) and bookkeeping
        if(_evaluate == "False") {
	    gSystem->mkdir( (TString)(_outdir+ fIter_t->first) );
            train_output = _outdir+ fIter_t->first;
        }
        else if(_evaluate == "True") {
	    gSystem->mkdir( (TString)(_outdir+ fIter_t->first +"_t") );
            train_output = _outdir+ fIter_t->first +"_t/";     
	}

        gSystem->CopyFile( "tmvaglob.C", (_outdir+"tmvaglob.C").c_str() );
        gSystem->CopyFile( "variables.C", (_outdir+"variables.C").c_str() );
        gSystem->CopyFile( "plot.C", (_outdir+"plot.C").c_str() );
        gSystem->CopyFile( "Train.cxx", (_outdir+"Train.cxx").c_str(), true );

        gSystem->CopyFile( "tmvaglob.C", ( train_output+"/tmvaglob.C").c_str() );
	gSystem->CopyFile( "TMVAGui.C", ( train_output+"/TMVAGui.C").c_str() );
	gSystem->CopyFile( "efficiencies.C", ( train_output+"/efficiencies.C").c_str() );

        
        if(_train == "True") runTraining(train_output+"/TMVA.root", fIter_t->first, fIter_t->second);
    }

    // Evaluating
    if(_evaluate == "True"){

    std::map<std::string, std::string>::iterator fIter_e = pt_bin_e.begin();
    std::map<std::string, std::string>::iterator lIter_e = pt_bin_e.end();

    for(;fIter_e!=lIter_e;++fIter_e){

            std::string wt_bin;
            wt_bin = fIter_e->first;
    	    runEvaluating("weights/", wt_bin, fIter_e->second);

    	}
    }

    return;
}


void Train::readTrainFile(){

    TFile* sig = new TFile("signal.root","READ");
    TFile* bkg = new TFile("background.root","READ");

    TTree* sTree = (TTree*)sig->Get("minuit");
    TTree* bTree = (TTree*)bkg->Get("minuit");

    //// save file name for MVA training/evaluating
    treesMVA[name]["signal"] = sTree;
    treesMVA[name]["background"] = bTree;

}




void Train::initOutput(std::string name) {

    std::string oname = _outdir+name+".root";
    currentOut = TFile::Open(oname.c_str(), "RECREATE");

    tmp = TFile::Open("tmp.root", "RECREATE");

}
 
void Train::writeOutput(){

    currentOut->cd();

    // loop over all histograms
    std::map<std::string, std::map<std::string, TH1F*> >::iterator fIter = currentHist.begin();
    std::map<std::string, std::map<std::string, TH1F*> >::iterator lIter = currentHist.end();
    for(;fIter!=lIter;++fIter){
        std::map<std::string, TH1F*>::iterator ffIter = fIter->second.begin();
        std::map<std::string, TH1F*>::iterator flIter = fIter->second.end();
        for(;ffIter!=flIter;++ffIter)
            ffIter->second->Write();
    }
    currentOut->Close();
}     




void Train::setup(){

    _variables.clear();
    _spectators.clear();

    _spectators.push_back("FatJet_Pt");

    _variables.push_back("FatJet_Tau3M");

    pt_bin["incl"] = "all";
    pt_bin_e["incl"] = "all";

    // set sanity cuts
    _match = "";

}



// **** traning tmva ****
void Train::runTraining(std::string outfile, std::string ptbin, std::string ptcuts){
    
    TString on(outfile);
    TFile* outputFile = TFile::Open(on, "RECREATE");
    outputFile->cd();


    TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

    // add variables
    for(unsigned int v = 0; v < _variables.size(); ++v){
        factory->AddVariable(_variables[v].c_str(), 'F');
    }

    // if want to add spectators
    //for(unsigned int s = 0; s < _spectators.size(); ++s){
    //    factory->AddSpectator( _spectators[s].c_str(), 'F');
    //}

    std::map<std::string, std::map<std::string, TTree*> >::iterator fIter_f = treesMVA.begin();
    std::map<std::string, std::map<std::string, TTree*> >::iterator lIter_f = treesMVA.end();
    for(;fIter_f!=lIter_f;++fIter_f){

        std::string sel = _match;
	std::cout<<"selection (training sample): "<<sel<<std::endl;

        std::map<std::string, TTree*>::iterator fIter_t = fIter_f->second.begin();
        std::map<std::string, TTree*>::iterator lIter_t = fIter_f->second.end();

        for(;fIter_t!=lIter_t;++fIter_t){
            if(_evaluate == "True") mva_t[fIter_f->first][fIter_t->first] = (TTree*) fIter_t->second->CopyTree(("EventNumber % 2 == 0 && "+sel).c_str());
	    else if(_evaluate == "False") mva_t[fIter_f->first][fIter_t->first] = (TTree*) fIter_t->second->CopyTree(sel.c_str());	
        }
    }


    factory->AddSignalTree(mva_t["stop"]["signal"], 1);

    factory->AddBackgroundTree(mva_t["SM"]["background"], 1);

    if (_reweight == "False"){
            factory->SetSignalWeightExpression("EventWeight");
            factory->SetBackgroundWeightExpression("EventWeight");
    }



    std::string mycuts = ""; 
    std::string mycutb = "";
    
    if(_evaluate == "False") factory->PrepareTrainingAndTestTree(mycuts.c_str(), mycutb.c_str(), "nTrain_Signal=0:nTrain_Background=0:nTest_Signal=0:nTest_Background=0:SplitMode=Random:NormMode=NumEvents:!V");
    else if(_evaluate == "True") factory->PrepareTrainingAndTestTree(mycuts.c_str(), mycutb.c_str(), "nTrain_Signal=0:nTrain_Background=0:nTest_Signal=1:nTest_Background=1:SplitMode=Random:NormMode=NumEvents:!V");

    
    if (Use["Likelihood"])
    	factory->BookMethod( TMVA::Types::kLikelihood, "Likelihood",
                	        "H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=400" );
    if (Use["Cuts"])
    	factory->BookMethod( TMVA::Types::kCuts, "Cuts",
        	                "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart" );
    if (Use["PDERS"])
    	factory->BookMethod( TMVA::Types::kPDERS, "PDERS",
                	        "!H:!V:NormTree=T:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600" );
    if (Use["KNN"])
    	factory->BookMethod( TMVA::Types::kKNN, "KNN",
        	                "H:nkNN=20:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:!Trim" );
    if (Use["HMatrix"])
    	factory->BookMethod( TMVA::Types::kHMatrix, "HMatrix", "!H:!V:VarTransform=None" );
    if (Use["Fisher"])
    	factory->BookMethod( TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );
    if (Use["MLP"])
	factory->BookMethod( TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator" );
    if (Use["SVM"])
    	factory->BookMethod( TMVA::Types::kSVM, "SVM", "Gamma=0.25:Tol=0.001:VarTransform=Norm" );	   
    if (Use["BDT"]) 
        factory->BookMethod( TMVA::Types::kBDT, "BDT",
                                "!H:!V:NTrees=500:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
    if (Use["BDTG"])
        factory->BookMethod( TMVA::Types::kBDT, "BDTG",
                                "!H:!V:NTrees=750:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
    if (Use["RuleFit"])
    	factory->BookMethod( TMVA::Types::kRuleFit, "RuleFit",                        
        			"H:!V:RuleFitModule=RFTMVA:Model=ModRuleLinear:MinImp=0.001:RuleMinDist=0.001:NTrees=20:fEventsMin=0.01:fEventsMax=0.5:GDTau=-1.0:GDTauPrec=0.01:GDStep=0.01:GDNSteps=10000:GDErrScale=1.02" );
    
    
       
    factory->TrainAllMethods();
    factory->TestAllMethods();

    if(_evaluate == "False") factory->EvaluateAllMethods();
    
    outputFile->Close();
    delete factory;
    

}

void Train::runEvaluating(std::string outdir, std::string ptbin, std::string ptcuts){

   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );

   _fvar.resize((int)_variables.size());
   for(unsigned int v = 0; v < _variables.size(); ++v){
       reader->AddVariable(_variables[v].c_str(), &(_fvar[v]));
   }


   TString prefix = "TMVAClassification";

   // Book method(s)
   std::map<std::string, TMVA::IMethod*> method;
   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      if (it->second) {
         TString methodName = TString(it->first) + TString(" method");
         TString weightfile = outdir + prefix +TString("_") + TString(it->first) + TString(".weights.xml");
         std::cout<<"weightfile: "<<weightfile<<std::endl;
         method[(std::string)(methodName)] = reader->BookMVA( methodName, weightfile ); 
      }
   }


    std::map<std::string, std::map<std::string, TTree*> >::iterator fIter_f = treesMVA.begin();
    std::map<std::string, std::map<std::string, TTree*> >::iterator lIter_f = treesMVA.end();
    // loop over files
    for(;fIter_f!=lIter_f;++fIter_f){

        std::string sel = _match;
	std::cout<<"sel (evaluating sample): "<<sel<<std::endl;

        std::cout<<"fIter_f->first: "<<fIter_f->first<<std::endl;
        std::map<std::string, TTree*>::iterator fIter_t = fIter_f->second.begin();
        std::map<std::string, TTree*>::iterator lIter_t = fIter_f->second.end();

        TFile *target  = new TFile( (TString)(_outdir+ "MVA"+ fIter_f->first + ".root"),"RECREATE" );

        // loop over trees
        for(;fIter_t!=lIter_t;++fIter_t){
                std::cout<<"fIter_t->first: "<<fIter_t->first<<std::endl;
                // get the test tree 
		tmp->cd();
                TTree* mva_e = (TTree*) fIter_t->second->CopyTree(("EventNumber % 2 == 1 && "+sel).c_str());  

                // book all the histograms here (all methods)
		std::map<std::string, TH1F*> hist_disc;
		hist_disc["BDT method"] = new TH1F( ("MVA_"+fIter_t->first+"_BDT").c_str(),  "MVA_BDT",  80, -0.1, 0.6);
                hist_disc["BDT method"]->Sumw2();
          

                // add variables
                for(unsigned int v = 0; v < _variables.size(); ++v){
        		mva_e->SetBranchAddress( (_variables[v]).c_str(), &(_fvar[v]) );
        		std::cout<<"_variables: "<<_variables[v]<<std::endl;
                }
                Float_t EventWeight = 0;
                Float_t FatJet_Pt_SF = 0;
                Float_t TrimmedJet_Pt_SF = 0;
                Float_t FatJet_Pt = 0;
                Float_t TrimmedJet_Pt = 0;
                Long64_t EventNumber = 0;
                mva_e->SetBranchAddress("EventWeight", &EventWeight);
        	mva_e->SetBranchAddress("FatJet_Pt_SF", &FatJet_Pt_SF);
        	mva_e->SetBranchAddress("TrimmedJet_Pt_SF", &TrimmedJet_Pt_SF);
                mva_e->SetBranchAddress("FatJet_Pt", &FatJet_Pt);
                mva_e->SetBranchAddress("TrimmedJet_Pt", &TrimmedJet_Pt);
                mva_e->SetBranchAddress("EventNumber", &EventNumber);


                // loop over events
                Float_t weight;
        	for (Long64_t ievt=0; ievt<mva_e->GetEntries();ievt++) {
                     mva_e->GetEntry(ievt);

                     weight = EventWeight;
                    
                     // loop over methods
   		     std::map<std::string, TMVA::IMethod*>::iterator fIter_m = method.begin();
                     std::map<std::string, TMVA::IMethod*>::iterator lIter_m = method.end();
                     for(;fIter_m!=lIter_m;++fIter_m){
		     	hist_disc[fIter_m->first]->Fill(fIter_m->second->GetMvaValue(), weight);
		     }

               }
	       target->cd();
               if(fIter_t->first == "signal" || fIter_t->first == "background") {
			hist_disc["BDT method"]->Write();
               }

               delete hist_disc["BDT method"];
        }

        target->Close();
   }   


   method.clear();
   
   delete reader;
}

#ifndef TRAIN_H
#define TRAIN_H

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
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/IMethod.h"

#include "../1LStopBoosted/CrossSections.h"
#include "../1LStopBoosted/PlottingTools.h"
#include "../1LStopBoosted/selection.h"

using namespace std;


class Train{
    
public:
    Train(); 
    Train(std::string outdir, std::string train, std::string evaluate, std::string lumi);
    ~Train();
    
    void run();
    
private:
    
    void setup(); 
    void runTraining(std::string outfile, std::string ptbin, std::string ptcuts);
    void runEvaluating(std::string outdir, std::string ptbin, std::string ptcuts);

    void initOutput(std::string name);
    void writeOutput();
  
 
    void readTrainFile();
      
    PlottingTools* p;
    CrossSections* xsec;
    std::map< std::string,std::map<std::string,TTree*> > treesMVA;
    std::map< std::string,std::map<std::string,TTree*> > mva_t;

    std::map<std::string, std::map<std::string, TH1F*> > currentHist;

    std::map<std::string,int> Use;
    std::map<std::string,std::string> pt_bin;
    std::map<std::string,std::string> pt_bin_e;

    std::vector<std::string> _variables;
    std::vector<Float_t> _fvar;
    std::vector<std::string> _spectators;
    std::string _type;
    std::string _match;
    std::string _separation;
    std::string _sanitycuts;
     
    TFile* currentIn;
    TFile* currentOut;
    TFile* tmp;
   
    std::map< std::string, TTree*> currentTrees;
    
    std::string _outdir;
    std::string _lumi;
    std::string _train;
    std::string _evaluate;
    std::string _train_bin;
    std::string _use_bin;
    std::string _trimmed;
    std::string _reweight;
    std::string _plant;

    std::map<std::string,TTree*> _trees;

    std::map<std::string,TH1F*> _utr_hist;
    std::map<std::string,TH1F*> _tr_hist;
    std::map<std::string,TH1F*> _utr_new_hist;
    std::map<std::string,TH1F*> _tr_new_hist;
    std::map<std::string,TH1F*> _utr_SF_hist;
    std::map<std::string,TH1F*> _tr_SF_hist;

    std::map< std::string,std::map<std::string,TH1F*> > _histo;

    Int_t nBins;
    Float_t min;
    Float_t max;


};


#endif


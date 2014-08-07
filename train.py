import ROOT
from ROOT import * 



def main():

    #sig_f = TFile("../DLTree/T750_L1_0.root")
    #bkg_f = TFile("../DLTree/Tt.root")
    #f = TFile("/group/atlas/data/D3PDs/xwang/1LStopBoosted/plot_output/20140711_DL/merge.root")
    f = TFile("/group/atlas/data/D3PDs/xwang/1LStopBoosted/plot_output/20140727_DL/merge.root")
    
    sig_train_tree = f.Get('train')
    bkg_train_tree = f.Get('train')
    
    sig_test_tree = f.Get('validate')
    bkg_test_tree = f.Get('validate')
    
    ROOT.TMVA.Tools.Instance()
     
    # note that it seems to be mandatory to have an
    # output file, just passing None to TMVA::Factory(..)
    # does not work. Make sure you don't overwrite an
    # existing file.
    fout = ROOT.TFile("TMVA.root","RECREATE")
     
    factory = ROOT.TMVA.Factory("TMVAClassification", fout, ":".join(["!V","!Silent","Color","DrawProgressBar","Transformations=I;D;P;G,D","AnalysisType=Classification"]))
    
    factory.AddVariable("MET", "F") 
    #factory.AddVariable("mTW", "F") 
    	#factory.AddVariable("HT", "F") 
    	#factory.AddVariable("HTratio", "F") 
    	#factory.AddVariable("METsig", "F") 
    factory.AddVariable("HTmissSig", "F") 
    factory.AddVariable("aMT2", "F") 
    	#factory.AddVariable("MT2tau", "F") 
    factory.AddVariable("Topness", "F")
    factory.AddVariable("Jet1_Pt", "F") 
    factory.AddVariable("Jet2_Pt", "F") 
    factory.AddVariable("Jet3_Pt", "F")
    factory.AddVariable("Jet4_Pt", "F") 
    factory.AddVariable("Jet1_dPhiMET", "F") 
    factory.AddVariable("Jet2_dPhiMET", "F") 
    factory.AddVariable("Jet3_dPhiMET", "F") 
    factory.AddVariable("Jet4_dPhiMET", "F") 
    	#factory.AddVariable("Lepton_BTag70Jet_mindR", "F") 
    factory.AddVariable("Lepton_BMV1Jet_dR","F");
    factory.AddVariable("Lepton_TrimmedJet1_dR", "F") 
    factory.AddVariable("TrimmedJet1_Pt", "F") 
    factory.AddVariable("TrimmedJet1_4VM", "F") 
    	#factory.AddVariable("TrimmedJet2_dPhiMET", "F") 
     
    factory.AddSpectator("cutBTag70","F")
    factory.AddSpectator("Tauveto","F")
    factory.AddSpectator("tNboost_tauveto","F")
    factory.AddSpectator("tNboost_fj2met","F")

    sig_wt = 1.0
    bkg_wt = 1.0
    
    factory.AddSignalTree(sig_train_tree, sig_wt, TMVA.Types.kTraining)
    factory.AddBackgroundTree(bkg_train_tree, bkg_wt, TMVA.Types.kTraining)
    factory.AddSignalTree(sig_test_tree, sig_wt, TMVA.Types.kTesting)
    factory.AddBackgroundTree(bkg_test_tree, bkg_wt, TMVA.Types.kTesting)
    
    # apply event weight
    factory.SetSignalWeightExpression("EventWeight");
    factory.SetBackgroundWeightExpression("EventWeight");
    
    
    # cuts defining the signal and background sample
    #sigCut = ROOT.TCut("Signal > 0.5 && Tauveto < 0.5 && cutBTag70 > 0.5")
    #bgCut = ROOT.TCut("Signal < 0.5 && Tauveto < 0.5 && cutBTag70 > 0.5")
    sigCut = ROOT.TCut("Signal > 0.5 && tNboost_tauveto < 0.5 && cutBTag70 > 0.5 && tNboost_fj2met > 0.5")
    bgCut = ROOT.TCut("Signal < 0.5 && tNboost_tauveto < 0.5 && cutBTag70 > 0.5 && tNboost_fj2met > 0.5")     

    factory.PrepareTrainingAndTestTree(sigCut,   # signal events
                                       bgCut,    # background events
                                       ":".join([
                                            "nTrain_Signal=0",
                                            "nTrain_Background=0",
                                            "nTest_Signal=0",
                                            "nTest_Background=0",
                                            #"SplitMode=Random",
                                            "SplitMode=Block",
                                            #"NormMode=NumEvents",
                                            "NormMode=EqualNumEvents",
                                            #"NormMode=None",
                                            "!V"
                                           ]))
    
    
    method = factory.BookMethod(ROOT.TMVA.Types.kBDT, "BDT",
                       ":".join([
                           "!H",
                           "!V",
                           "NTrees=850",
                           #"MinNodeSize=2",
                           #"nEventsMin=150",
                           #"MaxDepth=3",
                           "MaxDepth=3",
                           "BoostType=AdaBoost",
                           "AdaBoostBeta=0.5",
                           "SeparationType=GiniIndex",
                           #"nCuts=20",
                           "nCuts=50",
                           "PruneMethod=NoPruning",
                           ]))
     
    factory.TrainAllMethods()
    factory.TestAllMethods()
    factory.EvaluateAllMethods()


if __name__ == '__main__':
    main()


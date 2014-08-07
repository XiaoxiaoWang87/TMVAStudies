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

#include "../../BoostedStop/PlottingTools.h"
#include "../../BoostedStop/HtmlConfig.h"
#include "Plot.h"
#include "../../BoostedStop/usefull.h"

int main(int argc, char *argv[]){
	
    
    Plot* m = new Plot();
	
    m->run();
    
    delete m;
    
    return 0;
}
Plot::Plot(){}
Plot::~Plot(){}

void Plot::run(){
    
    
    std::string dir = "histograms/11302012/";
    p = new PlottingTools(dir);
    p->AtlasStyle();
    
    html = new HtmlConfig("HtmlConfig.txt", dir);
    
    setupCuts();
    setupColor();
    
    setupFiles();
    
    readFiles();
    
    makePlots();
    
    return;
}
void Plot::makePlots(){
    
    
    
    for(unsigned i = 0; i < _files.size(); ++i){
        //checkReweight(_files[i]);
    }
        
    checkSigBkg();

    return;
}



void Plot::checkReweight(std::string n){
    
      DrawTwoHistOverlay(_hist[n]["h_signal_TrimmedJet_M_no_rw"], _hist[n]["h_signal_TrimmedJet_M_rw"], true, true, false, false, 0, -1, "before reweight", "after reweight", 0.7, 0.7, 0.9, 0.9, (std::string)("histograms/11262012/checkReweight_"+n+"_signal_TrimmedJet_M.png"), "", "fraction", 0, -10, false, false, "", false);   
      DrawTwoHistOverlay(_hist[n]["h_signal_TrimmedJet_Pt_no_rw"], _hist[n]["h_signal_TrimmedJet_Pt_rw"], true, true, false, false, 0, -1, "before reweight", "after reweight", 0.7, 0.7, 0.9, 0.9, (std::string)("histograms/11262012/checkReweight_"+n+"_signal_TrimmedJet_Pt.png"), "", "fraction", 0, -10, false, false, "", false);
      DrawTwoHistOverlay(_hist[n]["h_signal_TrimmedJet_d12_no_rw"], _hist[n]["h_signal_TrimmedJet_d12_rw"], true, true, false, false, 0, -1, "before reweight", "after reweight", 0.7, 0.7, 0.9, 0.9, (std::string)("histograms/11262012/checkReweight_"+n+"_signal_TrimmedJet_d12.png"), "", "fraction", 0, -10, false, false, "", false);
      DrawTwoHistOverlay(_hist[n]["h_signal_TrimmedJet_Tau1_no_rw"], _hist[n]["h_signal_TrimmedJet_Tau1_rw"], true, true, false, false, 0, -1, "before reweight", "after reweight", 0.7, 0.7, 0.9, 0.9, (std::string)("histograms/11262012/checkReweight_"+n+"_signal_TrimmedJet_Tau1.png"), "", "fraction", 0, -10, false, false, "", false);

      DrawTwoHistOverlay(_hist[n]["h_signal_FatJet_M_no_rw"], _hist[n]["h_signal_FatJet_M_rw"], true, true, false, false, 0, -1, "before reweight", "after reweight", 0.7, 0.7, 0.9, 0.9, (std::string)("histograms/11262012/checkReweight_"+n+"_signal_FatJet_M.png"), "", "fraction", 0, -10, false, false, "", false);
      DrawTwoHistOverlay(_hist[n]["h_signal_FatJet_Pt_no_rw"], _hist[n]["h_signal_FatJet_Pt_rw"], true, true, false, false, 0, -1, "before reweight", "after reweight", 0.7, 0.7, 0.9, 0.9, (std::string)("histograms/11262012/checkReweight_"+n+"_signal_FatJet_Pt.png"), "", "fraction", 0, -10, false, false, "", false);
      DrawTwoHistOverlay(_hist[n]["h_signal_FatJet_d12_no_rw"], _hist[n]["h_signal_FatJet_d12_rw"], true, true, false, false, 0, -1, "before reweight", "after reweight", 0.7, 0.7, 0.9, 0.9, (std::string)("histograms/11262012/checkReweight_"+n+"_signal_FatJet_d12.png"), "", "fraction", 0, -10, false, false, "", false);
      DrawTwoHistOverlay(_hist[n]["h_signal_FatJet_Tau1_no_rw"], _hist[n]["h_signal_FatJet_Tau1_rw"], true, true, false, false, 0, -1, "before reweight", "after reweight", 0.7, 0.7, 0.9, 0.9, (std::string)("histograms/11262012/checkReweight_"+n+"_signal_FatJet_Tau1.png"), "", "fraction", 0, -10, false, false, "", false);

      DrawTwoHistOverlay(_hist[n]["h_background_TrimmedJet_M_no_rw"], _hist[n]["h_background_TrimmedJet_M_rw"], true, true, false, false, 0, -1, "before reweight", "after reweight", 0.7, 0.7, 0.9, 0.9, (std::string)("histograms/11262012/checkReweight_"+n+"_background_TrimmedJet_M.png"), "", "fraction", 0, -10, false, false, "", false);
      DrawTwoHistOverlay(_hist[n]["h_background_TrimmedJet_Pt_no_rw"], _hist[n]["h_background_TrimmedJet_Pt_rw"], true, true, false, false, 0, -1, "before reweight", "after reweight", 0.7, 0.7, 0.9, 0.9, (std::string)("histograms/11262012/checkReweight_"+n+"_background_TrimmedJet_Pt.png"), "", "fraction", 0, -10, false, false, "", false);
      DrawTwoHistOverlay(_hist[n]["h_background_TrimmedJet_d12_no_rw"], _hist[n]["h_background_TrimmedJet_d12_rw"], true, true, false, false, 0, -1, "before reweight", "after reweight", 0.7, 0.7, 0.9, 0.9, (std::string)("histograms/11262012/checkReweight_"+n+"_background_TrimmedJet_d12.png"), "", "fraction", 0, -10, false, false, "", false);
      DrawTwoHistOverlay(_hist[n]["h_background_TrimmedJet_Tau1_no_rw"], _hist[n]["h_background_TrimmedJet_Tau1_rw"], true, true, false, false, 0, -1, "before reweight", "after reweight", 0.7, 0.7, 0.9, 0.9, (std::string)("histograms/11262012/checkReweight_"+n+"_background_TrimmedJet_Tau1.png"), "", "fraction", 0, -10, false, false, "", false);


      return;
}



void Plot::checkSigBkg(){

	DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_M_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_M_rw"],_hist["WplusJetsAll"]["h_background_TrimmedJet_M_no_rw"], _hist["WplusJetsAll"]["h_background_TrimmedJet_M_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11302012/checkSigBkg_Wjets_TrimmedJet_M.png", "", "fraction", 0, -10, false, "");
        DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_d12_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_d12_rw"],_hist["WplusJetsAll"]["h_background_TrimmedJet_d12_no_rw"], _hist["WplusJetsAll"]["h_background_TrimmedJet_d12_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11302012/checkSigBkg_Wjets_TrimmedJet_d12.png", "", "fraction", 0, -10, false, "");
        DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_d23_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_d23_rw"],_hist["WplusJetsAll"]["h_background_TrimmedJet_d23_no_rw"], _hist["WplusJetsAll"]["h_background_TrimmedJet_d23_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11302012/checkSigBkg_Wjets_TrimmedJet_d23.png", "", "fraction", 0, -10, false, "");
        DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_d34_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_d34_rw"],_hist["WplusJetsAll"]["h_background_TrimmedJet_d34_no_rw"], _hist["WplusJetsAll"]["h_background_TrimmedJet_d34_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11302012/checkSigBkg_Wjets_TrimmedJet_d34.png", "", "fraction", 0, -10, false, "");
        DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_Tau1_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_Tau1_rw"],_hist["WplusJetsAll"]["h_background_TrimmedJet_Tau1_no_rw"], _hist["WplusJetsAll"]["h_background_TrimmedJet_Tau1_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11302012/checkSigBkg_Wjets_TrimmedJet_Tau1.png", "", "fraction", 0, -10, false, "");
        DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_Tau2_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_Tau2_rw"],_hist["WplusJetsAll"]["h_background_TrimmedJet_Tau2_no_rw"], _hist["WplusJetsAll"]["h_background_TrimmedJet_Tau2_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11302012/checkSigBkg_Wjets_TrimmedJet_Tau2.png", "", "fraction", 0, -10, false, "");
        DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_Tau3_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_Tau3_rw"],_hist["WplusJetsAll"]["h_background_TrimmedJet_Tau3_no_rw"], _hist["WplusJetsAll"]["h_background_TrimmedJet_Tau3_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11302012/checkSigBkg_Wjets_TrimmedJet_Tau3.png", "", "fraction", 0, -10, false, "");
        DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_Tau3Tau1_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_Tau3Tau1_rw"],_hist["WplusJetsAll"]["h_background_TrimmedJet_Tau3Tau1_no_rw"], _hist["WplusJetsAll"]["h_background_TrimmedJet_Tau3Tau1_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11302012/checkSigBkg_Wjets_TrimmedJet_Tau3Tau1.png", "", "fraction", 0, -10, false, "");
        DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_Tau2Tau1_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_Tau2Tau1_rw"],_hist["WplusJetsAll"]["h_background_TrimmedJet_Tau2Tau1_no_rw"], _hist["WplusJetsAll"]["h_background_TrimmedJet_Tau2Tau1_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11302012/checkSigBkg_Wjets_TrimmedJet_Tau2Tau1.png", "", "fraction", 0, -10, false, "");

        DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_M_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_M_rw"],_hist["J5"]["h_background_TrimmedJet_M_no_rw"], _hist["J5"]["h_background_TrimmedJet_M_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11302012/checkSigBkg_QCD_TrimmedJet_M.png", "", "fraction", 0, -10, false, "");
        DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_d12_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_d12_rw"],_hist["J5"]["h_background_TrimmedJet_d12_no_rw"], _hist["J5"]["h_background_TrimmedJet_d12_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11302012/checkSigBkg_QCD_TrimmedJet_d12.png", "", "fraction", 0, -10, false, "");
        DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_d23_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_d23_rw"],_hist["J5"]["h_background_TrimmedJet_d23_no_rw"], _hist["J5"]["h_background_TrimmedJet_d23_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11302012/checkSigBkg_QCD_TrimmedJet_d23.png", "", "fraction", 0, -10, false, "");
        DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_d34_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_d34_rw"],_hist["J5"]["h_background_TrimmedJet_d34_no_rw"], _hist["J5"]["h_background_TrimmedJet_d34_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11302012/checkSigBkg_QCD_TrimmedJet_d34.png", "", "fraction", 0, -10, false, "");
        DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_Tau1_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_Tau1_rw"],_hist["J5"]["h_background_TrimmedJet_Tau1_no_rw"], _hist["J5"]["h_background_TrimmedJet_Tau1_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11302012/checkSigBkg_QCD_TrimmedJet_Tau1.png", "", "fraction", 0, -10, false, "");
        DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_Tau2_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_Tau2_rw"],_hist["J5"]["h_background_TrimmedJet_Tau2_no_rw"], _hist["J5"]["h_background_TrimmedJet_Tau2_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11302012/checkSigBkg_QCD_TrimmedJet_Tau2.png", "", "fraction", 0, -10, false, "");
        DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_Tau3_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_Tau3_rw"],_hist["J5"]["h_background_TrimmedJet_Tau3_no_rw"], _hist["J5"]["h_background_TrimmedJet_Tau3_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11302012/checkSigBkg_QCD_TrimmedJet_Tau3.png", "", "fraction", 0, -10, false, "");
        DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_Tau3Tau1_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_Tau3Tau1_rw"],_hist["J5"]["h_background_TrimmedJet_Tau3Tau1_no_rw"], _hist["J5"]["h_background_TrimmedJet_Tau3Tau1_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11302012/checkSigBkg_QCD_TrimmedJet_Tau3Tau1.png", "", "fraction", 0, -10, false, "");
        DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_Tau2Tau1_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_Tau2Tau1_rw"],_hist["J5"]["h_background_TrimmedJet_Tau2Tau1_no_rw"], _hist["J5"]["h_background_TrimmedJet_Tau2Tau1_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11302012/checkSigBkg_QCD_TrimmedJet_Tau2Tau1.png", "", "fraction", 0, -10, false, "");



        DrawSixHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_M_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_M_rw"],_hist["WplusJetsAll"]["h_background_TrimmedJet_M_no_rw"], _hist["WplusJetsAll"]["h_background_TrimmedJet_M_rw"], _hist["J5"]["h_background_TrimmedJet_M_no_rw"], _hist["J5"]["h_background_TrimmedJet_M_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg W+jets not-reweighted", "Bkg W+jets reweighted","Bkg QCD not-reweighted", "Bkg QCD reweighted", 0.7, 0.65, 0.95, 0.9, "histograms/11302012/checkSigBkg_Wjets_QCD_TrimmedJet_M.png", "", "fraction");
        DrawSixHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_d12_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_d12_rw"],_hist["WplusJetsAll"]["h_background_TrimmedJet_d12_no_rw"], _hist["WplusJetsAll"]["h_background_TrimmedJet_d12_rw"], _hist["J5"]["h_background_TrimmedJet_d12_no_rw"], _hist["J5"]["h_background_TrimmedJet_d12_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg W+jets not-reweighted", "Bkg W+jets reweighted","Bkg QCD not-reweighted", "Bkg QCD reweighted", 0.7, 0.65, 0.95, 0.9, "histograms/11302012/checkSigBkg_Wjets_QCD_TrimmedJet_d12.png", "", "fraction");
        DrawSixHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_d23_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_d23_rw"],_hist["WplusJetsAll"]["h_background_TrimmedJet_d23_no_rw"], _hist["WplusJetsAll"]["h_background_TrimmedJet_d23_rw"], _hist["J5"]["h_background_TrimmedJet_d23_no_rw"], _hist["J5"]["h_background_TrimmedJet_d23_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg W+jets not-reweighted", "Bkg W+jets reweighted","Bkg QCD not-reweighted", "Bkg QCD reweighted", 0.7, 0.65, 0.95, 0.9, "histograms/11302012/checkSigBkg_Wjets_QCD_TrimmedJet_d23.png", "", "fraction");
        DrawSixHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_d34_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_d34_rw"],_hist["WplusJetsAll"]["h_background_TrimmedJet_d34_no_rw"], _hist["WplusJetsAll"]["h_background_TrimmedJet_d34_rw"], _hist["J5"]["h_background_TrimmedJet_d34_no_rw"], _hist["J5"]["h_background_TrimmedJet_d34_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg W+jets not-reweighted", "Bkg W+jets reweighted","Bkg QCD not-reweighted", "Bkg QCD reweighted", 0.7, 0.65, 0.95, 0.9, "histograms/11302012/checkSigBkg_Wjets_QCD_TrimmedJet_d34.png", "", "fraction");
        DrawSixHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_Tau1_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_Tau1_rw"],_hist["WplusJetsAll"]["h_background_TrimmedJet_Tau1_no_rw"], _hist["WplusJetsAll"]["h_background_TrimmedJet_Tau1_rw"], _hist["J5"]["h_background_TrimmedJet_Tau1_no_rw"], _hist["J5"]["h_background_TrimmedJet_Tau1_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg W+jets not-reweighted", "Bkg W+jets reweighted","Bkg QCD not-reweighted", "Bkg QCD reweighted", 0.7, 0.65, 0.95, 0.9, "histograms/11302012/checkSigBkg_Wjets_QCD_TrimmedJet_Tau1.png", "", "fraction");
        DrawSixHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_Tau2_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_Tau2_rw"],_hist["WplusJetsAll"]["h_background_TrimmedJet_Tau2_no_rw"], _hist["WplusJetsAll"]["h_background_TrimmedJet_Tau2_rw"], _hist["J5"]["h_background_TrimmedJet_Tau2_no_rw"], _hist["J5"]["h_background_TrimmedJet_Tau2_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg W+jets not-reweighted", "Bkg W+jets reweighted","Bkg QCD not-reweighted", "Bkg QCD reweighted", 0.7, 0.65, 0.95, 0.9, "histograms/11302012/checkSigBkg_Wjets_QCD_TrimmedJet_Tau2.png", "", "fraction");
        DrawSixHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_Tau3_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_Tau3_rw"],_hist["WplusJetsAll"]["h_background_TrimmedJet_Tau3_no_rw"], _hist["WplusJetsAll"]["h_background_TrimmedJet_Tau3_rw"], _hist["J5"]["h_background_TrimmedJet_Tau3_no_rw"], _hist["J5"]["h_background_TrimmedJet_Tau3_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg W+jets not-reweighted", "Bkg W+jets reweighted","Bkg QCD not-reweighted", "Bkg QCD reweighted", 0.7, 0.65, 0.95, 0.9, "histograms/11302012/checkSigBkg_Wjets_QCD_TrimmedJet_Tau3.png", "", "fraction");
        DrawSixHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_Tau3Tau1_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_Tau3Tau1_rw"],_hist["WplusJetsAll"]["h_background_TrimmedJet_Tau3Tau1_no_rw"], _hist["WplusJetsAll"]["h_background_TrimmedJet_Tau3Tau1_rw"], _hist["J5"]["h_background_TrimmedJet_Tau3Tau1_no_rw"], _hist["J5"]["h_background_TrimmedJet_Tau3Tau1_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg W+jets not-reweighted", "Bkg W+jets reweighted","Bkg QCD not-reweighted", "Bkg QCD reweighted", 0.7, 0.65, 0.95, 0.9, "histograms/11302012/checkSigBkg_Wjets_QCD_TrimmedJet_Tau3Tau1.png", "", "fraction");
        DrawSixHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_Tau2Tau1_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_Tau2Tau1_rw"],_hist["WplusJetsAll"]["h_background_TrimmedJet_Tau2Tau1_no_rw"], _hist["WplusJetsAll"]["h_background_TrimmedJet_Tau2Tau1_rw"], _hist["J5"]["h_background_TrimmedJet_Tau2Tau1_no_rw"], _hist["J5"]["h_background_TrimmedJet_Tau2Tau1_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg W+jets not-reweighted", "Bkg W+jets reweighted","Bkg QCD not-reweighted", "Bkg QCD reweighted", 0.7, 0.65, 0.95, 0.9, "histograms/11302012/checkSigBkg_Wjets_QCD_TrimmedJet_Tau2Tau1.png", "", "fraction");


      //DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_M_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_M_rw"],_hist["Tt"]["h_background_tauhad_TrimmedJet_M_no_rw"], _hist["Tt"]["h_background_tauhad_TrimmedJet_M_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11262012/checkSigBkg_TrimmedJet_M.png", "", "fraction", 0, -10, false, "");
      //DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_Pt_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_Pt_rw"],_hist["Tt"]["h_background_tauhad_TrimmedJet_Pt_no_rw"], _hist["Tt"]["h_background_tauhad_TrimmedJet_Pt_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11262012/checkSigBkg_TrimmedJet_Pt.png", "", "fraction", 0, -10, false, "");
      //DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_d12_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_d12_rw"],_hist["Tt"]["h_background_tauhad_TrimmedJet_d12_no_rw"], _hist["Tt"]["h_background_tauhad_TrimmedJet_d12_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11262012/checkSigBkg_TrimmedJet_d12.png", "", "fraction", 0, -10, false, "");
      //DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_Tau1_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_Tau1_rw"],_hist["Tt"]["h_background_tauhad_TrimmedJet_Tau1_no_rw"], _hist["Tt"]["h_background_tauhad_TrimmedJet_Tau1_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11262012/checkSigBkg_TrimmedJet_Tau1.png", "", "fraction", 0, -10, false, "");

      //DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_Tau3_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_Tau3_rw"],_hist["Tt"]["h_background_tauhad_TrimmedJet_Tau3_no_rw"], _hist["Tt"]["h_background_tauhad_TrimmedJet_Tau3_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11262012/checkSigBkg_TrimmedJet_Tau3.png", "", "fraction", 0, -10, false, "");
      //DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_Tau3Tau1_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_Tau3Tau1_rw"],_hist["Tt"]["h_background_tauhad_TrimmedJet_Tau3Tau1_no_rw"], _hist["Tt"]["h_background_tauhad_TrimmedJet_Tau3Tau1_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11262012/checkSigBkg_TrimmedJet_Tau3Tau1.png", "", "fraction", 0, -10, false, "");
      //DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_d12d34_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_d12d34_rw"],_hist["Tt"]["h_background_tauhad_TrimmedJet_d12d34_no_rw"], _hist["Tt"]["h_background_tauhad_TrimmedJet_d12d34_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11262012/checkSigBkg_TrimmedJet_d12d34.png", "", "fraction", 0, -10, false, "");
      //DrawFourHistOverlay(_hist["TtAll"]["h_signal_TrimmedJet_Tau3M_no_rw"], _hist["TtAll"]["h_signal_TrimmedJet_Tau3M_rw"],_hist["Tt"]["h_background_tauhad_TrimmedJet_Tau3M_no_rw"], _hist["Tt"]["h_background_tauhad_TrimmedJet_Tau3M_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11262012/checkSigBkg_TrimmedJet_Tau3M.png", "", "fraction", 0, -10, false, "");

      //DrawFourHistOverlay(_hist["TtAll"]["h_signal_RelDiff_M_no_rw"], _hist["TtAll"]["h_signal_RelDiff_M_rw"],_hist["Tt"]["h_background_tauhad_RelDiff_M_no_rw"], _hist["Tt"]["h_background_tauhad_RelDiff_M_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11262012/checkSigBkg_RelDiff_M.png", "", "fraction", 0, -10, false, "");
      //DrawFourHistOverlay(_hist["TtAll"]["h_signal_RelDiff_Tau3_no_rw"], _hist["TtAll"]["h_signal_RelDiff_Tau3_rw"],_hist["Tt"]["h_background_tauhad_RelDiff_Tau3_no_rw"], _hist["Tt"]["h_background_tauhad_RelDiff_Tau3_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11262012/checkSigBkg_RelDiff_Tau3.png", "", "fraction", 0, -10, false, "");


      //DrawFourHistOverlay(_hist["TtAll"]["h_signal_FatJet_M_no_rw"], _hist["TtAll"]["h_signal_FatJet_M_rw"],_hist["Tt"]["h_background_tauhad_FatJet_M_no_rw"], _hist["Tt"]["h_background_tauhad_FatJet_M_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11262012/checkSigBkg_FatJet_M.png", "", "fraction", 0, -10, false, "");
      //DrawFourHistOverlay(_hist["TtAll"]["h_signal_FatJet_Pt_no_rw"], _hist["TtAll"]["h_signal_FatJet_Pt_rw"],_hist["Tt"]["h_background_tauhad_FatJet_Pt_no_rw"], _hist["Tt"]["h_background_tauhad_FatJet_Pt_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11262012/checkSigBkg_FatJet_Pt.png", "", "fraction", 0, -10, false, "");
      //DrawFourHistOverlay(_hist["TtAll"]["h_signal_FatJet_d12_no_rw"], _hist["TtAll"]["h_signal_FatJet_d12_rw"],_hist["Tt"]["h_background_tauhad_FatJet_d12_no_rw"], _hist["Tt"]["h_background_tauhad_FatJet_d12_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11262012/checkSigBkg_FatJet_d12.png", "", "fraction", 0, -10, false, "");
      //DrawFourHistOverlay(_hist["TtAll"]["h_signal_FatJet_Tau1_no_rw"], _hist["TtAll"]["h_signal_FatJet_Tau1_rw"],_hist["Tt"]["h_background_tauhad_FatJet_Tau1_no_rw"], _hist["Tt"]["h_background_tauhad_FatJet_Tau1_rw"], true, true, false, 0, -1, "Sig not-reweighted", "Sig reweighted", "Bkg not-reweighted", "Bkg reweighted", 0.7, 0.7, 0.9, 0.9, "histograms/11262012/checkSigBkg_FatJet_Tau1.png", "", "fraction", 0, -10, false, "");



      //DrawTwoHistOverlay(_hist["Tt"]["SF_FatJet_Pt_background_tauhad_hist"], _hist["TtAll"]["SF_FatJet_Pt_signal_hist"], true, true, false, false, 0, -1, "background", "signal", 0.7, 0.7, 0.9, 0.9, (std::string)("histograms/11262012/checkSigBkg_SF.png"), "fat jet p_{T} [GeV]", "weight", 0, -10, false, false, "", false);

      ////cross-check the difference between allhad sig and tt sig
      //DrawTwoHistOverlay(_hist["AllHad"]["h_signal_FatJet_d12_no_rw"], _hist["Tt"]["h_signal_FatJet_d12_no_rw"], true, true, false, false, 0, -1, "allhad before reweight", "tt before reweight", 0.7, 0.7, 0.9, 0.9, (std::string)("histograms/11262012/check_signal_FatJet_d12_norw.png"), "", "fraction", 0, -10, false, false, "", false);
      //DrawTwoHistOverlay(_hist["AllHad"]["h_signal_FatJet_d12_rw"], _hist["Tt"]["h_signal_FatJet_d12_rw"], true, true, false, false, 0, -1, "allhad after reweight", "tt after reweight", 0.7, 0.7, 0.9, 0.9, (std::string)("histograms/11262012/check_signal_FatJet_d12_rw.png"), "", "fraction", 0, -10, false, false, "", false);
      //DrawTwoHistOverlay(_hist["AllHad"]["h_signal_FatJet_M_no_rw"], _hist["Tt"]["h_signal_FatJet_M_no_rw"], true, true, false, false, 0, -1, "allhad before reweight", "tt before reweight", 0.7, 0.7, 0.9, 0.9, (std::string)("histograms/11262012/check_signal_FatJet_M_norw.png"), "", "fraction", 0, -10, false, false, "", false);
      //DrawTwoHistOverlay(_hist["AllHad"]["h_signal_FatJet_M_rw"], _hist["Tt"]["h_signal_FatJet_M_rw"], true, true, false, false, 0, -1, "allhad after reweight", "tt after reweight", 0.7, 0.7, 0.9, 0.9, (std::string)("histograms/11262012/check_signal_FatJet_M_rw.png"), "", "fraction", 0, -10, false, false, "", false);
      //DrawTwoHistOverlay(_hist["AllHad"]["h_signal_FatJet_Pt_no_rw"], _hist["Tt"]["h_signal_FatJet_Pt_no_rw"], true, true, false, false, 0, -1, "allhad before reweight", "tt before reweight", 0.7, 0.7, 0.9, 0.9, (std::string)("histograms/11262012/check_signal_FatJet_Pt_norw.png"), "", "fraction", 0, -10, false, false, "", false);
      //DrawTwoHistOverlay(_hist["AllHad"]["h_signal_FatJet_Pt_rw"], _hist["Tt"]["h_signal_FatJet_Pt_rw"], true, true, false, false, 0, -1, "allhad after reweight", "tt after reweight", 0.7, 0.7, 0.9, 0.9, (std::string)("histograms/11262012/check_signal_FatJet_Pt_rw.png"), "", "fraction", 0, -10, false, false, "", false);
      //DrawTwoHistOverlay(_hist["AllHad"]["h_signal_FatJet_Tau1_no_rw"], _hist["Tt"]["h_signal_FatJet_Tau1_no_rw"], true, true, false, false, 0, -1, "allhad before reweight", "tt before reweight", 0.7, 0.7, 0.9, 0.9, (std::string)("histograms/11262012/check_signal_FatJet_Tau1_norw.png"), "", "fraction", 0, -10, false, false, "", false);
      //DrawTwoHistOverlay(_hist["AllHad"]["h_signal_FatJet_Tau1_rw"], _hist["Tt"]["h_signal_FatJet_Tau1_rw"], true, true, false, false, 0, -1, "allhad after reweight", "tt after reweight", 0.7, 0.7, 0.9, 0.9, (std::string)("histograms/11262012/check_signal_FatJet_Tau1_rw.png"), "", "fraction", 0, -10, false, false, "", false);
      return; 
}


void Plot::setupColor(){
    _color.clear();
    
    _color.push_back(kRed);
    _color.push_back(kBlue);
    _color.push_back(kMagenta);
    _color.push_back(kCyan+3);
    _color.push_back(kGreen-3);
    _color.push_back(kYellow+3);
    _color.push_back(kRed+4);
    _color.push_back(kBlue-3);
    _color.push_back(kMagenta+4);
    _color.push_back(kCyan-6);
    _color.push_back(kGreen+3);
    _color.push_back(kYellow-6);
    _color.push_back(kRed-7);
    _color.push_back(kBlue-6);
    _color.push_back(kMagenta-7);
    _color.push_back(kCyan-10);
    _color.push_back(kGreen-6);
    _color.push_back(kRed-10);
    _color.push_back(kBlue-8);
    _color.push_back(kMagenta-10);
    
    
    
}
void Plot::setupCuts(){
    _cuts.clear();
    
    _cuts.push_back("EventDQ");
    _cuts.push_back("All");
    
    
    return;
}
void Plot::readFiles(){
    
    // loop over files, open, read & store histograms
    for(unsigned i = 0; i < _files.size(); ++i){
        std::map<std::string,TH1F*> htmp;
        TFile* f = TFile::Open(("../histograms/11302012_check/"+_files[i]+".root").c_str(), "READ");
        TDirectory *dir = gDirectory;
        TKey *key;
        TIter nextkey(dir->GetListOfKeys());
        
        while(key=(TKey*)nextkey()){
            TObject *obj = key->ReadObj();
            if(obj->IsA()->InheritsFrom("TH1F")){
                TH1F *hist_original = (TH1F*)obj;
                string histname = hist_original->GetName();
                std::cout<<"histname: "<<histname<<std::endl;
                hist_original->Sumw2();
                // overflow & underflow

                // why set over/underflow bin error like this???
                /////double ub = hist_original->GetBinContent(0);
                /////hist_original->AddBinContent(1,ub);
                /////hist_original->SetBinError(1,sqrt(hist_original->GetBinContent(1)));
                /////
                /////double ob = hist_original->GetBinContent(hist_original->GetNbinsX()+1);
                /////hist_original->AddBinContent(hist_original->GetNbinsX(),ob);
                /////hist_original->SetBinError(hist_original->GetNbinsX(), sqrt(hist_original->GetBinContent(hist_original->GetNbinsX())));
                /////if(hist_original->Integral() != 0)
                /////    hist_original->Scale(1./hist_original->Integral()); // always normalize to 1
                /////hist_original->GetYaxis()->SetRangeUser(0.,hist_original->GetMaximum()*1.5);
                
                std::string xa = hist_original->GetXaxis()->GetTitle();
                std::string ya = hist_original->GetYaxis()->GetTitle();
                
                if(std::strstr(xa.c_str(), "GeV") != NULL)
                    ya = ya+" GeV";
                hist_original->GetYaxis()->SetTitle(ya.c_str());
                
                htmp[histname] = hist_original;
            }
            
        }
        _hist[_files[i]] = htmp;
    }
    
    // add up all AllHad and Tt samples for signal
    if(_hist["AllHad"].size() > 0){
    	std::map<std::string, TH1F*>::iterator fIter = _hist["AllHad"].begin();
    	std::map<std::string, TH1F*>::iterator lIter = _hist["AllHad"].end();
        
        std::map<std::string,TH1F*> htmp;
        for(;fIter!=lIter;++fIter){
            TH1F* hn = (TH1F*)fIter->second->Clone();
            std::string n = fIter->first;
                        
            if(_hist["Tt"].size() > 0)
  	      if(_hist["Tt"][n]->Integral() > 0)	
                 hn->Add(_hist["Tt"][n]);
   
            htmp[n] = hn;
                
        }
        _hist["TtAll"] = htmp;
    }

    if(_hist["WenuNp0"].size() > 0){
        std::map<std::string, TH1F*>::iterator fIter = _hist["WenuNp0"].begin();
        std::map<std::string, TH1F*>::iterator lIter = _hist["WenuNp0"].end();

        std::map<std::string,TH1F*> htmp;
        for(;fIter!=lIter;++fIter){
            TH1F* hn = (TH1F*)fIter->second->Clone();
            std::string n = fIter->first;

            if(_hist["WenuNp1"].size() > 0)
              if(_hist["WenuNp1"][n]->Integral() > 0)
            		hn->Add(_hist["WenuNp1"][n]);
            if(_hist["WenuNp2"].size() > 0)
              if(_hist["WenuNp2"][n]->Integral() > 0)
	    		hn->Add(_hist["WenuNp2"][n]);
            if(_hist["WenuNp3"].size() > 0)
              if(_hist["WenuNp3"][n]->Integral() > 0)
	    		hn->Add(_hist["WenuNp3"][n]);
            if(_hist["WenuNp4"].size() > 0)
              if(_hist["WenuNp4"][n]->Integral() > 0)
            		hn->Add(_hist["WenuNp4"][n]);
            if(_hist["WenuNp5"].size() > 0)
              if(_hist["WenuNp5"][n]->Integral() > 0)
	    		hn->Add(_hist["WenuNp5"][n]);
            if(_hist["WmunuNp0"].size() > 0)
              if(_hist["WmunuNp0"][n]->Integral() > 0)
	    		hn->Add(_hist["WmunuNp0"][n]); 
            if(_hist["WmunuNp1"].size() > 0)
              if(_hist["WmunuNp1"][n]->Integral() > 0)
            		hn->Add(_hist["WmunuNp1"][n]);
            if(_hist["WmunuNp2"].size() > 0)
              if(_hist["WmunuNp2"][n]->Integral() > 0)
            		hn->Add(_hist["WmunuNp2"][n]);
            if(_hist["WmunuNp3"].size() > 0)
              if(_hist["WmunuNp3"][n]->Integral() > 0)
            		hn->Add(_hist["WmunuNp3"][n]);
            if(_hist["WmunuNp4"].size() > 0)
              if(_hist["WmunuNp4"][n]->Integral() > 0)
            		hn->Add(_hist["WmunuNp4"][n]);
            if(_hist["WmunuNp5"].size() > 0)
              if(_hist["WmunuNp5"][n]->Integral() > 0)
            		hn->Add(_hist["WmunuNp5"][n]);
            if(_hist["WtaunuNp0"].size() > 0)
              if(_hist["WtaunuNp0"][n]->Integral() > 0)
	    		hn->Add(_hist["WtaunuNp0"][n]);
            if(_hist["WtaunuNp1"].size() > 0)
              if(_hist["WtaunuNp1"][n]->Integral() > 0)
            		hn->Add(_hist["WtaunuNp1"][n]);
            if(_hist["WtaunuNp2"].size() > 0)
              if(_hist["WtaunuNp2"][n]->Integral() > 0)
          	        hn->Add(_hist["WtaunuNp2"][n]);
            if(_hist["WtaunuNp3"].size() > 0)
              if(_hist["WtaunuNp3"][n]->Integral() > 0)
            		hn->Add(_hist["WtaunuNp3"][n]);
            if(_hist["WtaunuNp4"].size() > 0)
              if(_hist["WtaunuNp4"][n]->Integral() > 0)
            		hn->Add(_hist["WtaunuNp4"][n]);
            if(_hist["WtaunuNp5"].size() > 0)
              if(_hist["WtaunuNp5"][n]->Integral() > 0)
            		hn->Add(_hist["WtaunuNp5"][n]);

            htmp[n] = hn;

        }
        _hist["WplusJetsAll"] = htmp;
    }

    if(_hist["J4"].size() > 0){
        std::map<std::string, TH1F*>::iterator fIter = _hist["J4"].begin();
        std::map<std::string, TH1F*>::iterator lIter = _hist["J4"].end();

        std::map<std::string,TH1F*> htmp;
        for(;fIter!=lIter;++fIter){
            TH1F* hn = (TH1F*)fIter->second->Clone();
            std::string n = fIter->first;

            if(_hist["J5"].size() > 0)
                if(_hist["J5"][n]->Integral() > 0)
                        hn->Add(_hist["J5"][n]);
            if(_hist["J6"].size() > 0)
                if(_hist["J6"][n]->Integral() > 0)
	    		hn->Add(_hist["J6"][n]);	
            if(_hist["J7"].size() > 0)
                if(_hist["J7"][n]->Integral() > 0)
	    		hn->Add(_hist["J7"][n]);
            if(_hist["J8"].size() > 0)
                if(_hist["J8"][n]->Integral() > 0)
            		hn->Add(_hist["J8"][n]);
            htmp[n] = hn;

        }
        _hist["QCDAll"] = htmp;
    }
    
    
    return;
}
void Plot::setupFiles(){
    
    _files.push_back("AllHad");
    _files.push_back("Tt");
    _files.push_back("WenuNp0");
    _files.push_back("WenuNp1");
    _files.push_back("WenuNp2");
    _files.push_back("WenuNp3");
    _files.push_back("WenuNp4");
    _files.push_back("WenuNp5");
    _files.push_back("WmunuNp0");
    _files.push_back("WmunuNp1");
    _files.push_back("WmunuNp2");
    _files.push_back("WmunuNp3");
    _files.push_back("WmunuNp4");
    _files.push_back("WmunuNp5");
    _files.push_back("WtaunuNp0");
    _files.push_back("WtaunuNp1");
    _files.push_back("WtaunuNp2");
    _files.push_back("WtaunuNp3");
    _files.push_back("WtaunuNp4");
    _files.push_back("WtaunuNp5");
    _files.push_back("J4");
    _files.push_back("J5");
    _files.push_back("J6");
    _files.push_back("J7");
    _files.push_back("J8"); 
    
    return;
}

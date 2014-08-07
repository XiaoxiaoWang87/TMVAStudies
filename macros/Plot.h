#ifndef PLOT_H
#define PLOT_H

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

using namespace std;



class Plot{
    
public:
    Plot();
    ~Plot();
    void run();
    
    
private:
    PlottingTools* p;
    HtmlConfig* html;
    std::vector<std::string> _cuts;
    std::vector<std::string> _files;
    std::vector<Color_t> _color;
        
    void setupCuts();
    void setupFiles();
    void setupColor();
    void readFiles();
    void makePlots();
    void checkReweight(std::string n);
    void checkSigBkg();    

    std::map<std::string, std::map<std::string,TH1F*> > _hist;
    
    
};



#endif


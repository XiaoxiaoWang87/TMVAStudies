import numpy as np
import array

import ROOT
from ROOT import *

import AtlasStyle
import PlottingUtls as Plt


class Hist:

    def __init__(self, name):

        # after common preselection
        self.h_bdt = TH1F(name+"_bdt", name+"_bdt", 20, -0.35, 0.45) 
        self.h_scan_bdt = TH1F(name+"_scan_bdt", name+"_scan_bdt", 20,  -0.35, 0.45)

        # add additional cuts such as mt
        self.h_bdt_add_cut = TH1F(name+"_bdt_add_cut", name+"_bdt_add_cut", 20, -0.35, 0.45)
        self.h_scan_bdt_add_cut = TH1F(name+"_scan_bdt_add_cut", name+"_scan_bdt_add_cut", 20,  -0.35, 0.45)

        # add mt in the training
        self.h_bdt_w_mt = TH1F(name+"_bdt_w_mt", name+"_bdt_w_mt", 20, -0.35, 0.45)
        self.h_scan_bdt_w_mt = TH1F(name+"_scan_bdt_w_mt", name+"_scan_bdt_w_mt", 20,  -0.35, 0.45)


        # using a different set of hists for plotting
        self.h_bdt_plt = TH1F(name+"_bdt_plt", name+"_bdt_plt", 30, -0.35, 0.45)
        self.h_bdt_add_cut_plt = TH1F(name+"_bdt_add_cut_plt", name+"_bdt_add_cut_plt", 30, -0.35, 0.45)


        # scan over different cut values of mt
        self.h_bdt_add_cut_group = {}
        self.h_scan_bdt_add_cut_group = {}
        for i in range(3,10):
            self.h_bdt_add_cut_group[str(i)] = TH1F(name+"_bdt_add_cut_"+str(i), name+"_bdt_add_cut_"+str(i), 20, -0.35, 0.45)
            self.h_scan_bdt_add_cut_group[str(i)] = TH1F(name+"_scan_bdt_add_cut_"+str(i), name+"_scan_bdt_add_cut_"+str(i), 20,  -0.35, 0.45)

        # sanity check of distributions
        self.h_mt_add_bdt_high = TH1F(name+"_mt_add_bdt_high", name+"_mt_add_bdt_high", 30, 60, 300)
        self.h_mt_add_bdt_med = TH1F(name+"_mt_add_bdt_med", name+"_mt_add_bdt_med", 30, 60, 300)
        self.h_mt_add_bdt_low = TH1F(name+"_mt_add_bdt_low", name+"_mt_add_bdt_low", 30, 60, 300)

        #self.h_tauveto_add_bdt_high = TH1F(name+"_tauveto_add_bdt_high", name+"_tauveto_add_bdt_high", 2, 0, 2)
        #self.h_tauveto_add_bdt_med = TH1F(name+"_tauveto_add_bdt_med", name+"_tauveto_add_bdt_med", 2, 0, 2)
        #self.h_tauveto_add_bdt_low = TH1F(name+"_tauveto_add_bdt_low", name+"_tauveto_add_bdt_low", 2, 0, 2)

        #self.h_btag_add_bdt_high = TH1F(name+"_btag_add_bdt_high", name+"_btag_add_bdt_high", 2, 0, 2)
        #self.h_btag_add_bdt_med = TH1F(name+"_btag_add_bdt_med", name+"_btag_add_bdt_med", 2, 0, 2)
        #self.h_btag_add_bdt_low = TH1F(name+"_btag_add_bdt_low", name+"_btag_add_bdt_low", 2, 0, 2)
     
        # for neural net deep learning
        self.h_nn_train_w_mt = TH1F() 
        self.h_nn_validate_w_mt = TH1F() 
        self.h_nn_evaluate_w_mt = TH1F() 
        self.h_scan_nn_evaluate_w_mt = TH1F() 

        self.h_nn_train_wo_mt = TH1F() 
        self.h_nn_validate_wo_mt = TH1F()
        self.h_nn_evaluate_wo_mt = TH1F()
        self.h_nn_evaluate_wo_mt_add_cut = TH1F()
        self.h_scan_nn_evaluate_wo_mt_add_cut = TH1F()

        self.h_mt_evaluate_wo_mt = TH1F()

class Count:
    def __init__(self, name):
        self.minus3 = 0
        self.minus2 = 0
        self.all = 0
        self.no = 0
        self.all_raw = 0
        self.no_raw = 0

def Scan(h):
    h_scan = h.Clone()
    for i in range(1,h.GetNbinsX()+1):
        h_scan.SetBinContent(i, h.Integral(i, h.GetNbinsX())*1.0 / h.Integral(1, h.GetNbinsX()) )
    return h_scan

def ScanAddCut(h, hc):
    h_scan = hc.Clone()
    for i in range(1,hc.GetNbinsX()+1):
        h_scan.SetBinContent(i, hc.Integral(i, hc.GetNbinsX())*1.0 / h.Integral(1, h.GetNbinsX()) )
    return h_scan

def ScanAddCutPrime(h_xsec, h, hc):
    h_scan = hc.Clone()
    print h.Integral(1, h.GetNbinsX()), h.Integral(1, h.GetNbinsX())/h_xsec, hc.Integral(1, hc.GetNbinsX())
    for i in range(1,hc.GetNbinsX()+1):
        h_scan.SetBinContent(i, hc.Integral(i, hc.GetNbinsX())*1.0 / h.Integral(1, h.GetNbinsX()) * h_xsec )
        print hc.Integral(i, hc.GetNbinsX()), hc.Integral(i, hc.GetNbinsX())*1.0 / h.Integral(1, h.GetNbinsX()) * h_xsec
    return h_scan



def main():

    xsec = {}
    xsec['T650_L1'] = 0.0139566
    xsec['T650_L50'] = 0.0139566
    xsec['T700_L1'] = 0.0081141
    xsec['T700_L50'] = 0.0081141
    xsec['T750_L1'] = 0.00480639
    xsec['T750_L50'] = 0.00480639
    xsec['T800_L1'] = 0.00289588
    xsec['T800_L50'] = 0.00289588
    xsec['Tt'] = 253.00 * 0.543

    # for mt cut scan
    group_name = {}
    for i in range(3,10):
        cut = str(i*25)
        group_name[str(i)] = "BDT (wo mT) + mT>"+ cut


    reader = ROOT.TMVA.Reader()
    reader2 = ROOT.TMVA.Reader()    

    met = array.array('f',[0])
    mt = array.array('f',[0])
    htsig = array.array('f',[0])
    amt2 = array.array('f',[0])
    topness = array.array('f',[0])
    jet1_pt = array.array('f',[0])
    jet2_pt = array.array('f',[0])
    jet3_pt = array.array('f',[0])
    jet4_pt = array.array('f',[0])
    jet1_met_dphi = array.array('f',[0])
    jet2_met_dphi = array.array('f',[0])
    jet3_met_dphi = array.array('f',[0])
    jet4_met_dphi = array.array('f',[0])
    lep_fj1_dr = array.array('f',[0])
    fj1_pt = array.array('f',[0])
    fj1_m = array.array('f',[0])

    lepmv1b_dr = array.array('f',[0])

    btag = array.array('f',[0])
    tauveto = array.array('f',[0])
    #tnboost_jets = array.array('i',[0])
    #tnboost_btag = array.array('i',[0])
    #tnboost_jmet = array.array('i',[0])
    #tnboost_met = array.array('i',[0])
    #tnboost_mt = array.array('i',[0])
    #tnboost_amt2 = array.array('i',[0])
    #tnboost_topness = array.array('i',[0])
    #tnboost_htsig = array.array('i',[0])
    tnboost_fj2met = array.array('f',[0])
    tnboost_tauveto = array.array('f',[0])
    #tnboost_toptag = array.array('i',[0])
    #tnboost_lepb = array.array('i',[0])
    #tnboost = array.array('i',[0])


    reader.AddVariable("MET", met)
    #reader.AddVariable("mTW", mt) 
    #reader.AddVariable("HT", ht) 
    #reader.AddVariable("HTratio", htratio) 
    #reader.AddVariable("METsig", metsig) 
    reader.AddVariable("HTmissSig", htsig)
    reader.AddVariable("aMT2", amt2)
    #reader.AddVariable("MT2tau", mt2tau) 
    reader.AddVariable("Topness", topness)
    reader.AddVariable("Jet1_Pt", jet1_pt)
    reader.AddVariable("Jet2_Pt", jet2_pt)
    reader.AddVariable("Jet3_Pt", jet3_pt)
    reader.AddVariable("Jet4_Pt", jet4_pt)
    reader.AddVariable("Jet1_dPhiMET", jet1_met_dphi)
    reader.AddVariable("Jet2_dPhiMET", jet2_met_dphi)
    reader.AddVariable("Jet3_dPhiMET", jet3_met_dphi)
    reader.AddVariable("Jet4_dPhiMET", jet4_met_dphi)
    reader.AddVariable("Lepton_BMV1Jet_dR", lepmv1b_dr)
    reader.AddVariable("Lepton_TrimmedJet1_dR", lep_fj1_dr)
    reader.AddVariable("TrimmedJet1_Pt", fj1_pt)
    reader.AddVariable("TrimmedJet1_4VM", fj1_m)

    # not used in the training, but need for preselection
    reader.AddSpectator("cutBTag70", btag)
    reader.AddSpectator("Tauveto", tauveto)
    reader.AddSpectator("tNboost_tauveto", tnboost_tauveto)
    reader.AddSpectator("tNboost_fj2met",tnboost_fj2met)

    reader.BookMVA("BDT","weights/TMVAClassification_BDT_wo_mt.weights.xml")
    

    reader2.AddVariable("MET", met)
    reader2.AddVariable("mTW", mt)
    #reader2.AddVariable("HT", ht) 
    #reader2.AddVariable("HTratio", htratio) 
    #reader2.AddVariable("METsig", metsig) 
    reader2.AddVariable("HTmissSig", htsig)
    reader2.AddVariable("aMT2", amt2)
    #reader2.AddVariable("MT2tau", mt2tau) 
    reader2.AddVariable("Topness", topness)
    reader2.AddVariable("Jet1_Pt", jet1_pt)
    reader2.AddVariable("Jet2_Pt", jet2_pt)
    reader2.AddVariable("Jet3_Pt", jet3_pt)
    reader2.AddVariable("Jet4_Pt", jet4_pt)
    reader2.AddVariable("Jet1_dPhiMET", jet1_met_dphi)
    reader2.AddVariable("Jet2_dPhiMET", jet2_met_dphi)
    reader2.AddVariable("Jet3_dPhiMET", jet3_met_dphi)
    reader2.AddVariable("Jet4_dPhiMET", jet4_met_dphi)
    reader2.AddVariable("Lepton_BMV1Jet_dR", lepmv1b_dr)
    reader2.AddVariable("Lepton_TrimmedJet1_dR", lep_fj1_dr)
    reader2.AddVariable("TrimmedJet1_Pt", fj1_pt)
    reader2.AddVariable("TrimmedJet1_4VM", fj1_m)

    # not used in the training, but need for preselection
    reader2.AddSpectator("cutBTag70", btag)
    reader2.AddSpectator("Tauveto", tauveto)
    reader2.AddSpectator("tNboost_tauveto", tnboost_tauveto)
    reader2.AddSpectator("tNboost_fj2met",tnboost_fj2met)

    reader2.BookMVA("BDT","weights/TMVAClassification_BDT_w_mt.weights.xml")



    hist = {}

    hist['signal'] = Hist('signal')
    hist['background'] = Hist('background')
    
    count = {}

    count['signal'] = Count('signal')
    count['background'] = Count('background')
    
    f = TFile("/group/atlas/data/D3PDs/xwang/1LStopBoosted/plot_output/20140727_DL/merge.root")
    
    tree = f.Get('evaluate')
    #tree = f.Get('train')    

    pulse = 0

    for e in tree:

        pulse = pulse + 1
        #if pulse > 10:
        #    continue

        met[0] = e.MET
        mt[0] = e.mTW
        htsig[0] = e.HTmissSig
        amt2[0] = e.aMT2
        topness[0] = e.Topness
        jet1_pt[0] = e.Jet1_Pt
        jet2_pt[0] = e.Jet2_Pt
        jet3_pt[0] = e.Jet3_Pt
        jet4_pt[0] = e.Jet4_Pt
        jet1_met_dphi[0] = e.Jet1_dPhiMET
        jet2_met_dphi[0] = e.Jet2_dPhiMET
        jet3_met_dphi[0] = e.Jet3_dPhiMET
        jet4_met_dphi[0] = e.Jet4_dPhiMET
        lepmv1b_dr[0] = e.Lepton_BMV1Jet_dR
        lep_fj1_dr[0] = e.Lepton_TrimmedJet1_dR
        fj1_pt[0] = e.TrimmedJet1_Pt
        fj1_m[0] = e.TrimmedJet1_4VM

        tauveto[0] = e.Tauveto
        btag[0] = e.cutBTag70
        tnboost_tauveto[0] = e.tNboost_tauveto 
        tnboost_fj2met[0] = e.tNboost_fj2met


        BDT = reader.EvaluateMVA("BDT")
        BDT2 = reader2.EvaluateMVA("BDT")

        sig_wt = e.EventWeight * xsec['T700_L1']
        bkg_wt = e.EventWeight * xsec['Tt'] 

        #####################
        # common preselection
        if e.cutBTag70==0:
            continue
        #####################


        if e.Signal == 1:
            hist['signal'].h_bdt.Fill(BDT, sig_wt)
            hist['signal'].h_bdt_plt.Fill(BDT, sig_wt)
        elif e.Signal == 0:
            hist['background'].h_bdt.Fill(BDT, bkg_wt)
            hist['background'].h_bdt_plt.Fill(BDT, bkg_wt)


        # for BDT (NN) related study, always apply standard tau veto on top of preselection
        if e.tNboost_tauveto==0 and e.tNboost_fj2met==1:
        #if e.Tauveto==0:
            #if True:
            if e.mTW > 125:
                if e.Signal == 1:
                    hist['signal'].h_bdt_add_cut.Fill(BDT, sig_wt)
                    hist['signal'].h_bdt_add_cut_plt.Fill(BDT, sig_wt)
                elif e.Signal == 0:
                    hist['background'].h_bdt_add_cut.Fill(BDT, bkg_wt)
                    hist['background'].h_bdt_add_cut_plt.Fill(BDT, bkg_wt)

            if e.Signal == 1:
                hist['signal'].h_bdt_w_mt.Fill(BDT2, sig_wt)
            elif e.Signal == 0:
                hist['background'].h_bdt_w_mt.Fill(BDT2, bkg_wt)



            #################
            # BDT (called 2, means without using mT) + mT var study
            for i in range(3,10):
                if e.mTW > i*25:       
                    if e.Signal == 1:
                        hist['signal'].h_bdt_add_cut_group[str(i)].Fill(BDT, sig_wt) 
                    elif e.Signal == 0:
                        hist['background'].h_bdt_add_cut_group[str(i)].Fill(BDT, bkg_wt)


            if BDT > 0.2:
                if e.Signal == 1:
                    hist['signal'].h_mt_add_bdt_high.Fill(e.mTW, sig_wt)
                    #hist['signal'].h_tauveto_add_bdt_high.Fill(e.Tauveto, sig_wt)
                    #hist['signal'].h_btag_add_bdt_high.Fill(e.cutBTag70, sig_wt)
                elif e.Signal == 0:
                    hist['background'].h_mt_add_bdt_high.Fill(e.mTW, bkg_wt)
                    #hist['background'].h_tauveto_add_bdt_high.Fill(e.Tauveto, bkg_wt)
                    #hist['background'].h_btag_add_bdt_high.Fill(e.cutBTag70, bkg_wt)

            if BDT > 0.1:
                if e.Signal == 1:
                    hist['signal'].h_mt_add_bdt_med.Fill(e.mTW, sig_wt)
                    #hist['signal'].h_tauveto_add_bdt_med.Fill(e.Tauveto, sig_wt)
                    #hist['signal'].h_btag_add_bdt_med.Fill(e.cutBTag70, sig_wt)
                elif e.Signal == 0:
                    hist['background'].h_mt_add_bdt_med.Fill(e.mTW, bkg_wt)
                    #hist['background'].h_tauveto_add_bdt_med.Fill(e.Tauveto, bkg_wt)
                    #hist['background'].h_btag_add_bdt_med.Fill(e.cutBTag70, bkg_wt)        

            if BDT > 0:
                if e.Signal == 1:
                    hist['signal'].h_mt_add_bdt_low.Fill(e.mTW, sig_wt)
                    #hist['signal'].h_tauveto_add_bdt_low.Fill(e.Tauveto, sig_wt)
                    #hist['signal'].h_btag_add_bdt_low.Fill(e.cutBTag70, sig_wt)
                elif e.Signal == 0:
                    hist['background'].h_mt_add_bdt_low.Fill(e.mTW, bkg_wt)
                    #hist['background'].h_tauveto_add_bdt_low.Fill(e.Tauveto, bkg_wt)
                    #hist['background'].h_btag_add_bdt_low.Fill(e.cutBTag70, bkg_wt)
            #################



        # for benchmark comparisons, do not apply the same tau veto as for BDT
        if e.Signal == 1:
            count['signal'].no = count['signal'].no + sig_wt
            count['signal'].no_raw = count['signal'].no_raw + 1
        elif e.Signal == 0:
            count['background'].no = count['background'].no + bkg_wt
            count['background'].no_raw = count['background'].no_raw + 1


        if e.tNboost_jets and e.tNboost_jmet and e.tNboost_met and e.tNboost_amt2 and e.tNboost_topness and e.tNboost_htsig and e.tNboost_fj2met and e.tNboost_toptag and e.tNboost_lepb:
            if e.Signal == 1:
                count['signal'].minus3 = count['signal'].minus3 + sig_wt    
            elif e.Signal == 0:
                count['background'].minus3 = count['background'].minus3 + bkg_wt


        if e.tNboost_jets and e.tNboost_jmet and e.tNboost_met and e.tNboost_mt and e.tNboost_amt2 and e.tNboost_topness and e.tNboost_htsig and e.tNboost_fj2met and e.tNboost_toptag and e.tNboost_lepb:
            if e.Signal == 1:
                count['signal'].minus2 = count['signal'].minus2 + sig_wt
            elif e.Signal == 0:
                count['background'].minus2 = count['background'].minus2 + bkg_wt


        #if e.tNboost:
        if e.tNboost_jets and e.tNboost_btag and e.tNboost_jmet and e.tNboost_met and e.tNboost_mt and e.tNboost_amt2 and e.tNboost_topness and e.tNboost_htsig and e.tNboost_fj2met and e.tNboost_tauveto==0 and e.tNboost_toptag and e.tNboost_lepb:
        #if e.tNboost_jets and e.tNboost_btag and e.tNboost_jmet and e.tNboost_met and e.tNboost_mt and e.tNboost_amt2 and e.tNboost_topness and e.tNboost_htsig and e.tNboost_toptag and e.tNboost_lepb:
            if e.Signal == 1:
                count['signal'].all = count['signal'].all + sig_wt
                count['signal'].all_raw = count['signal'].all_raw + 1
            elif e.Signal == 0:
                count['background'].all = count['background'].all + bkg_wt
                count['background'].all_raw = count['background'].all_raw + 1


    # base: after preselection
    hist['signal'].h_scan_bdt = Scan(hist['signal'].h_bdt)
    hist['background'].h_scan_bdt = Scan(hist['background'].h_bdt)

    # evaluate: tau + btag + mt + bdt
    hist['signal'].h_scan_bdt_add_cut = ScanAddCut(hist['signal'].h_bdt, hist['signal'].h_bdt_add_cut)
    hist['background'].h_scan_bdt_add_cut = ScanAddCut(hist['background'].h_bdt, hist['background'].h_bdt_add_cut)

    # evaluate: tau + btag + bdt (with mt)
    hist['signal'].h_scan_bdt_w_mt = ScanAddCut(hist['signal'].h_bdt, hist['signal'].h_bdt_w_mt)
    hist['background'].h_scan_bdt_w_mt = ScanAddCut(hist['background'].h_bdt, hist['background'].h_bdt_w_mt)


    for i in range(3,10):
        hist['signal'].h_scan_bdt_add_cut_group[str(i)] = ScanAddCut(hist['signal'].h_bdt, hist['signal'].h_bdt_add_cut_group[str(i)])
        hist['background'].h_scan_bdt_add_cut_group[str(i)] = ScanAddCut(hist['background'].h_bdt, hist['background'].h_bdt_add_cut_group[str(i)])



    print count['signal'].all_raw, count['signal'].no_raw, count['signal'].all, count['signal'].minus3, count['signal'].no
    print count['background'].all_raw, count['background'].no_raw, count['background'].all, count['background'].minus3, count['background'].no

    benchmark_effS1 = float(count['signal'].minus3) / float(count['signal'].no)  
    benchmark_bkgR1 = float(count['background'].no) / float(count['background'].minus3) 

    benchmark_effS2 = float(count['signal'].all) / float(count['signal'].no) 
    benchmark_bkgR2 = float(count['background'].no) / float(count['background'].all)

    benchmark_effS3 = float(count['signal'].minus2) / float(count['signal'].no)
    benchmark_bkgR3 = float(count['background'].no) / float(count['background'].minus2)    


    # for neural net deep learning
    nn_w_mt_f = TFile("/group/atlas/prj/xiaoxiao/1LStopBoosted_SUSY0314/1LStopBoosted/AGILEPack/nn2_w_mt.root", "read")

    hist['signal'].h_nn_train_w_mt = nn_w_mt_f.Get("h_NN_train_sig_preselection")
    hist['background'].h_nn_train_w_mt = nn_w_mt_f.Get("h_NN_train_bkg_preselection")

    hist['signal'].h_nn_validate_w_mt = nn_w_mt_f.Get("h_NN_validate_sig_preselection")
    hist['background'].h_nn_validate_w_mt = nn_w_mt_f.Get("h_NN_validate_bkg_preselection")

    hist['signal'].h_nn_evaluate_w_mt = nn_w_mt_f.Get("h_NN_evaluate_sig_preselection")
    hist['background'].h_nn_evaluate_w_mt = nn_w_mt_f.Get("h_NN_evaluate_bkg_preselection")

    # evaluate: tau + btag + nn (with mt)
    hist['signal'].h_scan_nn_evaluate_w_mt = ScanAddCutPrime(xsec["T700_L1"], hist['signal'].h_bdt, hist['signal'].h_nn_evaluate_w_mt)
    hist['background'].h_scan_nn_evaluate_w_mt = ScanAddCutPrime(xsec['Tt'], hist['background'].h_bdt, hist['background'].h_nn_evaluate_w_mt)

    nn_wo_mt_f = TFile("/group/atlas/prj/xiaoxiao/1LStopBoosted_SUSY0314/1LStopBoosted/AGILEPack/nn2_wo_mt.root", "read")

    hist['signal'].h_nn_train_wo_mt = nn_wo_mt_f.Get("h_NN_train_sig_preselection")
    hist['background'].h_nn_train_wo_mt = nn_wo_mt_f.Get("h_NN_train_bkg_preselection")

    hist['signal'].h_nn_validate_wo_mt = nn_wo_mt_f.Get("h_NN_validate_sig_preselection")
    hist['background'].h_nn_validate_wo_mt = nn_wo_mt_f.Get("h_NN_validate_bkg_preselection")

    hist['signal'].h_nn_evaluate_wo_mt = nn_wo_mt_f.Get("h_NN_evaluate_sig_preselection")
    hist['background'].h_nn_evaluate_wo_mt = nn_wo_mt_f.Get("h_NN_evaluate_bkg_preselection")

    hist['signal'].h_nn_evaluate_wo_mt_add_cut = nn_wo_mt_f.Get("h_NN_evaluate_sig_mt_cut_preselection")
    hist['background'].h_nn_evaluate_wo_mt_add_cut = nn_wo_mt_f.Get("h_NN_evaluate_bkg_mt_cut_preselection")

    # evaluate: tau + btag + mt + nn
    hist['signal'].h_scan_nn_evaluate_wo_mt_add_cut = ScanAddCutPrime(xsec["T700_L1"], hist['signal'].h_bdt, hist['signal'].h_nn_evaluate_wo_mt_add_cut)
    hist['background'].h_scan_nn_evaluate_wo_mt_add_cut = ScanAddCutPrime(xsec['Tt'], hist['background'].h_bdt, hist['background'].h_nn_evaluate_wo_mt_add_cut)

    # check: mt distribution
    hist['signal'].h_mt_evaluate_wo_mt = nn_wo_mt_f.Get("h_mt_evaluate_sig_preselection")
    hist['background'].h_mt_evaluate_wo_mt = nn_wo_mt_f.Get("h_mt_evaluate_bkg_preselection")   


    #Plt.DrawROCcurve2(hist['signal'].h_scan_bdt, hist['background'].h_scan_bdt, "BDT", hist['signal'].h_scan_bdt_add_cut, hist['background'].h_scan_bdt_add_cut, "BDT + m_{T}>125 + #tau veto + #geq1b", benchmark_effS1, benchmark_bkgR1, "tNboost - m_{T}>125 - #tau veto - #geq1b", benchmark_effS2, benchmark_bkgR2, "tNboost", "#varepsilon_{signal}", "1.0/#varepsilon_{background}", "plots/MVA_ROC.pdf")

    #################
    #Plt.DrawROCcurve2(hist['signal'].h_scan_bdt, hist['background'].h_scan_bdt, "BDT", hist['signal'].h_scan_bdt_add_cut, hist['background'].h_scan_bdt_add_cut, "BDT + m_{T}>125", benchmark_effS1, benchmark_bkgR1, "tNboost - m_{T}>125", benchmark_effS2, benchmark_bkgR2, "tNboost", "#varepsilon_{signal}", "1.0/#varepsilon_{background}", "plots/MVA_ROC.pdf")

    h_sig = {}
    h_bkg = {}
    h_sig['1. BDT (w M_{T})'] = hist['signal'].h_scan_bdt_w_mt
    h_bkg['1. BDT (w M_{T})'] = hist['background'].h_scan_bdt_w_mt
    h_sig['2. BDT (w/o M_{T}) + m_{T}>125'] = hist['signal'].h_scan_bdt_add_cut
    h_bkg['2. BDT (w/o M_{T}) + m_{T}>125'] = hist['background'].h_scan_bdt_add_cut
    h_sig['3. Deep NN (w M_{T})'] = hist['signal'].h_scan_nn_evaluate_w_mt
    h_bkg['3. Deep NN (w M_{T})'] = hist['background'].h_scan_nn_evaluate_w_mt
    h_sig['4. Deep NN (w/o M_{T}) + m_{T}>125'] = hist['signal'].h_scan_nn_evaluate_wo_mt_add_cut
    h_bkg['4. Deep NN (w/o M_{T}) + m_{T}>125'] = hist['background'].h_scan_nn_evaluate_wo_mt_add_cut
    p_sig = {}
    p_bkg = {}
    #p_sig['3. tN_boost - m_{T}>125'] = benchmark_effS1
    #p_bkg['3. tN_boost - m_{T}>125'] = benchmark_bkgR1
    p_sig['5. tN_boost'] = benchmark_effS2
    p_bkg['5. tN_boost'] = benchmark_bkgR2
    
    Plt.DrawROCcurvePointGroup(h_sig, h_bkg, p_sig, p_bkg, "#varepsilon_{signal}", "1.0/#varepsilon_{background}", "plots/MVA_ROC.pdf")

    Plt.DrawROCcurveGroup(hist['signal'].h_scan_bdt_add_cut_group, hist['background'].h_scan_bdt_add_cut_group, group_name, "#varepsilon_{signal}", "1.0/#varepsilon_{background}", "plots/MVA_ROC_Group.pdf")

    Plt.DrawTwoHistOverlay(hist['signal'].h_mt_add_bdt_high, hist['background'].h_mt_add_bdt_high, "Signal: m(#tilde{t}_{1},#tilde{#chi}_{1}^{0})=(700,1)", "Background: t#bar{t}", "M_{T}", "Arbitrary Unit", True, True, 3, "plots/MT_AFTER_MVA_BDT_HIGH.pdf")
    Plt.DrawTwoHistOverlay(hist['signal'].h_mt_add_bdt_med, hist['background'].h_mt_add_bdt_med, "Signal: m(#tilde{t}_{1},#tilde{#chi}_{1}^{0})=(700,1)", "Background: t#bar{t}", "M_{T}", "Arbitrary Unit", True, True, 3, "plots/MT_AFTER_MVA_BDT_MED.pdf")
    Plt.DrawTwoHistOverlay(hist['signal'].h_mt_add_bdt_low, hist['background'].h_mt_add_bdt_low, "Signal: m(#tilde{t}_{1},#tilde{#chi}_{1}^{0})=(700,1)", "Background: t#bar{t}", "M_{T}", "Arbitrary Unit", True, True, 3, "plots/MT_AFTER_MVA_BDT_LOW.pdf")
 
    Plt.DrawTwoHistOverlay(hist['signal'].h_mt_evaluate_wo_mt, hist['background'].h_mt_evaluate_wo_mt, "Signal: m(#tilde{t}_{1},#tilde{#chi}_{1}^{0})=(700,1)", "Background: t#bar{t}", "M_{T}", "Arbitrary Unit", True, True, 3, "plots/MT_AFTER_DL_NN_HIGH.pdf")

    #Plt.DrawTwoHistOverlay(hist['signal'].h_tauveto_add_bdt_high, hist['background'].h_tauveto_add_bdt_high, "Signal: m(#tilde{t}_{1},#tilde{#chi}_{1}^{0})=(700,1)", "Background: t#bar{t}", "tau veto", "Arbitrary Unit", True, False, 3, "plots/TAUVETO_AFTER_MVA_BDT_HIGH.pdf")
    #Plt.DrawTwoHistOverlay(hist['signal'].h_tauveto_add_bdt_med, hist['background'].h_tauveto_add_bdt_med, "Signal: m(#tilde{t}_{1},#tilde{#chi}_{1}^{0})=(700,1)", "Background: t#bar{t}", "tau veto", "Arbitrary Unit", True, False, 3, "plots/TAUVETO_AFTER_MVA_BDT_MED.pdf")
    #Plt.DrawTwoHistOverlay(hist['signal'].h_tauveto_add_bdt_low, hist['background'].h_tauveto_add_bdt_low, "Signal: m(#tilde{t}_{1},#tilde{#chi}_{1}^{0})=(700,1)", "Background: t#bar{t}", "tau veto", "Arbitrary Unit", True, False, 3, "plots/TAUVETO_AFTER_MVA_BDT_LOW.pdf")

    #Plt.DrawTwoHistOverlay(hist['signal'].h_btag_add_bdt_high, hist['background'].h_btag_add_bdt_high, "Signal: m(#tilde{t}_{1},#tilde{#chi}_{1}^{0})=(700,1)", "Background: t#bar{t}", "btag", "Arbitrary Unit", True, False, 3, "plots/BTAG_AFTER_MVA_BDT_HIGH.pdf")
    #Plt.DrawTwoHistOverlay(hist['signal'].h_btag_add_bdt_med, hist['background'].h_btag_add_bdt_med, "Signal: m(#tilde{t}_{1},#tilde{#chi}_{1}^{0})=(700,1)", "Background: t#bar{t}", "btag", "Arbitrary Unit", True, False, 3, "plots/BTAG_AFTER_MVA_BDT_MED.pdf")
    #Plt.DrawTwoHistOverlay(hist['signal'].h_btag_add_bdt_low, hist['background'].h_btag_add_bdt_low, "Signal: m(#tilde{t}_{1},#tilde{#chi}_{1}^{0})=(700,1)", "Background: t#bar{t}", "btag", "Arbitrary Unit", True, False, 3, "plots/BTAG_AFTER_MVA_BDT_LOW.pdf")
    #################

    Plt.DrawFourHistOverlay(hist['signal'].h_nn_train_w_mt, hist['signal'].h_nn_validate_w_mt, hist['background'].h_nn_train_w_mt, hist['background'].h_nn_validate_w_mt, 'signal (training)', 'signal (testing)', 'tt (training)', 'tt (testing)', 'Deep NN', 'Arbitrary Unit', True, False, 0, 'plots/NN_w_mt_Overtrain.pdf')
    Plt.DrawFourHistOverlay(hist['signal'].h_nn_train_wo_mt, hist['signal'].h_nn_validate_wo_mt, hist['background'].h_nn_train_wo_mt, hist['background'].h_nn_validate_wo_mt, 'signal (training)', 'signal (testing)', 'tt (training)', 'tt (testing)', 'Deep NN', 'Arbitrary Unit', True, False, 0, 'plots/NN_wo_mt_Overtrain.pdf')

    Plt.DrawTwoHistOverlay(hist['signal'].h_nn_evaluate_w_mt, hist['background'].h_nn_evaluate_w_mt, "Signal: m(#tilde{t}_{1},#tilde{#chi}_{1}^{0})=(700,1)", "Background: t#bar{t}", "Deep NN", "Arbitrary Unit", True, False, 4, "plots/NN_w_mt.pdf")
    Plt.DrawTwoHistOverlay(hist['signal'].h_bdt_w_mt, hist['background'].h_bdt_w_mt, "Signal: m(#tilde{t}_{1},#tilde{#chi}_{1}^{0})=(700,1)", "Background: t#bar{t}", "BDT Score", "Arbitrary Unit", True, False, 3, "plots/MVA_BDT_w_mt.pdf")
        

    #Plt.DrawTwoHistOverlay(hist['signal'].h_bdt_plt, hist['background'].h_bdt_plt, "Signal: m(#tilde{t}_{1},#tilde{#chi}_{1}^{0})=(700,1)", "Background: t#bar{t}", "BDT Score", "Arbitrary Unit", True, False, 3, "plots/MVA_BDT.pdf")
    #Plt.DrawTwoHistOverlay(hist['signal'].h_bdt_add_cut_plt, hist['background'].h_bdt_add_cut_plt, "Signal: m(#tilde{t}_{1},#tilde{#chi}_{1}^{0})=(700,1)", "Background: t#bar{t}", "BDT Score", "Arbitrary Unit", True, False, 3, "plots/MVA_BDT_add_cut.pdf")

if __name__ == '__main__':
    main()

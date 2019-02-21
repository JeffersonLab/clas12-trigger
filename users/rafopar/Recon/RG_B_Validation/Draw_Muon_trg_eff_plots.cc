/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Draw_Muon_trg_eff_plots.cc
 * Author: rafopar
 *
 * Created on February 20, 2019, 1:18 PM
 */

#include <cstdlib>
#include <TCanvas.h>

using namespace std;

/*
 * 
 */
void Draw_Muon_trg_eff_plots() {

    TCanvas *c1 = new TCanvas("c1", "", 750, 750);
    
    TFile *file_in = new TFile("Muon_Trg_Eff.root");
    
    TH2D *h_Pposneg_all_pairs1 = (TH2D*)file_in->Get("h_Pposneg_all_pairs1");
    
    h_Pposneg_all_pairs1->SetTitle("; P_{neg} [GeV]; P_{pos} [GeV]");
    h_Pposneg_all_pairs1->Draw("colz");
    c1->Print("Figs/PPosNeg_Muon_Pairs_all.eps");
    c1->Print("Figs/PPosNeg_Muon_Pairs_all.pdf");
    c1->Print("Figs/PPosNeg_Muon_Pairs_all.png");
    
    TH2D *h_Pposneg_tr_missed1 = (TH2D*)file_in->Get("h_Pposneg_tr_missed1");
    h_Pposneg_tr_missed1->SetTitle("; P_{neg} [GeV]; P_{pos} [GeV]");
    h_Pposneg_tr_missed1->Draw("colz");
    c1->Print("Figs/PPosNeg_Muon_Pairs_trg_missed.eps");
    c1->Print("Figs/PPosNeg_Muon_Pairs_trg_missed.pdf");
    c1->Print("Figs/PPosNeg_Muon_Pairs_trg_missed.png");
    
    
    TH2D *h_PCal_pos_neg_missed1 = (TH2D*)file_in->Get("h_PCal_pos_neg_missed1");
    h_PCal_pos_neg_missed1->SetTitle("; E_{PCal}^{neg} [GeV]; E_{PCal}^{pos} [GeV]");
    h_PCal_pos_neg_missed1->Draw("colz");
    c1->Print("Figs/EPcal_pos_neg_missed_highmom.eps");
    c1->Print("Figs/EPcal_pos_neg_missed_highmom.pdf");
    c1->Print("Figs/EPcal_pos_neg_missed_highmom.png");
    
    TH2D *h_PCal_yxc_pos_all1 = (TH2D*)file_in->Get("h_PCal_yxc_pos_all1");
    h_PCal_yxc_pos_all1->SetTitle("; PCal_{X} [cm]; PCal_{Y} [cm]");
    
    TH2D *h_PCal_yxc_pos_missed1 = (TH2D*)file_in->Get("h_PCal_yxc_pos_missed1");
    h_PCal_yxc_pos_missed1->SetTitle("; PCal_{X} [cm]; PCal_{Y} [cm]");
    h_PCal_yxc_pos_missed1->SetMarkerStyle(20);
    h_PCal_yxc_pos_missed1->SetMarkerColor(2);
    
    h_PCal_yxc_pos_all1->Draw("colz");
    h_PCal_yxc_pos_missed1->Draw("Same");
    c1->Print("Figs/Missed_on_PCal_YXc1.eps");
    c1->Print("Figs/Missed_on_PCal_YXc1.pdf");
    c1->Print("Figs/Missed_on_PCal_YXc1.png");
}


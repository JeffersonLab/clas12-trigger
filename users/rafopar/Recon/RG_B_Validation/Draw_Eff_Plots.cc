/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Draw_Eff_Plots.cc
 * Author: rafopar
 *
 * Created on February 14, 2019, 12:28 PM
 */

#include <cstdlib>
#include <TLine.h>

using namespace std;

/*
 * 
 */
void Draw_Eff_Plots() {

    TCanvas *c1 = new TCanvas("c1", "", 750, 750);

    const double vz_MAX_cut = 5.;
    const double vz_MIN_cut = -10.;

    
    TFile *file_in = new TFile("Trig_Eff_6213.root", "Read");
    
    TH1D *h_P_Good_em0 = (TH1D*)file_in->Get("h_P_Good_em0");
    TH1D *h_P_Good_em_missed_trg_thresholds1 = (TH1D*)file_in->Get("h_P_Good_em_missed_trg_thresholds1");
    
    
    h_P_Good_em0->SetTitle("; P [GeV]");
    h_P_Good_em0->SetFillColor(45);
    
    h_P_Good_em_missed_trg_thresholds1->SetLineColor(4);
    h_P_Good_em_missed_trg_thresholds1->SetFillColor(4);
    h_P_Good_em_missed_trg_thresholds1->SetTitle("; P [GeV]");
    
    c1->SetLogy();
    
    h_P_Good_em0->Draw();
    h_P_Good_em_missed_trg_thresholds1->Draw("Same");
    c1->Print("Figs/All_vs_Missed_Momdep.eps");
    c1->Print("Figs/All_vs_Missed_Momdep.pdf");
    c1->Print("Figs/All_vs_Missed_Momdep.png");
    
    TH2D *h_n_HTCC_trg_good_em_nphe2 = (TH2D*)file_in->Get("h_n_HTCC_trg_good_em_nphe2");
    h_n_HTCC_trg_good_em_nphe2->SetTitle("; nphe; # of trigs");
    
    c1->SetLogy(0);
    TH1D *h_nphe_missed = (TH1D*)h_n_HTCC_trg_good_em_nphe2->ProjectionX("h_nphe_missed", 1, 1);
    h_nphe_missed->Draw();
    c1->Print("Figs/nphe_missed1.eps");
    c1->Print("Figs/nphe_missed1.pdf");
    c1->Print("Figs/nphe_missed1.png");
    
    TH2D *h_n_HTCC_trg_good_em_P2 = (TH2D*)file_in->Get("h_n_HTCC_trg_good_em_P2");
    TH1D *h_P_nphe_missed1 = (TH1D*)h_n_HTCC_trg_good_em_P2->ProjectionX("h_P_nphe_missed1", 1, 1);
    h_P_nphe_missed1->SetFillColor(2);
    h_P_nphe_missed1->SetLineColor(2);
    
    TH1D *h_P_Good_em_missed_trg_thresholds_nphefail1 = (TH1D*)file_in->Get("h_P_Good_em_missed_trg_thresholds_nphefail1");
    h_P_Good_em_missed_trg_thresholds_nphefail1->SetFillColor(30);
    h_P_Good_em_missed_trg_thresholds_nphefail1->SetLineColor(30);
    
    
    TH2D *h_n_EC_trg_good_em_P2 = (TH2D*)file_in->Get("h_n_EC_trg_good_em_P2");
    TH1D *h_P_PCalEC_missed2 = (TH1D*)h_n_EC_trg_good_em_P2->ProjectionX("h_P_PCalEC_missed2", 1, 1);
    h_P_PCalEC_missed2->SetFillColor(1);
    h_P_PCalEC_missed2->SetLineColor(1);
    
    
    h_P_Good_em_missed_trg_thresholds1->Draw();
    h_P_nphe_missed1->Draw("Same");
    h_P_PCalEC_missed2->Draw("Same");
    h_P_Good_em_missed_trg_thresholds_nphefail1->Draw("Same");
    c1->Print("Figs/Missing_Decomposition.eps");
    c1->Print("Figs/Missing_Decomposition.pdf");
    c1->Print("Figs/Missing_Decomposition.png");
    
    TH1D *h_vz_Good_em0 = (TH1D*)file_in->Get("h_vz_Good_em0");
    h_vz_Good_em0->SetTitle("; Vz [cm]");
    h_vz_Good_em0->Draw();
    TLine *line1 = new TLine();
    line1->DrawLine(vz_MAX_cut, 0, vz_MAX_cut, h_vz_Good_em0->GetMaximum());
    line1->DrawLine(vz_MIN_cut, 0, vz_MIN_cut, h_vz_Good_em0->GetMaximum());
    c1->Print("Figs/vz_cut.eps");
    c1->Print("Figs/vz_cut.pdf");
    c1->Print("Figs/vz_cut.png");
 
    
    
    TFile *file_DCRoads = new TFile("DC_Roads_check.root", "Read");
    
    
    
    
}


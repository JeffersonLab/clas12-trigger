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
    
    int run = 6299;
    
    TFile *file_in = new TFile(Form("Muon_Trg_Eff_%d.root", run));
    //TFile *file_in = new TFile(Form("Muon_Trg_Eff_%d_Processed.root", run));
    
    TH2D *h_Pposneg_all_pairs1 = (TH2D*)file_in->Get("h_Pposneg_all_pairs1");
    
    h_Pposneg_all_pairs1->SetTitle("; P_{neg} [GeV]; P_{pos} [GeV]");
    h_Pposneg_all_pairs1->Draw("colz");
    c1->Print(Form("Figs/PPosNeg_Muon_Pairs_all_%d.eps", run));
    c1->Print(Form("Figs/PPosNeg_Muon_Pairs_all_%d.pdf", run));
    c1->Print(Form("Figs/PPosNeg_Muon_Pairs_all_%d.png", run));
    
    TH2D *h_Pposneg_tr_missed1 = (TH2D*)file_in->Get("h_Pposneg_tr_missed1");
    h_Pposneg_tr_missed1->SetMinimum(-0.1);
    h_Pposneg_tr_missed1->SetTitle("; P_{neg} [GeV]; P_{pos} [GeV]");
    h_Pposneg_tr_missed1->Draw("colz");
    c1->Print(Form("Figs/PPosNeg_Muon_Pairs_trg_missed_%d.eps", run));
    c1->Print(Form("Figs/PPosNeg_Muon_Pairs_trg_missed_%d.pdf", run));
    c1->Print(Form("Figs/PPosNeg_Muon_Pairs_trg_missed_%d.png", run));
    
    
    TH2D *h_PCal_pos_neg_missed1 = (TH2D*)file_in->Get("h_PCal_pos_neg_missed1");
    h_PCal_pos_neg_missed1->SetMinimum(-0.1);
    h_PCal_pos_neg_missed1->SetTitle("; E_{PCal}^{neg} [GeV]; E_{PCal}^{pos} [GeV]");
    h_PCal_pos_neg_missed1->Draw("colz");
    c1->Print(Form("Figs/EPcal_pos_neg_missed_highmom_%d.eps", run));
    c1->Print(Form("Figs/EPcal_pos_neg_missed_highmom_%d.pdf", run));
    c1->Print(Form("Figs/EPcal_pos_neg_missed_highmom_%d.png", run));
    
    TH2D *h_PCal_yxc_pos_all1 = (TH2D*)file_in->Get("h_PCal_yxc_pos_all1");
    h_PCal_yxc_pos_all1->SetTitle("; PCal_{X} [cm]; PCal_{Y} [cm]");
    
    TH2D *h_PCal_yxc_pos_missed1 = (TH2D*)file_in->Get("h_PCal_yxc_pos_missed1");
    h_PCal_yxc_pos_missed1->SetTitle("; PCal_{X} [cm]; PCal_{Y} [cm]");
    h_PCal_yxc_pos_missed1->SetMarkerStyle(20);
    h_PCal_yxc_pos_missed1->SetMarkerColor(2);
    
    h_PCal_yxc_pos_all1->Draw("colz");
    h_PCal_yxc_pos_missed1->Draw("Same");
    c1->Print(Form("Figs/Missed_on_PCal_YXc1_%d.eps", run));
    c1->Print(Form("Figs/Missed_on_PCal_YXc1_%d.pdf", run));
    c1->Print(Form("Figs/Missed_on_PCal_YXc1_%d.png", run));
    
    
    
    TFile *file_stage_highstat = new TFile("stage1_study_6299_highstat.root", "Read");
    
    TH2D *h_PCal_cl_sec_Emin2 = (TH2D*)file_stage_highstat->Get("h_PCal_cl_sec_Emin2");
    h_PCal_cl_sec_Emin2->SetTitle("PCal; E_{min} [GeV]; sector");
    h_PCal_cl_sec_Emin2->Draw("colz");
    c1->Print("Figs/PCal_sect_Emin_with_offline_good_tracks.eps");
    c1->Print("Figs/PCal_sect_Emin_with_offline_good_tracks.pdf");
    c1->Print("Figs/PCal_sect_Emin_with_offline_good_tracks.png");
    
    c1->SetLogy();
    TH1D *h_Pcal_cl_Emin1 = (TH1D*)h_PCal_cl_sec_Emin2->ProjectionX("h_Pcal_cl_Emin1", 1, 6);
    h_Pcal_cl_Emin1->Draw("colz");
    c1->Print("Figs/PCal_Emin_with_offline_good_tracks.eps");
    c1->Print("Figs/PCal_Emin_with_offline_good_tracks.pdf");
    c1->Print("Figs/PCal_Emin_with_offline_good_tracks.png");
    
    c1->SetLogy(0);
    c1->SetLeftMargin(0.12);
    c1->SetGrid(1, 1);
    TH1D *h_cumulative_PCal_offline_good_electrons = (TH1D*)h_Pcal_cl_Emin1->GetCumulative();
    h_cumulative_PCal_offline_good_electrons->Scale(100./h_cumulative_PCal_offline_good_electrons->GetMaximum());
    h_cumulative_PCal_offline_good_electrons->SetMinimum(97.);
    h_cumulative_PCal_offline_good_electrons->SetTitle("; E_{min} [GeV]; Percent kept");
    h_cumulative_PCal_offline_good_electrons->Draw("hist");
    c1->Print("Figs/PCal_cumulative_Emin_good_tracks.eps");
    c1->Print("Figs/PCal_cumulative_Emin_good_tracks.pdf");
    c1->Print("Figs/PCal_cumulative_Emin_good_tracks.png");
}


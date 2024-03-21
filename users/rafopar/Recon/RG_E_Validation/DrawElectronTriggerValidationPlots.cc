/* 
 * File:   DrawElectronTriggerValidationPlots.cc
 * Author: rafopar
 *
 * Created on November 22, 2021, 11:22 AM
 */

#include <cstdlib>

using namespace std;

/*
 * 
 */
int DrawElectronTriggerValidationPlots( int run ) {

    gStyle->SetOptStat(0);

    TF1 *f_lin1 = new TF1("f_lin1", "[0] + [1]*x", 0., 180.);

    TLine *line1 = new TLine();
    line1->SetLineColor(2);
    line1->SetLineWidth(3); 
    
    TCanvas *c1 = new TCanvas("c1", "", 950, 950);
    c1->SetTopMargin(0.02);
    c1->SetRightMargin(0.02);
    c1->SetLeftMargin(0.14);

    TFile *file_in = new TFile(Form("Validate_Electron_%d.root", run));

    TH2D *h_PCal_yxc1 = (TH2D*) file_in->Get("h_PCal_yxc1");
    h_PCal_yxc1->SetTitle("; PCal_X [cm]; PCal_Y [cm]");
    h_PCal_yxc1->SetMarkerColor(2);

    TH2D *h_PCal_yxc2 = (TH2D*) file_in->Get("h_PCal_yxc2");
    h_PCal_yxc2->SetTitle("; PCal_X [cm]; PCal_Y [cm]");
    h_PCal_yxc2->SetMarkerColor(4);
    h_PCal_yxc1->Draw("Scatter");
    h_PCal_yxc2->Draw("Scatter Same");
    c1->Print(Form("Figs/PCal_YX_Fiducial_%d.pdf", run));
    c1->Print(Form("Figs/PCal_YX_Fiducial_%d.png", run));
    c1->Print(Form("Figs/PCal_YX_Fiducial_%d.root", run));

    TH2D *h_ECin_yxc1 = (TH2D*) file_in->Get("h_ECin_yxc1");
    h_ECin_yxc1->SetTitle("; ECin_X [cm]; ECin_Y [cm]");
    h_ECin_yxc1->SetMarkerColor(2);

    TH2D *h_ECin_yxc2 = (TH2D*) file_in->Get("h_ECin_yxc2");
    h_ECin_yxc2->SetTitle("; ECin_X [cm]; ECin_Y [cm]");
    h_ECin_yxc2->SetMarkerColor(4);
    h_ECin_yxc1->Draw("Scatter");
    h_ECin_yxc2->Draw("Scatter Same");
    c1->Print(Form("Figs/ECin_YX_Fiducial_%d.pdf", run));
    c1->Print(Form("Figs/ECin_YX_Fiducial_%d.png", run));
    c1->Print(Form("Figs/ECin_YX_Fiducial_%d.root", run));

    TH2D *h_ECout_yxc1 = (TH2D*) file_in->Get("h_ECout_yxc1");
    h_ECout_yxc1->SetTitle("; ECout_X [cm]; ECout_Y [cm]");
    h_ECout_yxc1->SetMarkerColor(2);

    TH2D *h_ECout_yxc2 = (TH2D*) file_in->Get("h_ECout_yxc2");
    h_ECout_yxc2->SetTitle("; ECout_X [cm]; ECout_Y [cm]");
    h_ECout_yxc2->SetMarkerColor(4);
    h_ECout_yxc1->Draw("Scatter");
    h_ECout_yxc2->Draw("Scatter Same");
    c1->Print(Form("Figs/ECout_YX_Fiducial_%d.pdf", run));
    c1->Print(Form("Figs/ECout_YX_Fiducial_%d.png", run));
    c1->Print(Form("Figs/ECout_YX_Fiducial_%d.root", run));
    
    const double SF_min = 0.18;
    TH2D *h_SF1 = (TH2D*)file_in->Get("h_SF1");
    h_SF1->SetTitle("; P[GeV] ; SF");
    h_SF1->Draw("colz");
    line1->DrawLine(0.5, SF_min, 10., SF_min);
    c1->Print(Form("Figs/SF1_%d.pdf", run));
    c1->Print(Form("Figs/SF1_%d.png", run));
    c1->Print(Form("Figs/SF1_%d.root", run));

    TH2D *h_SF2 = (TH2D*)file_in->Get("h_SF2");
    h_SF2->SetTitle("; P[GeV] ; SF");
    h_SF2->Draw("colz");
    line1->DrawLine(0.5, SF_min, 10., SF_min);
    c1->Print(Form("Figs/SF2_%d.pdf", run));
    c1->Print(Form("Figs/SF2_%d.png", run));
    c1->Print(Form("Figs/SF2_%d.root", run));
    

    TH2D *h_VTP_HTCC_times1 = (TH2D*) file_in->Get("h_VTP_HTCC_times1");
    h_VTP_HTCC_times1->SetTitle("; t_{HTCC} [ns]; t_{VTP} [4ns]");
    h_VTP_HTCC_times1->SetAxisRange(50., 200., "X");
    h_VTP_HTCC_times1->SetAxisRange(0., 105., "Y");
    h_VTP_HTCC_times1->Draw("colz");
    f_lin1->SetParameters(35., 0.25);
    f_lin1->DrawCopy("Same");
    f_lin1->SetParameters(55., 0.25);
    f_lin1->DrawCopy("Same");
    c1->Print(Form("Figs/VTP_t_HTCC_t_%d.pdf", run));
    c1->Print(Form("Figs/VTP_t_HTCC_t_%d.png", run));
    c1->Print(Form("Figs/VTP_t_HTCC_t_%d.root", run));

    TH1D *h_P_em_Good_em1 = (TH1D*) file_in->Get("h_P_em_Good_em1");
    h_P_em_Good_em1->SetTitle("; P_{e^{-}} [GeV]");
    h_P_em_Good_em1->SetLineColor(2);
    TH1D *h_P_em_Good_em_TrgPassed1 = (TH1D*) file_in->Get("h_P_em_Good_em_TrgPassed1");
    h_P_em_Good_em_TrgPassed1->SetTitle("; P_{e^{-}} [GeV]");
    h_P_em_Good_em_TrgPassed1->SetLineColor(4);
    h_P_em_Good_em1->Draw();
    h_P_em_Good_em_TrgPassed1->Draw("Same");

    TRatioPlot *rp_Eff1 = new TRatioPlot(h_P_em_Good_em_TrgPassed1, h_P_em_Good_em1, "errasym");
    rp_Eff1->GetLowerPad()->SetTopMargin(0.);
    rp_Eff1->GetLowerPad()->SetGridy();
    rp_Eff1->GetUpperPad()->SetBottomMargin(0.);
    rp_Eff1->Draw();
    rp_Eff1->GetLowerRefGraph()->SetMaximum(1.01);
    rp_Eff1->GetLowerRefGraph()->SetMinimum(0.97);
    c1->Print(Form("Figs/Eff_MomDep_WithThresholds_%d.pdf", run));
    c1->Print(Form("Figs/Eff_MomDep_WithThresholds_%d.png", run));
    c1->Print(Form("Figs/Eff_MomDep_WithThresholds_%d.root", run));

    const double nphe_AboveThr = 2.;
    const double Etot_AboveThr = 0.2;
    TH2D *h_Etot_Nphe_Failed1 = (TH2D*)file_in->Get("h_Etot_Nphe_Failed1");
    h_Etot_Nphe_Failed1->SetTitle("; E_{Tot} [GeV]; Nphe");
    h_Etot_Nphe_Failed1->Draw("colz");
    line1->DrawLine(Etot_AboveThr, nphe_AboveThr, 1.5, nphe_AboveThr);
    line1->DrawLine(Etot_AboveThr, nphe_AboveThr, Etot_AboveThr, 20.5);
    c1->Print(Form("Figs/Nphe_Etot_Failed_%d.pdf", run));
    c1->Print(Form("Figs/Nphe_Etot_Failed_%d.png", run));
    c1->Print(Form("Figs/Nphe_Etot_Failed_%d.root", run));
    
    TH1D *h_P_em_Good_emAboveThreshold1 = (TH1D*) file_in->Get("h_P_em_Good_emAboveThreshold1");
    h_P_em_Good_emAboveThreshold1->SetTitle("; P_{e^{-}} [GeV]");
    h_P_em_Good_emAboveThreshold1->SetLineColor(2);
    TH1D *h_P_em_Good_emAboveThreshold_TrgPassed1 = (TH1D*) file_in->Get("h_P_em_Good_emAboveThreshold_TrgPassed1");
    h_P_em_Good_emAboveThreshold_TrgPassed1->SetTitle("; P_{e^{-}} [GeV]");
    h_P_em_Good_emAboveThreshold_TrgPassed1->SetLineColor(4);
    h_P_em_Good_emAboveThreshold_TrgPassed1->Draw();
    h_P_em_Good_emAboveThreshold_TrgPassed1->Draw("Same");

    TRatioPlot *rp_Eff2 = new TRatioPlot(h_P_em_Good_emAboveThreshold_TrgPassed1, h_P_em_Good_emAboveThreshold1, "errasym");
    rp_Eff2->GetLowerPad()->SetTopMargin(0.);
    rp_Eff2->GetLowerPad()->SetGridy();
    rp_Eff2->GetUpperPad()->SetBottomMargin(0.);
    rp_Eff2->Draw();
    rp_Eff2->GetLowerRefGraph()->SetMaximum(1.01);
    rp_Eff2->GetLowerRefGraph()->SetMinimum(0.9);
    c1->Print(Form("Figs/Eff_MomDep_AboveThresholds_%d.pdf", run));
    c1->Print(Form("Figs/Eff_MomDep_AboveThresholds_%d.png", run));
    c1->Print(Form("Figs/Eff_MomDep_AboveThresholds_%d.root", run));

    
    TH1D *h_P_em_NotSoGood_em_TrgPassed1 = (TH1D*) file_in->Get("h_P_em_NotSoGood_em_TrgPassed1");
    h_P_em_NotSoGood_em_TrgPassed1->SetTitle("; P_{e^{-}} [GeV]");
    h_P_em_NotSoGood_em_TrgPassed1->SetLineColor(4);

    TH1D *h_P_em_NotSoGood_em1 = (TH1D*) file_in->Get("h_P_em_NotSoGood_em1");
    h_P_em_NotSoGood_em1->SetTitle("; P_{e^{-}} [GeV]");
    h_P_em_NotSoGood_em1->SetLineColor(1);
    h_P_em_NotSoGood_em_TrgPassed1->SetMaximum( 1.1*h_P_em_NotSoGood_em1->GetMaximum() );
    
    TRatioPlot *rp_Eff3 = new TRatioPlot(h_P_em_NotSoGood_em_TrgPassed1, h_P_em_NotSoGood_em1, "errasym");
    //rp_Eff3->
    rp_Eff3->Draw();
    rp_Eff3->GetUpperPad()->cd();
    h_P_em_Good_em1->Draw("Same");
    c1->Print(Form("Figs/Eff_MomDep_NoEtotCut_%d.pdf", run));
    c1->Print(Form("Figs/Eff_MomDep_NoEtotCut_%d.png", run));
    c1->Print(Form("Figs/Eff_MomDep_NoEtotCut_%d.root", run));
    
    
    return 0;
}


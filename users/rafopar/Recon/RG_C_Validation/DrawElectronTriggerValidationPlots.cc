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
int DrawElectronTriggerValidationPlots() {

    gStyle->SetOptStat(0);

    TF1 *f_lin1 = new TF1("f_lin1", "[0] + [1]*x", 0., 180.);

    TLine *line1 = new TLine();
    line1->SetLineColor(2);
    line1->SetLineWidth(3); 
    
    TCanvas *c1 = new TCanvas("c1", "", 950, 950);
    c1->SetTopMargin(0.02);
    c1->SetRightMargin(0.02);
    c1->SetLeftMargin(0.14);

    TFile *file_in = new TFile("Validate_Electron.root");

    TH2D *h_PCal_yxc1 = (TH2D*) file_in->Get("h_PCal_yxc1");
    h_PCal_yxc1->SetTitle("; PCal_X [cm]; PCal_Y [cm]");
    h_PCal_yxc1->SetMarkerColor(2);

    TH2D *h_PCal_yxc2 = (TH2D*) file_in->Get("h_PCal_yxc2");
    h_PCal_yxc2->SetTitle("; PCal_X [cm]; PCal_Y [cm]");
    h_PCal_yxc2->SetMarkerColor(4);
    h_PCal_yxc1->Draw();
    h_PCal_yxc2->Draw("Same");
    c1->Print("Figs/PCal_YX_Fiducial.pdf");
    c1->Print("Figs/PCal_YX_Fiducial.png");
    c1->Print("Figs/PCal_YX_Fiducial.root");

    TH2D *h_ECin_yxc1 = (TH2D*) file_in->Get("h_ECin_yxc1");
    h_ECin_yxc1->SetTitle("; ECin_X [cm]; ECin_Y [cm]");
    h_ECin_yxc1->SetMarkerColor(2);

    TH2D *h_ECin_yxc2 = (TH2D*) file_in->Get("h_ECin_yxc2");
    h_ECin_yxc2->SetTitle("; ECin_X [cm]; ECin_Y [cm]");
    h_ECin_yxc2->SetMarkerColor(4);
    h_ECin_yxc1->Draw();
    h_ECin_yxc2->Draw("Same");
    c1->Print("Figs/ECin_YX_Fiducial.pdf");
    c1->Print("Figs/ECin_YX_Fiducial.png");
    c1->Print("Figs/ECin_YX_Fiducial.root");

    TH2D *h_ECout_yxc1 = (TH2D*) file_in->Get("h_ECout_yxc1");
    h_ECout_yxc1->SetTitle("; ECout_X [cm]; ECout_Y [cm]");
    h_ECout_yxc1->SetMarkerColor(2);

    TH2D *h_ECout_yxc2 = (TH2D*) file_in->Get("h_ECout_yxc2");
    h_ECout_yxc2->SetTitle("; ECout_X [cm]; ECout_Y [cm]");
    h_ECout_yxc2->SetMarkerColor(4);
    h_ECout_yxc1->Draw();
    h_ECout_yxc2->Draw("Same");
    c1->Print("Figs/ECout_YX_Fiducial.pdf");
    c1->Print("Figs/ECout_YX_Fiducial.png");
    c1->Print("Figs/ECout_YX_Fiducial.root");

    TH2D *h_VTP_HTCC_times1 = (TH2D*) file_in->Get("h_VTP_HTCC_times1");
    h_VTP_HTCC_times1->SetTitle("; t_{HTCC} [ns]; t_{VTP} [4ns]");
    h_VTP_HTCC_times1->SetAxisRange(50., 200., "X");
    h_VTP_HTCC_times1->SetAxisRange(0., 105., "Y");
    h_VTP_HTCC_times1->Draw("colz");
    f_lin1->SetParameters(30., 0.25);
    f_lin1->DrawCopy("Same");
    f_lin1->SetParameters(60., 0.25);
    f_lin1->DrawCopy("Same");
    c1->Print("Figs/VTP_t_HTCC_t.pdf");
    c1->Print("Figs/VTP_t_HTCC_t.png");
    c1->Print("Figs/VTP_t_HTCC_t.root");

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
    rp_Eff1->GetLowerRefGraph()->SetMinimum(0.9);
    c1->Print("Figs/Eff_MomDep_WithThresholds.pdf");
    c1->Print("Figs/Eff_MomDep_WithThresholds.png");
    c1->Print("Figs/Eff_MomDep_WithThresholds.root");

    const double nphe_AboveThr = 3.;
    const double Etot_AboveThr = 0.35;
    TH2D *h_Etot_Nphe_Failed1 = (TH2D*)file_in->Get("h_Etot_Nphe_Failed1");
    h_Etot_Nphe_Failed1->SetTitle("; E_{Tot} [GeV]; Nphe");
    h_Etot_Nphe_Failed1->Draw("colz");
    line1->DrawLine(Etot_AboveThr, nphe_AboveThr, 1.5, nphe_AboveThr);
    line1->DrawLine(Etot_AboveThr, nphe_AboveThr, Etot_AboveThr, 20.5);
    c1->Print("Figs/Nphe_Etot_Failed.pdf");
    c1->Print("Figs/Nphe_Etot_Failed.png");
    c1->Print("Figs/Nphe_Etot_Failed.root");
    
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
    c1->Print("Figs/Eff_MomDep_AboveThresholds.pdf");
    c1->Print("Figs/Eff_MomDep_AboveThresholds.png");
    c1->Print("Figs/Eff_MomDep_AboveThresholds.root");

    
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
    c1->Print("Figs/Eff_MomDep_NoEtotCut.pdf");
    c1->Print("Figs/Eff_MomDep_NoEtotCut.png");
    c1->Print("Figs/Eff_MomDep_NoEtotCut.root");
    
    
    return 0;
}


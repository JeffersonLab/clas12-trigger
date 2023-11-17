/* 
 * File:   Compare_Q2_Plots.cc
 * Author: rafopar
 *
 * Created on October 21, 2023, 8:24 PM
 */

#include <cstdlib>

using namespace std;

/*
 * 
 */
void Compare_Q2_Plots(int run1, int run2) {

    double x, y;

    TCanvas *c1 = new TCanvas("c1", "", 950, 950);

    std::map<int, double> m_charge_Corr;
    m_charge_Corr[18497] = 1.;
    //m_charge_Corr[18497] = 0.7835;
    //m_charge_Corr[18508] = 1.;
    m_charge_Corr[18508] = 1.202;
    
    
    std::map<int, double> m_charge;
    // This is very not reliable way, but in the data stream the FCup charge is not reliable.
    // I skipped 1st 100K events of each run, marked timestamps of the 100K and 200K events,
    // Then using BPM calculated the everage current during this period (about 6 sec)
    m_charge[18497] = 52.6*5.78;  
    m_charge[18508] = 52.5*6.49;
    
    TFile *file_run1 = new TFile(Form("Validate_DC_Roads_WithTSBitsTorusOutbend_10p55_Run_%d.root", run1));
    TFile *file_run2 = new TFile(Form("Validate_DC_Roads_WithTSBitsTorusOutbend_10p55_Run_%d.root", run2));

    TH1D *h_Q2_Good_em1_run1 = (TH1D*) file_run1->Get("h_Q2_Good_em1");
    h_Q2_Good_em1_run1->SetTitle("; Q^{2} [GeV^{2}]");
    h_Q2_Good_em1_run1->SetLineColor(2);
    TH1D *h_Q2_passed_em1_run1 = (TH1D*) file_run1->Get("h_Q2_passed_em1");
    h_Q2_passed_em1_run1->SetTitle("; Q^{2} [GeV^{2}]");
    h_Q2_passed_em1_run1->SetLineColor(2);
    TH1D *h_Q2_HasTrgBit_em1_run1 = (TH1D*) file_run1->Get("h_Q2_HasTrgBit_em1");
    h_Q2_HasTrgBit_em1_run1->SetTitle("; Q^{2} [GeV^{2}]");
    h_Q2_HasTrgBit_em1_run1->SetLineColor(2);

    TGraph *gr_run1 = (TGraph*) file_run1->Get("gr_beamCharge");
    gr_run1->GetPoint(2, x, y);
    //double charge_run1 = y*m_charge_Corr[run1];
    double charge_run1 = m_charge[run1];

    h_Q2_Good_em1_run1->Scale(1. / charge_run1);
    h_Q2_passed_em1_run1->Scale(1. / charge_run1);
    h_Q2_HasTrgBit_em1_run1->Scale(1. / charge_run1);

    TH1D *h_Q2_Good_em1_run2 = (TH1D*) file_run2->Get("h_Q2_Good_em1");
    h_Q2_Good_em1_run2->SetTitle("; Q^{2} [GeV^{2}]");
    h_Q2_Good_em1_run2->SetLineColor(4);

    TH1D *h_Q2_passed_em1_run2 = (TH1D*) file_run2->Get("h_Q2_passed_em1");
    h_Q2_passed_em1_run2->SetTitle("; Q^{2} [GeV^{2}]");
    h_Q2_passed_em1_run2->SetLineColor(4);

    TH1D *h_Q2_HasTrgBit_em1_run2 = (TH1D*) file_run2->Get("h_Q2_HasTrgBit_em1");
    h_Q2_HasTrgBit_em1_run2->SetTitle("; Q^{2} [GeV^{2}]");
    h_Q2_HasTrgBit_em1_run2->SetLineColor(4);

    TGraph *gr_run2 = (TGraph*) file_run2->Get("gr_beamCharge");
    gr_run2->GetPoint(2, x, y);
    //double charge_run2 = y*m_charge_Corr[run2];
    double charge_run2 = m_charge[run2];

    h_Q2_Good_em1_run2->Scale(1. / charge_run2);
    h_Q2_passed_em1_run2->Scale(1. / charge_run2);
    h_Q2_HasTrgBit_em1_run2->Scale(1. / charge_run2);
    h_Q2_Good_em1_run1->Draw();
    h_Q2_Good_em1_run2->Draw("Same");

    TLatex *lat1 = new TLatex();
    lat1->SetNDC();

    TRatioPlot *rp_GoodQ2 = new TRatioPlot(h_Q2_Good_em1_run2, h_Q2_Good_em1_run1);
    rp_GoodQ2->Draw();
    rp_GoodQ2->GetLowerPad()->SetTopMargin(0);
    rp_GoodQ2->GetUpperPad()->SetBottomMargin(0);
    rp_GoodQ2->GetLowerRefGraph()->SetMaximum(2.2);
    rp_GoodQ2->GetLowerRefGraph()->SetMinimum(1.2);
    rp_GoodQ2->GetUpperPad()->cd();
    lat1->SetTextColor(h_Q2_Good_em1_run1->GetLineColor());
    lat1->DrawLatex(0.65, 0.7, Form("Run %d", run1));
    lat1->SetTextColor(h_Q2_Good_em1_run2->GetLineColor());
    lat1->DrawLatex(0.65, 0.6, Form("Run %d", run2));
    c1->Print(Form("Figs/Compare_Q2_good_em1_%d_%d.pdf", run1, run2));
    c1->Print(Form("Figs/Compare_Q2_good_em1_%d_%d.png", run1, run2));
    c1->Print(Form("Figs/Compare_Q2_good_em1_%d_%d.root", run1, run2));

    c1->Clear();

    TRatioPlot *rp_PassedQ2 = new TRatioPlot(h_Q2_passed_em1_run2, h_Q2_passed_em1_run1);
    rp_PassedQ2->Draw();
    rp_PassedQ2->GetLowerPad()->SetTopMargin(0);
    rp_PassedQ2->GetUpperPad()->SetBottomMargin(0);
    rp_PassedQ2->GetLowerRefGraph()->SetMaximum(2.2);
    rp_PassedQ2->GetLowerRefGraph()->SetMinimum(0.6);
    rp_PassedQ2->GetUpperPad()->cd();
    lat1->SetTextColor(h_Q2_Good_em1_run1->GetLineColor());
    lat1->DrawLatex(0.65, 0.7, Form("Run %d", run1));
    lat1->SetTextColor(h_Q2_Good_em1_run2->GetLineColor());
    lat1->DrawLatex(0.65, 0.6, Form("Run %d", run2));
    c1->Print(Form("Figs/Compare_Q2_Passed_em1_%d_%d.pdf", run1, run2));
    c1->Print(Form("Figs/Compare_Q2_Passed_em1_%d_%d.png", run1, run2));
    c1->Print(Form("Figs/Compare_Q2_Passed_em1_%d_%d.root", run1, run2));


    c1->Clear();

    TRatioPlot *rp_HasTrgBit = new TRatioPlot(h_Q2_HasTrgBit_em1_run2, h_Q2_HasTrgBit_em1_run1);
    rp_HasTrgBit->Draw();
    rp_HasTrgBit->GetLowerPad()->SetTopMargin(0);
    rp_HasTrgBit->GetUpperPad()->SetBottomMargin(0);
    rp_HasTrgBit->GetLowerRefGraph()->SetMaximum(1.6);
    rp_HasTrgBit->GetLowerRefGraph()->SetMinimum(0.6);
    rp_HasTrgBit->GetUpperPad()->cd();
    lat1->SetTextColor(h_Q2_HasTrgBit_em1_run1->GetLineColor());
    lat1->DrawLatex(0.65, 0.7, Form("Run %d", run1));
    lat1->SetTextColor(h_Q2_HasTrgBit_em1_run2->GetLineColor());
    lat1->DrawLatex(0.65, 0.6, Form("Run %d", run2));
    c1->Print(Form("Figs/Compare_Q2_HasTrgBit_em1_%d_%d.pdf", run1, run2));
    c1->Print(Form("Figs/Compare_Q2_HasTrgBit_em1_%d_%d.png", run1, run2));
    c1->Print(Form("Figs/Compare_Q2_HasTrgBit_em1_%d_%d.root", run1, run2));

    c1->Clear();
    TH2D *h_th_P_HasTrgBit_em1_run1 = (TH2D*) file_run1->Get("h_th_P_HasTrgBit_em1");
    h_th_P_HasTrgBit_em1_run1->SetTitle("; P [GeV]; #theta [deg]");
    h_th_P_HasTrgBit_em1_run1->Draw("colz");
    lat1->DrawLatex(0.5, 0.7, Form("Run %d", run1));
    c1->Print(Form("Figs/th_P_HasTrgBit_%d.pdf", run1));
    c1->Print(Form("Figs/th_P_HasTrgBit_%d.png", run1));
    c1->Print(Form("Figs/th_P_HasTrgBit_%d.root", run1));

    TH2D *h_th_P_HasTrgBit_em1_run2 = (TH2D*) file_run2->Get("h_th_P_HasTrgBit_em1");
    h_th_P_HasTrgBit_em1_run2->SetTitle("; P [GeV]; #theta [deg]");
    h_th_P_HasTrgBit_em1_run2->Draw("colz");
    lat1->DrawLatex(0.5, 0.7, Form("Run %d", run2));
    c1->Print(Form("Figs/th_P_HasTrgBit_%d.pdf", run2));
    c1->Print(Form("Figs/th_P_HasTrgBit_%d.png", run2));
    c1->Print(Form("Figs/th_P_HasTrgBit_%d.root", run2));
}


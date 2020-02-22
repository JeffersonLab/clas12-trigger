/* 
 * File:   DrawPlots.cc
 * Author: rafopar
 *
 * Created on February 21, 2020, 5:05 AM
 */

#include <cstdlib>

#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TLine.h>
#include <TCanvas.h>
#include <TRatioPlot.h>

using namespace std;

/*
 * 
 */
void DrawPlots() {

    const double t_VTPMax = 72.;
    const double t_VTPMin = 64.;
    const double t_HTCCMax = 98;
    const double t_HTCCMin = 82;
    const double vzMax = 20.;
    const double vzMin = -30.;

    TCanvas *c1 = new TCanvas("c1", "", 950, 950);

    TLine *line1 = new TLine();
    line1->SetLineColor(4);
    line1->SetLineWidth(4);

    TFile *file_in = new TFile("DC_Roads_check_BonusInbend.root", "Read");

    TH1D *h_tHTCC1 = (TH1D*) file_in->Get("h_tHTCC1");
    h_tHTCC1->SetTitle("; t_{HTCC} [ns]");

    c1->SetLogy();
    h_tHTCC1->SetAxisRange(45., 200., "X");
    h_tHTCC1->Draw();
    line1->DrawLine(t_HTCCMax, 0., t_HTCCMax, h_tHTCC1->GetMaximum());
    line1->DrawLine(t_HTCCMin, 0., t_HTCCMin, h_tHTCC1->GetMaximum());
    c1->Print("Figs/tHTCC1.eps");
    c1->Print("Figs/tHTCC1.pdf");
    c1->Print("Figs/tHTCC1.png");

    c1->SetLogy(0);

    TH2D *h_sec_vz_em1 = (TH2D*) file_in->Get("h_sec_vz_em1");
    h_sec_vz_em1->SetTitle("; vz [cm]; sector");
    h_sec_vz_em1->Draw("colz");
    line1->DrawLine(vzMax, -0.5, vzMax, 6.5);
    line1->DrawLine(vzMin, -0.5, vzMin, 6.5);
    c1->Print("Figs/Sev_Vz1.eps");
    c1->Print("Figs/Sev_Vz1.pdf");
    c1->Print("Figs/Sev_Vz1.png");

    TH1D *h_vz_Proj1 = (TH1D*) h_sec_vz_em1->ProjectionX("h_vz_Proj1", 2, 2);
    h_vz_Proj1->SetTitle("Sector 2; vz [mm]");
    h_vz_Proj1->Draw();
    line1->DrawLine(vzMax, 0., vzMax, h_vz_Proj1->GetMaximum());
    line1->DrawLine(vzMin, 0., vzMin, h_vz_Proj1->GetMaximum());
    c1->Print("Figs/vz_Sec2_1.eps");
    c1->Print("Figs/vz_Sec2_1.pdf");
    c1->Print("Figs/vz_Sec2_1.png");


    TH2D *h_sec_vz_em_RoadFail1 = (TH2D*) file_in->Get("h_sec_vz_em_RoadFail1");
    h_sec_vz_em_RoadFail1->SetTitle("; vz [cm]; sector");
    h_sec_vz_em_RoadFail1->Draw("colz");
    c1->Print("Figs/sec_vz_RoadFailed1.eps");
    c1->Print("Figs/sec_vz_RoadFailed1.pdf");
    c1->Print("Figs/sec_vz_RoadFailed1.png");

    c1->SetLogy();
    TH1D *h_vz_sec2to6_em = (TH1D*) h_sec_vz_em1->ProjectionX("h_vz_sec2to6_em", 2, 6);
    TH1D *h_v1_sec2to6_emRoadFailed = (TH1D*) h_sec_vz_em_RoadFail1->ProjectionX("h_vz_sec2to6_emRoadFailed", 2, 6);
    h_vz_sec2to6_em->SetMinimum(0.5);
    h_vz_sec2to6_em->SetTitle("Sectors 2-6; vz [cm]");
    h_vz_sec2to6_em->Draw();
    h_v1_sec2to6_emRoadFailed->SetLineColor(2);
    h_v1_sec2to6_emRoadFailed->SetFillColor(2);
    h_v1_sec2to6_emRoadFailed->Draw("Same");
    line1->DrawLine(vzMax, 0., vzMax, h_vz_sec2to6_em->GetMaximum());
    line1->DrawLine(vzMin, 0., vzMin, h_vz_sec2to6_em->GetMaximum());
    c1->Print("Figs/vz_sec2to6_AllAndFailed.eps");
    c1->Print("Figs/vz_sec2to6_AllAndFailed.pdf");
    c1->Print("Figs/vz_sec2to6_AllAndFailed.png");

    //c1->SetLogy(0);
    TH2D *h_Q2_sec1 = (TH2D*) file_in->Get("h_Q2_sec1");
    h_Q2_sec1->SetTitle("Sectors 2-6; Q^{2} [GeV^{2}]; sector");

    TH2D *h_Q2_sec_RoadFailed1 = (TH2D*) file_in->Get("h_Q2_sec_RoadFailed1");
    h_Q2_sec_RoadFailed1->SetTitle("Sectors 2-6; Q^{2} [GeV^{2}]; sector");

    TH1D *h_Q2_sec2to6 = (TH1D*) h_Q2_sec1->ProjectionX("h_Q2_sec2to6", 2, 6);
    TH1D *h_Q2_RoadFailed1 = (TH1D*) h_Q2_sec_RoadFailed1->ProjectionX("h_Q2_RoadFailed1", 2, 6);
    h_Q2_RoadFailed1->SetLineColor(2);
    h_Q2_RoadFailed1->SetFillColor(2);
    h_Q2_sec2to6->SetMinimum(0.5);
    h_Q2_sec2to6->Draw();
    h_Q2_RoadFailed1->Draw("Same");
    c1->Print("Figs/Q2_Sec2to6.eps");
    c1->Print("Figs/Q2_Sec2to6.pdf");
    c1->Print("Figs/Q2_Sec2to6.png");

    TH2D *h_th_P_em1 = (TH2D*) file_in->Get("h_th_P_em1");
    h_th_P_em1->SetTitle("; P [GeV]; #theta [deg]");

    c1->SetLogy(0);
    TH2D *h_th_P_em_RoadFailed1 = (TH2D*) file_in->Get("h_th_P_em_RoadFailed1");
    h_th_P_em_RoadFailed1->SetMarkerColor(2);
    h_th_P_em_RoadFailed1->SetMarkerStyle(2);
    h_th_P_em_RoadFailed1->SetMarkerSize(0.5);

    h_th_P_em1->Draw("colz");
    h_th_P_em_RoadFailed1->Draw("Same");
    c1->Print("Figs/th_P_Sec2to6.eps");
    c1->Print("Figs/th_P_Sec2to6.pdf");
    c1->Print("Figs/th_P_Sec2to6.png");


    TH1D *h_Pem1tmp = (TH1D*) h_th_P_em1->ProjectionX("h_Pem1tmp", 1, h_th_P_em1->GetNbinsY());
    TH1D *h_PemGood = (TH1D*) h_Pem1tmp->Rebin(5, "h_PemGood");

    TH1D *h_PemFailedtmp1 = (TH1D*) h_th_P_em_RoadFailed1->ProjectionX("h_PemFailedtmp1", 1, h_th_P_em_RoadFailed1->GetNbinsY());
    TH1D *h_PemFailed1 = (TH1D*) h_PemFailedtmp1->Rebin(5, "h_PemFailed1");
    h_PemFailed1->SetLineColor(2);
    h_PemFailed1->SetFillColor(2);

    c1->SetLogy();
    h_PemGood->SetMinimum(0.5);
    h_PemGood->Draw();
    h_PemFailed1->Draw("Same");
    c1->Print("Figs/P_em_Sec2to6.eps");
    c1->Print("Figs/P_em_Sec2to6.pdf");
    c1->Print("Figs/P_em_Sec2to6.png");

    c1->SetLogy(0);
    TH1D *h_PemWithTrg = (TH1D*) h_PemGood->Clone("h_PemWithTrg");
    h_PemWithTrg->Add(h_PemFailed1, -1);
    h_PemWithTrg->SetLineColor(95);

    TRatioPlot *rp_Pem = new TRatioPlot(h_PemWithTrg, h_PemGood, "errasym");
    rp_Pem->GetUpperPad()->SetBottomMargin(0);
    rp_Pem->GetLowerPad()->SetTopMargin(0);

    rp_Pem->Draw();
    rp_Pem->GetLowerRefGraph()->SetMaximum(1.001);
    rp_Pem->GetLowerRefGraph()->SetMinimum(0.992);
    c1->Update();
    c1->Print("Figs/RoadEff_Pem.eps");
    c1->Print("Figs/RoadEff_Pem.pdf");
    c1->Print("Figs/RoadEff_Pem.png");
}


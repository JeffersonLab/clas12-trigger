/* 
 * File:   Draw_DC_RoadValidate_2p2.cc
 * Author: rafopar
 *
 * Created on June 16, 2022, 10:24 AM
 */

#include <cstdlib>

using namespace std;

/*
 * 
 */
int Draw_DC_RoadValidate_2p2() {
    
    TCanvas *c1 = new TCanvas("c1", "", 950, 950);
    
    TFile file_in("Validate_DC_Roads_WithTSBits_2p1.root", "Read");
    
    TH2D *h_th_P_Allem2 = (TH2D*)file_in.Get("h_th_P_Allem2");
    h_th_P_Allem2->SetTitle("; P [GeV]; #theta [deg]");
    h_th_P_Allem2->Draw("colz");
    c1->Print("Figs/th_P_Ell_Elec_2p2GeV.pdf");
    c1->Print("Figs/th_P_Ell_Elec_2p2GeV.png");
    c1->Print("Figs/th_P_Ell_Elec_2p2GeV.root");

    TH2D *h_th_P_Missed3 = (TH2D*)file_in.Get("h_th_P_Missed3");
    h_th_P_Missed3->SetTitle("; P [GeV]; #theta [deg]");
    h_th_P_Missed3->Draw("colz");
    c1->Print("Figs/th_P_Ell_Elec_Missed_2p2GeV.pdf");
    c1->Print("Figs/th_P_Ell_Elec_Missed_2p2GeV.png");
    c1->Print("Figs/th_P_Ell_Elec_Missed_2p2GeV.root");

    TH1D *h_P_all_em2 = (TH1D*)h_th_P_Allem2->ProjectionX("h_P_all_em2", 1, h_th_P_Allem2->GetNbinsY() );
    h_P_all_em2->SetLineColor(4);
    h_P_all_em2->SetFillColor(4);

    TH1D *h_P_missed_em3 = (TH1D*)h_th_P_Missed3->ProjectionX("h_P_missed_em3", 1, h_th_P_Missed3->GetNbinsY() );
    h_P_missed_em3->SetLineColor(2);
    h_P_missed_em3->SetFillColor(2);
    
    TH1D *h_P_haveTrgBit_em_2 = (TH1D*)h_P_all_em2->Clone("h_P_haveTrgBit_em_2");
    h_P_haveTrgBit_em_2->SetLineColor(2);
    h_P_haveTrgBit_em_2->SetFillColor(2);
    h_P_haveTrgBit_em_2->Add(h_P_missed_em3, -1.);
    
    gStyle->SetOptStat(0);
    
    h_P_all_em2->Draw();
    h_P_haveTrgBit_em_2->Draw("Same");
    c1->Print("Figs/P_em_All_and_WithTrgBits.pdf");
    c1->Print("Figs/P_em_All_and_WithTrgBits.png");
    c1->Print("Figs/P_em_All_and_WithTrgBits.root");
    
    TRatioPlot *rp1 = new TRatioPlot( h_P_haveTrgBit_em_2, h_P_all_em2 );
    rp1->Draw();
    rp1->GetLowerRefGraph()->SetMaximum(1.05);
    c1->Print("Kuku.pdf");
    
    return 0;
}
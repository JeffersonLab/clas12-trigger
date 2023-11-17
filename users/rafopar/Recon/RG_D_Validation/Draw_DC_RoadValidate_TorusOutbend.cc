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
void Draw_DC_RoadValidate_TorusOutbend(int run) {

    TCanvas *c1 = new TCanvas("c1", "", 950, 950);

    TFile *file_in = new TFile(Form("Validate_DC_Roads_WithTSBitsTorusOutbend_10p55_Run_%d.root", run), "Read");

    TH2D *h_th_P_Allem2 = (TH2D*) file_in->Get("h_th_P_Allem2");
    h_th_P_Allem2->SetTitle("; P [GeV]; #theta [deg]");
    h_th_P_Allem2->Draw("colz");
    c1->Print(Form("Figs/th_P_All_Elec_TorusOutbend_%d.pdf", run));
    c1->Print(Form("Figs/th_P_All_Elec_TorusOutbend_%d.png", run));
    c1->Print(Form("Figs/th_P_All_Elec_TorusOutbend_%d.root", run));

    TH2D *h_th_P_Missed3 = (TH2D*) file_in->Get("h_th_P_Missed3");
    h_th_P_Missed3->SetTitle("; P [GeV]; #theta [deg]");
    h_th_P_Missed3->Draw("colz");
    c1->Print(Form("Figs/th_P_Ell_Elec_Missed_TorusOutbend_%d.pdf", run));
    c1->Print(Form("Figs/th_P_Ell_Elec_Missed_TorusOutbend_%d.png", run));
    c1->Print(Form("Figs/th_P_Ell_Elec_Missed_TorusOutbend_%d.root", run));

    TH1D *h_P_all_em2 = (TH1D*) h_th_P_Allem2->ProjectionX("h_P_all_em2", 1, h_th_P_Allem2->GetNbinsY());
    h_P_all_em2->SetLineColor(4);
    h_P_all_em2->SetFillColor(4);

    TH1D *h_P_missed_em3 = (TH1D*) h_th_P_Missed3->ProjectionX("h_P_missed_em3", 1, h_th_P_Missed3->GetNbinsY());
    h_P_missed_em3->SetLineColor(2);
    h_P_missed_em3->SetFillColor(2);

    TH1D *h_P_haveTrgBit_em_2 = (TH1D*) h_P_all_em2->Clone("h_P_haveTrgBit_em_2");
    h_P_haveTrgBit_em_2->SetLineColor(2);
    h_P_haveTrgBit_em_2->SetFillColor(2);
    h_P_haveTrgBit_em_2->Add(h_P_missed_em3, -1.);

    //gStyle->SetOptStat(0);

    h_P_all_em2->Draw();
    h_P_haveTrgBit_em_2->Draw("Same");
    c1->Print(Form("Figs/P_em_All_and_WithTrgBits_TorusOutBend_%d.pdf", run));
    c1->Print(Form("Figs/P_em_All_and_WithTrgBits_TorusOutBend_%d.png", run));
    c1->Print(Form("Figs/P_em_All_and_WithTrgBits_TorusOutBend_%d.root", run));

    TRatioPlot *rp1 = new TRatioPlot(h_P_haveTrgBit_em_2, h_P_all_em2, "asym");
    rp1->Draw();
    rp1->GetLowerRefGraph()->GetYaxis()->SetNdivisions(101);
    rp1->GetLowerRefGraph()->SetMaximum(1.01);
    rp1->GetLowerRefGraph()->SetMinimum(0.98);
    c1->Print(Form("Figs/em_Eff_vsMom_TorusOutBend_%d.pdf", run));
    c1->Print(Form("Figs/em_Eff_vsMom_TorusOutBend_%d.png", run));
    c1->Print(Form("Figs/em_Eff_vsMom_TorusOutBend_%d.root", run));

    TH2D *h_th_P_Allep2 = (TH2D*) file_in->Get("h_th_P_Allep2");
    h_th_P_Allep2->SetTitle("; P [GeV]; #theta [deg]");
    h_th_P_Allep2->Draw("colz");
    c1->Print(Form("Figs/th_P_All_ep_Torus_OutBend_%d.pdf", run));
    c1->Print(Form("Figs/th_P_All_ep_Torus_OutBend_%d.png", run));
    c1->Print(Form("Figs/th_P_All_ep_Torus_OutBend_%d.root", run));

    TH2D *h_th_P_Missed_ep3 = (TH2D*) file_in->Get("h_th_P_Missed_ep3");
    h_th_P_Missed_ep3->SetTitle("; P [GeV]; #theta [deg]");
    h_th_P_Missed_ep3->Draw("colz");
    c1->Print(Form("Figs/th_P_All_ep_Missed_Torus_Outbend_%d.pdf", run));
    c1->Print(Form("Figs/th_P_All_ep_Missed_Torus_Outbend_%d.png", run));
    c1->Print(Form("Figs/th_P_All_ep_Missed_Torus_Outbend_%d.root", run));

    TH1D *h_P_all_ep2 = (TH1D*) h_th_P_Allep2->ProjectionX("h_P_all_ep2", 1, h_th_P_Allep2->GetNbinsY());
    h_P_all_ep2->SetLineColor(4);
    h_P_all_ep2->SetFillColor(4);

    TH1D *h_P_missed_ep3 = (TH1D*) h_th_P_Missed_ep3->ProjectionX("h_P_missed_ep3", 1, h_th_P_Missed_ep3->GetNbinsY());
    h_P_missed_ep3->SetLineColor(2);
    h_P_missed_ep3->SetFillColor(2);

    TH1D *h_P_haveTrgBit_ep_2 = (TH1D*) h_P_all_ep2->Clone("h_P_haveTrgBit_ep_2");
    h_P_haveTrgBit_ep_2->SetLineColor(2);
    h_P_haveTrgBit_ep_2->SetFillColor(2);
    h_P_haveTrgBit_ep_2->Add(h_P_missed_ep3, -1.);

    h_P_all_ep2->Draw();
    h_P_haveTrgBit_ep_2->Draw("Same");
    c1->Print(Form("Figs/P_ep_All_and_WithTrgBits_Torus_OutBend_%d.pdf", run));
    c1->Print(Form("Figs/P_ep_All_and_WithTrgBits_Torus_OutBend_%d.png", run));
    c1->Print(Form("Figs/P_ep_All_and_WithTrgBits_Torus_OutBend_%d.root", run));

    TRatioPlot *rp_ep1 = new TRatioPlot(h_P_haveTrgBit_ep_2, h_P_all_ep2, "asym");
    rp_ep1->Draw();
    rp_ep1->GetLowerRefGraph()->GetYaxis()->SetNdivisions(101);
    rp_ep1->GetLowerRefGraph()->SetMaximum(1.01);
    rp_ep1->GetLowerRefGraph()->SetMinimum(0.98);
    c1->Print(Form("Figs/ep_Eff_vsMom_Torus_OutBend_%d.pdf", run));
    c1->Print(Form("Figs/ep_Eff_vsMom_Torus_OutBend_%d.png", run));
    c1->Print(Form("Figs/ep_Eff_vsMom_Torus_OutBend_%d.root", run));

    TH1D *h_Q2_Good_em1 = (TH1D*) file_in->Get("h_Q2_Good_em1");
    h_Q2_Good_em1->SetTitle("; Q^{2} [GeV^{2}]");
    h_Q2_Good_em1->SetLineColor(4);
    TH1D *h_Q2_passed_em1 = (TH1D*) file_in->Get("h_Q2_passed_em1");
    h_Q2_passed_em1->SetTitle("; Q^{2} [GeV^{2}]");
    h_Q2_passed_em1->SetLineColor(2);

    TLatex *lat1 = new TLatex();
    lat1->SetNDC();
    lat1->SetTextFont(42);

    TRatioPlot *rp_Q2_em1 = new TRatioPlot(h_Q2_passed_em1, h_Q2_Good_em1, "asym");
    rp_Q2_em1->Draw();
    rp_Q2_em1->GetLowerPad()->SetTopMargin(0);
    rp_Q2_em1->GetUpperPad()->SetBottomMargin(0);
    rp_Q2_em1->GetLowerPad()->SetGridx();
    rp_Q2_em1->GetLowerPad()->SetGridy();
    rp_Q2_em1->GetLowerRefGraph()->SetMaximum(1.001);
    rp_Q2_em1->GetLowerRefGraph()->SetMinimum(0.975);
    rp_Q2_em1->GetUpperPad()->SetLogy();
    rp_Q2_em1->GetUpperPad()->cd();
    lat1->SetTextColor(h_Q2_Good_em1->GetLineColor());
    lat1->DrawLatex(0.55, 0.7, "Good Electrons");
    lat1->SetTextColor(h_Q2_passed_em1->GetLineColor());
    lat1->DrawLatex(0.55, 0.6, "Has Q^{2} bit set ");
    c1->Print(Form("Figs/Q2_eff_em_TorusOutbend_%d.pdf", run));
    c1->Print(Form("Figs/Q2_eff_em_TorusOutbend_%d.png", run));
    c1->Print(Form("Figs/Q2_eff_em_TorusOutbend_%d.root", run));

//    TH2D *h_th_P_Allem2 = (TH2D*) file_in->Get("h_th_P_Allem2");
//    h_th_P_Allem2->SetTitle("; P [GeV]; #theta [deg]");
//    h_th_P_Allem2->Draw("colz");
//    c1->Print(Form("Figs/th_P_All_em_Torus_OutBend_%d.pdf", run));
//    c1->Print(Form("Figs/th_P_All_em_Torus_OutBend_%d.png", run));
//    c1->Print(Form("Figs/th_P_All_em_Torus_OutBend_%d.root", run));
//
//    TH2D *h_th_P_Missed_em3 = (TH2D*) file_in->Get("h_th_P_Missed_em3");
//    h_th_P_Missed_em3->SetTitle("; P [GeV]; #theta [deg]");
//    h_th_P_Missed_em3->Draw("colz");
//    c1->Print(Form("Figs/th_P_All_em_Missed_Torus_Outbend_%d.pdf", run));
//    c1->Print(Form("Figs/th_P_All_em_Missed_Torus_Outbend_%d.png", run));
//    c1->Print(Form("Figs/th_P_All_em_Missed_Torus_Outbend_%d.root", run));

}
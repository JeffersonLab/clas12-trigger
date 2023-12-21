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
int Draw_DC_RoadValidate_10p55(int run) {

    TCanvas *c1 = new TCanvas("c1", "", 950, 950);

    TFile *file_in = new TFile(Form("Validate_DC_Roads_Run_%d.root", run), "Read");
    //TFile file_in(Form("Validate_DC_Roads_Run_%d_bak.root", run), "Read");

    TH2D *h_th_P_Allem2 = (TH2D*) file_in->Get("h_th_P_Allem2");
    h_th_P_Allem2->SetTitle("; P [GeV]; #theta [deg]");
    h_th_P_Allem2->Draw("colz");
    c1->Print(Form("Figs/th_P_All_Elec_%d.pdf", run));
    c1->Print(Form("Figs/th_P_All_Elec_%d.png", run));
    c1->Print(Form("Figs/th_P_All_Elec_%d.root", run));

    TH2D *h_th_P_Missed3 = (TH2D*) file_in->Get("h_th_P_Missed3");
    h_th_P_Missed3->SetTitle("; P [GeV]; #theta [deg]");
    h_th_P_Missed3->Draw("colz");
    c1->Print(Form("Figs/th_P_Ell_Elec_Missed_%d.pdf", run));
    c1->Print(Form("Figs/th_P_Ell_Elec_Missed_%d.png", run));
    c1->Print(Form("Figs/th_P_Ell_Elec_Missed_%d.root", run));

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
    c1->Print(Form("Figs/P_em_All_and_WithTrgBits_%d.pdf", run));
    c1->Print(Form("Figs/P_em_All_and_WithTrgBits_%d.png", run));
    c1->Print(Form("Figs/P_em_All_and_WithTrgBits_%d.root", run));

    TRatioPlot *rp1 = new TRatioPlot(h_P_haveTrgBit_em_2, h_P_all_em2, "asym");
    rp1->Draw();
    rp1->GetLowerRefGraph()->GetYaxis()->SetNdivisions(101);
    rp1->GetLowerRefGraph()->SetMaximum(1.01);
    rp1->GetLowerRefGraph()->SetMinimum(0.98);
    c1->Print(Form("Figs/em_Eff_vsMom_%d.pdf", run));
    c1->Print(Form("Figs/em_Eff_vsMom_%d.png", run));
    c1->Print(Form("Figs/em_Eff_vsMom_%d.root", run));

    TH2D *h_th_P_Allep2 = (TH2D*) file_in->Get("h_th_P_Allep2");
    h_th_P_Allep2->SetTitle("; P [GeV]; #theta [deg]");
    h_th_P_Allep2->Draw("colz");
    c1->Print(Form("Figs/th_P_All_ep_%d.pdf", run));
    c1->Print(Form("Figs/th_P_All_ep_%d.png", run));
    c1->Print(Form("Figs/th_P_All_ep_%d.root", run));

    TH2D *h_th_P_Missed_ep3 = (TH2D*) file_in->Get("h_th_P_Missed_ep3");
    h_th_P_Missed_ep3->SetTitle("; P [GeV]; #theta [deg]");
    h_th_P_Missed_ep3->Draw("colz");
    c1->Print(Form("Figs/th_P_All_ep_Missed_%d.pdf", run));
    c1->Print(Form("Figs/th_P_All_ep_Missed_%d.png", run));
    c1->Print(Form("Figs/th_P_All_ep_Missed_%d.root", run));

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
    c1->Print(Form("Figs/P_ep_All_and_WithTrgBits_%d.pdf", run));
    c1->Print(Form("Figs/P_ep_All_and_WithTrgBits_%d.pdf", run));
    c1->Print(Form("Figs/P_ep_All_and_WithTrgBits_%d.pdf", run));

    TRatioPlot *rp_ep1 = new TRatioPlot(h_P_haveTrgBit_ep_2, h_P_all_ep2, "asym");
    rp_ep1->Draw();
    rp_ep1->GetLowerRefGraph()->GetYaxis()->SetNdivisions(101);
    rp_ep1->GetLowerRefGraph()->SetMaximum(1.01);
    rp_ep1->GetLowerRefGraph()->SetMinimum(0.98);
    c1->Print(Form("Figs/ep_Eff_vsMom_%d.pdf", run));
    c1->Print(Form("Figs/ep_Eff_vsMom_%d.png", run));
    c1->Print(Form("Figs/ep_Eff_vsMom_%d.root", run));


    const int n_Ecuts = 4;

    TH1D * h_p_em[n_Ecuts];
    TH1D * h_W[n_Ecuts];
    TH1D * h_xB[n_Ecuts];
    TH1D * h_Q2_[n_Ecuts];

    TCanvas *c_P = new TCanvas("c_P", "", 950, 950);
    c_P->SetTopMargin(0.02);
    c_P->SetRightMargin(0.02);

    TCanvas *c_W = new TCanvas("c_W", "", 950, 950);
    c_W->SetTopMargin(0.02);
    c_W->SetRightMargin(0.02);

    TCanvas *c_xB = new TCanvas("c_xB", "", 950, 950);
    c_xB->SetTopMargin(0.02);
    c_xB->SetRightMargin(0.02);

    TCanvas *c_Q2 = new TCanvas("c_Q2", "", 950, 950);
    c_Q2->SetTopMargin(0.02);
    c_Q2->SetRightMargin(0.02);

    TLatex *lat1 = new TLatex();
    lat1->SetNDC();
    lat1->SetTextFont(42);

    const int cols[n_Ecuts] = {1, 2, 4, 6};
    const double Ecuts[n_Ecuts] = {150, 200, 300, 400};

    for (int i = 0; i < n_Ecuts; i++) {
        h_p_em[i] = (TH1D*) file_in->Get(Form("h_p_em%d", i));
        h_p_em[i]->SetTitle("; P [GeV]");
        h_p_em[i]->SetLineColor(cols[i]);
        h_p_em[i]->SetFillColor(cols[i]);

        c_P->cd();

        i == 0 ? h_p_em[i]->Draw() : h_p_em[i]->Draw("Same");
        lat1->SetTextColor(cols[i]);
        lat1->DrawLatex(0.35, 0.92 - 0.05 * i, Form("E > %1.1f MeV", Ecuts[i]));

        c_W->cd();
        h_W[i] = (TH1D*) file_in->Get(Form("h_W%d", i));
        h_W[i]->SetTitle("; W [GeV]");
        h_W[i]->SetLineColor(cols[i]);
        h_W[i]->SetFillColor(cols[i]);
        i == 0 ? h_W[i]->Draw() : h_W[i]->Draw("Same");
        lat1->DrawLatex(0.35, 0.92 - 0.05 * i, Form("E > %1.1f MeV", Ecuts[i]));

        c_xB->cd();
        h_xB[i] = (TH1D*) file_in->Get(Form("h_xB%d", i));
        h_xB[i]->SetTitle("; xB");
        h_xB[i]->SetLineColor(cols[i]);
        h_xB[i]->SetFillColor(cols[i]);
        i == 0 ? h_xB[i]->Draw() : h_xB[i]->Draw("Same");
        lat1->DrawLatex(0.35, 0.92 - 0.05 * i, Form("E > %1.1f MeV", Ecuts[i]));

        c_Q2->cd();
        h_Q2_[i] = (TH1D*) file_in->Get(Form("h_Q2_%d", i));
        h_Q2_[i]->SetTitle("; Q^{2} [GeV^{2}]");
        h_Q2_[i]->SetLineColor(cols[i]);
        h_Q2_[i]->SetFillColor(cols[i]);
        i == 0 ? h_Q2_[i]->Draw() : h_Q2_[i]->Draw("Same");
        lat1->DrawLatex(0.35, 0.92 - 0.05 * i, Form("E > %1.1f MeV", Ecuts[i]));

    }

    c_P->Print(Form("Figs/P_energy_cuts_%d.pdf", run));
    c_P->Print(Form("Figs/P_energy_cuts_%d.png", run));
    c_P->Print(Form("Figs/P_energy_cuts_%d.root", run));

    c_W->Print(Form("Figs/W_energy_cuts_%d.pdf", run));
    c_W->Print(Form("Figs/W_energy_cuts_%d.png", run));
    c_W->Print(Form("Figs/W_energy_cuts_%d.root", run));

    c_xB->Print(Form("Figs/xB_energy_cuts_%d.pdf", run));
    c_xB->Print(Form("Figs/xB_energy_cuts_%d.png", run));
    c_xB->Print(Form("Figs/xB_energy_cuts_%d.root", run));

    c_Q2->Print(Form("Figs/Q2_energy_cuts_%d.pdf", run));
    c_Q2->Print(Form("Figs/Q2_energy_cuts_%d.png", run));
    c_Q2->Print(Form("Figs/Q2_energy_cuts_%d.root", run));
    
    return 0;
}
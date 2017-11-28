#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TCanvas.h>

void Draw_VTP_hists(){

  gStyle->SetHistFillColor(4);
  gStyle->SetOptStat(0);
  
  gROOT->ForceStyle();
    
  TCanvas *c1 = new TCanvas("c1", "", 750, 750);

  TFile *file_in = new TFile("VTP_out.root", "Read");

  TH1D *h_HTCC_time1 = (TH1D*)file_in->Get("h_HTCC_time1");
  h_HTCC_time1->Draw();
  h_HTCC_time1->SetTitle("; HTCC mask time");
  c1->Print("figs/HTCC_time1.eps");
  c1->Print("figs/HTCC_time1.pdf");
  c1->Print("figs/HTCC_time1.png");

  TH1D *h_n_HTCC_masks = (TH1D*)file_in->Get("h_n_HTCC_masks");
  h_n_HTCC_masks->SetTitle("; # of HTCC masks/per event");
  h_n_HTCC_masks->Draw();
  c1->Print("figs/n_HTCC_masks.eps");
  c1->Print("figs/n_HTCC_masks.pdf");
  c1->Print("figs/n_HTCC_masks.png");

  TH1D *h_n_HTCC_hits = (TH1D*)file_in->Get("h_n_HTCC_hits");
  h_n_HTCC_hits->SetTitle("; # of HTCC hits per event");
  h_n_HTCC_hits->Draw();
  c1->Print("figs/n_HTCC_hits.eps");
  c1->Print("figs/n_HTCC_hits.pdf");
  c1->Print("figs/n_HTCC_hits.png");

  TH1D *h_HTCC_hit_chan1 = (TH1D*)file_in->Get("h_HTCC_hit_chan1");
  h_HTCC_hit_chan1->SetTitle("; HTCC mask bite index");
  h_HTCC_hit_chan1->Draw();
  c1->Print("figs/HTCC_hits.eps");
  c1->Print("figs/HTCC_hits.pdf");
  c1->Print("figs/HTCC_hits.png");

  // ======= FTOF ======
  
  TH2D *h_FTOF_time1 = (TH2D*)file_in->Get("h_FTOF_time1");
  h_FTOF_time1->Draw("colz");
  h_FTOF_time1->SetTitle("; FTOF mask time; sector");
  c1->Print("figs/FTOF_time1.eps");
  c1->Print("figs/FTOF_time1.pdf");
  c1->Print("figs/FTOF_time1.png");

  TH2D *h_n_FTOF_masks = (TH2D*)file_in->Get("h_n_FTOF_masks");
  h_n_FTOF_masks->SetTitle("; # of FTOF masks/per event; sector");
  h_n_FTOF_masks->Draw("colz");
  c1->Print("figs/n_FTOF_masks.eps");
  c1->Print("figs/n_FTOF_masks.pdf");
  c1->Print("figs/n_FTOF_masks.png");

  TH2D *h_n_FTOF_hits = (TH2D*)file_in->Get("h_n_FTOF_hits");
  h_n_FTOF_hits->SetTitle("; # of FTOF hits per event; sector");
  h_n_FTOF_hits->Draw("colz");
  c1->Print("figs/n_FTOF_hits.eps");
  c1->Print("figs/n_FTOF_hits.pdf");
  c1->Print("figs/n_FTOF_hits.png");

  TH2D *h_FTOF_hit_chan1 = (TH2D*)file_in->Get("h_FTOF_hit_chan1");
  h_FTOF_hit_chan1->SetTitle("; FTOF mask bite index; sector");
  h_FTOF_hit_chan1->Draw("colz");
  c1->Print("figs/FTOF_hits.eps");
  c1->Print("figs/FTOF_hits.pdf");
  c1->Print("figs/FTOF_hits.png");

  // === EC and PCal
  
  const int n_view = 3;

  TH2D *h_N_ECpeaks1_[n_view];
  TH2D *h_t_ECpeak1_[n_view];
  TH2D *h_coord_ECpeak1_[n_view];
  TH2D *h_ECcl_U[n_view];

  TH2D *h_N_PCalpeaks1_[n_view];
  TH2D *h_t_PCalpeak1_[n_view];
  TH2D *h_coord_PCalpeak1_[n_view];
  TH2D *h_PCalcl_U[n_view];

  
  std::string view_name[n_view] = {"U", "V", "W"};
  
  for( int i_view = 0; i_view < n_view; i_view++ ){

    h_N_ECpeaks1_[i_view] = (TH2D*)file_in->Get(Form("h_N_ECpeaks1_%d", i_view));
    h_N_ECpeaks1_[i_view]->SetTitle(Form("; # of EC %s peaks; sector", view_name[i_view].c_str()));
    h_N_ECpeaks1_[i_view]->Draw("colz");
    c1->Print(Form("figs/EC_N_%s_peaks.eps", view_name[i_view].c_str()));
    c1->Print(Form("figs/EC_N_%s_peaks.pdf", view_name[i_view].c_str()));
    c1->Print(Form("figs/EC_N_%s_peaks.png", view_name[i_view].c_str()));

    h_t_ECpeak1_[i_view] = (TH2D*)file_in->Get(Form("h_t_ECpeak1_%d", i_view));
    h_t_ECpeak1_[i_view]->SetTitle(Form("; time EC %s peak /32ns ; sector", view_name[i_view].c_str()));
    h_t_ECpeak1_[i_view]->Draw("colz");
    c1->Print(Form("figs/EC_t_%s_peak.eps", view_name[i_view].c_str()));
    c1->Print(Form("figs/EC_t_%s_peak.pdf", view_name[i_view].c_str()));
    c1->Print(Form("figs/EC_t_%s_peak.png", view_name[i_view].c_str()));

    h_coord_ECpeak1_[i_view] = (TH2D*)file_in->Get(Form("h_coord_ECpeak1_%d", i_view));
    h_coord_ECpeak1_[i_view]->SetTitle(Form("; Strip number of EC %s peak ; sector", view_name[i_view].c_str()));
    h_coord_ECpeak1_[i_view]->Draw("colz");
    c1->Print(Form("figs/EC_coord_%s_peak.eps", view_name[i_view].c_str()));
    c1->Print(Form("figs/EC_coord_%s_peak.pdf", view_name[i_view].c_str()));
    c1->Print(Form("figs/EC_coord_%s_peak.png", view_name[i_view].c_str()));

    h_ECcl_U[i_view] = (TH2D*)file_in->Get(Form("h_ECcl_%s1", view_name[i_view].c_str()));
    h_ECcl_U[i_view]->SetTitle(Form("; Strip number of EC %s cluster; sector", view_name[i_view].c_str()));
    h_ECcl_U[i_view]->Draw("colz");
    c1->Print(Form("figs/EC_coord_%s_clust.eps", view_name[i_view].c_str()));
    c1->Print(Form("figs/EC_coord_%s_clust.pdf", view_name[i_view].c_str()));
    c1->Print(Form("figs/EC_coord_%s_clust.png", view_name[i_view].c_str()));

    h_N_PCalpeaks1_[i_view] = (TH2D*)file_in->Get(Form("h_N_PCalpeaks1_%d", i_view));
    h_N_PCalpeaks1_[i_view]->SetTitle(Form("; # of PCal %s peaks; sector", view_name[i_view].c_str()));
    h_N_PCalpeaks1_[i_view]->Draw("colz");
    c1->Print(Form("figs/PCal_N_%s_peaks.eps", view_name[i_view].c_str()));
    c1->Print(Form("figs/PCal_N_%s_peaks.pdf", view_name[i_view].c_str()));
    c1->Print(Form("figs/PCal_N_%s_peaks.png", view_name[i_view].c_str()));

    h_t_PCalpeak1_[i_view] = (TH2D*)file_in->Get(Form("h_t_PCalpeak1_%d", i_view));
    h_t_PCalpeak1_[i_view]->SetTitle(Form("; time of PCal %s peak/32 ns; sector", view_name[i_view].c_str()));
    h_t_PCalpeak1_[i_view]->Draw("colz");
    c1->Print(Form("figs/PCal_t_%s_peak.eps", view_name[i_view].c_str()));
    c1->Print(Form("figs/PCal_t_%s_peak.pdf", view_name[i_view].c_str()));
    c1->Print(Form("figs/PCal_t_%s_peak.png", view_name[i_view].c_str()));

    h_coord_PCalpeak1_[i_view] = (TH2D*)file_in->Get(Form("h_coord_PCalpeak1_%d", i_view));
    h_coord_PCalpeak1_[i_view]->SetTitle(Form("; Strip number of PCal %s peak; sector", view_name[i_view].c_str()));
    h_coord_PCalpeak1_[i_view]->Draw("colz");
    c1->Print(Form("figs/PCal_coord_%s_peak.eps", view_name[i_view].c_str()));
    c1->Print(Form("figs/PCal_coord_%s_peak.pdf", view_name[i_view].c_str()));
    c1->Print(Form("figs/PCal_coord_%s_peak.png", view_name[i_view].c_str()));

    h_PCalcl_U[i_view] = (TH2D*)file_in->Get(Form("h_PCalcl_%s1", view_name[i_view].c_str()));
    h_PCalcl_U[i_view]->SetTitle(Form("; Strip number of PCal %s cluster; sector", view_name[i_view].c_str()));
    h_PCalcl_U[i_view]->Draw("colz");
    c1->Print(Form("figs/PCal_coord_%s_clust.eps", view_name[i_view].c_str()));
    c1->Print(Form("figs/PCal_coord_%s_clust.pdf", view_name[i_view].c_str()));
    c1->Print(Form("figs/PCal_coord_%s_clust.png", view_name[i_view].c_str()));
    
  }

  TH2D *h_N_ECClust1 = (TH2D*)file_in->Get("h_N_ECClust1");
  h_N_ECClust1->SetTitle("; # of EC clusters; sector");
  h_N_ECClust1->Draw("colz");
  c1->Print("figs/N_ECClust1.eps");
  c1->Print("figs/N_ECClust1.pdf");
  c1->Print("figs/N_ECClust1.png");

  TH2D *h_ECcl_t1 = (TH2D*)file_in->Get("h_ECcl_t1");
  h_ECcl_t1->SetTitle("; cluster time/32 ns; sector");
  h_ECcl_t1->Draw("colz");
  c1->Print("figs/EC_t_clust.eps");
  c1->Print("figs/EC_t_clust.pdf");
  c1->Print("figs/EC_t_clust.png");

  TH2D *h_ECcl_E1 = (TH2D*)file_in->Get("h_ECcl_E1");
  h_ECcl_E1->SetTitle("; cluster Energy [ADC units]; sector");
  h_ECcl_E1->Draw("colz");
  c1->Print("figs/EC_cl_E.eps");
  c1->Print("figs/EC_cl_E.pdf");
  c1->Print("figs/EC_cl_E.png");

  TH1D *h_Proj_ECEcl_sec1 = (TH1D*)h_ECcl_E1->ProjectionX("h_Proj_ECEcl_sec1", 1, 1);
  h_Proj_ECEcl_sec1->SetTitle("Sector 1; ADC");
  h_Proj_ECEcl_sec1->Draw();
  c1->Print("figs/Proj_ECEcl_sec1.eps");
  c1->Print("figs/Proj_ECEcl_sec1.pdf");
  c1->Print("figs/Proj_ECEcl_sec1.png");
  
  TH1D *h_Proj_ECEcl_sec5 = (TH1D*)h_ECcl_E1->ProjectionX("h_Proj_ECEcl_sec5", 5, 5);
  h_Proj_ECEcl_sec5->SetTitle("Sector 5; ADC");
  h_Proj_ECEcl_sec5->Draw();
  c1->Print("figs/Proj_ECEcl_sec5.eps");
  c1->Print("figs/Proj_ECEcl_sec5.pdf");
  c1->Print("figs/Proj_ECEcl_sec5.png");

  TH2D *h_N_PCalClust1 = (TH2D*)file_in->Get("h_N_PCalClust1");
  h_N_PCalClust1->SetTitle("; # of PCal clusters; sector");
  h_N_PCalClust1->Draw("colz");
  c1->Print("figs/N_PCalClust1.eps");
  c1->Print("figs/N_PCalClust1.pdf");
  c1->Print("figs/N_PCalClust1.png");

  TH2D *h_PCalcl_t1 = (TH2D*)file_in->Get("h_PCalcl_t1");
  h_PCalcl_t1->SetTitle("; cluster time/32 ns; sector");
  h_PCalcl_t1->Draw("colz");
  c1->Print("figs/PCal_t_clust.eps");
  c1->Print("figs/PCal_t_clust.pdf");
  c1->Print("figs/PCal_t_clust.png");

  TH2D *h_PCalcl_E1 = (TH2D*)file_in->Get("h_PCalcl_E1");
  h_PCalcl_E1->SetTitle("; cluster Energy [ADC units]; sector");
  h_PCalcl_E1->Draw("colz");
  c1->Print("figs/PCal_cl_E.eps");
  c1->Print("figs/PCal_cl_E.pdf");
  c1->Print("figs/PCal_cl_E.png");

  c1->SetLeftMargin(0.14);
  TH2D *h_EC_yxc1 = (TH2D*)file_in->Get("h_EC_yxc1");
  h_EC_yxc1->SetTitle("Coordinates calculated using the cluster U,V and W; X [cm]; Y [cm]");
  h_EC_yxc1->Draw("colz");
  c1->Print("figs/EC_yxc1.eps");
  c1->Print("figs/EC_yxc1.pdf");
  c1->Print("figs/EC_yxc1.png");
  
  TH2D *h_EC_yxc_UV1 = (TH2D*)file_in->Get("h_EC_yxc_UV1");
  h_EC_yxc_UV1->SetTitle("Coordinates calculated using U and V peaks; X [cm]; Y [cm]");
  h_EC_yxc_UV1->Draw("colz");
  c1->Print("figs/EC_yxc_UV1.eps");
  c1->Print("figs/EC_yxc_UV1.pdf");
  c1->Print("figs/EC_yxc_UV1.png");

  TH2D *h_EC_yxc_UW1 = (TH2D*)file_in->Get("h_EC_yxc_UW1");
  h_EC_yxc_UW1->SetTitle("Coordinates calculated using U and W peaks; X [cm]; Y [cm]");
  h_EC_yxc_UW1->Draw("colz");
  c1->Print("figs/EC_yxc_UW1.eps");
  c1->Print("figs/EC_yxc_UW1.pdf");
  c1->Print("figs/EC_yxc_UW1.png");

  TH2D *h_EC_yxc_VW1 = (TH2D*)file_in->Get("h_EC_yxc_VW1");
  h_EC_yxc_VW1->SetTitle("Coordinates calculated using V and W peaks; X [cm]; Y [cm]");
  h_EC_yxc_VW1->Draw("colz");
  c1->Print("figs/EC_yxc_VW1.eps");
  c1->Print("figs/EC_yxc_VW1.pdf");
  c1->Print("figs/EC_yxc_VW1.png");

  TH2D *h_Dalitz_cl1 = (TH2D*)file_in->Get("h_Dalitz_cl1");
  h_Dalitz_cl1->SetTitle("Dalitz calculated using cluster coordiantes; Dalitz; Sector");
  h_Dalitz_cl1->GetXaxis()->SetTitleOffset(1.7);
  h_Dalitz_cl1->Draw("lego5");
  c1->Print("figs/EC_Dalitz_cl1.eps");
  c1->Print("figs/EC_Dalitz_cl1.pdf");
  c1->Print("figs/EC_Dalitz_cl1.png");

  c1->Clear();

  for( int i = 0; i < 6; i++ ){
    TH1D *h_proj = (TH1D*)h_Dalitz_cl1->ProjectionX(Form("h_Dalitz_cl1_proj_%d", i), i+1, i+1);
    h_proj->SetLineColor(i+1);
    h_proj->SetLineWidth(2);
    h_proj->SetFillStyle(0);
    if( i == 0 ){
      h_proj->SetAxisRange(0., 1.15*h_Dalitz_cl1->GetMaximum(), "Y");
      h_proj->DrawCopy();
    } else{
      
      h_proj->DrawCopy("Same");
    }
  }
  c1->Print("figs/EC_Dalitz_cl1_Projections.eps");
  c1->Print("figs/EC_Dalitz_cl1_Projections.pdf");
  c1->Print("figs/EC_Dalitz_cl1_Projections.png");

  TH2D *h_Dalitz_Peaks1 = (TH2D*)file_in->Get("h_Dalitz_Peaks1");
  h_Dalitz_Peaks1->SetTitle("Dalitz calculated using independent U, V and W peaks; Dalitz; Sector");
  h_Dalitz_Peaks1->GetXaxis()->SetTitleOffset(1.7);
  h_Dalitz_Peaks1->Draw("lego5");
  c1->Print("figs/EC_Dalitz_peaka1.eps");
  c1->Print("figs/EC_Dalitz_peaka1.pdf");
  c1->Print("figs/EC_Dalitz_peaka1.png");

                                                    
  TH2D *h_PCal_Dalitz_Clust1 = (TH2D*)file_in->Get("h_PCal_Dalitz_Clust1");
  h_PCal_Dalitz_Clust1->SetTitle("Dalitz calculated using cluster coordiantes; Dalitz; Sector");
  h_PCal_Dalitz_Clust1->GetXaxis()->SetTitleOffset(1.7);
  h_PCal_Dalitz_Clust1->Draw("lego5");
  c1->Print("figs/PCal_Dalitz_cl1.eps");
  c1->Print("figs/PCal_Dalitz_cl1.pdf");
  c1->Print("figs/PCal_Dalitz_cl1.png");
  
  TH2D *h_PCal_Dalitz_Peaks1 = (TH2D*)file_in->Get("h_PCal_Dalitz_Peaks1");
  h_PCal_Dalitz_Peaks1->SetTitle("Dalitz calculated using independent U, V and W peaks; Dalitz; Sector");
  h_PCal_Dalitz_Peaks1->GetXaxis()->SetTitleOffset(1.7);
  h_PCal_Dalitz_Peaks1->Draw("lego5");
  c1->Print("figs/PCal_Dalitz_peaks1.eps");
  c1->Print("figs/PCal_Dalitz_peaks1.pdf");
  c1->Print("figs/PCal_Dalitz_peaks1.png");

  
  TH2D *h_PCal_yxc1 = (TH2D*)file_in->Get("h_PCal_yxc1");
  h_PCal_yxc1->SetTitle("Coordinates calculated using the cluster U,V and W; X [cm]; Y [cm]");
  h_PCal_yxc1->Draw("colz");
  c1->Print("figs/PCal_yxc1.eps");
  c1->Print("figs/PCal_yxc1.pdf");
  c1->Print("figs/PCal_yxc1.png");
  
  TH2D *h_PCal_yxc_UV1 = (TH2D*)file_in->Get("h_PCal_yxc_UV1");
  h_PCal_yxc_UV1->SetTitle("Coordinates calculated using U and V peaks; X [cm]; Y [cm]");
  h_PCal_yxc_UV1->Draw("colz");
  c1->Print("figs/PCal_yxc_UV1.eps");
  c1->Print("figs/PCal_yxc_UV1.pdf");
  c1->Print("figs/PCal_yxc_UV1.png");

  TH2D *h_PCal_yxc_UW1 = (TH2D*)file_in->Get("h_PCal_yxc_UW1");
  h_PCal_yxc_UW1->SetTitle("Coordinates calculated using U and W peaks; X [cm]; Y [cm]");
  h_PCal_yxc_UW1->Draw("colz");
  c1->Print("figs/PCal_yxc_UW1.eps");
  c1->Print("figs/PCal_yxc_UW1.pdf");
  c1->Print("figs/PCal_yxc_UW1.png");

  TH2D *h_PCal_yxc_VW1 = (TH2D*)file_in->Get("h_PCal_yxc_VW1");
  h_PCal_yxc_VW1->SetTitle("Coordinates calculated using V and W peaks; X [cm]; Y [cm]");
  h_PCal_yxc_VW1->Draw("colz");
  c1->Print("figs/PCal_yxc_VW1.eps");
  c1->Print("figs/PCal_yxc_VW1.pdf");
  c1->Print("figs/PCal_yxc_VW1.png");

}

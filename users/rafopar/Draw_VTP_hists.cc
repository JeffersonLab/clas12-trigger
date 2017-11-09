#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TCanvas.h>

void Draw_VTP_hists(){

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

}

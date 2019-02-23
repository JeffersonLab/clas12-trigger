#ifndef STAGE1_STUDY_H
#define STAGE1_STUDY_H

#define stage1_study_cxx
#include "stage1_study.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>

#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_stream.h>

#include <VTPRoot.hh>

#include <vector>
#include <iostream>

using namespace std;


void stage1_study::Loop()
{
//   In a ROOT session, you can do:
//      root> .L stage1_study.C
//      root> stage1_study t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

    const double Mp = 0.9383;
    const double r2d = 57.295780;
    const int HTCC_TYPE = 15;
    const int DET_FTOF = 12;
    const int layer_FTOF1b = 2;
    const int VTP_TrigTag = 29; // 11101
    const int n_max_npart = 30;
    const int n_sect = 6;


    const int Muon_1stbit = 7;
    const int vtp_cl_tmax = 8;
    const int vtp_cl_tmin = 7;

    double vz_min_[n_sect] = {-12., -12., -12., -18., -12, -12};
    double vz_max_[n_sect] = {4., 4., 4., 2., -5., 6.};


    const double chi2pid_MIN = -100.;
    const double chi2pid_MAX = 40.;

    const double E_PCal_MIN = 0.01; // in GeV ftom rgb_v6.trg
    const double E_PCal_MAX = 0.06; // in GeV ftom rgb_v6.trg
    const double E_EC_MIN = 0.04; // in GeV ftom rgb_v6.trg
    const double E_EC_MAX = 0.12; // in GeV ftom rgb_v6.trg

    const double trg_PCal_MIN = 0.01;
    const double trg_PCal_MAX = 0.12;
    const double trg_EC_MIN = 0.04;
    const double trg_EC_MAX = 0.12;
   
    const int PCAL_Emaxcuts_test_points = 4;
    const double trg_PCal_EMax_cuts_[4] = {0.1, 0.125, 0.15, 0.175};
    

    TFile *file_out = new TFile(Form("stage1_study_%d.root", frun), "Recreate");

    TH2D *h_vz_sec1 = new TH2D("h_vz_sec1", "", 200, -20., 20., 7, -0.5, 6.5);
    TH2D *h_chi2_sec1 = new TH2D("h_chi2_sec1", "", 200, -400., 600., 7, -0.5, 6.5);


    TH1D *h_n_tr_words = new TH1D("h_n_tr_words", "", 21, -0.5, 20.5);
    TH1D *h_t_word = new TH1D("h_t_word", "", 101, -0.5, 100.5);

    TH2D *h_sec_time_muontr1 = new TH2D("h_sec_time_muontr1", "", 101, -0.5, 100.5, 7, -0.5, 6.5);
   
   TH2D *h_PCal_cl_sec_time1 = new TH2D("h_PCal_cl_sec_time1", "", 14, -0.5, 13.5, 7, -0.5, 6.5);
   
   TH2D *h_PCal_cl_sec_E1 = new TH2D("h_PCal_cl_sec_E1", "", 200, 0., 0.41, 7, -0.5, 6.5);
   TH2D *h_PCal_cl_sec_Emin1 = new TH2D("h_PCal_cl_sec_Emin1", "", 200, 0., 0.41, 7, -0.5, 6.5);

   TH2D *h_PCal_cl_sec_E2 = new TH2D("h_PCal_cl_sec_E2", "", 200, 0., 0.41, 7, -0.5, 6.5);
   TH2D *h_PCal_cl_sec_Emin2 = new TH2D("h_PCal_cl_sec_Emin2", "", 200, 0., 0.41, 7, -0.5, 6.5);
   
   TH2D *h_PCal_sec_ncl_tbin8 = new TH2D("h_PCal_sec_ncl_tbin8", "", 5, -0.5, 4.5, 7, -0.5, 6.5);

   TH1D *h_PCal_Esum1 = new TH1D("h_PCal_Esum1", "", 200, 0., 0.5);
   TH1D *h_PCal_Esum2 = new TH1D("h_PCal_Esum2", "", 200, 0., 0.5);
   
   TH1D *h_PCal_Esum_cuts_[PCAL_Emaxcuts_test_points];
   
   for( int ii = 0; ii < PCAL_Emaxcuts_test_points; ii++ ){
       h_PCal_Esum_cuts_[ii] = new TH1D(Form("h_PCal_Esum_cuts_%d", ii), "", 200, 0., 0.5);
   }
   
   TH2D *h_ECal_cl_sec_time1 = new TH2D("h_ECal_cl_sec_time1", "", 14, -0.5, 13.5, 7, -0.5, 6.5);
   
   TH2D *h_ECal_cl_sec_E1 = new TH2D("h_ECal_cl_sec_E1", "", 200, 0., 0.41, 7, -0.5, 6.5);
   TH2D *h_ECal_cl_sec_Emin1 = new TH2D("h_ECal_cl_sec_Emin1", "", 200, 0., 0.41, 7, -0.5, 6.5);

   TH2D *h_ECal_cl_sec_E2 = new TH2D("h_ECal_cl_sec_E2", "", 200, 0., 0.41, 7, -0.5, 6.5);
   TH2D *h_ECal_cl_sec_Emin2 = new TH2D("h_ECal_cl_sec_Emin2", "", 200, 0., 0.41, 7, -0.5, 6.5);

   TH2D *h_ECal_cl_sec_E3 = new TH2D("h_ECal_cl_sec_E3", "", 200, 0., 0.41, 7, -0.5, 6.5);
   TH2D *h_ECal_cl_sec_Emin3 = new TH2D("h_ECal_cl_sec_Emin3", "", 200, 0., 0.41, 7, -0.5, 6.5);
   TH2D *h_ECal_cl_sec_Emin4 = new TH2D("h_ECal_cl_sec_Emin4", "", 200, 0., 0.41, 7, -0.5, 6.5);
   TH2D *h_ECal_cl_sec_Emin5 = new TH2D("h_ECal_cl_sec_Emin5", "", 200, 0., 0.41, 7, -0.5, 6.5);
   
   TH2D *h_ECal_sec_ncl_tbin8 = new TH2D("h_ECal_sec_ncl_tbin8", "", 5, -0.5, 4.5, 7, -0.5, 6.5);
   
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   //for (Long64_t jentry=0; jentry<nentries;jentry++) {
   for (Long64_t jentry=0; jentry<30000;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
      
      
        int n_part = TMath::Min(int(REC_Particle_pz->size()), n_max_npart);

        map<int, int> ind_FTOF1b;
        map<int, int> ind_PCal;
        map<int, int> ind_ECin;
        map<int, int> ind_ECout;

        // =============================== PCal, ECin, ECout ===============================
        for (int i_cal = 0; i_cal < REC_Calorimeter_detector->size(); i_cal++) {

            int ipart = REC_Calorimeter_pindex->at(i_cal);

            if (REC_Calorimeter_layer->at(i_cal) == 1) {
                ind_PCal[ipart] = i_cal + 1;
            } else if (REC_Calorimeter_layer->at(i_cal) == 4) {
                ind_ECin[ipart] = i_cal + 1;
            } else if (REC_Calorimeter_layer->at(i_cal) == 7) {
                ind_ECout[ipart] = i_cal + 1;
            }


        }

        // ================================= FTOF ===========================================

        for (int i_sc = 0; i_sc < REC_Scintillator_index->size(); i_sc++) {
            //cout << REC_Scintillator_detector->at(i_sc) << "     " << REC_Scintillator_layer->at(i_sc) << "    " << REC_Scintillator_component->at(i_sc) << endl;

            int ipart = REC_Scintillator_pindex->at(i_sc);
            if (REC_Scintillator_detector->at(i_sc) == DET_FTOF) {

                if (REC_Scintillator_layer->at(i_sc) == layer_FTOF1b) {
                    ind_FTOF1b[ipart] = i_sc + 1;
                }

            }

        }
      
      
         vector<int> ind_charged;

        for (int ipart = 0; ipart < n_part; ipart++) {

            if (!(REC_Particle_charge->at(ipart) != 0 && REC_Particle_status->at(ipart) >= 2000 && REC_Particle_status->at(ipart) < 3000)) {
                continue;
            }

            // Require signal in FTOF1b
            if (!(ind_FTOF1b[ipart] >= 1)) {
                continue;
            }


            // Require a signal in all PCal, ECin, and ECout
            if (!(ind_PCal[ipart] >= 1 && ind_ECin[ipart] >= 1 && ind_ECout[ipart] >= 1)) {
                continue;
            }

            double E_PCal = REC_Calorimeter_energy->at(ind_PCal[ipart] - 1);
            double E_ECin = REC_Calorimeter_energy->at(ind_ECin[ipart] - 1);
            double E_ECout = REC_Calorimeter_energy->at(ind_ECout[ipart] - 1);


            // ======= Tracks should have energy depositions in the calorimeter above some thresholds, defined in the trg file
            if (!(E_PCal > E_PCal_MIN && E_PCal < E_PCal_MAX && (E_ECin + E_ECout > E_EC_MIN) && ( (E_ECin + E_ECout) < E_EC_MAX) ) ){
                continue;
            }


            double chi2_pid = REC_Particle_chi2pid->at(ipart);
            int sec_pcal = REC_Calorimeter_sector->at(ind_PCal[ipart] - 1) - 1;

            h_chi2_sec1->Fill(chi2_pid, sec_pcal);

            if (!(chi2_pid > chi2pid_MIN && chi2_pid < chi2pid_MAX)) {
                continue;
            }


            double vz = REC_Particle_vz->at(ipart);
            h_vz_sec1->Fill(vz, sec_pcal);

            if (!(vz > vz_min_[sec_pcal] && vz < vz_max_[sec_pcal])) {
                continue;
            }


            ind_charged.push_back(ipart);
        }
     
      
         // In the loop over REC_part, we should already defined all charged tracks
        // Now we will loop over possible tracks and select pairs of opposite sectors

        int n_charged = ind_charged.size();

        vector<std::pair<int, int> > pair_indexes;

        // We want at least 2 charged particles at this step to continue
//        if (n_charged < 2) {
//            continue;
//        }


        for (int i_charged = 0; i_charged < n_charged - 1; i_charged++) {

            for (int j_charged = i_charged + 1; j_charged < n_charged; j_charged++) {

                int sec1 = REC_Calorimeter_sector->at(ind_PCal[ind_charged.at(i_charged)] - 1) - 1;
                int sec2 = REC_Calorimeter_sector->at(ind_PCal[ind_charged.at(j_charged)] - 1) - 1;

                if (sec1 - sec2 == 3) {
                    pair_indexes.push_back(std::make_pair(ind_charged.at(j_charged), ind_charged.at(i_charged)));
                } else if (sec1 - sec2 == -3) {
                    pair_indexes.push_back(std::make_pair(ind_charged.at(i_charged), ind_charged.at(j_charged)));
                }

            }


        }


        int n_pairs = pair_indexes.size();
     
      

        VTPRoot vtp1(RAW_vtp_crate, RAW_vtp_word);

        int n_tr_words = vtp1.GetNTrigWords();
        h_n_tr_words->Fill(n_tr_words);
        
        set<int> sect_triggered;
        
        for( int itr = 0; itr < n_tr_words; itr++ ){
          Trig_word *cur_trg = vtp1.GetTrigWord(itr);
          
          int t_word = cur_trg->tr_time;
          
          h_t_word->Fill(t_word);
          
          if( !(t_word > 65 && t_word < 74) ) {continue;}
          
          
          
          ap_int<32> cur_word = cur_trg->tr_word;
          
          for( int sec = 0; sec < 6; sec++ ){
          
              if( cur_word(Muon_1stbit + sec, Muon_1stbit + sec) ){
                  
                  h_sec_time_muontr1->Fill(t_word, sec);
                  
                  int min_sect = TMath::Min(sec, (sec + 3)%6 );
                  
                  sect_triggered.insert(min_sect);
                  
              }
          
          }
          
        }
        
        set<int>::iterator it;
        for( it = sect_triggered.begin(); it != sect_triggered.end(); it++ ){
            int sec1 = *it;
            
            int sec2 = sec1 + 3;
            
            
            // ============== PCAL =============
            // ============== PCAL =============
            // ============== PCAL =============
            
            int n_PCalclust1 = vtp1.GetNPCalClusters(sec1);
            int n_PCalclust2 = vtp1.GetNPCalClusters(sec2);
            
            double Emin_pcal1 = 1000;
            double Emax_pcal1 = 1000;

            bool PCal_energy_cuts1 = false;
            bool PCal_Emin_cut1 = false;
            bool PCal_Emax_cut1 = false;
            
            bool PCal_energy_cuts1_[PCAL_Emaxcuts_test_points] = {false, false, false, false};

            int n_cl_bin8 = 0; // Number of clusters in the time bin 8
            
            for( int icl1 = 0; icl1 < n_PCalclust1; icl1++ ){
                TEC_Cluster *cur_cl = vtp1.GetPCalCluster(sec1, icl1);
                
                h_PCal_cl_sec_time1->Fill(cur_cl->time, sec1);
                
                double cur_cl_E = cur_cl->energy/10000.;
                
                if( cur_cl->time >= vtp_cl_tmin && cur_cl->time <= vtp_cl_tmax ){
                    
                    h_PCal_cl_sec_E1->Fill(cur_cl_E, sec1);
                    
                    if( cur_cl_E < Emin_pcal1 ) {
                        Emin_pcal1 = cur_cl_E;
                    }
                    
                    if( cur_cl_E > trg_PCal_MIN ){
                        PCal_Emin_cut1 = true;
                    }
                                        
                    if( cur_cl_E < trg_PCal_MAX ){
                        PCal_Emax_cut1 = true;
                    }

                    if( cur_cl_E > trg_PCal_MIN && cur_cl_E < trg_PCal_MAX ){
                        PCal_energy_cuts1 = true;
                    }
                    
                    for( int itest = 0; itest < PCAL_Emaxcuts_test_points; itest++ ){
                        if(cur_cl_E > trg_PCal_MIN && cur_cl_E < trg_PCal_EMax_cuts_[itest]){
                            PCal_energy_cuts1_[itest] = true;
                        }
                    }
                    
                    if (cur_cl->time == vtp_cl_tmax) {
                        n_cl_bin8 = n_cl_bin8 + 1;
                    }

                }
            }
            
            h_PCal_sec_ncl_tbin8->Fill(n_cl_bin8, sec1);
            h_PCal_cl_sec_Emin1->Fill(Emin_pcal1, sec1);
            
            
            double Emin_pcal2 = 1000;
            
            bool PCal_energy_cuts2 = false;
            bool PCal_Emin_cut2 = false;
            bool PCal_Emax_cut2 = false;
            bool PCal_energy_cuts2_[PCAL_Emaxcuts_test_points] = {false, false, false, false};
            
            n_cl_bin8 = 0; // Number of clusters in the time bin 8
            
            for( int icl2 = 0; icl2 < n_PCalclust2; icl2++ ){
                TEC_Cluster *cur_cl = vtp1.GetPCalCluster(sec2, icl2);
                
                h_PCal_cl_sec_time1->Fill(cur_cl->time, sec2);
                
                double cur_cl_E = cur_cl->energy/10000.;
                
                if( cur_cl->time >= vtp_cl_tmin && cur_cl->time <= vtp_cl_tmax ){
                    
                    h_PCal_cl_sec_E1->Fill(cur_cl_E, sec2);
                    
                    if( cur_cl_E < Emin_pcal2 ) {
                        Emin_pcal2 = cur_cl_E;
                    }

                    if( cur_cl_E > trg_PCal_MIN ){
                        PCal_Emin_cut2 = true;
                    }
                                        
                    if( cur_cl_E < trg_PCal_MAX ){
                        PCal_Emax_cut2 = true;
                    }

                    if( cur_cl_E > trg_PCal_MIN && cur_cl_E < trg_PCal_MAX ){
                        PCal_energy_cuts2 = true;
                    }
                    
                    for( int itest = 0; itest < PCAL_Emaxcuts_test_points; itest++ ){
                        if(cur_cl_E > trg_PCal_MIN && cur_cl_E < trg_PCal_EMax_cuts_[itest]){
                            PCal_energy_cuts2_[itest] = true;
                        }
                    }
                    
                    
                    
                    if (cur_cl->time == vtp_cl_tmax) {
                        n_cl_bin8 = n_cl_bin8 + 1;
                    }

                }
            }
            
            h_PCal_sec_ncl_tbin8->Fill(n_cl_bin8, sec2);
            h_PCal_cl_sec_Emin1->Fill(Emin_pcal2, sec2);


            for (int ipair = 0; ipair < n_pairs; ipair++) {
                int ind1 = pair_indexes.at(ipair).first;
                int ind2 = pair_indexes.at(ipair).second;

                int sec1_offline = REC_Calorimeter_sector->at(ind_PCal[ind1] - 1) - 1;
                int sec2_offline = sec1_offline + 3;
                
                if( (sec1_offline == sec1 && sec2_offline == sec2) || (sec1_offline == sec2 && sec2_offline == sec1) ){
                
                    h_PCal_cl_sec_Emin2->Fill(Emin_pcal1, sec1);
                    h_PCal_cl_sec_Emin2->Fill(Emin_pcal2, sec2);
                
                }

            }
            
            
            
             // ============== ECal =============
             // ============== ECal =============
             // ============== ECal =============
            
            
            int n_ECalclust1 = vtp1.GetNECClusters(sec1);
            int n_ECalclust2 = vtp1.GetNECClusters(sec2);
            
            double Emin_ec1 = 1000;
            bool EC_energy_cuts1 = false;
            bool EC_Emin_cut1 = false;
            bool EC_Emax_cut1 = false;
            
            n_cl_bin8 = 0; // Number of clusters in the time bin 8
            
            for( int icl1 = 0; icl1 < n_ECalclust1; icl1++ ){
                TEC_Cluster *cur_cl = vtp1.GetECCluster(sec1, icl1);
                
                h_ECal_cl_sec_time1->Fill(cur_cl->time, sec1);
                
                double cur_cl_E = cur_cl->energy/10000.;
                
                if( cur_cl->time >= vtp_cl_tmin && cur_cl->time <= vtp_cl_tmax ){
                    
                    h_ECal_cl_sec_E1->Fill(cur_cl_E, sec1);
                    
                    if( cur_cl_E < Emin_ec1 ) {
                        Emin_ec1 = cur_cl_E;
                    }

                    if( cur_cl_E > trg_EC_MIN && cur_cl_E < trg_EC_MAX ){
                        EC_energy_cuts1 = true;
                    }

                    if (cur_cl_E > trg_EC_MIN) {
                        EC_Emin_cut1 = true;
                    }
                    
                     if (cur_cl_E < trg_EC_MAX) {
                        EC_Emax_cut1 = true;
                    }
                    
                   
                    
                    if (cur_cl->time == vtp_cl_tmax) {
                        n_cl_bin8 = n_cl_bin8 + 1;
                    }

                }
            }
            
            h_ECal_sec_ncl_tbin8->Fill(n_cl_bin8, sec1);
            h_ECal_cl_sec_Emin1->Fill(Emin_ec1, sec1);
            

            double Emin_ec2 = 1000;
            bool EC_energy_cuts2 = false;
            bool EC_Emin_cut2 = false;
            bool EC_Emax_cut2 = false;

            n_cl_bin8 = 0; // Number of clusters in the time bin 8
            
            for( int icl2 = 0; icl2 < n_ECalclust2; icl2++ ){
                TEC_Cluster *cur_cl = vtp1.GetECCluster(sec2, icl2);
                
                h_ECal_cl_sec_time1->Fill(cur_cl->time, sec2);
                
                double cur_cl_E = cur_cl->energy/10000.;
                
                if( cur_cl->time >= vtp_cl_tmin && cur_cl->time <= vtp_cl_tmax ){
                    
                    h_ECal_cl_sec_E1->Fill(cur_cl_E, sec2);
                    
                    if( cur_cl_E < Emin_ec2 ) {
                        Emin_ec2 = cur_cl_E;
                    }

                    if( cur_cl_E > trg_EC_MIN && cur_cl_E < trg_EC_MAX ){
                        EC_energy_cuts2 = true;
                    }               
                    
                    if (cur_cl_E > trg_EC_MIN) {
                        EC_Emin_cut2 = true;
                    }
                    
                     if (cur_cl_E < trg_EC_MAX) {
                        EC_Emax_cut2 = true;
                    }
                    
                    
                    if (cur_cl->time == vtp_cl_tmax) {
                        n_cl_bin8 = n_cl_bin8 + 1;
                    }

                }
            }
            
            h_ECal_sec_ncl_tbin8->Fill(n_cl_bin8, sec2);
            h_ECal_cl_sec_Emin1->Fill(Emin_ec2, sec2);
           
            bool EC_trg_cuts = (Emin_ec1 > trg_EC_MIN && Emin_ec1 < trg_EC_MAX && Emin_ec2 > trg_EC_MIN && Emin_ec2 < trg_EC_MAX);

            
            if( EC_Emin_cut1 && EC_Emin_cut2 && PCal_Emin_cut1 && PCal_Emin_cut2){
                h_ECal_cl_sec_Emin3->Fill(Emin_ec1, sec1);
                h_ECal_cl_sec_Emin3->Fill(Emin_ec2, sec2);            
            }

            if (EC_energy_cuts1 && EC_energy_cuts2 && PCal_Emin_cut1 && PCal_Emin_cut2) {
                h_ECal_cl_sec_Emin4->Fill(Emin_ec1, sec1);
                h_ECal_cl_sec_Emin4->Fill(Emin_ec2, sec2);
            }
            
            if( EC_energy_cuts1 && EC_energy_cuts2 && PCal_energy_cuts1 && PCal_energy_cuts2 ){
                h_ECal_cl_sec_Emin5->Fill(Emin_ec1, sec1);
                h_ECal_cl_sec_Emin5->Fill(Emin_ec2, sec2);            
            }

            h_PCal_Esum1->Fill(Emin_pcal1 + Emin_pcal2);

            if (EC_energy_cuts1 && EC_energy_cuts2 && PCal_Emin_cut1 && PCal_Emin_cut2) {
                h_PCal_Esum2->Fill(Emin_pcal1 + Emin_pcal2);

            }
            
            for( int itest = 0; itest < PCAL_Emaxcuts_test_points; itest++ ){
                if( EC_energy_cuts1 && EC_energy_cuts2 && PCal_energy_cuts1_[itest] && PCal_energy_cuts2_[itest]){
                    h_PCal_Esum_cuts_[itest]->Fill(Emin_pcal1 + Emin_pcal2);
                }
            }
            
             for (int ipair = 0; ipair < n_pairs; ipair++) {
                int ind1 = pair_indexes.at(ipair).first;
                int ind2 = pair_indexes.at(ipair).second;

                int sec1_offline = REC_Calorimeter_sector->at(ind_PCal[ind1] - 1) - 1;
                int sec2_offline = sec1_offline + 3;
                
                if( (sec1_offline == sec1 && sec2_offline == sec2) || (sec1_offline == sec2 && sec2_offline == sec1) ){
                
                    h_ECal_cl_sec_Emin2->Fill(Emin_ec1, sec1);
                    h_ECal_cl_sec_Emin2->Fill(Emin_ec2, sec2);                
                }

            }
           
            
            
            
        }
        
   }
   
   gDirectory->Write();
}
#endif	// STAGE1_STUDY_H
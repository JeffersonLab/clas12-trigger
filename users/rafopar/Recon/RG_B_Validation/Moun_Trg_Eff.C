#ifndef MOUN_TRG_EFF_H
#define MOUN_TRG_EFF_H

#define Moun_Trg_Eff_cxx
#include "Moun_Trg_Eff.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_stream.h>

#include <VTPRoot.hh>

#include <iostream>

using namespace std;

double Mom_amplitude(double, double, double);

void Moun_Trg_Eff::Loop() {
    //   In a ROOT session, you can do:
    //      root> .L Moun_Trg_Eff.C
    //      root> Moun_Trg_Eff t
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

    const double Eb = 10.731;
    const double Mp = 0.9383;
    const double r2d = 57.295780;
    const int HTCC_TYPE = 15;
    const int DET_FTOF = 12;
    const int layer_FTOF1b = 2;
    const int VTP_TrigTag = 29; // 11101
    const int n_max_npart = 30;
    const int n_sect = 6;
    const double scale_PCal_coord = 1. / 6.5;
    const double scale_EC_coord = 1. / 8.;

    const double chi2pid_MIN = -100.;
    const double chi2pid_MAX = 40.;

    const double E_PCal_MIN = 0.01; // in GeV ftom rgb_v6.trg
    const double E_EC_MIN = 0.04; // in GeV ftom rgb_v6.trg
    const double E_EC_MAX = 0.12; // in GeV ftom rgb_v6.trg

    map<int, int> probe_1st_bit;
    
    probe_1st_bit[6286] = 24;
    probe_1st_bit[6299] = 14;
    //probe_1st_bit[6299] = 14;
    
    // ========
    cout<<"frun = "<<frun<<"     Probe 1st bit is "<<probe_1st_bit[frun]<<endl;
    
    
    const int tr_word_size = 32;

    double vz_min_[n_sect] = {-12., -12., -12., -18., -12, -12};
    double vz_max_[n_sect] = {4., 4., 4., 2., -5., 6.};

    double ECout_tight_cut_[n_sect] = {0.07, 0.07, 0.07, 0.07, 0.07, 0.07};
    double ECin_tight_cut_[n_sect] = {0.05, 0.05, 0.05, 0.05, 0.05, 0.05};
    double Pcal_tight_cut_[n_sect] = {0.035, 0.035, 0.035, 0.035, 0.035, 0.035};

    const double ECout_cut_[n_sect] = {0.08, 0.08, 0.08, 0.08, 0.08, 0.08};
    const double ECin_cut_[n_sect] = {0.06, 0.06, 0.06, 0.06, 0.06, 0.06};
    const double EPcal_cut_[n_sect] = {0.06, 0.06, 0.06, 0.06, 0.06, 0.06};
    const double Etot_cut_[n_sect] = {0.12, 0.12, 0.12, 0.12, 0.12, 0.12};

    //TFile *file_out = new TFile("Data/Muon_Trg_Eff_skimmed.root", "Recreate");
    TFile *file_out = new TFile(Form("Muon_Trg_Eff_%d.root", frun), "Recreate");

    //TTree *skim_tree = fChain->CloneTree(0);
    
    
    TH2D *h_vz_sec1 = new TH2D("h_vz_sec1", "", 200, -20., 20., 7, -0.5, 6.5);
    TH2D *h_chi2_sec1 = new TH2D("h_chi2_sec1", "", 200, -400., 600., 7, -0.5, 6.5);

    TH1D *h_n_charged1 = new TH1D("h_n_charged1", "", 11, -0.5, 10.5);
    TH1D *h_n_pairs1 = new TH1D("h_n_pairs1", "", 8, -0.5, 7.5);

    TH1D *h_Pair_charge_sum1 = new TH1D("h_Pair_charge_sum1", "", 5, -2.5, 2.5);
    
    TH2D *h_sec_neg_pos_road_trg1 = new TH2D("h_sec_neg_pos_road_trg1", "", 5, -0.5, 4.5, 7, -0.5, 6.5);
    
    TH2D *h_Pposneg_all_pairs1 = new TH2D("h_Pposneg_all_pairs1", "", 200, 0., 10.5, 200, 0., 10.5);
    TH2D *h_Pposneg_tr_missed1 = new TH2D("h_Pposneg_tr_missed1", "", 200, 0., 10.5, 200, 0., 10.5);

    TH2D *h_PCal_pos_neg_missed1 = new TH2D("h_PCal_pos_neg_missed1", "", 200, 0., 1.45, 200, 0., 1.45);
    TH2D *h_EC_pos_neg_missed1 = new TH2D("h_EC_pos_neg_missed1", "", 200, 0., 1.45, 200, 0., 1.45);
    
    TH2D *h_PCal_yxc_pos_all1 = new TH2D("h_PCal_yxc_pos_all1", "", 200, -400., 400., 200, -400., 400.);
    TH2D *h_PCal_yxc_pos_missed1 = new TH2D("h_PCal_yxc_pos_missed1", "", 200, -400., 400., 200, -400., 400.);
    
    TH2D *h_t_PCal_pos_neg1 = new TH2D("h_t_PCal_pos_neg1", "", 200, 150., 250., 200, 150., 250);
    
    TH1D *h_t_HTCC_mask_time1 = new TH1D("h_t_HTCC_mask_time1", "", 101, -0.5, 100.5);
    
    Long64_t nentries = fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    //for (Long64_t jentry = 0; jentry < nentries; jentry++) {
    for (Long64_t jentry = 0; jentry < 6000000; jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;
        
        if ((jentry + 1) % 20000 == 0) {
            cout.flush() << "Processed " << jentry << "\r";
        }
        
        

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
            if (!(E_PCal > E_PCal_MIN && (E_ECin + E_ECout > E_EC_MIN) && ( (E_ECin + E_ECout) < E_EC_MAX) ) ){
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


        h_n_charged1->Fill(ind_charged.size());



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
        h_n_pairs1->Fill(n_pairs);

//        if( n_pairs >= 1 ){
//            skim_tree->Fill();
//        }
        
        
        // ======================================        
        // ======================================   Looping over VTP trigger banks        
        // ======================================        
        // ======================================        

        VTPRoot vtp1(RAW_vtp_crate, RAW_vtp_word);

        int n_tr_words = vtp1.GetNTrigWords();

        
        int n_HTCC_masks = vtp1.GetNHTCCMasks();
        
        //cout<<"n_HTCC_masks = "<<n_HTCC_masks<<endl;
        
        vector<int> vtp_time_neg_pos_roads[n_sect];    // VTP time of bits 24-29 // rgb_v6.trg

        for( int i_tr_word = 0; i_tr_word < n_tr_words; i_tr_word++ ){

            Trig_word *cur_trg_word = vtp1.GetTrigWord(i_tr_word);

            ap_int<tr_word_size> cur_word = cur_trg_word->tr_word;

            for( int ibite = 0; ibite < n_sect; ibite++ ){
                if( cur_word(probe_1st_bit[frun] + ibite, probe_1st_bit[frun] + ibite) ){
                    vtp_time_neg_pos_roads[ibite].push_back(cur_trg_word->tr_time);
                }
            }
            
        }
        

        for (int ipair = 0; ipair < n_pairs; ipair++) {

            int ind1 = pair_indexes.at(ipair).first;
            int ind2 = pair_indexes.at(ipair).second;

            int q1 = REC_Particle_charge->at(ind1);
            int q2 = REC_Particle_charge->at(ind2);

            double P1 = Mom_amplitude(REC_Particle_px->at(ind1), REC_Particle_py->at(ind1), REC_Particle_pz->at(ind1));
            double P2 = Mom_amplitude(REC_Particle_px->at(ind2), REC_Particle_py->at(ind2), REC_Particle_pz->at(ind2));
            
            int sec1 = REC_Calorimeter_sector->at(ind_PCal[ind1] - 1) - 1;
            int sec2 = sec1 + 3;

            h_Pair_charge_sum1->Fill(q1 + q2);

            // ======================
            // ======================   Now study the case when charge sum is 0, i.e. when tracks are oppositely charged
            // ======================
            // ======================

            if (q1 + q2 == 0) {

                // Determine the sector of the negative particle
                int sec_neg = (q1 < 0) ? sec1 : sec2;
                double P_neg = (q1 < 0) ? P1 : P2;
                double P_pos = (q1 < 0) ? P2 : P1;

                int ind_neg = (q1 < 0) ? ind1 : ind2;
                int ind_pos = (q1 < 0) ? ind2 : ind1;
                
                
                double E_PCal_pos = REC_Calorimeter_energy->at(ind_PCal[ind_pos] - 1);
                double E_ECin_pos = REC_Calorimeter_energy->at(ind_ECin[ind_pos] - 1);
                double E_ECout_pos = REC_Calorimeter_energy->at(ind_ECout[ind_pos] - 1);

                double E_PCal_neg = REC_Calorimeter_energy->at(ind_PCal[ind_neg] - 1);
                double E_ECin_neg = REC_Calorimeter_energy->at(ind_ECin[ind_neg] - 1);
                double E_ECout_neg = REC_Calorimeter_energy->at(ind_ECout[ind_neg] - 1);
                
                double PCal_y_pos = REC_Calorimeter_y->at(ind_PCal[ind_pos] - 1);
                double PCal_x_pos = REC_Calorimeter_x->at(ind_PCal[ind_pos] - 1);
                
                double t_PCal_neg = REC_Calorimeter_time->at(ind_PCal[ind_neg] - 1);
                double t_PCal_pos = REC_Calorimeter_time->at(ind_PCal[ind_pos] - 1);
                
                h_t_PCal_pos_neg1->Fill(t_PCal_neg, t_PCal_pos);
                
                // Check, if neg_pos_road_sector bit is fired
                int n_bits = vtp_time_neg_pos_roads[sec_neg].size();
                
                h_sec_neg_pos_road_trg1->Fill(n_bits, sec_neg);
                
                h_Pposneg_all_pairs1->Fill(P_neg, P_pos);
                
                h_PCal_yxc_pos_all1->Fill(PCal_x_pos, PCal_y_pos);
                
                if( n_bits == 0 ){
                
                    h_Pposneg_tr_missed1->Fill(P_neg, P_pos);
                    
                    // Want to check PCal and EC energies, when momentum of both is above 2 GeV
                    
                    if( P_neg > 2. && P_pos > 2 ){
                        h_PCal_pos_neg_missed1->Fill(E_PCal_neg, E_PCal_pos);
                        h_EC_pos_neg_missed1->Fill(E_ECin_neg + E_ECout_neg, E_ECin_pos + E_ECout_pos );
                        h_PCal_yxc_pos_missed1->Fill(PCal_x_pos, PCal_y_pos);
                    }
                
                }
                
                // =============== Ben wants to check HTCC mask times ===============
                
                
                if( n_HTCC_masks > 0 ){
                    THTCC_mask *cur_htcc_mask = vtp1.GetHTCCMask(0);
                    
                    int cur_htcc_mask_time = cur_htcc_mask->time;
                    
                    h_t_HTCC_mask_time1->Fill(cur_htcc_mask_time);                  
                }
                                
                
            }

        }
    }

    gDirectory->Write();
}

double Mom_amplitude(double px, double py, double pz){

    return sqrt( px*px + py*py + pz*pz );
    
}

#endif // MOUN_TRG_EFF_H
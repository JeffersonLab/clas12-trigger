#ifndef DC_ROADS_CHECK_H
#define DC_ROADS_CHECK_H

#define DC_Roads_check_cxx
#include "DC_Roads_check.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_stream.h>

#include <VTPRoot.hh>

#include <TH1D.h>
#include <iostream>
#include <fstream>
using namespace std;

void DC_Roads_check::Loop() {
    //   In a ROOT session, you can do:
    //      root> .L DC_Roads_check.C
    //      root> DC_Roads_check t
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

    Long64_t nentries = fChain->GetEntriesFast();

    const double Eb = 10.731;
    const double Mp = 0.9383;
    const double r2d = 57.295780;
    const int HTCC_TYPE = 15;
    const int VTP_TrigTag = 29; // 11101
    const int n_max_npart = 30;
    const int n_sect = 6;
    const double scale_PCal_coord = 1. / 6.5;
    const double scale_EC_coord = 1. / 8.;

    const int tr_word_size = 32;
    
    TFile *file_out = new TFile("DC_Roads_check.root", "Recreate");
    TH1D *h_n_part1 = new TH1D("h_n_part1", "", 21, -0.5, 20.5);
    TH1D *h_n_tr_words = new TH1D("h_n_tr_words", "", 11, -0.5, 10.5);

    TH1D *h_n_em_trg1 = new TH1D("h_n_em_trg1", "", 6, -0.5, 5.5);
    TH1D *h_n_dcroad_trg1 = new TH1D("h_n_dcroad_trg1", "", 6, -0.5, 5.5);
    TH1D *h_n_dcroadPCU_trg1 = new TH1D("h_n_dcroadPCU_trg1", "", 6, -0.5, 5.5);

    TH1D *h_n_em_trg2 = new TH1D("h_n_em_trg2", "", 6, -0.5, 5.5);
    TH1D *h_n_dcroad_trg2 = new TH1D("h_n_dcroad_trg2", "", 6, -0.5, 5.5);
    TH1D *h_n_dcroadPCU_trg2 = new TH1D("h_n_dcroadPCU_trg2", "", 6, -0.5, 5.5);
    
    TH1D *h_em_sec1 = new TH1D("h_em_sec1", "", 7, -0.5, 6.5);
    TH1D *h_embits_sec1 = new TH1D("h_embits_sec1", "", 7, -0.5, 6.5);
    TH1D *h_dcroadbits_sec1 = new TH1D("h_dcroadbits_sec1", "", 7, -0.5, 6.5);
    TH1D *h_dcroadPCUbits_sec1 = new TH1D("h_dcroadPCUbits_sec1", "", 7, -0.5, 6.5);

    TH1D *h_em_sec2 = new TH1D("h_em_sec2", "", 7, -0.5, 6.5);
    TH1D *h_embits_sec2 = new TH1D("h_embits_sec2", "", 7, -0.5, 6.5);
    TH1D *h_dcroadbits_sec2 = new TH1D("h_dcroadbits_sec2", "", 7, -0.5, 6.5);
    TH1D *h_dcroadPCUbits_sec2 = new TH1D("h_dcroadPCUbits_sec2", "", 7, -0.5, 6.5);
    
    TH2D *h_em_bit_time_sec1 = new TH2D("h_em_bit_time_sec1", "", 7, -0.6, 6.5, 101, -0.5, 100.5);
    TH2D *h_dcroad_bit_time_sec1 = new TH2D("h_dcroad_bit_time_sec1", "", 7, -0.6, 6.5, 101, -0.5, 100.5);
    TH2D *h_dcroadPCU_bit_time_sec1 = new TH2D("h_dcroadPCU_bit_time_sec1", "", 7, -0.6, 6.5, 101, -0.5, 100.5);

    TH2D *h_em_bit_time_sec2 = new TH2D("h_em_bit_time_sec2", "", 7, -0.6, 6.5, 101, -0.5, 100.5);
    TH2D *h_dcroad_bit_time_sec2 = new TH2D("h_dcroad_bit_time_sec2", "", 7, -0.6, 6.5, 101, -0.5, 100.5);
    TH2D *h_dcroadPCU_bit_time_sec2 = new TH2D("h_dcroadPCU_bit_time_sec2", "", 7, -0.6, 6.5, 101, -0.5, 100.5);
    
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;

        int n_part = TMath::Min(int(REC_Particle_pz->size()), n_max_npart);
        map<int, int> ind_HTCC;
        map<int, int> ind_PCal;
        map<int, int> ind_ECin;
        map<int, int> ind_ECout;

        h_n_part1->Fill(n_part);

        bool em_candidate = false;


        // =============================== HTCC ===============================
        for (int i_cc = 0; i_cc < REC_Cherenkov_detector->size(); i_cc++) {

            // Want only HTCC for now
            if (REC_Cherenkov_detector->at(i_cc) == HTCC_TYPE) {
                ind_HTCC[REC_Cherenkov_pindex->at(i_cc)] = i_cc + 1; // Adding 1
            }
        }

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

        
        VTPRoot vtp1(RAW_vtp_crate, RAW_vtp_word);
        
        int n_tr_words = vtp1.GetNTrigWords();
        
        h_n_tr_words->Fill(n_tr_words);

        // Bit 0        : Electron all sec
        // Bits 1-6     : Electron sector based
        // Bits 11-16   : Electron with DC roads sector based
        // Bits 17-22   : Electrons w/ DC_Roads matched with PCU sector based
        
        vector<int> em_trg_sec;
        vector<int> em_trg_time;
        vector<int> dcroad_trg_sec;
        vector<int> dcroad_trg_time;
        vector<int> dcroadPCU_trg_sec;
        vector<int> dcroadPCU_trg_time;

        for (int i_tr_word = 0; i_tr_word < n_tr_words; i_tr_word++) {

            Trig_word *cur_trg_word = vtp1.GetTrigWord(i_tr_word);

            ap_int<tr_word_size> cur_word = cur_trg_word->tr_word;


            for (int ibite = 0; ibite < 6; ibite++) {
                
                if (cur_word(ibite + 1, ibite + 1)) { // Electron trig bits
                    em_trg_sec.push_back(ibite);
                    em_trg_time.push_back(cur_trg_word->tr_time);
                }


                if (cur_word(ibite + 11, ibite + 11)) { // Electron with DC roads
                    dcroad_trg_sec.push_back(ibite);
                    dcroad_trg_time.push_back(cur_trg_word->tr_time);
                }

                if (cur_word(ibite + 17, ibite + 17)) { // Electron with DC roads with PCU
                    dcroadPCU_trg_sec.push_back(ibite);
                    dcroadPCU_trg_time.push_back(cur_trg_word->tr_time);
                }
            }


        }

        
        int n_em_bits = em_trg_sec.size();
        int n_dcroad_bits = dcroad_trg_sec.size();
        int n_dcroadPCU_bits = dcroadPCU_trg_sec.size();

        h_n_em_trg1->Fill(n_em_bits);
        h_n_dcroad_trg1->Fill(n_dcroad_bits);
        h_n_dcroadPCU_trg1->Fill(n_dcroadPCU_bits);
        
        int n_em = 0;

        for (int i_part = 0; i_part < REC_Particle_status->size(); i_part++) {

            // We want electron in Forward detector
            if (!(REC_Particle_status->at(i_part) >= 2000 && REC_Particle_status->at(i_part) < 3000 && REC_Particle_pid->at(i_part) == 11)) {
                continue;
            }

            double Px = double(REC_Particle_px->at(i_part));
            double Py = double(REC_Particle_py->at(i_part));
            double Pz = double(REC_Particle_pz->at(i_part));
            double th = atan(sqrt(Px * Px + Py * Py) / Pz) * r2d;

            double phi = atan2(Py, Px) * r2d + 30.;
            if (phi < 0) {
                phi = phi + 360.;
            }

            int sec_em = int(phi / 60.);

            double P = sqrt(Px * Px + Py * Py + Pz * Pz);

            double vz = double(REC_Particle_vz->at(i_part));

            
//            if( !(ind_PCal[i_part] >= 1 && ind_HTCC[i_part] >= 1) ) {continue;}
//            
//            int sec_PCal = REC_Calorimeter_sector->at(ind_PCal[i_part] - 1) - 1;
//            
//            int x_HTCC = HTCC_rec_x->at(REC_Calorimeter_index->at(ind_HTCC[i_part] - 1));
//            int y_HTCC = HTCC_rec_y->at(REC_Calorimeter_index->at(ind_HTCC[i_part] - 1));
//            
//            double phi_HTCC = atan2(y_HTCC, x_HTCC) * r2d + 30.;
//            if (phi_HTCC < 0) {
//                phi_HTCC = phi_HTCC + 360.;
//            }
//
//            int sec_HTCC = phi_HTCC / 60;
            

            h_n_em_trg2->Fill(n_em_bits);
            h_n_dcroad_trg2->Fill(n_dcroad_bits);
            h_n_dcroadPCU_trg2->Fill(n_dcroadPCU_bits);

            if( P < 2 ){continue;}
            
            //if( sec_HTCC != sec_PCal ) {continue;}
            
//            double sec_Pcal = 
            
            h_em_sec1->Fill(sec_em);
            
            for( int i_em_bit = 0; i_em_bit < n_em_bits; i_em_bit++ ){
            
                if( em_trg_sec.at(i_em_bit) == sec_em ){
                    h_embits_sec1->Fill(sec_em);
                    
                    if( em_trg_time.at(i_em_bit) > 66. && em_trg_time.at(i_em_bit) < 69. ){
                        h_embits_sec2->Fill(sec_em);
                    }
                    
                    h_em_bit_time_sec1->Fill(sec_em, em_trg_time.at(i_em_bit));

                    if (n_em_bits == 1) {
                        h_em_bit_time_sec2->Fill(sec_em, em_trg_time.at(i_em_bit));
                    }
                }
            }
            
            for( int i_dc_road_bit = 0; i_dc_road_bit < n_dcroad_bits; i_dc_road_bit++ ){
                if( dcroad_trg_sec.at(i_dc_road_bit) == sec_em ){
                    h_dcroadbits_sec1->Fill(sec_em);

                    if (dcroad_trg_time.at(i_dc_road_bit) > 66. && dcroad_trg_time.at(i_dc_road_bit) < 69.) {
                        h_dcroadbits_sec2->Fill(sec_em);
                    }

                    
                    h_dcroad_bit_time_sec1->Fill(sec_em, dcroad_trg_time.at(i_dc_road_bit));
                }
            }
            
            for( int i_dcroadPCU = 0; i_dcroadPCU < n_dcroadPCU_bits; i_dcroadPCU++ ){
                if( dcroadPCU_trg_sec.at(i_dcroadPCU) == sec_em ){
                    h_dcroadPCUbits_sec1->Fill(sec_em);

                    if (dcroadPCU_trg_time.at(i_dcroadPCU) > 66. && dcroadPCU_trg_time.at(i_dcroadPCU) < 69.) {
                        h_dcroadPCUbits_sec2->Fill(sec_em);
                    }
                    
                    
                    h_dcroadPCU_bit_time_sec1->Fill(sec_em, dcroadPCU_trg_time.at(i_dcroadPCU));
                }
            }
            
            
            n_em = n_em + 1;
        }


        
        
        
    }

    gDirectory->Write();
}

#endif // DC_ROADS_CHECK_H


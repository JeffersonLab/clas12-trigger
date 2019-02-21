#ifndef MUON_TRIGGER_H
#define MUON_TRIGGER_H

#define Muon_Trigger_cxx
#include "Muon_Trigger.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_stream.h>

#include <VTPRoot.hh>

void Muon_Trigger::Loop() {
    //   In a ROOT session, you can do:
    //      root> .L Muon_Trigger.C
    //      root> Muon_Trigger t
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

    const double chi2pid_MIN = -100.;
    const double chi2pid_MAX = 40.;

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


    const int VTP_PCal_tmax = 8; // We will consider VTP clusters that have time between VTP_PCal_tmin and VTP_PCal_tmax
    const int VTP_PCal_tmin = 7;
    const int VTP_EC_tmax = 8; // We will consider VTP clusters that have time between VTP_PCal_tmin and VTP_PCal_tmax
    const int VTP_EC_tmin = 7;

    //TFile *file_out = new TFile("Data/skimmed_Muon_Trigger.root", "Recreate");
    TFile *file_out = new TFile("Muon_Trigger.root", "Recreate");

    //TTree *skim_tree = fChain->CloneTree(0);


    TH2D *h_vz_sec1 = new TH2D("h_vz_sec1", "", 200, -20., 20., 7, -0.5, 6.5);
    TH2D *h_chi2_sec1 = new TH2D("h_chi2_sec1", "", 200, -400., 600., 7, -0.5, 6.5);

    TH2D *h_EPcal_sec1 = new TH2D("h_EPcal_sec1", "", 200, 0., 0.25, 7, -0.5, 6.5);
    TH2D *h_EECin_sec1 = new TH2D("h_EECin_sec1", "", 200, 0., 0.25, 7, -0.5, 6.5);
    TH2D *h_EECout_sec1 = new TH2D("h_EECout_sec1", "", 200, 0., 0.25, 7, -0.5, 6.5);

    TH2D *h_EPcal_sec2 = new TH2D("h_EPcal_sec2", "", 200, 0., 0.25, 7, -0.5, 6.5);
    TH2D *h_EECin_sec2 = new TH2D("h_EECin_sec2", "", 200, 0., 0.25, 7, -0.5, 6.5);
    TH2D *h_EECout_sec2 = new TH2D("h_EECout_sec2", "", 200, 0., 0.25, 7, -0.5, 6.5);


    // ================ VTP Clusters ==============================
    TH2D *h_NVTP_Pcal_clust_sec1 = new TH2D("h_NPcal_clust_sec1", "", 25, -0.5, 24.5, 7, -0.5, 6.5);
    TH2D *h_t_VTP_PCal_clust_sec1 = new TH2D("h_t_VTP_PCal_clust_sec1", "", 26, -0.5, 25.5, 7, -0.5, 6.5);

    TH2D *h_E_VTP_PCal_sec1 = new TH2D("h_E_VTP_PCal_sec1", "", 200, 0., 0.4, 7, -0.5, 6.5);

    TH2D *h_Emin_VTP_PCal_sec1 = new TH2D("h_Emin_VTP_PCal_sec1", "", 200, 0., 0.4, 7, -0.5, 6.5);

    TH2D *h_NVTP_EC_clust_sec1 = new TH2D("h_NVTP_EC_clust_sec1", "", 25, -0.5, 24.5, 7, -0.5, 6.5);
    TH2D *h_t_VTP_EC_clust_sec1 = new TH2D("h_t_VTP_EC_clust_sec1", "", 26, -0.5, 25.5, 7, -0.5, 6.5);

    TH2D *h_E_VTP_EC_sec1 = new TH2D("h_E_VTP_EC_sec1", "", 200, 0., 0.4, 7, -0.5, 6.5);

    TH2D *h_Emin_VTP_EC_sec1 = new TH2D("h_Emin_VTP_EC_sec1", "", 200, 0., 0.4, 7, -0.5, 6.5);
    
    TH2D *h_Emin_VTP_Etot_sec1 = new TH2D("h_Emin_VTP_Etot_sec1", "", 200, 0., 0.4, 7, -0.5, 6.5);


    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
    //for (Long64_t jentry = 0; jentry < 100000; jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;

        if ((jentry + 1) % 20000 == 0) {
            cout.flush() << "Processed " << jentry << "\r";
            //gDirectory->Write("hist_Dir", TObject::kOverwrite);
        }


        VTPRoot vtp1(RAW_vtp_crate, RAW_vtp_word);

        int n_tr_words = vtp1.GetNTrigWords();

        vector<int> Muon_trg_sec; // 0:(sec1 and sec 4), 1:(sec2 and sec5), 2:(sec3 and sec6)
        vector<int> Muon_trg_time;

        for (int i_tr_word = 0; i_tr_word < n_tr_words; i_tr_word++) {

            Trig_word *cur_trg_word = vtp1.GetTrigWord(i_tr_word);

            ap_int<tr_word_size> cur_word = cur_trg_word->tr_word;


            for (int ibite = 0; ibite < 3; ibite++) {

                if (cur_word(7 + ibite, 7 + ibite)) {
                    Muon_trg_sec.push_back(ibite);
                    Muon_trg_time.push_back(cur_trg_word->tr_time);
                }

            }


        }

        //cout<<Muon_trg_sec.size()<<endl;

        if (Muon_trg_sec.size() == 0) {
            continue;
        }


        //cout<<Muon_trg_sec.at(0)<<endl;

        // =========== We should select charged particle pairs in opposite sectors of FD ===============

        int n_part = TMath::Min(int(REC_Particle_pz->size()), n_max_npart);
        map<int, int> ind_HTCC;
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

        vector<int> ind_charged;

        for (int ipart = 0; ipart < n_part; ipart++) {

            if (!(REC_Particle_charge->at(ipart) != 0 && REC_Particle_status->at(ipart) >= 2000 && REC_Particle_status->at(ipart) < 3000)) {
                continue;
            }

            double chi2_pid = REC_Particle_chi2pid->at(ipart);



            // Require a signal in all PCal, ECin, and ECout
            if (!(ind_PCal[ipart] >= 1 && ind_ECin[ipart] >= 1 && ind_ECout[ipart] >= 1)) {
                continue;
            }

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
        if (n_charged < 2) {
            continue;
        }


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

//                if( n_pairs >= 1 ){
//                    skim_tree->Fill();
//                }

        //cout<<"Number of pairs is"<<n_pairs<<endl;

        for (int ipair = 0; ipair < n_pairs; ipair++) {
            int ind1 = pair_indexes.at(ipair).first;
            int ind2 = pair_indexes.at(ipair).second;

            //            cout<<n_part<<"    "<<n_charged<<"    "<<REC_Particle_pid->at(0)<<"   "<<REC_Particle_pid->at(1)<<"   "<<REC_Particle_status->at(0)<<"   "
            //                    <<REC_Particle_status->at(1)<<"    "<<ind1<<"    "<<ind2<<endl;

            int sec1 = REC_Calorimeter_sector->at(ind_PCal[ind1] - 1) - 1;
            int sec2 = sec1 + 3;
            //int sec2 = REC_Calorimeter_sector->at(ind_PCal[ind2] - 1) - 1;

            //cout<<"sec = "<<sec<<"    Sec2 = "<<sec2<<endl;

            double EPcal_1 = REC_Calorimeter_energy->at(ind_PCal[ind1] - 1);
            double EPcal_2 = REC_Calorimeter_energy->at(ind_PCal[ind2] - 1);

            double EECin_1 = REC_Calorimeter_energy->at(ind_ECin[ind1] - 1);
            double EECin_2 = REC_Calorimeter_energy->at(ind_ECin[ind2] - 1);

            double EECout_1 = REC_Calorimeter_energy->at(ind_ECout[ind1] - 1);
            double EECout_2 = REC_Calorimeter_energy->at(ind_ECout[ind2] - 1);


            h_EPcal_sec1->Fill(EPcal_1, sec1);
            h_EPcal_sec1->Fill(EPcal_2, sec2);

            h_EECin_sec1->Fill(EECin_1, sec1);
            h_EECin_sec1->Fill(EECin_2, sec2);

            h_EECout_sec1->Fill(EECout_1, sec1);
            h_EECout_sec1->Fill(EECout_2, sec2);

            if (EECin_1 < ECin_tight_cut_[sec1] && EECout_1 < ECout_tight_cut_[sec1]) {
                h_EPcal_sec2->Fill(EPcal_1, sec1);
            }
            if (EECin_2 < ECin_tight_cut_[sec2] && EECout_2 < ECout_tight_cut_[sec2]) {
                h_EPcal_sec2->Fill(EPcal_2, sec2);
            }


            if (EPcal_1 < Pcal_tight_cut_[sec1] && EECout_1 < ECout_tight_cut_[sec1]) {
                h_EECin_sec2->Fill(EECin_1, sec1);
            }

            if (EPcal_2 < Pcal_tight_cut_[sec2] && EECout_2 < ECout_tight_cut_[sec2]) {
                h_EECin_sec2->Fill(EECin_2, sec2);
            }

            if (EPcal_1 < Pcal_tight_cut_[sec1] && EECin_1 < ECin_tight_cut_[sec1]) {
                h_EECout_sec2->Fill(EECout_1, sec1);
            }

            if (EPcal_2 < Pcal_tight_cut_[sec2] && EECin_2 < ECin_tight_cut_[sec2]) {
                h_EECout_sec2->Fill(EECout_2, sec2);
            }

            double E_tot1 = EPcal_1 + EECin_1 + EECout_1;
            double E_tot2 = EPcal_2 + EECin_2 + EECout_2;

            if (!(EECout_1 < ECout_cut_[sec1] && EECout_2 < ECout_cut_[sec2] && EECin_1 < ECin_cut_[sec1] && EECin_2 < ECin_cut_[sec2]
                    && EPcal_1 < EPcal_cut_[sec1] && EPcal_2 < EPcal_cut_[sec2] && E_tot1 < Etot_cut_[sec1] && E_tot2 < Etot_cut_[sec2])) {
                continue;
            }


            // ================ VTP part ==================================

            int n_VTP_PCal_clust_sec1 = vtp1.GetNPCalClusters(sec1);
            int n_VTP_PCal_clust_sec2 = vtp1.GetNPCalClusters(sec2);

            h_NVTP_Pcal_clust_sec1->Fill(n_VTP_PCal_clust_sec1, sec1);
            h_NVTP_Pcal_clust_sec1->Fill(n_VTP_PCal_clust_sec2, sec2);


            map<int, double> min_vtp_energy_time_PCal;
            map<int, double> min_vtp_count_time_PCal;

            double E_min = 1000;
            for (int ivtp_cl1 = 0; ivtp_cl1 < n_VTP_PCal_clust_sec1; ivtp_cl1++) {

                TEC_Cluster *vtp_ec_cl1 = vtp1.GetPCalCluster(sec1, ivtp_cl1);

                h_t_VTP_PCal_clust_sec1->Fill(vtp_ec_cl1->time, sec1);

                if (vtp_ec_cl1->time >= VTP_PCal_tmin && vtp_ec_cl1->time <= VTP_PCal_tmax) {
                    h_E_VTP_PCal_sec1->Fill(vtp_ec_cl1->energy / 10000., sec1);
                    //                   cout<<vtp_ec_cl1->time<<"    "<<vtp_ec_cl1->energy<<endl;    

                    if (min_vtp_energy_time_PCal.count(vtp_ec_cl1->time) == 0) {
                        min_vtp_energy_time_PCal[vtp_ec_cl1->time] = 10000.;
                        min_vtp_count_time_PCal[vtp_ec_cl1->time] = 0;
                    }

                    min_vtp_count_time_PCal[vtp_ec_cl1->time] = min_vtp_count_time_PCal[vtp_ec_cl1->time] + 1;
                    if (vtp_ec_cl1->energy / 10000. < min_vtp_energy_time_PCal[vtp_ec_cl1->time]) {
                        min_vtp_energy_time_PCal[vtp_ec_cl1->time] = vtp_ec_cl1->energy / 10000.;
                    }


                    if (vtp_ec_cl1->energy / 10000. < E_min) {
                        E_min = vtp_ec_cl1->energy / 10000.;
                    }


                }

            }

            if (1 /*min_vtp_count_time_PCal[7] == 4 && min_vtp_count_time_PCal[8] == 4 */) {
                h_Emin_VTP_PCal_sec1->Fill(E_min, sec1);
                //                cout << "Calculated Emin = " << E_min << endl;
                //
                //                if (E_min > 0.15) {
                //                    cin.ignore();
                //                }

            }
            //         cout << "    =======================    " << endl;
            double Emin_PCal1 = E_min;


            min_vtp_energy_time_PCal.clear();
            min_vtp_count_time_PCal.clear();
           
            E_min = 1000;
            for (int ivtp_cl2 = 0; ivtp_cl2 < n_VTP_PCal_clust_sec2; ivtp_cl2++) {

                TEC_Cluster *vtp_ec_cl2 = vtp1.GetPCalCluster(sec2, ivtp_cl2);

                h_t_VTP_PCal_clust_sec1->Fill(vtp_ec_cl2->time, sec2);

                if (vtp_ec_cl2->time >= VTP_PCal_tmin && vtp_ec_cl2->time <= VTP_PCal_tmax) {
                    h_E_VTP_PCal_sec1->Fill(vtp_ec_cl2->energy / 10000., sec2);
                    //                   cout<<vtp_ec_cl1->time<<"    "<<vtp_ec_cl1->energy<<endl;    

                    if (min_vtp_energy_time_PCal.count(vtp_ec_cl2->time) == 0) {
                        min_vtp_energy_time_PCal[vtp_ec_cl2->time] = 10000.;
                        min_vtp_count_time_PCal[vtp_ec_cl2->time] = 0;
                    }

                    min_vtp_count_time_PCal[vtp_ec_cl2->time] = min_vtp_count_time_PCal[vtp_ec_cl2->time] + 1;
                    if (vtp_ec_cl2->energy / 10000. < min_vtp_energy_time_PCal[vtp_ec_cl2->time]) {
                        min_vtp_energy_time_PCal[vtp_ec_cl2->time] = vtp_ec_cl2->energy / 10000.;
                    }


                    if (vtp_ec_cl2->energy / 10000. < E_min) {
                        E_min = vtp_ec_cl2->energy / 10000.;
                    }


                }

            }


            if (/* min_vtp_count_time_PCal[7] == 4 && min_vtp_count_time_PCal[8] == 4*/ 1) {
                h_Emin_VTP_PCal_sec1->Fill(E_min, sec2);
            }
            double Emin_PCal2 = E_min;
            
            //= = = = = = = = = = = = = = = = = EC Clusters = = = = = = = = = = = = = = = = =
            
            int n_VTP_EC_clust_sec1 = vtp1.GetNECClusters(sec1);
            int n_VTP_EC_clust_sec2 = vtp1.GetNECClusters(sec2);


            map<int, double> min_vtp_energy_time_EC;
            map<int, double> min_vtp_count_time_EC;

            E_min = 1000;
            for (int ivtp_cl1 = 0; ivtp_cl1 < n_VTP_EC_clust_sec1; ivtp_cl1++) {

                TEC_Cluster *vtp_ec_cl1 = vtp1.GetECCluster(sec1, ivtp_cl1);

                h_t_VTP_EC_clust_sec1->Fill(vtp_ec_cl1->time, sec1);

                if (vtp_ec_cl1->time >= VTP_EC_tmin && vtp_ec_cl1->time <= VTP_EC_tmax) {
                    h_E_VTP_EC_sec1->Fill(vtp_ec_cl1->energy / 10000., sec1);
                    //                   cout<<vtp_ec_cl1->time<<"    "<<vtp_ec_cl1->energy<<endl;    

                    if (min_vtp_energy_time_EC.count(vtp_ec_cl1->time) == 0) {
                        min_vtp_energy_time_EC[vtp_ec_cl1->time] = 10000.;
                        min_vtp_count_time_EC[vtp_ec_cl1->time] = 0;
                    }

                    min_vtp_count_time_EC[vtp_ec_cl1->time] = min_vtp_count_time_EC[vtp_ec_cl1->time] + 1;
                    if (vtp_ec_cl1->energy / 10000. < min_vtp_energy_time_EC[vtp_ec_cl1->time]) {
                        min_vtp_energy_time_EC[vtp_ec_cl1->time] = vtp_ec_cl1->energy / 10000.;
                    }


                    if (vtp_ec_cl1->energy / 10000. < E_min) {
                        E_min = vtp_ec_cl1->energy / 10000.;
                    }


                }

            }
            if (/* min_vtp_count_time_PCal[7] == 4 && min_vtp_count_time_PCal[8] == 4*/ 1) {
                h_Emin_VTP_EC_sec1->Fill(E_min, sec1);
            }
            double Emin_EC1 = E_min;
            

            min_vtp_energy_time_EC.clear();
            min_vtp_count_time_EC.clear();

            E_min = 1000;
            for (int ivtp_cl2 = 0; ivtp_cl2 < n_VTP_EC_clust_sec2; ivtp_cl2++) {

                TEC_Cluster *vtp_ec_cl2 = vtp1.GetECCluster(sec2, ivtp_cl2);

                h_t_VTP_EC_clust_sec1->Fill(vtp_ec_cl2->time, sec2);

                if (vtp_ec_cl2->time >= VTP_EC_tmin && vtp_ec_cl2->time <= VTP_EC_tmax) {
                    h_E_VTP_EC_sec1->Fill(vtp_ec_cl2->energy / 10000., sec2);
                    //                   cout<<vtp_ec_cl1->time<<"    "<<vtp_ec_cl1->energy<<endl;

                    if (min_vtp_energy_time_EC.count(vtp_ec_cl2->time) == 0) {
                        min_vtp_energy_time_EC[vtp_ec_cl2->time] = 10000.;
                        min_vtp_count_time_EC[vtp_ec_cl2->time] = 0;
                    }

                    min_vtp_count_time_EC[vtp_ec_cl2->time] = min_vtp_count_time_EC[vtp_ec_cl2->time] + 1;
                    if (vtp_ec_cl2->energy / 10000. < min_vtp_energy_time_EC[vtp_ec_cl2->time]) {
                        min_vtp_energy_time_EC[vtp_ec_cl2->time] = vtp_ec_cl2->energy / 10000.;
                    }


                    if (vtp_ec_cl2->energy / 10000. < E_min) {
                        E_min = vtp_ec_cl2->energy / 10000.;
                    }


                }

            }
            if (/* min_vtp_count_time_PCal[7] == 4 && min_vtp_count_time_PCal[8] == 4*/ 1) {
                h_Emin_VTP_EC_sec1->Fill(E_min, sec2);
            }
            double Emin_EC2 = E_min;
            
            double Etot1 = Emin_PCal1 + Emin_EC1;
            double Etot2 = Emin_PCal2 + Emin_EC2;
            
            h_Emin_VTP_Etot_sec1->Fill(Etot1, sec1);
            h_Emin_VTP_Etot_sec1->Fill(Etot2, sec2);
            
        }

    }


    gDirectory->Write();
}

#endif // MUON_TRIGGER_H


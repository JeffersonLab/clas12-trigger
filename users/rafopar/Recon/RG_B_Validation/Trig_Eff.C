#define Trig_Eff_cxx
#include "Trig_Eff.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>

#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_stream.h>

#include <VTPRoot.hh>

#include <iostream>
#include <fstream>

using namespace std;

void Trig_Eff::Loop() {
    //   In a ROOT session, you can do:
    //      root> .L Trig_Eff.C
    //      root> Trig_Eff t
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
    const int VTP_TrigTag = 29; // 11101
    const int n_max_npart = 30;
    const int n_sect = 6;
    const double scale_PCal_coord = 1. / 6.5;
    const double scale_EC_coord = 1. / 8.;

    const double PCal_Threshold = 0.06;
    const double EC_Threshold = 0.01;
    const double ESum_Threshold = 0.3;

    const double t_HTCC_max = 340; // above this VTB banks are lost

    // const double SF_max = 0.26;
    // const double SF_min = 0.18;
    const double SF_max = 0.39;
    const double SF_min = 0.18;
    const double SF_min_noEC = 0.15;
    const double PCal_MIP_cut = 0.045;

    const double Nphe_cut = 2;


    const double PCal_UMax_cut = 80.;
    const double PCal_UMin_cut = 3.; // For oubendings this doesn't matter much;
    const double PCal_VMax_cut = 70.;
    const double PCal_VMin_cut = 3.;
    const double PCal_WMax_cut = 70.;
    const double PCal_WMin_cut = 3.;

    const double ECin_UMax_cut = 34.;
    const double ECin_UMin_cut = 2.; // For oubendings this doesn't matter much;
    const double ECin_VMax_cut = 34.;
    const double ECin_VMin_cut = 3.;
    const double ECin_WMax_cut = 34.;
    const double ECin_WMin_cut = 3.;

    const double ECout_UMax_cut = 34.;
    const double ECout_UMin_cut = 3.; // For oubendings this doesn't matter much;
    const double ECout_VMax_cut = 34;
    const double ECout_VMin_cut = 3.;
    const double ECout_WMax_cut = 33.;
    const double ECout_WMin_cut = 3.;

    const double vz_MAX_cut = 5.;
    const double vz_MIN_cut = -10.;

    TLorentzVector L_beam, L_em, L_targ, L_W;
    L_beam.SetPxPyPzE(0., 0., Eb, Eb);
    L_targ.SetPxPyPzE(0., 0., 0., Mp);

    TFile *file_out = new TFile(Form("Trig_Eff_%d.root", frun), "Recreate");
    //TFile *file_out = new TFile(Form("Data/skim_em_%d.root", frun), "Recreate");

    //TTree *skim_tree = (TTree*)fChain->CloneTree(0);

    TH1D *h_vtp_tr_time = new TH1D("h_vtp_tr_time", "", 402, -0.5, 401.5);
    TH1D *h_vtp_tr_bits1 = new TH1D("h_vtp_tr_bits1", "", 33, -0.5, 32.5);

    TH1D *h_n_part1 = new TH1D("h_n_part1", "", 21, -0.5, 20.5);
    TH1D *h_nphe1 = new TH1D("h_nphe1", "", 200, 0., 50.);
    TH1D *h_nphe2 = new TH1D("h_nphe2", "", 200, 0., 50.);
    TH2D *h_nphe_phi1 = new TH2D("h_nphe_phi1", "", 200, 0., 50., 60, 0., 360.);
    TH2D *h_nphe_phi2 = new TH2D("h_nphe_phi2", "", 200, 0., 50., 60, 0., 360.);

    TH1D *h_W1 = new TH1D("h_W1", "", 200, 0.5 * Mp, 2.2 * Mp);
    TH1D *h_W2 = new TH1D("h_W2", "", 200, 0.5 * Mp, 2.2 * Mp);
    TH1D *h_W3 = new TH1D("h_W3", "", 200, 0.5 * Mp, 2.2 * Mp);

    TH1D *h_W_Good_em1 = new TH1D("h_W_Good_em1", "", 200, 0.5 * Mp, 2.2 * Mp);
    TH1D *h_W_Good_em_trg_thresholds1 = new TH1D("h_W_Good_em_trg_thresholds1", "", 200, 0.5 * Mp, 2.2 * Mp);
    TH1D *h_W_Good_em_missed1 = new TH1D("h_W_Good_em_missed1", "", 200, 0.5 * Mp, 2.2 * Mp);
    TH1D *h_W_Good_em_missed_trg_thresholds1 = new TH1D("h_W_Good_em_missed_trg_thresholds1", "", 200, 0.5 * Mp, 2.2 * Mp);
    TH1D *h_W_Good_noEC1 = new TH1D("h_W_Good_noEC1", "", 200, 0.5 * Mp, 2.2 * Mp);
    TH1D *h_W_Good_noEC_trg_thresholds1 = new TH1D("h_W_Good_noEC_trg_thresholds1", "", 200, 0.5 * Mp, 2.2 * Mp);
    TH1D *h_W_Good_noEC_missed1 = new TH1D("h_W_Good_noEC_missed1", "", 200, 0.5 * Mp, 2.2 * Mp);
    TH1D *h_W_Good_noEC_missed_trg_thresholds1 = new TH1D("h_W_Good_noEC_missed_trg_thresholds1", "", 200, 0.5 * Mp, 2.2 * Mp);

    TH2D *h_n_HTCC_trg_good_em_missed0 = new TH2D("h_n_HTCC_trg_good_em_missed0", "", 10, -0.5, 9.5, 7, -0.5, 6.5);
    TH2D *h_n_HTCC_trg_good_em_missed1 = new TH2D("h_n_HTCC_trg_good_em_missed1", "", 10, -0.5, 9.5, 7, -0.5, 6.5);

    TH2D *h_n_HTCC_trg_good_em_P1 = new TH2D("h_n_HTCC_trg_good_em_P1", "", 100, 0.02 * Eb, 1.2 * Eb, 5, -0.5, 4.5);
    TH2D *h_n_HTCC_trg_good_em_nphe1 = new TH2D("h_n_HTCC_trg_good_em_nphe1", "", 40, -0.5, 39.5, 5, -0.5, 4.5);
    TH2D *h_n_HTCC_trg_good_em_nphe2 = new TH2D("h_n_HTCC_trg_good_em_nphe2", "", 40, -0.5, 39.5, 5, -0.5, 4.5);
    TH2D *h_n_HTCC_trg_good_em_P2 = new TH2D("h_n_HTCC_trg_good_em_P2", "", 100, 0.02 * Eb, 1.2 * Eb, 5, -0.5, 4.5);

    TH2D *h_nphe_sect_missing1 = new TH2D("h_nphe_sect_missing1", "", 56, -0.5, 55.5, 7, -0.5, 6.5);
    TH2D *h_HTCC_YXc_miss1 = new TH2D("h_HTCC_YXc_miss1", "", 100, -100, 100, 100, -100, 100.);
    TH2D *h_HTCC_YXc_miss2 = new TH2D("h_HTCC_YXc_miss2", "", 100, -100, 100, 100, -100, 100.);
    TH2D *h_HTCC_YXc_miss3 = new TH2D("h_HTCC_YXc_miss3", "", 100, -100, 100, 100, -100, 100.);
    TH2D *h_HTCC_YXc_miss4 = new TH2D("h_HTCC_YXc_miss4", "", 100, -100, 100, 100, -100, 100.);
    
    TH2D *h_sec_PCal_HTCC_miss1 = new TH2D("h_sec_PCal_HTCC_miss1", "", 7, -0.5, 6.5, 7, -0.5, 6.5);
    TH2D *h_sec_PCal_HTCC_miss2 = new TH2D("h_sec_PCal_HTCC_miss2", "", 7, -0.5, 6.5, 7, -0.5, 6.5);
    
    TH1D *h_nphe_HTCC_miss1 = new TH1D("h_nphe_HTCC_miss1", "", 100, -0.5, 35.5);
    TH1D *h_nphe_HTCC_miss2 = new TH1D("h_nphe_HTCC_miss2", "", 100, -0.5, 35.5);
    
    TH2D *h_t_HTCC_nphe_missed1 = new TH2D("h_t_HTCC_nphe_missed1", "", 200, 0., 400., 55, -0.5, 54.5);

    TH2D *h_n_PCal_trg_good_em_P1 = new TH2D("h_n_PCal_trg_good_em_P1", "", 100, 0.02 * Eb, 1.2 * Eb, 5, -0.5, 4.5);
    TH2D *h_n_PCal_trg_good_em_P2 = new TH2D("h_n_PCal_trg_good_em_P2", "", 100, 0.02 * Eb, 1.2 * Eb, 5, -0.5, 4.5);
    TH2D *h_n_EC_trg_good_em_P1 = new TH2D("h_n_EC_trg_good_em_P1", "", 100, 0.02 * Eb, 1.2 * Eb, 5, -0.5, 4.5);
    TH2D *h_n_EC_trg_good_em_P2 = new TH2D("h_n_EC_trg_good_em_P2", "", 100, 0.02 * Eb, 1.2 * Eb, 5, -0.5, 4.5);
    TH2D *h_n_DCeleinbend_trg_good_em_P2 = new TH2D("h_n_DCeleinbend_trg_good_em_P2", "", 200, 0.02 * Eb, 1.2 * Eb, 5, -0.5, 4.5);

    TH2D *h_HTCC_vtp_em_sect1 = new TH2D("h_HTCC_vtp_em_sect1", "", 7, -0.5, 6.5, 7, -0.5, 6.5);
    TH2D *h_PCal_vtp_em_sect1 = new TH2D("h_PCal_vtp_em_sect1", "", 7, -0.5, 6.5, 7, -0.5, 6.5);
    TH2D *h_EC_vtp_em_sect1 = new TH2D("h_EC_vtp_em_sect1", "", 7, -0.5, 6.5, 7, -0.5, 6.5);
    TH2D *h_DCinbend_vtp_em_sect1 = new TH2D("h_DCinbend_vtp_em_sect1", "", 7, -0.5, 6.5, 7, -0.5, 6.5);


    TH1D *h_P_em1 = new TH1D("h_P_em1", "", 100, 0.02 * Eb, 1.2 * Eb);
    TH1D *h_P_neg1 = new TH1D("h_P_neg1", "", 100, 0.02 * Eb, 1.2 * Eb);

    TH1D *h_P_Good_em1 = new TH1D("h_P_Good_em1", "", 100, 0.02 * Eb, 1.2 * Eb);
    TH1D *h_P_Good_em_trg_thresholds1 = new TH1D("h_P_Good_em_trg_thresholds1", "", 100, 0.02 * Eb, 1.2 * Eb);
    TH1D *h_P_Good_em_trg_thresholds_tr_found1 = new TH1D("h_P_Good_em_trg_thresholds_tr_found1", "", 100, 0.02 * Eb, 1.2 * Eb);
    TH1D *h_P_Good_em_trg_thresholds_NoDCRoad1 = new TH1D("h_P_Good_em_trg_thresholds_NoDCRoad1", "", 100, 0.02 * Eb, 1.2 * Eb);
    TH1D *h_P_Good_em_missed1 = new TH1D("h_P_Good_em_missed1", "", 100, 0.02 * Eb, 1.2 * Eb);
    TH1D *h_P_Good_em_missed_trg_thresholds1 = new TH1D("h_P_Good_em_missed_trg_thresholds1", "", 100, 0.02 * Eb, 1.2 * Eb);
    TH1D *h_P_Good_em_missed_trg_thresholds_nphefail1 = new TH1D("h_P_Good_em_missed_trg_thresholds_nphefail1", "", 100, 0.02 * Eb, 1.2 * Eb);

    TH1D *h_P_Good_noEC1 = new TH1D("h_P_Good_noEC1", "", 100, 0.02 * Eb, 1.2 * Eb);
    TH1D *h_P_Good_noEC_trg_thresholds1 = new TH1D("h_P_Good_noEC_trg_thresholds1", "", 100, 0.02 * Eb, 1.2 * Eb);
    TH1D *h_P_Good_noEC_missed1 = new TH1D("h_P_Good_noEC_missed1", "", 100, 0.02 * Eb, 1.2 * Eb);
    TH1D *h_P_Good_noEC_missed_trg_thresholds1 = new TH1D("h_P_Good_noEC_missed_trg_thresholds1", "", 100, 0.02 * Eb, 1.2 * Eb);

    TH1D *h_P_Good_em0 = new TH1D("h_P_Good_em0", "", 100, 0.02 * Eb, 1.2 * Eb);
    TH1D *h_P_Good_em_DC_Missed0 = new TH1D("h_P_Good_em_DC_Missed0", "", 100, 0.02 * Eb, 1.2 * Eb);
    TH1D *h_P_Good_em_trg_thresholds_DC_Missed0 = new TH1D("h_P_Good_em_trg_thresholds_DC_Missed0", "", 100, 0.02 * Eb, 1.2 * Eb);
    TH1D *h_vz_Good_em0 = new TH1D("h_vz_Good_em0", "", 200, -25., 25.);
    TH1D *h_vz_Good_em_tr_missed0 = new TH1D("h_vz_Good_em_tr_missed0", "", 200, -25., 55.);
    TH1D *h_vz_Good_em_trg_thresholds_DC_Missed0 = new TH1D("h_vz_Good_em_trg_thresholds_DC_Missed0", "", 200, -25., 25.);
    TH2D *h_PCal_yxc_trg_thresholds_DC_Missed0 = new TH2D("h_PCal_yxc_trg_thresholds_DC_Missed0", "", 200, -420., 420., 200, -420., 420.);


    TH1D *h_t_HTCC1 = new TH1D("h_t_HTCC1", "", 200, 0., 400);
    TH1D *h_t_HTCC2 = new TH1D("h_t_HTCC2", "", 200, 0., 400);

    TH2D *h_VTP_HTCC_times1 = new TH2D("h_VTP_HTCC_times1", "", 200, 0., 400., 200, 0., 405.);
    TH2D *h_VTP_HTCC_times2 = new TH2D("h_VTP_HTCC_times2", "", 200, 0., 400., 200, 0., 405.);
    TH2D *h_VTP_HTCC_times2_2 = new TH2D("h_VTP_HTCC_times2_2", "", 200, 0., 400., 200, 0., 405.);
    TH2D *h_VTP_HTCC_times3 = new TH2D("h_VTP_HTCC_times3", "", 200, 0., 400., 200, 0., 405.);
    TH2D *h_VTP_HTCC_times4 = new TH2D("h_VTP_HTCC_times4", "", 200, 0., 400., 200, 0., 405.);
    TH2D *h_VTP_HTCC_times5 = new TH2D("h_VTP_HTCC_times5", "", 200, 0., 400., 200, 0., 405.);
    TH2D *h_VTP_HTCC_times6 = new TH2D("h_VTP_HTCC_times6", "", 200, 0., 400., 200, 0., 405.);


    TH2D *h_PCal_yxc1 = new TH2D("h_PCal_yxc1", "", 200, -420., 420., 200, -420., 420.);
    TH2D *h_PCal_yxc2 = new TH2D("h_PCal_yxc2", "", 200, -420., 420., 200, -420., 420.);
    TH2D *h_PCal_yxc3 = new TH2D("h_PCal_yxc3", "", 200, -420., 420., 200, -420., 420.);
    TH1D *h_PCal_U1 = new TH1D("h_PCal_U1", "", 200, 0., 86.);
    TH1D *h_PCal_V1 = new TH1D("h_PCal_V1", "", 200, 0., 80.);
    TH1D *h_PCal_W1 = new TH1D("h_PCal_W1", "", 200, 0., 80.);
    TH2D *h_PCal_E_sec1 = new TH2D("h_PCal_E_sec1", "", 200, 0., 0.6, 7, -0.5, 6.5);

    TH2D *h_ECin_yxc1 = new TH2D("h_ECin_yxc1", "", 200, -420., 420., 200, -420., 420.);
    TH2D *h_ECin_yxc2 = new TH2D("h_ECin_yxc2", "", 200, -420., 420., 200, -420., 420.);
    TH1D *h_ECin_U1 = new TH1D("h_ECin_U1", "", 200, 0., 40.);
    TH1D *h_ECin_V1 = new TH1D("h_ECin_V1", "", 200, 0., 40.);
    TH1D *h_ECin_W1 = new TH1D("h_ECin_W1", "", 200, 0., 40.);

    TH2D *h_ECout_yxc1 = new TH2D("h_ECout_yxc1", "", 200, -420., 420., 200, -420., 420.);
    TH2D *h_ECout_yxc2 = new TH2D("h_ECout_yxc2", "", 200, -420., 420., 200, -420., 420.);
    TH1D *h_ECout_U1 = new TH1D("h_ECout_U1", "", 200, 0., 40.);
    TH1D *h_ECout_V1 = new TH1D("h_ECout_V1", "", 200, 0., 40.);
    TH1D *h_ECout_W1 = new TH1D("h_ECout_W1", "", 200, 0., 40.);

    TH2D *h_ETot_sec1 = new TH2D("h_ETot_sec1", "", 200, 0., 1.6, 7, -0.5, 6.5);
    TH2D *h_ETot_sec2 = new TH2D("h_ETot_sec2", "", 200, 0., 1.6, 7, -0.5, 6.5);
    TH2D *h_ETot_sec3 = new TH2D("h_ETot_sec3", "", 200, 0., 1.6, 7, -0.5, 6.5);
    TH2D *h_ETot_sec4 = new TH2D("h_ETot_sec4", "", 200, 0., 1.6, 7, -0.5, 6.5);

    TH2D *h_SF1 = new TH2D("h_SF1", "", 200, 0., 1.2 * Eb, 200, 0., 0.5);
    TH2D * h_SF1_[n_sect];
    TH2D * h_SF2_[n_sect];
    TH2D * h_SF3_[n_sect];

    TH2D * h_th_P1_[n_sect];
    TH2D * h_th_P2_[n_sect];


    for (int i = 0; i < n_sect; i++) {
        h_SF1_[i] = new TH2D(Form("h_SF1_%d", i), "", 200, 0., 1.2 * Eb, 200, 0., 0.5);
        h_SF2_[i] = new TH2D(Form("h_SF2_%d", i), "", 200, 0., 1.2 * Eb, 200, 0., 0.5);
        h_SF3_[i] = new TH2D(Form("h_SF3_%d", i), "", 200, 0., 1.2 * Eb, 200, 0., 0.5);

        h_th_P1_[i] = new TH2D(Form("h_th_P1_%d", i), "", 200, 0., 1.2 * Eb, 200, 0., 45.);
        h_th_P2_[i] = new TH2D(Form("h_th_P2_%d", i), "", 200, 0., 1.2 * Eb, 200, 0., 45.);

    }

    TH2D *h_E_EC_sec1 = new TH2D("h_E_EC_sec1", "", 200, 0., 0.5, 7, -0.6, 6.5);
    TH2D *h_E_EC_sec2 = new TH2D("h_E_EC_sec2", "", 200, 0., 0.5, 7, -0.6, 6.5);
    TH2D *h_E_EC_sec3 = new TH2D("h_E_EC_sec3", "", 200, 0., 0.5, 7, -0.6, 6.5);

    TH2D *h_E_PCal_sec1 = new TH2D("h_E_PCal_sec1", "", 200, 0., 1.5, 7, -0.6, 6.5);
    TH2D *h_E_PCal_sec2 = new TH2D("h_E_PCal_sec2", "", 200, 0., 1.5, 7, -0.6, 6.5);


    TH2D *h_EC_yxc1 = new TH2D("h_EC_yxc1", "", 200, -420., 420., 200, -420., 420.);
    TH2D *h_EC_yxc2 = new TH2D("h_EC_yxc2", "", 200, -420., 420., 200, -420., 420.);
    TH2D *h_EC_yxc3 = new TH2D("h_EC_yxc3", "", 200, -420., 420., 200, -420., 420.);


    ofstream miss_events("tr_missing.dat");

    Long64_t nentries = fChain->GetEntriesFast();

    //nentries = 100000;

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);
        nbytes += nb;
        // if (Cut(ientry) < 0) continue;

        if ((ientry + 1) % 10000 == 0) {
            cout.flush() << "           Processed:       " << ientry << "\r";
        }


        long int run_conf_ev_number = RUN_config_event->at(0);
        long int run_conf_RUN = RUN_config_run->at(0);

        vector<int> v_vtp_time;
        vector<ap_int < 32 >> v_vtp_trbit;

        for (int ii = 0; ii < RAW_vtp_crate->size(); ii++) {

            //cout<<RAW_vtp_crate->at(ii)<<"      "<<RAW_vtp_word->at(ii)<<endl;

            if (RAW_vtp_crate->at(ii) == 100) {
                ap_int<32> vtp_word = ap_int<32>(RAW_vtp_word->at(ii));

                //cout<<vtp_word(31, 27)<<endl;

                if (vtp_word(31, 27) == VTP_TrigTag) {

                    int vtp_time = vtp_word(26, 16);
                    h_vtp_tr_time->Fill(vtp_time);

                    ap_int<32> vtp_tr_bits;
                    vtp_tr_bits(15, 0) = vtp_word(15, 0);

                    vtp_word = ap_int<32>(RAW_vtp_word->at(ii + 1));
                    vtp_tr_bits(31, 16) = vtp_word(15, 0);

                    v_vtp_time.push_back(vtp_time);
                    v_vtp_trbit.push_back(vtp_tr_bits);

                    for (int ibit = 0; ibit < 32; ibit++) {
                        h_vtp_tr_bits1->Fill(ibit, vtp_tr_bits(ibit, ibit));
                    }

                    ii = ii + 1;
                }

            }

        }


        VTPRoot vtp1(RAW_vtp_crate, RAW_vtp_word);

        int n_Inbend_DC_Roads[n_sect] = {0};

        for (int isec = 0; isec < n_sect; isec++) {
            int n_cur_roads = vtp1.GetNDCRoads(isec);

            for (int iroad = 0; iroad < n_cur_roads; iroad++) {

                if (vtp1.IsRoadInbending(isec, iroad)) {
                    n_Inbend_DC_Roads[isec] = n_Inbend_DC_Roads[isec] + 1;
                }

            }

            //cout<<"sec = "<<isec<<"          N_Inbend_DCRoads = "<<n_Inbend_DC_Roads[isec]<<endl;
        }

        int ev_number_VTP = vtp1.GetEvNumber();


        int n_part = TMath::Min(int(REC_Particle_pz->size()), n_max_npart);
        map<int, int> ind_HTCC;
        map<int, int> ind_PCal;
        map<int, int> ind_ECin;
        map<int, int> ind_ECout;

        h_n_part1->Fill(n_part);

        bool em_candidate = false;

        for (int i_part = 0; i_part < n_part; i_part++) {

            // ==== Before assigning, index, all indexes are initialized to -1, this way we can check, whether
            // ==== that particular detector is related to the particle "i_part"
            ind_HTCC[i_part] = -1;
            ind_PCal[i_part] = -1;
            ind_ECin[i_part] = -1;
            ind_ECout[i_part] = -1;

            // =============================== HTCC ===============================
            for (int i_cc = 0; i_cc < REC_Cherenkov_detector->size(); i_cc++) {

                // Want only HTCC for now
                if (REC_Cherenkov_detector->at(i_cc) == HTCC_TYPE) {

                    if (REC_Cherenkov_pindex->at(i_cc) == i_part) {
                        ind_HTCC[i_part] = i_cc;
                    }
                }
            }


            // =============================== PCal, ECin, ECout ===============================
            for (int i_cal = 0; i_cal < REC_Calorimeter_detector->size(); i_cal++) {

                if (REC_Calorimeter_pindex->at(i_cal) == i_part) {

                    if (REC_Calorimeter_layer->at(i_cal) == 1) {
                        ind_PCal[i_part] = i_cal;
                    } else if (REC_Calorimeter_layer->at(i_cal) == 4) {
                        ind_ECin[i_part] = i_cal;
                    } else if (REC_Calorimeter_layer->at(i_cal) == 7) {
                        ind_ECout[i_part] = i_cal;
                    }
                }

            }

            if (ind_HTCC[i_part] >= 0 && ind_PCal[i_part] >= 0 && REC_Particle_charge->at(i_part) < 0) {
                em_candidate = true;
            }

        }

        // if( em_candidate ){
        // 	skim_tree->Fill();
        // }

        for (int i_part = 0; i_part < n_part; i_part++) {

            // ======= Selecting only negatives
            if (REC_Particle_charge->at(i_part) >= 0) {
                continue;
            }
            if (REC_Particle_pid->at(i_part) != 11) {
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

            int sect_particle = int(phi / 60.);

            double P = sqrt(Px * Px + Py * Py + Pz * Pz);

            double vz = double(REC_Particle_vz->at(i_part));

            h_P_neg1->Fill(P);

            if (REC_Particle_pid->at(i_part) == 11) {
                h_P_em1->Fill(P);
            }


            L_em.SetPxPyPzE(Px, Py, Pz, P);
            L_W = L_targ + L_beam - L_em;

            double W = L_W.M();

            bool HTCC_pass = false;
            bool PCal_pass = false;
            bool ECin_pass = false;
            bool ECout_pass = false;
            bool EC_pass = false;

            double nphe = -1;
            double phi_HTCC = -1000.;

            double PCal_U = -1;
            double PCal_V = -1;
            double PCal_W = -1;
            double PCal_y = 0.;
            double PCal_x = 0.;

            double ECin_U = -1;
            double ECin_V = -1;
            double ECin_W = -1;
            double ECin_y = 0.;
            double ECin_x = 0.;

            double ECout_U = -1;
            double ECout_V = -1;
            double ECout_W = -1;

            double EPCal = 0; // PCal energy
            double EECin = 0; // ECin energy
            double EECout = 0; // ECout Energy

            double E_EC = 0; // EC energy = E_ECin + E_ECout
            double E_tot = 0; // Tot energy E_PCal + E_ECin + E_Ecout (if exists)

            // ======================== HTCC =======================
            if (ind_HTCC[i_part] >= 0) {
                int ind_HTCC_rec = REC_Cherenkov_index->at(ind_HTCC[i_part]);

                //cout<<HTCC_rec_nphe->at(ind_HTCC_rec) - REC_Cherenkov_nphe->at(ind_HTCC[i_part])<<endl;

                nphe = HTCC_rec_nphe->at(ind_HTCC_rec);
                phi_HTCC = HTCC_rec_phi->at(ind_HTCC_rec) * r2d + 30.;
                if (phi_HTCC < 0.) {
                    phi_HTCC = phi_HTCC + 360.;
                };

                h_nphe1->Fill(nphe);
                h_nphe_phi1->Fill(nphe, phi_HTCC);

                if (nphe > Nphe_cut) {
                    HTCC_pass = true;
                }
            }

            // ======================== PCal =======================
            if (ind_PCal[i_part] >= 0) {
                int ind_PCal_cl = REC_Calorimeter_index->at(ind_PCal[i_part]);
                //cout<<ECAL_clusters_x->at(ind_PCal_cl)<<"     "<<REC_Calorimeter_x->at(ind_PCal[i_part])<<endl;

                PCal_y = ECAL_clusters_y->at(ind_PCal_cl);
                PCal_x = ECAL_clusters_x->at(ind_PCal_cl);
                h_PCal_yxc1->Fill(PCal_x, PCal_y);

                PCal_U = (ECAL_clusters_coordU->at(ind_PCal_cl) - 4.) * scale_PCal_coord;
                PCal_V = (ECAL_clusters_coordV->at(ind_PCal_cl) - 4.) * scale_PCal_coord;
                PCal_W = (ECAL_clusters_coordW->at(ind_PCal_cl) - 4.) * scale_PCal_coord;

                EPCal = ECAL_clusters_energy->at(ind_PCal_cl);


                h_PCal_U1->Fill(PCal_U);
                h_PCal_V1->Fill(PCal_V);
                h_PCal_W1->Fill(PCal_W);

                if (PCal_U > PCal_UMin_cut && PCal_U < PCal_UMax_cut && PCal_V > PCal_VMin_cut && PCal_V < PCal_VMax_cut &&
                        PCal_W > PCal_WMin_cut && PCal_W < PCal_WMax_cut) {

                    h_PCal_yxc2->Fill(PCal_x, PCal_y);
                    h_PCal_E_sec1->Fill(EPCal, sect_particle);
                    PCal_pass = true;
                }
            }

            // ======================== EC In =======================
            if (ind_ECin[i_part] >= 0) {
                int ind_ECin_cl = REC_Calorimeter_index->at(ind_ECin[i_part]);

                ECin_y = ECAL_clusters_y->at(ind_ECin_cl);
                ECin_x = ECAL_clusters_x->at(ind_ECin_cl);
                h_ECin_yxc1->Fill(ECin_x, ECin_y);

                ECin_U = (ECAL_clusters_coordU->at(ind_ECin_cl) - 4) * scale_EC_coord;
                ECin_V = (ECAL_clusters_coordV->at(ind_ECin_cl) - 4) * scale_EC_coord;
                ECin_W = (ECAL_clusters_coordW->at(ind_ECin_cl) - 4) * scale_EC_coord;

                EECin = ECAL_clusters_energy->at(ind_ECin_cl);

                h_ECin_U1->Fill(ECin_U);
                h_ECin_V1->Fill(ECin_V);
                h_ECin_W1->Fill(ECin_W);

                if (ECin_U > ECin_UMin_cut && ECin_U < ECin_UMax_cut && ECin_V > ECin_VMin_cut && ECin_V < ECin_VMax_cut &&
                        ECin_W > ECin_WMin_cut && ECin_W < ECin_WMax_cut) {

                    h_ECin_yxc2->Fill(ECAL_clusters_x->at(ind_ECin_cl), ECAL_clusters_y->at(ind_ECin_cl));

                    ECin_pass = true;
                }

            }



            // ======================== EC Out =======================
            if (ind_ECout[i_part] >= 0) {
                int ind_ECout_cl = REC_Calorimeter_index->at(ind_ECout[i_part]);

                h_ECout_yxc1->Fill(ECAL_clusters_x->at(ind_ECout_cl), ECAL_clusters_y->at(ind_ECout_cl));

                EECout = ECAL_clusters_energy->at(ind_ECout_cl);

                ECout_U = (ECAL_clusters_coordU->at(ind_ECout_cl) - 4) * scale_EC_coord;
                ECout_V = (ECAL_clusters_coordV->at(ind_ECout_cl) - 4) * scale_EC_coord;
                ECout_W = (ECAL_clusters_coordW->at(ind_ECout_cl) - 4) * scale_EC_coord;

                h_ECout_U1->Fill(ECout_U);
                h_ECout_V1->Fill(ECout_V);
                h_ECout_W1->Fill(ECout_W);

                if (ECout_U > ECout_UMin_cut && ECout_U < ECout_UMax_cut && ECout_V > ECout_VMin_cut && ECout_V < ECout_VMax_cut &&
                        ECout_W > ECout_WMin_cut && ECout_W < ECout_WMax_cut) {

                    h_ECout_yxc2->Fill(ECAL_clusters_x->at(ind_ECout_cl), ECAL_clusters_y->at(ind_ECout_cl));
                    ECout_pass = true;
                }
            }

            E_EC = EECin + EECout;
            E_tot = E_EC + EPCal;

            bool trg_E_threshold_pass = (E_tot > ESum_Threshold) && (E_EC > EC_Threshold) && (EPCal > PCal_Threshold) ||
                    ((ind_ECin[i_part] < 0) && (EPCal > ESum_Threshold));

            double SF = E_tot / P;
            h_SF1->Fill(P, SF);

            h_ETot_sec1->Fill(E_tot, sect_particle);

            h_SF1_[sect_particle]->Fill(P, SF);

            if (SF > 0.2 && ind_PCal[i_part] >= 0 && ind_HTCC[i_part] >= 0 && PCal_pass && PCal_MIP_cut) {
                h_nphe2->Fill(nphe);
            }

            if (PCal_pass && EPCal > PCal_MIP_cut && nphe > 2) {
                h_SF2_[sect_particle]->Fill(P, SF);
            }

            if (ind_ECin[i_part] < 0 && ind_ECout[i_part] < 0 && ind_PCal[i_part] >= 0 && ind_HTCC[i_part] >= 0 && PCal_pass && nphe > 2) {
                h_SF3_[sect_particle]->Fill(P, SF);
            }

            bool Good_Electron = (ECin_pass && SF > SF_min && SF < SF_max && EPCal > PCal_MIP_cut && PCal_pass && HTCC_pass);
            bool Good_noEC = (ind_ECin[i_part] < 0 && SF > SF_min_noEC && HTCC_pass && PCal_pass && EPCal > PCal_MIP_cut);
            if (!(Good_Electron || Good_noEC)) {
                continue;
            }

            h_th_P1_[sect_particle]->Fill(P, th);
            h_EC_yxc1->Fill(PCal_x, PCal_y);
            h_W1->Fill(W);

            h_ETot_sec2->Fill(E_tot, sect_particle);

            if (Good_Electron) {
                h_W_Good_em1->Fill(W);
                h_ETot_sec3->Fill(E_tot, sect_particle);

                h_P_Good_em1->Fill(P);

                if (trg_E_threshold_pass) {
                    h_W_Good_em_trg_thresholds1->Fill(W);
                    h_P_Good_em_trg_thresholds1->Fill(P);
                }
            }
            if (Good_noEC) {
                h_W_Good_noEC1->Fill(W);
                h_P_Good_noEC1->Fill(P);
                h_ETot_sec4->Fill(E_tot, sect_particle);

                if (trg_E_threshold_pass) {
                    h_W_Good_noEC_trg_thresholds1->Fill(W);
                    h_P_Good_noEC_trg_thresholds1->Fill(P);
                }
            }


            int n_em_VTP_trig = 0; // Number of VTP triggeres with electron trigger, i.e. when bit 0 is set
            int n_em_VTP_trig_[n_sect] = {0};
            int n_em_VTP_trig_Good_em_[n_sect] = {0}; // Number of electron trigger bits when we have a good e-, i.e. with PCal, EC, nphe > 7 Fiducial and SF
            int n_em_VTP_trig_Good_noEC_[n_sect] = {0}; // Number of electron trigger bits when ECin is missing, nphe > 7 SF > 0.1 and PCal Fiducial
            int n_em_VTP_trig_HTCC_[n_sect] = {0}; // Number of HTCC trigger bints
            int n_em_VTP_trig_PCalEC_[n_sect] = {0}; // Number of PCalxEC triggers in a given sector
            int n_em_VTP_trig_PCal_[n_sect] = {0}; // Number of PCa triggers in a given sector
            int n_em_VTP_trig_EC_[n_sect] = {0}; // Number of EC triggers in a given sector
            int n_em_VTP_trig_eleDCroad_[n_sect] = {0}; // Number of Electron x DCRoad triggers in a given sector
            int n_em_VTP_trig_HTCC_allsec = 0; // Number of PCalxEC triggers in a given sector
            int n_em_VTP_trig_PCal_allsec = 0;
            int n_em_VTP_trig_EC_allsec = 0;

            int n_em_all_sect_trig = 0;
            int n_em_all_sect_DCinbend_trig = 0;

            double t_HTCC, t_VTP;

            int sec_em = REC_Calorimeter_sector->at(ind_PCal[i_part]) - 1;
            t_HTCC = double(REC_Cherenkov_time->at(ind_HTCC[i_part]));

            if (t_HTCC > t_HTCC_max) {
                continue;
            }

            double x_HTCC = HTCC_rec_x->at(REC_Cherenkov_index->at(ind_HTCC[i_part]));
            double y_HTCC = HTCC_rec_y->at(REC_Cherenkov_index->at(ind_HTCC[i_part]));

            phi_HTCC = atan2(y_HTCC, x_HTCC) * r2d + 30.;
            if (phi_HTCC < 0) {
                phi_HTCC = phi_HTCC + 360.;
            }

            int sec_HTCC = phi_HTCC / 60;
            
            
            if( sec_HTCC != sec_em ) {continue;}

            for (int i_vtp = 0; i_vtp < v_vtp_time.size(); i_vtp++) {

                h_VTP_HTCC_times1->Fill(REC_Cherenkov_time->at(ind_HTCC[i_part]), v_vtp_time.at(i_vtp));

                bool em_tot_trig = v_vtp_trbit.at(i_vtp)(0, 0);
                bool em_sect_trig = v_vtp_trbit.at(i_vtp)(1, 6);
                bool HTCC_trg = v_vtp_trbit.at(i_vtp)(7, 12);
                int em_sect_trig_int = v_vtp_trbit.at(i_vtp)(1, 6);
                bool PCal_trg = v_vtp_trbit.at(i_vtp)(13, 18);
                bool EC_trg = v_vtp_trbit.at(i_vtp)(19, 24);
                bool em_DC_inbend_trig = v_vtp_trbit.at(i_vtp)(25, 30);

                if (PCal_trg) {
                    n_em_VTP_trig_PCal_allsec = n_em_VTP_trig_PCal_allsec + 1;
                }
                if (EC_trg) {
                    n_em_VTP_trig_EC_allsec = n_em_VTP_trig_EC_allsec + 1;
                }

                if (HTCC_trg) {
                    n_em_VTP_trig_HTCC_allsec = n_em_VTP_trig_HTCC_allsec + 1;
                }

                if (em_sect_trig) {
                    n_em_all_sect_trig = n_em_all_sect_trig + 1;
                }

                if (em_DC_inbend_trig) {
                    n_em_all_sect_DCinbend_trig = n_em_all_sect_DCinbend_trig + 1;
                }

                for (int iS = 0; iS < n_sect; iS++) {

                    if (v_vtp_trbit.at(i_vtp)(iS + 7, iS + 7)) {
                        // ======= Checking the presence of the HTCC trigger
                        h_HTCC_vtp_em_sect1->Fill(sec_em, iS);
                        n_em_VTP_trig_HTCC_[iS] = n_em_VTP_trig_HTCC_[iS] + 1;
                    }

                    if (v_vtp_trbit.at(i_vtp)(iS + 13, iS + 13)) {
                        h_PCal_vtp_em_sect1->Fill(sec_em, iS);
                        n_em_VTP_trig_PCal_[iS] = n_em_VTP_trig_PCal_[iS] + 1;
                    }

                    if (v_vtp_trbit.at(i_vtp)(iS + 19, iS + 19)) {
                        h_EC_vtp_em_sect1->Fill(sec_em, iS);
                        n_em_VTP_trig_EC_[iS] = n_em_VTP_trig_EC_[iS] + 1;
                    }

                    if (v_vtp_trbit.at(i_vtp)(iS + 25, iS + 25)) {
                        h_DCinbend_vtp_em_sect1->Fill(sec_em, iS);
                        n_em_VTP_trig_eleDCroad_[iS] = n_em_VTP_trig_eleDCroad_[iS] + 1;
                        h_VTP_HTCC_times3->Fill(REC_Cherenkov_time->at(ind_HTCC[i_part]), v_vtp_time.at(i_vtp));
                    }


                    if (v_vtp_trbit.at(i_vtp)(iS + 1, iS + 1)) {
                        n_em_VTP_trig_[iS] = n_em_VTP_trig_[iS] + 1;
                        //h_VTP_HTCC_times3->Fill(REC_Cherenkov_time->at(ind_HTCC[i_part]), v_vtp_time.at(i_vtp));
                    }


                    if (v_vtp_trbit.at(i_vtp)(iS + 7, iS + 7)) {
                        h_VTP_HTCC_times4->Fill(REC_Cherenkov_time->at(ind_HTCC[i_part]), v_vtp_time.at(i_vtp));
                    }


                }



                if (em_sect_trig) {

                    t_VTP = double(v_vtp_time.at(i_vtp));

                    h_VTP_HTCC_times2->Fill(REC_Cherenkov_time->at(ind_HTCC[i_part]), v_vtp_time.at(i_vtp));

                    //	    if( v_vtp_time.at(i_vtp) > 32 + 0.25*REC_Cherenkov_time->at(ind_HTCC[i_part]) && v_vtp_time.at(i_vtp) < 40 + 0.25*REC_Cherenkov_time->at(ind_HTCC[i_part]) ){
                    //if (1/*v_vtp_time.at(i_vtp) > 32 + 0.25*REC_Cherenkov_time->at(ind_HTCC[i_part]) && v_vtp_time.at(i_vtp) < 40 + 0.25*REC_Cherenkov_time->at(ind_HTCC[i_part])*/) {
                    if ( v_vtp_time.at(i_vtp ) > 260 ) {
                        n_em_VTP_trig = n_em_VTP_trig + 1;

                        for (int iS = 0; iS < n_sect; iS++) {
                            if (v_vtp_trbit.at(i_vtp)(iS + 1, iS + 1)) {

                                if (Good_Electron) {
                                    n_em_VTP_trig_Good_em_[iS] = n_em_VTP_trig_Good_em_[iS] + 1;
                                }
                                if (Good_noEC) {
                                    n_em_VTP_trig_Good_noEC_[iS] = n_em_VTP_trig_Good_noEC_[iS] + 1;
                                }

                            }





                        }
                    }



                }

            }


            if (Good_Electron && trg_E_threshold_pass) {
                h_vz_Good_em0->Fill(vz);

                if (vz > vz_MIN_cut && vz < vz_MAX_cut) {
                    h_P_Good_em0->Fill(P);
                }
            }

            for (int iS = 0; iS < n_sect; iS++) {
                if ((n_em_VTP_trig_eleDCroad_[iS] == 0 && n_em_VTP_trig_[iS] != 0) && Good_Electron) {
                    h_P_Good_em_DC_Missed0->Fill(P);

                    if (trg_E_threshold_pass) {
                        h_P_Good_em_trg_thresholds_DC_Missed0->Fill(P);
                        h_vz_Good_em_trg_thresholds_DC_Missed0->Fill(vz);
                        h_PCal_yxc_trg_thresholds_DC_Missed0->Fill(PCal_x, PCal_y);
                        //cout << " sec_em =  " << sec_em << "      iS = " << iS << "     P = " << P << endl;
                        //cout<<" iS =  "<<iS<<"     n_em_VTP_trig_eleDCroad =  "<<n_em_VTP_trig_eleDCroad_[iS]<<"    n_em_VTP_trig_ = "<<n_em_VTP_trig_[iS]<<endl;
                        //cout << "em_sect_trig " << n_em_all_sect_trig << "    em_DC_inbend_trig " << n_em_all_sect_DCinbend_trig << endl;
                    }
                }
            }
            //=== Loop finished over trig2VTP ===


            h_E_EC_sec2->Fill(E_EC, REC_Calorimeter_sector->at(ind_PCal[i_part]) - 1.);
            h_E_PCal_sec1->Fill(EPCal, REC_Calorimeter_sector->at(ind_PCal[i_part]) - 1.);



            if (Good_Electron) {
                h_n_HTCC_trg_good_em_missed0->Fill(n_em_VTP_trig_HTCC_[sec_em], sec_em);
                h_n_HTCC_trg_good_em_P1->Fill(P, n_em_VTP_trig_HTCC_[sec_em]);
                h_n_HTCC_trg_good_em_nphe1->Fill(nphe, n_em_VTP_trig_HTCC_[sec_em]);

                h_n_PCal_trg_good_em_P1->Fill(P, n_em_VTP_trig_PCal_[sec_em]);
                h_n_EC_trg_good_em_P1->Fill(P, n_em_VTP_trig_EC_[sec_em]);
                //cout<<sec_em<<"   "<<n_em_VTP_trig_PCalEC_[0]<<"   "<<n_em_VTP_trig_PCalEC_[1]<<"   "<<n_em_VTP_trig_PCalEC_[2]<<"   "<<n_em_VTP_trig_PCalEC_[3]<<"   "<<n_em_VTP_trig_PCalEC_[4]<<"   "<<n_em_VTP_trig_PCalEC_[5]<<endl;
            }


            if (n_em_VTP_trig_[REC_Calorimeter_sector->at(ind_PCal[i_part]) - 1] == 0) {

                // =============== Good electron was not found by trigger



                if (Good_Electron && n_em_VTP_trig_Good_em_[REC_Calorimeter_sector->at(ind_PCal[i_part]) - 1] == 0 && vz > vz_MIN_cut && vz < vz_MAX_cut) {
                    h_W_Good_em_missed1->Fill(W);
                    h_P_Good_em_missed1->Fill(P);

                    if (trg_E_threshold_pass) {
                        h_W_Good_em_missed_trg_thresholds1->Fill(W);
                        h_P_Good_em_missed_trg_thresholds1->Fill(P);

                        h_n_HTCC_trg_good_em_missed1->Fill(n_em_VTP_trig_HTCC_[sec_em], sec_em);
                        h_n_HTCC_trg_good_em_nphe2->Fill(nphe, n_em_VTP_trig_HTCC_[sec_em]);
                        h_n_HTCC_trg_good_em_P2->Fill(P, n_em_VTP_trig_HTCC_[sec_em]);


                        h_n_PCal_trg_good_em_P2->Fill(P, n_em_VTP_trig_PCal_[sec_em]);
                        h_n_EC_trg_good_em_P2->Fill(P, n_em_VTP_trig_EC_[sec_em]);
                        h_n_DCeleinbend_trg_good_em_P2->Fill(P, n_em_VTP_trig_eleDCroad_[sec_em]);
                        h_t_HTCC1->Fill(t_HTCC);
                        h_vz_Good_em_tr_missed0->Fill(vz);

                        if (n_em_VTP_trig_HTCC_[sec_em] == 0) {
                            
                            
                            h_t_HTCC_nphe_missed1->Fill(t_HTCC, nphe);
                            
                            h_nphe_sect_missing1->Fill(nphe, sec_em);

//                            double x_HTCC = HTCC_rec_x->at(REC_Cherenkov_index->at(ind_HTCC[i_part]));
//                            double y_HTCC = HTCC_rec_y->at(REC_Cherenkov_index->at(ind_HTCC[i_part]));
//                            
//                            double phi_HTCC = atan2(y_HTCC, x_HTCC)*r2d + 30.;
//                            if( phi_HTCC < 0 ) {phi_HTCC = phi_HTCC + 360.;}
//                            
//                            int sec_HTCC = phi_HTCC/60;
                            
                            if (nphe > 3) {
                                h_HTCC_YXc_miss1->Fill(x_HTCC, y_HTCC);
                                
                                h_sec_PCal_HTCC_miss1->Fill(sec_HTCC, sec_em);
                            } else {
                                //cout<<n_em_VTP_trig_HTCC_allsec<<endl;
                                h_HTCC_YXc_miss2->Fill(x_HTCC, y_HTCC);
                                h_sec_PCal_HTCC_miss2->Fill(sec_HTCC, sec_em);
                            }
                            
                            // ========================== Loop over HTCC_REC bank to check sectors =============
                            
//                            for( int i_htccrec = 0; i_htccrec < HTCC_rec_x->size(); i_htccrec++ ){
//                                double x_htcc_rec = HTCC_rec_x->at(i_htccrec);
//                                double y_htcc_rec = HTCC_rec_y->at(i_htccrec);
//                                double phi_htcc
//                            }
                            
                            
                            // ========================== Loop over HTCC_REC bank to check sectors =============
                            
                            
                            
                            if( sec_em == sec_HTCC ){
                                h_nphe_HTCC_miss1->Fill(nphe);
                                h_HTCC_YXc_miss3->Fill(x_HTCC, y_HTCC);
                            } else{
                                h_nphe_HTCC_miss2->Fill(nphe);
                                h_HTCC_YXc_miss4->Fill(x_HTCC, y_HTCC);
                            }
                            
                            
                        }

                        
                        
                        if (nphe < 6 && n_em_VTP_trig_HTCC_[sec_em] == 0) {
                            h_P_Good_em_missed_trg_thresholds_nphefail1->Fill(P);
                        }

                        //                        long int run_conf_ev_number = RUN_config_event->at(0);
                        //                        long int run_conf_RUN = RUN_config_run->at(0);

                        miss_events << setw(5) << run_conf_RUN << setw(12) << run_conf_ev_number << setw(12) << ev_number_VTP << setw(5) << sec_em 
                                << setw(6) << bool(n_em_VTP_trig_HTCC_[sec_em]) << setw(6) << bool(n_em_VTP_trig_EC_[sec_em]) << 
                                setw(6) << bool(n_em_VTP_trig_eleDCroad_[sec_em])<<setw(12)<< nphe << endl;

                    }

                }

                if (Good_noEC && n_em_VTP_trig_Good_noEC_[REC_Calorimeter_sector->at(ind_PCal[i_part]) - 1] == 0) {
                    h_W_Good_noEC_missed1->Fill(W);
                    h_P_Good_noEC_missed1->Fill(P);

                    if (trg_E_threshold_pass) {
                        h_W_Good_noEC_missed_trg_thresholds1->Fill(W);
                        h_P_Good_noEC_missed_trg_thresholds1->Fill(P);
                    }

                }


            } else {

                // The trigger bit of electron is found, Here we want to check (Electron x DC_Road) trigger

                if (Good_Electron) {

                    h_P_Good_em_trg_thresholds_tr_found1->Fill(P);

//                    if (n_em_VTP_trig_eleDCroad_[sec_em] == 0) {
//                        //if( n_Inbend_DC_Roads[sec_em] == 0 ){
//                        cout << "KUKU    W A R N I N G DC TRIGGER FAILED " << endl;
//                        h_P_Good_em_trg_thresholds_NoDCRoad1->Fill(P);
//                        h_t_HTCC2->Fill(t_HTCC);
//                    }
                }

            }





        }


    }

    //skim_tree->Write();
    gDirectory->Write();
    file_out->Close();
}

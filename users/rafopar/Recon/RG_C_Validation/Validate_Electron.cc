/* 
 * File:   Validate_Electron.cc
 * Author: rafopar
 *
 * Created on November 12, 2021, 9:06 PM
 */

#include <cstdlib>
#include <bitset>

// ===== Hipo headers =====
#include <reader.h>
#include <writer.h>
#include <dictionary.h>

#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_stream.h>

#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TMath.h>

#include <VTPRoot.hh>

#include <RecParticle.h>
//#include <TruthMatchTools.h>

//using namespace TruthMatchTools;
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    std::cout << " reading file example program (HIPO) " << __cplusplus << std::endl;

    char inputFile[256];

    if (argc > 1) {
        sprintf(inputFile, "%s", argv[1]);
        //sprintf(outputFile,"%s",argv[2]);
    } else {
        std::cout << " *** please provide a file name..." << std::endl;
        exit(0);
    }

    const double Eb = 10.54726;
    const double Mp = 0.9383;
    const double r2d = 57.295780;
    const int HTCC_TYPE = 15;
    const int VTP_TrigTag = 29; // 11101
    const int n_max_npart = 30;
    const int n_sect = 6;
    const double scale_PCal_coord = 1. / 6.5;
    const double scale_EC_coord = 1. / 8.;

    const double P_MinRoads = 1.;

    const double PCal_Threshold = 0.06;
    const double EC_Threshold = 0.01;
    const double ESum_Threshold = 0.3;
    const double ESum_AboveThresholdCut = 0.4;
    const double Nphe_AboveThresholdcut = 3;

    const double t_HTCC_max = 160; // above this VTB banks are lost
    const double t_HTCC_min = 65; // above this VTB banks are lost

    // const double SF_max = 0.26;
    // const double SF_min = 0.18;
    const double SF_max = 0.39;
    const double SF_min = 0.18;
    const double SF_min_noEC = 0.15;
    const double PCal_MIP_cut = 0.045;

    const double Nphe_cut = 2;

    const double PCal_UMax_cut = 80.;
    const double PCal_UMin_cut = 3.; // For oubendings this doesn't matter much;
    const double PCal_VMax_cut = 73.;
    const double PCal_VMin_cut = 3.;
    const double PCal_WMax_cut = 73.;
    const double PCal_WMin_cut = 3.;

    const double ECin_UMax_cut = 35.;
    const double ECin_UMin_cut = 1.5; // For oubendings this doesn't matter much;
    const double ECin_VMax_cut = 35.;
    const double ECin_VMin_cut = 3.;
    const double ECin_WMax_cut = 35.;
    const double ECin_WMin_cut = 3.;

    const double ECout_UMax_cut = 34.;
    const double ECout_UMin_cut = 1.5; // For oubendings this doesn't matter much;
    const double ECout_VMax_cut = 35;
    const double ECout_VMin_cut = 3.;
    const double ECout_WMax_cut = 35.;
    const double ECout_WMin_cut = 3.;

    hipo::reader reader;
    reader.open(inputFile);

    hipo::dictionary factory;

    reader.readDictionary(factory);

    factory.show();

    hipo::event event;
    int counter = 0;

    hipo::bank bRunConfig(factory.getSchema("RUN::config"));
    hipo::bank bVTP(factory.getSchema("RAW::vtp"));
    hipo::bank bECalClusters(factory.getSchema("ECAL::clusters"));
    hipo::bank bRecPart(factory.getSchema("REC::Particle"));
    hipo::bank bRecCal(factory.getSchema("REC::Calorimeter"));
    hipo::bank bRecCherenkov(factory.getSchema("REC::Cherenkov"));
    hipo::bank bRecEvent(factory.getSchema("REC::Event"));
    hipo::bank bHTCCRec(factory.getSchema("HTCC::rec"));


    TFile *file_out = new TFile("Validate_Electron.root", "Recreate");
    TH1D *h_vtp_tr_time = new TH1D("h_vtp_tr_time", "", 102, -0.5, 101.5);
    TH1D *h_vtp_tr_bits1 = new TH1D("h_vtp_tr_bits1", "", 33, -0.5, 32.5);
    TH1D *h_nphe1 = new TH1D("h_nphe1", "", 200, 0., 50.);
    TH1D *h_nphe2 = new TH1D("h_nphe2", "", 200, 0., 50.);
    TH2D *h_nphe_phi1 = new TH2D("h_nphe_phi1", "", 200, 0., 50., 60, 0., 360.);
    TH2D *h_PCal_yxc1 = new TH2D("h_PCal_yxc1", "", 200, -420., 420., 200, -420., 420.);
    TH2D *h_PCal_yxc2 = new TH2D("h_PCal_yxc2", "", 200, -420., 420., 200, -420., 420.);
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

    TH1D *h_chi2PID1  = new TH1D("h_chi2PID1", "", 200, -20., 20.);
    TH1D *h_chi2PID_Failed1  = new TH1D("h_chi2PID_Failed1", "", 200, -20., 20.);
    
    TH1D *h_vz1 = new TH1D("h_vz1", "", 200, -30., 30.);
    TH1D *h_vz_Failed1 = new TH1D("h_vz_Failed1", "", 200, -30., 30.);
    
    TH2D *h_SF1 = new TH2D("h_SF1", "", 200, 0., 1.2 * Eb, 200, 0., 0.5);
    TH2D *h_SF2 = new TH2D("h_SF2", "", 200, 0., 1.2 * Eb, 200, 0., 0.5);
    TH2D * h_SF1_[n_sect];
    TH2D * h_SF2_[n_sect];

    for (int i = 0; i < n_sect; i++) {
        h_SF1_[i] = new TH2D(Form("h_SF1_%d", i), "", 200, 0., 1.2 * Eb, 200, 0., 0.5);
        h_SF2_[i] = new TH2D(Form("h_SF2_%d", i), "", 200, 0., 1.2 * Eb, 200, 0., 0.5);
    }

    TH2D *h_VTP_HTCC_times1 = new TH2D("h_VTP_HTCC_times1", "", 200, 0., 400., 200, 0., 405.);
    TH2D *h_VTP_HTCC_times2 = new TH2D("h_VTP_HTCC_times2", "", 200, 0., 400., 200, 0., 405.);

    TH1D *h_P_em_NotSoGood_em1 = new TH1D("h_P_em_NotSoGood_em1", "", 40, 0., 1.05 * Eb);
    TH1D *h_P_em_Good_em1 = new TH1D("h_P_em_Good_em1", "", 40, 0., 1.05 * Eb);
    TH1D *h_P_em_Good_emAboveThreshold1 = new TH1D("h_P_em_Good_emAboveThreshold1", "", 40, 0., 1.05 * Eb);
    TH1D *h_P_em_Good_em_TrgPassed1 = new TH1D("h_P_em_Good_em_TrgPassed1", "", 40, 0., 1.05 * Eb);
    TH1D *h_P_em_NotSoGood_em_TrgPassed1 = new TH1D("h_P_em_NotSoGood_em_TrgPassed1", "", 40, 0., 1.05 * Eb);
    TH1D *h_P_em_Good_emAboveThreshold_TrgPassed1 = new TH1D("h_P_em_Good_emAboveThreshold_TrgPassed1", "", 40, 0., 1.05 * Eb);

    TH1D *h_Etot_Failed1 = new TH1D("h_Etot_Failed1", "", 200, 0., 1.5);
    TH1D *h_Nphe_Failed1 = new TH1D("h_Nphe_Failed1", "", 200, 0., 20.5);
    TH1D *h_Nphe_Failed2 = new TH1D("h_Nphe_Failed2", "", 200, 0., 20.5);
    TH1D *h_tHTCC_Failed1 = new TH1D("h_tHTCC_Failed1", "", 200, 0., 200.);
    TH1D *h_tHTCC_Failed2 = new TH1D("h_tHTCC_Failed2", "", 200, 0., 200.);
    TH1D *h_tHTCC_Failed3 = new TH1D("h_tHTCC_Failed3", "", 200, 0., 200.);
    TH2D *h_Etot_Nphe_Failed1 = new TH2D("h_Etot_Nphe_Failed1", "", 200, 0., 1.5, 200, 0., 20.5);
    TH2D *h_Etot_EPcal_Failed1 = new TH2D("h_Etot_EPcal_Failed1", "", 200, 0., 1.5, 200, 0., 1.5);
    TH2D *h_Etot_EPcal_Failed2 = new TH2D("h_Etot_EPcal_Failed2", "", 200, 0., 1.5, 200, 0., 1.5);

    TH2D *h_PCal_XY_failedAboveThr1 = new TH2D("h_PCal_XY_failedAboveThr1", "", 200, -300., 300., 200, -300., 300.);

    int evCounter = 0;
    int nEvPID11 = 0;
    try {

        while (reader.next() == true) {
            reader.read(event);

            evCounter = evCounter + 1;

            if (evCounter % 10000 == 0) {
                //cout.flush() << "Processed " << evCounter << " events \r";
            }


            event.getStructure(bRunConfig);
            event.getStructure(bRecPart);
            event.getStructure(bRecCal);
            event.getStructure(bRecCherenkov);
            event.getStructure(bRecEvent);
            event.getStructure(bVTP);
            event.getStructure(bHTCCRec);
            event.getStructure(bECalClusters);


            vector<int> v_vtp_time;
            vector<ap_int < 32 >> v_vtp_trbit;

            for (int ii = 0; ii < bVTP.getRows(); ii++) {


                if (bVTP.getInt("crate", ii) == 100) {

                    ap_int<32> vtp_word = ap_int<32>(bVTP.getInt("word", ii));

                    //cout<<bitset<32>(vtp_word)<<endl;

                    if (vtp_word(31, 27) == VTP_TrigTag) {

                        int vtp_time = vtp_word(26, 16);
                        h_vtp_tr_time->Fill(vtp_time);

                        ap_int<32> vtp_tr_bits;
                        vtp_tr_bits(15, 0) = vtp_word(15, 0);

                        vtp_word = ap_int<32>(bVTP.getInt("word", ii + 1));
                        vtp_tr_bits(31, 16) = vtp_word(15, 0);

                        v_vtp_time.push_back(vtp_time);
                        v_vtp_trbit.push_back(vtp_tr_bits);

                        for (int ibit = 0; ibit < 32; ibit++) {
                            h_vtp_tr_bits1->Fill(ibit, vtp_tr_bits(ibit, ibit));
                        }


                        ii = ii + 1; // As we read two words here, so we increment ii by 1
                    }
                }

            }

            int nPart = bRecPart.getRows();

            map<int, int> ind_HTCC;
            map<int, int> ind_PCal;
            map<int, int> ind_ECin;
            map<int, int> ind_ECout;

            bool em_candidate = false;

            for (int i_part = 0; i_part < nPart; i_part++) {

                // ==== Before assigning, index, all indexes are initialized to -1, this way we can check, whether
                // ==== that particular detector is related to the particle "i_part"
                ind_HTCC[i_part] = -1;
                ind_PCal[i_part] = -1;
                ind_ECin[i_part] = -1;
                ind_ECout[i_part] = -1;


                int nCherenkov = bRecCherenkov.getRows();
                // =============================== HTCC ===============================
                for (int i_cc = 0; i_cc < nCherenkov; i_cc++) {

                    // Want only HTCC for now
                    if (bRecCherenkov.getInt("detector", i_cc) == HTCC_TYPE) {

                        if (bRecCherenkov.getInt("pindex", i_cc) == i_part) {
                            ind_HTCC[i_part] = i_cc;
                        }
                    }
                }

                int nCal = bRecCal.getRows();

                // =============================== PCal, ECin, ECout ===============================
                for (int i_cal = 0; i_cal < nCal; i_cal++) {

                    if (bRecCal.getInt("pindex", i_cal) == i_part) {

                        int layer = bRecCal.getInt("layer", i_cal);

                        if (layer == 1) {
                            ind_PCal[i_part] = i_cal;
                        } else if (layer == 4) {
                            ind_ECin[i_part] = i_cal;
                        } else if (layer == 7) {
                            ind_ECout[i_part] = i_cal;
                        }
                    }

                }
            }

            for (int i_part = 0; i_part < nPart; i_part++) {
                //RecParticle recp = TruthMatchTools::GetRecParticle(bRecPart, i_part);
                RecParticle recp(bRecPart, bRecCal, bRecCherenkov, i_part, ind_PCal[i_part], ind_ECin[i_part], ind_ECout[i_part], ind_HTCC[i_part]);

                // ==== Select only negatives
                if (recp.charge() >= 0) {
                    //continue;
                }


                if (!(TMath::Abs(recp.status()) >= 2000 && TMath::Abs(recp.status()) < 4000)) {
                    continue;
                }

                if( !( recp.secPCal() == recp.secHTCC() && recp.secPCal() == recp.secECin() ) ){
                    continue;
                }
                
                if (recp.pid() != 11) {
                    continue;
                }

                if (recp.pid() == 11) {
                    nEvPID11 += 1;
                }
                
                if( !(recp.vz() > -10. && recp.vz() < 0.) ){
                    continue;
                }
                
                if( recp.npheHTCC() < 3 ){
                    continue;
                }
                
                

                h_chi2PID1->Fill(recp.chi2pid());
                h_vz1->Fill(recp.vz());
                
//                if( recp.chi2pid() < -1. ){
//                    continue;
//                }
                
                int sect_particle = int(recp.phi() / 60.);

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
                double ECout_y = 0.;
                double ECout_x = 0.;

                double EPCal = 0; // PCal energy
                double EECin = 0; // ECin energy
                double EECout = 0; // ECout Energy

                double E_EC = 0; // EC energy = E_ECin + E_ECout
                double E_tot = 0; // Tot energy E_PCal + E_ECin + E_Ecout (if exists)


                // ======================== HTCC =======================
                if (ind_HTCC[i_part] >= 0) {

                    int ind_HTCC_rec = bRecCherenkov.getInt("index", ind_HTCC[i_part]);

                    //cout<<HTCC_rec_nphe->at(ind_HTCC_rec) - REC_Cherenkov_nphe->at(ind_HTCC[i_part])<<endl;

                    nphe = double(bHTCCRec.getFloat("nphe", ind_HTCC_rec));
                    phi_HTCC = double(bHTCCRec.getFloat("phi", ind_HTCC_rec) * r2d + 30);
                    if (phi_HTCC < 0.) {
                        phi_HTCC = phi_HTCC + 360.;
                    }

                    h_nphe1->Fill(nphe);
                    h_nphe_phi1->Fill(nphe, phi_HTCC);

                    if (nphe > Nphe_cut) {
                        HTCC_pass = true;
                    }
                }

                // ======================== PCal =======================
                if (ind_PCal[i_part] >= 0) {
                    int ind_PCal_cl = bRecCal.getInt("index", ind_PCal[i_part]);
                    //cout<<ECAL_clusters_x->at(ind_PCal_cl)<<"     "<<REC_Calorimeter_x->at(ind_PCal[i_part])<<endl;

                    PCal_y = double(bECalClusters.getFloat("y", ind_PCal_cl));
                    PCal_x = double(bECalClusters.getFloat("x", ind_PCal_cl));
                    h_PCal_yxc1->Fill(PCal_x, PCal_y);

                    PCal_U = double(bECalClusters.getInt("coordU", ind_PCal_cl)) * scale_PCal_coord;
                    PCal_V = double(bECalClusters.getInt("coordV", ind_PCal_cl)) * scale_PCal_coord;
                    PCal_W = double(bECalClusters.getInt("coordW", ind_PCal_cl)) * scale_PCal_coord;

                    EPCal = double(bECalClusters.getFloat("energy", ind_PCal_cl));

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
                    int ind_ECin_cl = bRecCal.getInt("index", ind_ECin[i_part]);

                    ECin_y = double(bECalClusters.getFloat("y", ind_ECin_cl));
                    ECin_x = double(bECalClusters.getFloat("x", ind_ECin_cl));
                    h_ECin_yxc1->Fill(ECin_x, ECin_y);

                    ECin_U = double(bECalClusters.getInt("coordU", ind_ECin_cl)) * scale_EC_coord;
                    ECin_V = double(bECalClusters.getInt("coordV", ind_ECin_cl)) * scale_EC_coord;
                    ECin_W = double(bECalClusters.getInt("coordW", ind_ECin_cl)) * scale_EC_coord;

                    EECin = double(bECalClusters.getFloat("energy", ind_ECin_cl));


                    h_ECin_U1->Fill(ECin_U);
                    h_ECin_V1->Fill(ECin_V);
                    h_ECin_W1->Fill(ECin_W);

                    if (ECin_U > ECin_UMin_cut && ECin_U < ECin_UMax_cut && ECin_V > ECin_VMin_cut && ECin_V < ECin_VMax_cut &&
                            ECin_W > ECin_WMin_cut && ECin_W < ECin_WMax_cut) {

                        h_ECin_yxc2->Fill(ECin_x, ECin_y);

                        ECin_pass = true;
                    }

                }


                // ======================== EC Out =======================
                if (ind_ECout[i_part] >= 0) {

                    int ind_ECout_cl = bRecCal.getInt("index", ind_ECout[i_part]);

                    ECout_y = double(bECalClusters.getFloat("y", ind_ECout_cl));
                    ECout_x = double(bECalClusters.getFloat("x", ind_ECout_cl));
                    h_ECout_yxc1->Fill(ECin_x, ECin_y);

                    ECout_U = double(bECalClusters.getInt("coordU", ind_ECout_cl)) * scale_EC_coord;
                    ECout_V = double(bECalClusters.getInt("coordV", ind_ECout_cl)) * scale_EC_coord;
                    ECout_W = double(bECalClusters.getInt("coordW", ind_ECout_cl)) * scale_EC_coord;

                    EECout = double(bECalClusters.getFloat("energy", ind_ECout_cl));

                    h_ECout_U1->Fill(ECout_U);
                    h_ECout_V1->Fill(ECout_V);
                    h_ECout_W1->Fill(ECout_W);

                    if (ECout_U > ECout_UMin_cut && ECout_U < ECout_UMax_cut && ECout_V > ECout_VMin_cut && ECout_V < ECout_VMax_cut &&
                            ECout_W > ECout_WMin_cut && ECout_W < ECout_WMax_cut) {

                        h_ECout_yxc2->Fill(ECout_x, ECout_y);
                        ECout_pass = true;
                    }
                }

                E_EC = EECin + EECout;
                E_tot = E_EC + EPCal;

                bool trg_E_threshold_pass = (E_tot > ESum_Threshold) && (E_EC > EC_Threshold) && (EPCal > PCal_Threshold) ||
                        ((ind_ECin[i_part] < 0) && (EPCal > ESum_Threshold));

                double SF = E_tot / recp.p();

                h_SF1->Fill(recp.p(), SF);

                h_ETot_sec1->Fill(E_tot, sect_particle);

                h_SF1_[sect_particle]->Fill(recp.p(), SF);

                if (SF > 0.2 && ind_PCal[i_part] >= 0 && ind_HTCC[i_part] >= 0 && PCal_pass && PCal_MIP_cut) {
                    h_nphe2->Fill(nphe);
                }

                if (PCal_pass && EPCal > PCal_MIP_cut && nphe > 2) {
                    h_SF2_[sect_particle]->Fill(recp.p(), SF);
                }

                bool Good_Electron_AboveThreshold = (ECin_pass && SF > SF_min && SF < SF_max && (E_tot > ESum_AboveThresholdCut) && (E_EC > EC_Threshold) && (EPCal > PCal_Threshold) && PCal_pass && nphe > Nphe_AboveThresholdcut);
                bool Good_Electron = (ECin_pass && SF > SF_min && SF < SF_max && (E_tot > ESum_Threshold) && (E_EC > EC_Threshold) && (EPCal > PCal_Threshold) && PCal_pass && HTCC_pass);
                bool NotSoGoodElectron = (ECin_pass && SF > SF_min && SF < SF_max && (E_EC > EC_Threshold) && (EPCal > PCal_Threshold) && PCal_pass && HTCC_pass);
                bool Good_noEC = (ind_ECin[i_part] < 0 && SF > SF_min_noEC && HTCC_pass && PCal_pass && EPCal > PCal_MIP_cut);
                if (!(Good_Electron || Good_noEC || NotSoGoodElectron)) {
                    continue;
                }


                int n_em_VTP_trig = 0; // Number of VTP triggeres with electron trigger, i.e. when bit 0 is set
                int n_em_VTP_trig_[n_sect] = {0};
                int n_em_VTP_trig_Good_em_[n_sect] = {0}; // Number of electron trigger bits when we have a good e-, i.e. with PCal, EC, nphe > 7 Fiducial and SF
                int n_em_VTP_trig_Good_noEC_[n_sect] = {0}; // Number of electron trigger bits when ECin is missing, nphe > 7 SF > 0.1 and PCal Fiducial
                int n_em_VTP_trig_HTCC_[n_sect] = {0}; // Number of HTCC trigger bints
                int n_em_VTP_trig_PCalEC_[n_sect] = {0}; // Number of PCalxEC triggers in a given sector
                int n_em_VTP_trig_eleDCroad_[n_sect] = {0}; // Number of Electron x DCRoad triggers in a given sector
                int n_em_VTP_trig_HTCC_allsec = 0; // Number of PCalxEC triggers in a given sector
                int n_em_VTP_trig_PCalEC_allsec = 0;

                int n_em_all_sect_trig = 0;
                int n_em_all_sect_DCinbend_trig = 0;

                double t_HTCC, t_VTP;

                int sec_em = bRecCal.getInt("sector", ind_PCal[i_part]) - 1;
                t_HTCC = double(bRecCherenkov.getFloat("time", ind_HTCC[i_part]));

                if (Good_Electron) {
                    h_P_em_Good_em1->Fill(recp.p());
                }


                if (Good_Electron_AboveThreshold) {
                    h_P_em_Good_emAboveThreshold1->Fill(recp.p());
                }

                for (int i_vtp = 0; i_vtp < v_vtp_time.size(); i_vtp++) {

                    h_VTP_HTCC_times1->Fill(t_HTCC, v_vtp_time.at(i_vtp));

                    bool em_tot_trig = v_vtp_trbit.at(i_vtp)(14, 14);
                    bool em_sect_trig = v_vtp_trbit.at(i_vtp)(15, 20);
                    bool em_DC_inbend_trig = v_vtp_trbit.at(i_vtp)(1, 6);
                    int em_sect_trig_int = v_vtp_trbit.at(i_vtp)(15, 20);

                    for (int iS = 0; iS < n_sect; iS++) {

                        if (v_vtp_trbit.at(i_vtp)(iS + 15, iS + 15)) {

                            if (30 + 0.25 * t_HTCC < v_vtp_time.at(i_vtp) < 60 + 0.25 * t_HTCC) {
                                n_em_VTP_trig_[iS] = n_em_VTP_trig_[iS] + 1;

                                //h_VTP_HTCC_times3->Fill(REC_Cherenkov_time->at(ind_HTCC[i_part]), v_vtp_time.at(i_vtp));
                            }
                        }


                    }

                }

                if (NotSoGoodElectron) {
                    h_P_em_NotSoGood_em1->Fill(recp.p());

                    if (n_em_VTP_trig_[sec_em] >= 1) {
                        h_P_em_NotSoGood_em_TrgPassed1->Fill(recp.p());
                        //cout<<recp.secECin()<<"    "<<recp.secPCal()<<"    "<<recp.secHTCC()<<endl;
                    } else {

                        if (recp.p() > 2) {
                            h_chi2PID_Failed1->Fill(recp.chi2pid() );
                            h_Etot_Nphe_Failed1->Fill(E_tot, nphe);
                            h_Etot_Failed1->Fill(E_tot);
                            h_Nphe_Failed1->Fill(nphe);
                            h_tHTCC_Failed1->Fill(t_HTCC);
                            h_vz_Failed1->Fill(recp.vz());
                            
                            h_Etot_EPcal_Failed1->Fill(E_tot, EPCal);
                            
                            cout<<recp.secECin()<<"    "<<recp.secPCal()<<"    "<<recp.secHTCC()<<endl;
                            
                            //cout<<bRunConfig.getInt("run", 0)<<"     "<<bRunConfig.getInt("event", 0)<<endl;
                        }
                    }
                }

                if (Good_Electron) {
                    if (n_em_VTP_trig_[sec_em] >= 1) {
                        h_P_em_Good_em_TrgPassed1->Fill(recp.p());
                    } else {

                        if (nphe > 4) {
                            h_Etot_EPcal_Failed2->Fill(E_tot, EPCal);
                        }

                        if (E_tot > 0.3) {
                            h_Nphe_Failed2->Fill(nphe);
                            h_tHTCC_Failed2->Fill(t_HTCC);
                            if (nphe > 3) {
                                h_tHTCC_Failed3->Fill(t_HTCC);
                            }
                        }
                    }
                }

                if (Good_Electron_AboveThreshold) {
                    if (n_em_VTP_trig_[sec_em] >= 1) {
                        h_P_em_Good_emAboveThreshold_TrgPassed1->Fill(recp.p());
                    } else {
                        h_PCal_XY_failedAboveThr1->Fill(PCal_x, PCal_y);
                    }
                }

            }


        }
    } catch (const char *msg) {
        cerr << msg << endl;
    }

    cout << " Kuku " << endl;
    cout << "nPID_11 = " << nEvPID11 << endl;
    gDirectory->Write();

    return 0;
}
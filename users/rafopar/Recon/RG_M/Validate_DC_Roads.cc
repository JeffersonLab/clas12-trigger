/* 
 * File:   Validate_DC_Roads.cc
 * Author: rafopar
 *
 * Created on November 11, 2021, 10:00 AM
 */

#include <cstdlib>

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

#include <TruthMatchTools.h>
using namespace TruthMatchTools;

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


    const double Eb = 5.98636;
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
    const double ESum_Threshold = 0.15;

    const double t_HTCC_max = 140; // above this VTB banks are lost

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

    const double ECin_UMax_cut = 33.;
    const double ECin_UMin_cut = 2.; // For oubendings this doesn't matter much;
    const double ECin_VMax_cut = 33.;
    const double ECin_VMin_cut = 3.;
    const double ECin_WMax_cut = 33.;
    const double ECin_WMin_cut = 3.;

    const double ECout_UMax_cut = 34.;
    const double ECout_UMin_cut = 3.; // For oubendings this doesn't matter much;
    const double ECout_VMax_cut = 34;
    const double ECout_VMin_cut = 3.;
    const double ECout_WMax_cut = 33.;
    const double ECout_WMin_cut = 3.;

    hipo::reader reader;
    reader.open(inputFile);

    hipo::dictionary factory;

    reader.readDictionary(factory);

    factory.show();

    hipo::event event;
    int counter = 0;

    hipo::bank bRunConfig(factory.getSchema("RUN::config"));
    hipo::bank bRunTrg(factory.getSchema("RUN::trigger"));
    hipo::bank bECalClusters(factory.getSchema("ECAL::clusters"));
    hipo::bank bRecPart(factory.getSchema("REC::Particle"));
    hipo::bank bRecCal(factory.getSchema("REC::Calorimeter"));
    hipo::bank bRecCherenkov(factory.getSchema("REC::Cherenkov"));
    hipo::bank bRecEvent(factory.getSchema("REC::Event"));
    hipo::bank bHTCCRec(factory.getSchema("HTCC::rec"));

    TFile *file_out = new TFile("Validate_DC_Roads_WithTSBits.root", "Recreate");

    TH1D *h_nemFD1 = new TH1D("h_nemFD1", "", 11, -0.5, 10.5);

    TH1D *h_DC_RoadBitsets1 = new TH1D("h_DC_RoadBitsets1", "", 5, -0.5, 4.5);
    TH1D *h_DC_RoadBitsets2 = new TH1D("h_DC_RoadBitsets2", "", 5, -0.5, 4.5); // Any e- trg bit, if there is a recon electro.
    TH2D *h_th_phi_Allem1 = new TH2D("h_th_phi_Allem1", "", 200, 0., 360., 200, 0., 45.);
    TH2D *h_th_phi_Missed2 = new TH2D("h_th_phi_Missed2", "", 200, 0., 360., 200, 0., 45.);
    TH2D *h_th_P_Allem1 = new TH2D("h_th_P_Allem1", "", 200, 0., Eb, 200, 0., 45);
    TH2D *h_th_P_Allem2 = new TH2D("h_th_P_Allem2", "", 200, 0., Eb, 200, 0., 45);
    TH2D *h_th_P_Missed2 = new TH2D("h_th_P_Missed2", "", 200, 0., Eb, 200, 0., 45);
    TH2D *h_th_P_Missed3 = new TH2D("h_th_P_Missed3", "", 200, 0., Eb, 200, 0., 45);
    
    TH1D *TrgBits1 = new TH1D("TrgBits1", "", 65, -0.5, 64.5);

    int evCounter = 0;
    try {

        while (reader.next() == true) {
            reader.read(event);

            evCounter = evCounter + 1;

            if (evCounter % 10000 == 0) {
                cout.flush() << "Processed " << evCounter << " events \r";
            }

            event.getStructure(bRunConfig);
            event.getStructure(bRecPart);
            event.getStructure(bRecCal);
            event.getStructure(bRecCherenkov);
            event.getStructure(bRecEvent);
            event.getStructure(bHTCCRec);
            event.getStructure(bECalClusters);
            event.getStructure(bRunTrg);

            bool em_NoDCBits[n_sect + 1] = {0}; // Trg bits for e- w/o DR_Roads. 0 for Allsec, 1,2,3,4,5,6 for each sec
            bool em_WithDCBits[n_sect + 1] = {0}; // Trg bits for e- w DR_Roads. 0 for Allsec, 1,2,3,4,5,6 for each sec
            bool em_RecInSec[n_sect] = {0}; // em_is reconstructed in a given sector

            int nPart = bRecPart.getRows();

            bool anyemRec = false;

            int n_emFD = 0;
            vector< RecParticle> v_em;

            map<int, int> ind_HTCC;
            map<int, int> ind_PCal;
            map<int, int> ind_ECin;
            map<int, int> ind_ECout;

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


            for (int ipart = 0; ipart < nPart; ipart++) {
                RecParticle recp = TruthMatchTools::GetRecParticle(bRecPart, ipart);

                // ==== Select only negatives
                if (recp.charge >= 0) {
                    continue;
                }

                int sect_particle = int(recp.phi / 60.);

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

                int sec = recp.phi / 60;

                //                cout<<"pid = "<<recp.pid<<endl;
                //                cout<<"status = "<<recp.status<<endl;



                // ======================== HTCC =======================
                if (ind_HTCC[ipart] >= 0) {

                    int ind_HTCC_rec = bRecCherenkov.getInt("index", ind_HTCC[ipart]);

                    //cout<<HTCC_rec_nphe->at(ind_HTCC_rec) - REC_Cherenkov_nphe->at(ind_HTCC[i_part])<<endl;

                    nphe = double(bHTCCRec.getFloat("nphe", ind_HTCC_rec));
                    phi_HTCC = double(bHTCCRec.getFloat("phi", ind_HTCC_rec) * r2d + 30);
                    if (phi_HTCC < 0.) {
                        phi_HTCC = phi_HTCC + 360.;
                    }

                    //                    h_nphe1->Fill(nphe);
                    //                    h_nphe_phi1->Fill(nphe, phi_HTCC);

                    if (nphe > Nphe_cut) {
                        HTCC_pass = true;
                    }
                }


                // ======================== PCal =======================
                if (ind_PCal[ipart] >= 0) {
                    int ind_PCal_cl = bRecCal.getInt("index", ind_PCal[ipart]);
                    //cout<<ECAL_clusters_x->at(ind_PCal_cl)<<"     "<<REC_Calorimeter_x->at(ind_PCal[i_part])<<endl;

                    PCal_y = double(bECalClusters.getFloat("y", ind_PCal_cl));
                    PCal_x = double(bECalClusters.getFloat("x", ind_PCal_cl));

                    PCal_U = double(bECalClusters.getInt("coordU", ind_PCal_cl)) * scale_PCal_coord;
                    PCal_V = double(bECalClusters.getInt("coordV", ind_PCal_cl)) * scale_PCal_coord;
                    PCal_W = double(bECalClusters.getInt("coordW", ind_PCal_cl)) * scale_PCal_coord;

                    EPCal = double(bECalClusters.getFloat("energy", ind_PCal_cl));


                    if (PCal_U > PCal_UMin_cut && PCal_U < PCal_UMax_cut && PCal_V > PCal_VMin_cut && PCal_V < PCal_VMax_cut &&
                            PCal_W > PCal_WMin_cut && PCal_W < PCal_WMax_cut) {

                        PCal_pass = true;
                    }
                }


                // ======================== EC In =======================
                if (ind_ECin[ipart] >= 0) {
                    int ind_ECin_cl = bRecCal.getInt("index", ind_ECin[ipart]);

                    ECin_y = double(bECalClusters.getFloat("y", ind_ECin_cl));
                    ECin_x = double(bECalClusters.getFloat("x", ind_ECin_cl));

                    ECin_U = double(bECalClusters.getInt("coordU", ind_ECin_cl)) * scale_EC_coord;
                    ECin_V = double(bECalClusters.getInt("coordV", ind_ECin_cl)) * scale_EC_coord;
                    ECin_W = double(bECalClusters.getInt("coordW", ind_ECin_cl)) * scale_EC_coord;

                    EECin = double(bECalClusters.getFloat("energy", ind_ECin_cl));


                    if (ECin_U > ECin_UMin_cut && ECin_U < ECin_UMax_cut && ECin_V > ECin_VMin_cut && ECin_V < ECin_VMax_cut &&
                            ECin_W > ECin_WMin_cut && ECin_W < ECin_WMax_cut) {

                        ECin_pass = true;
                    }

                }


                // ======================== EC Out =======================
                if (ind_ECout[ipart] >= 0) {

                    int ind_ECout_cl = bRecCal.getInt("index", ind_ECout[ipart]);

                    ECout_y = double(bECalClusters.getFloat("y", ind_ECout_cl));
                    ECout_x = double(bECalClusters.getFloat("x", ind_ECout_cl));

                    ECout_U = double(bECalClusters.getInt("coordU", ind_ECout_cl)) * scale_EC_coord;
                    ECout_V = double(bECalClusters.getInt("coordV", ind_ECout_cl)) * scale_EC_coord;
                    ECout_W = double(bECalClusters.getInt("coordW", ind_ECout_cl)) * scale_EC_coord;

                    EECout = double(bECalClusters.getFloat("energy", ind_ECout_cl));

                    if (ECout_U > ECout_UMin_cut && ECout_U < ECout_UMax_cut && ECout_V > ECout_VMin_cut && ECout_V < ECout_VMax_cut &&
                            ECout_W > ECout_WMin_cut && ECout_W < ECout_WMax_cut) {

                        ECout_pass = true;
                    }
                }

                E_EC = EECin + EECout;
                E_tot = E_EC + EPCal;

                bool trg_E_threshold_pass = ((E_tot > ESum_Threshold) && (E_EC > EC_Threshold) && (EPCal > PCal_Threshold)) ||
                        ((ind_ECin[ipart] < 0) && (EPCal > ESum_Threshold));


                if (recp.pid == 11 && TMath::Abs(recp.status) > 2000 && TMath::Abs(recp.status) < 4000 && trg_E_threshold_pass && HTCC_pass /* && recp.p > P_MinRoads */) {
                    anyemRec = true;
                    em_RecInSec[sec] = true;
                    n_emFD = n_emFD + 1;
                    v_em.push_back(recp);
                }
            }

            h_nemFD1->Fill(n_emFD);

            if (n_emFD < 1) {
                continue;
            }

            long TS_TrgWord = bRunConfig.getLong("trigger", 0);

            em_WithDCBits[0] = TS_TrgWord & 1 ? true : false;
            em_NoDCBits[0] = TS_TrgWord & 128 ? true : false; // 128 is bit 7

            for (int ibit = 0; ibit < 6; ibit++) {
                long secBitWithDC = TMath::Power(2, ibit + 1);
                long secBitNoDC = TMath::Power(2, ibit + 8);
                em_WithDCBits[ibit + 1] = TS_TrgWord & secBitWithDC;
                em_NoDCBits[ibit + 1] = TS_TrgWord & secBitNoDC;
            }

            
            int FTTrigger = bRunTrg.getInt("trigger", 1);
            if( FTTrigger > 0 ){
                cout<<FTTrigger<<endl;
            }
            for( int ibit = 0; ibit < 32; ibit++ ){
                
                if( ( FTTrigger & (1<<ibit) ) ){
                    TrgBits1->Fill(ibit);
                }
                
            }
            
            //cout << "   TS word ============= " << TS_TrgWord << endl;

            double th_em = acos(v_em.at(0).pz / v_em.at(0).p) * TMath::RadToDeg();

            for (int iSec = 0; iSec < n_sect; iSec++) {

                // cout<<em_RecInSec[iSec]<<"   "<<em_NoDCBits[iSec + 1]<<"   "<<em_WithDCBits[iSec + 1]<<endl;

                if (em_RecInSec[iSec] && em_NoDCBits[iSec + 1]) {


                    h_th_P_Allem2->Fill(v_em.at(0).p, th_em);

                    if (em_WithDCBits[iSec + 1]) {
                        h_DC_RoadBitsets1->Fill(1);
                    } else {
                        h_DC_RoadBitsets1->Fill(0);
                        h_th_P_Missed3->Fill(v_em.at(0).p, th_em);
                    }
                }

            }

            if (anyemRec && em_NoDCBits[0]) {
                h_th_phi_Allem1->Fill(v_em.at(0).phi, th_em);
                h_th_P_Allem1->Fill(v_em.at(0).p, th_em);

                if (em_WithDCBits[0]) {
                    h_DC_RoadBitsets2->Fill(1);
                } else {
                    h_DC_RoadBitsets2->Fill(0);
                    h_th_phi_Missed2->Fill(v_em.at(0).phi, th_em);
                    h_th_P_Missed2->Fill(v_em.at(0).p, th_em);
                }
            }

        }
    } catch (const char *msg) {
        cerr << msg << endl;
    }

    gDirectory->Write();

    return 0;
}


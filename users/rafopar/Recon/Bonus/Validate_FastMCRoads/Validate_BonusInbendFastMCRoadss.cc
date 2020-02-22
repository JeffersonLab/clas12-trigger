/* 
 * File:   Validate_RGBOutbendRoads.cc
 * Author: rafopar
 *
 * Created on December 5, 2019, 4:50 PM
 */

#include <cstdlib>

#include <reader.h>
#include <dictionary.h>

#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TMath.h>
#include <TLorentzVector.h>

#include <VTPRoot.hh>

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


    // =====================================================
    //                    Trigger CUTS
    // =====================================================

    const double E_PCalMin = 0.06;
    const double E_TotMin = 0.25;
    const double NPheMin = 2.;

    const double Eb = 10.4;
    const double Mp = 0.9383;

    const double t_VTPMax = 72.;
    const double t_VTPMin = 64.;
    const double t_HTCCMax = 98;
    const double t_HTCCMin = 82;
    const double vzMax = 20.;
    const double vzMin = -30.;



    // =====================================================
    //                    Electron PID CUTS
    // =====================================================

    const double SF_Min = 0.2;


    const int DET_HTCC = 15;


    const int tr_word_size = 32;

    TFile *file_out = new TFile("DC_Roads_check_BonusInbend.root", "Recreate");
    TH1D *h_n_part1 = new TH1D("h_n_part1", "", 21, -0.5, 20.5);
    TH1D *h_n_tr_words = new TH1D("h_n_tr_words", "", 11, -0.5, 10.5);
    TH1D *h_n_em_trg1 = new TH1D("h_n_em_trg1", "", 6, -0.5, 5.5);
    TH1D *h_n_dcroad_trg1 = new TH1D("h_n_dcroad_trg1", "", 6, -0.5, 5.5);
    TH2D *h_th_P1 = new TH2D("h_th_P1", "", 200, 0., Eb, 200, 0., 65);
    TH2D *h_SF_em1 = new TH2D("h_SF_em1", "", 200, 0., Eb, 200, 0., 0.35);
    TH1D *h_Nphe_em1 = new TH1D("h_Nphe_em1", "", 200, -1., 35.);
    TH1D *h_Nphe_em_TrgMissed1 = new TH1D("h_Nphe_em_TrgMissed1", "", 200, -1., 35.);
    TH1D *h_tHTCC1 = new TH1D("h_tHTCC1", "", 200, 0., 400.);
    TH1D *h_tHTCC_TrgMissed1 = new TH1D("h_tHTCC_TrgMissed1", "", 200, 0., 400.);

    TH1D *h_P_Goodem1 = new TH1D("h_P_Goodem1", "", 200, 0., 1.05 * Eb);
    TH1D *h_P_Goodem_NoTrg1 = new TH1D("h_P_Goodem_NoTrg1", "", 200, 0., 1.05 * Eb);
    TH1D *h_P_Goodem_NoTrg2 = new TH1D("h_P_Goodem_NoTrg2", "", 200, 0., 1.05 * Eb);
    TH1D *h_P_Goodem_NoTrg3 = new TH1D("h_P_Goodem_NoTrg3", "", 200, 0., 1.05 * Eb);

    TH1D *h_Q2_Goodem1 = new TH1D("h_Q2_Goodem1", "", 200, 0., 4.5);
    TH1D *h_Q2_Goodem_NoTrg1 = new TH1D("h_Q2_Goodem_NoTrg1", "", 200, 0., 4.5);
    TH1D *h_Q2_Goodem_NoTrg2 = new TH1D("h_Q2_Goodem_NoTrg2", "", 200, 0., 4.5);
    TH1D *h_Q2_Goodem_NoTrg3 = new TH1D("h_Q2_Goodem_NoTrg3", "", 200, 0., 4.5);

    TH2D *h_sec_vz_em1 = new TH2D("h_sec_vz_em1", "", 200, -40., 40, 7, -0.5, 6.5);
    TH2D *h_sec_vz_em_RoadFail1 = new TH2D("h_sec_vz_em_RoadFail1", "", 200, -40., 40, 7, -0.5, 6.5);
    TH2D *h_sec_vz_em_RoadFailBigRange1 = new TH2D("h_sec_vz_em_RoadFailBigRange1", "", 200, -60., 140, 7, -0.5, 6.5);

    TH2D *h_th_P_em1 = new TH2D("h_th_P_em1", "", 200, 0., Eb, 200, 0., 65);
    TH2D *h_th_P_em_RoadFailed1 = new TH2D("h_th_P_em_RoadFailed1", "", 200, 0., Eb, 200, 0., 65);

    TH2D *h_Q2_sec1 = new TH2D("h_Q2_sec1", "", 200, 0., 10.5, 7, -0.5, 6.5);
    TH2D *h_Q2_sec_RoadFailed1 = new TH2D("h_Q2_sec_RoadFailed1", "", 200, 0., 10.5, 7, -0.5, 6.5);

    TH2D *h_PCal_YXc1 = new TH2D("h_PCal_YXc1", "", 200, -400., 400., 200, -400., 400.);
    TH2D *h_PCal_YXc_TrgMissed1 = new TH2D("h_PCal_YXc_TrgMissed1", "", 200, -400., 400., 200, -400., 400.);
    TH2D *h_PCal_YXc_TrgMissed2 = new TH2D("h_PCal_YXc_TrgMissed2", "", 200, -400., 400., 200, -400., 400.);

    TH2D *h_tVTP_HTCC1 = new TH2D("h_tVTP_HTCC1", "", 200, 0., 400., 200., 0., 100.);
    TH1D *h_n_trgFound1 = new TH1D("h_n_trgFound1", "", 4, -0.5, 3.5);
    TH1D *h_E_Tot_trgMissed1 = new TH1D("h_E_Tot_trgMissed1", "", 200, 0., 2.5);
    TH1D *h_Pem_trgMissed1 = new TH1D("h_Pem_trgMissed1", "", 200, 0., 2.5);

    TH2D *h_tVTPRoads_HTCC1 = new TH2D("h_tVTPRoads_HTCC1", "", 200, 0., 400., 200., 0., 100.);
    TH1D *h_n_RoadtrgFound1 = new TH1D("h_n_RoadtrgFound1", "", 4, -0.5, 3.5);
    TH2D *h_n_RoadtrgFound_sec1 = new TH2D("h_n_RoadtrgFound_sec1", "", 4, -0.5, 3.5, 7, -0.5, 6.5);
    TH1D *h_E_Tot_RoadtrgMissed1 = new TH1D("h_E_Tot_RoadtrgMissed1", "", 200, 0., 2.5);
    TH1D *h_Pem_RoadtrgMissed1 = new TH1D("h_Pem_RoadtrgMissed1", "", 200, 0., 2.5);

    TH1D *h_n_em1 = new TH1D("h_n_em1", "", 11, -0.5, 10.5);

    TH1D *h_testRoadVTPTIme1 = new TH1D("h_testRoadVTPTIme1", "", 101, -0.5, 100.5);


    hipo::reader reader;
    reader.open(inputFile);

    hipo::dictionary factory;

    reader.readDictionary(factory);

    factory.show();
    hipo::structure particles;
    hipo::structure detectors;

    hipo::event event;
    int counter = 0;

    hipo::bank dataPART;
    hipo::bank dataCALO;

    hipo::bank PART(factory.getSchema("REC::Particle"));
    hipo::bank bRecCalo(factory.getSchema("REC::Calorimeter"));
    hipo::bank bRecCC(factory.getSchema("REC::Cherenkov"));
    hipo::bank bRawVTP(factory.getSchema("RAW::vtp"));
    hipo::bank bRunConf(factory.getSchema("RUN::config"));

    const int n_max_em = 20;
    const int n_max_ep = 20;
    const int n_max_p = 20;

    int ind_em[n_max_em];
    int ind_ep[n_max_ep];
    int ind_p[n_max_p];

    int VTPSIZE = 3000;

    long vtp_crate[VTPSIZE];
    long vtp_word[VTPSIZE];

    unsigned long int evCounter = 0;

    while (reader.next() == true) {
        evCounter++;
        if ((evCounter + 1) % 50000 == 0) {
            cout.flush() << "Processed " << evCounter << "\r";
        }

//        if (evCounter > 200000) {
//            break;
//        }

        reader.read(event);

        event.getStructure(bRunConf);
        
        int evNumber = bRunConf.getInt("event", 0);
        
        //cout<<evNumber<<endl;
        
        
        map<int, int> indPCal;
        map<int, int> indECin;
        map<int, int> indECout;
        map<int, int> indHTCC;

        event.getStructure(bRecCalo);
        int n_RecCalo = bRecCalo.getRows();


        for (int icalo = 0; icalo < n_RecCalo; icalo++) {

            int pindex = bRecCalo.getInt("pindex", icalo);
            int layer = bRecCalo.getInt("layer", icalo);

            if (layer == 1) {
                indPCal[pindex] = icalo + 1;
            } else if (layer == 4) {
                indECin[pindex] = icalo + 1;
            } else if (layer == 7) {
                indECout[pindex] = icalo + 1;
            }

        }


        event.getStructure(bRecCC);
        int nCC = bRecCC.getRows();

        for (int iCC = 0; iCC < nCC; iCC++) {

            int pindex = bRecCC.getInt("pindex", iCC);
            int det = bRecCC.getInt("detector", iCC);
            if (det == DET_HTCC) {
                indHTCC[pindex] = iCC + 1;
            }
        }


        // Bit 0        : Electron all sec
        // Bits 1-6     : Electron sector based
        // Bit 7        : Electron w/ DCRoads all sec
        // Bits 8-13    : Electron with DC roads sector based

        event.getStructure(bRawVTP);
        int n_VTP = bRawVTP.getRows();
        //cout<<n_VTP<<endl;

        for (int i = 0; i < n_VTP; i++) {
            vtp_crate[i] = (long) bRawVTP.getInt("crate", i);
            vtp_word[i] = (long) bRawVTP.getInt("word", i);

            //cout<<vtp_crate[i]<<"\t"<<vtp_word[i]<<endl;
        }

        vector<long> v_vtp_crate(vtp_crate, vtp_crate + n_VTP);
        vector<long> v_vtp_word(vtp_word, vtp_word + n_VTP);

        VTPRoot vtp1(&v_vtp_crate, &v_vtp_word);

        int n_tr_words = vtp1.GetNTrigWords();

        h_n_tr_words->Fill(n_tr_words);


        vector<int> em_trg_sec;
        vector<int> em_trg_time;
        vector<int> dcroad_trg_sec;
        vector<int> dcroad_trg_time;



        for (int i_tr_word = 0; i_tr_word < n_tr_words; i_tr_word++) {

            Trig_word *cur_trg_word = vtp1.GetTrigWord(i_tr_word);

            ap_int<tr_word_size> cur_word = cur_trg_word->tr_word;


            for (int ibite = 0; ibite < 6; ibite++) {

                if (cur_word(ibite + 1, ibite + 1)) { // Electron trig bits
                    em_trg_sec.push_back(ibite);
                    em_trg_time.push_back(cur_trg_word->tr_time);
                }


                if (cur_word(ibite + 8, ibite + 8)) { // Electron with DC roads

                    if (cur_trg_word->tr_time > t_VTPMin && cur_trg_word->tr_time < t_VTPMax) {
                        dcroad_trg_sec.push_back(ibite);
                    }
                    dcroad_trg_time.push_back(cur_trg_word->tr_time);

                    h_testRoadVTPTIme1->Fill(cur_trg_word->tr_time);
                }

            }


        }


        int n_em_bits = em_trg_sec.size();
        int n_dcroad_bits = dcroad_trg_sec.size();

        h_n_em_trg1->Fill(n_em_bits);
        h_n_dcroad_trg1->Fill(n_dcroad_bits);


        event.getStructure(PART);
        int nPART = PART.getRows();

        int n_em = 0;

        for (int ipart = 0; ipart < nPART; ipart++) {

            int pid = PART.getInt("pid", ipart);
            float px = PART.getFloat("px", ipart);
            float py = PART.getFloat("py", ipart);
            float pz = PART.getFloat("pz", ipart);

            float vz = PART.getFloat("vz", ipart);

            int charge = PART.getInt("charge", ipart);
            int stat = PART.getInt("status", ipart);


            float p = sqrt(px * px + py * py + pz * pz);
            double th = acos(pz / p) * TMath::RadToDeg();
            double Q2 = 2 * Eb * p * (1 - cos(th * TMath::DegToRad()));

            h_th_P1->Fill(p, th);

            double EPcal = 0;
            double EECin = 0;
            double EECout = 0;

            float xPCal = -10000;
            float yPCal = -10000;
            int sect_PCal = -100;

            if (indPCal[ipart] > 0) {
                EPcal = bRecCalo.getFloat("energy", indPCal[ipart] - 1);
                yPCal = bRecCalo.getFloat("y", indPCal[ipart] - 1);
                xPCal = bRecCalo.getFloat("x", indPCal[ipart] - 1);

                h_PCal_YXc1->Fill(xPCal, yPCal);

                double phi_PCal = atan2(yPCal, xPCal) * TMath::RadToDeg() + 30;

                if (phi_PCal < 0) {
                    phi_PCal = phi_PCal + 360.;
                }

                sect_PCal = (phi_PCal / 60.);
            }

            float xECin = -10000;
            float yECin = -10000;
            if (indECin[ipart] > 0) {
                EECin = bRecCalo.getFloat("energy", indECin[ipart] - 1);
                yECin = bRecCalo.getFloat("y", indECin[ipart] - 1);
                xECin = bRecCalo.getFloat("x", indECin[ipart] - 1);
            }

            float xECout = -10000;
            float yECout = -10000;
            if (indECout[ipart] > 0) {
                EECout = bRecCalo.getFloat("energy", indECout[ipart] - 1);
                yECout = bRecCalo.getFloat("y", indECin[ipart] - 1);
                xECout = bRecCalo.getFloat("x", indECin[ipart] - 1);
            }

            double Etot = EPcal + EECin + EECout;
            double EEC = EECin + EECout;

            float nphe = 0;
            float t_HTCC = 0;

            if (indHTCC[ipart] > 0) {
                nphe = bRecCC.getFloat("nphe", indHTCC[ipart] - 1);
                t_HTCC = bRecCC.getFloat("time", indHTCC[ipart] - 1);
                h_tHTCC1->Fill(t_HTCC);
            }

            bool trg_Conditions = (EPcal > E_PCalMin) && (Etot > E_TotMin) && (nphe > NPheMin);
            bool SF_Passed = Etot / p > SF_Min;

            bool tHTCC_Passed = (t_HTCC > t_HTCCMin) && (t_HTCC < t_HTCCMax);

            if (EPcal > E_PCalMin && Etot > E_TotMin && nphe > NPheMin) {
            }

            if (pid == 11 && TMath::Abs(stat) >= 2000 && TMath::Abs(stat) <= 4000) {
                h_SF_em1->Fill(p, Etot / p);
                h_Nphe_em1->Fill(nphe);



                if (trg_Conditions && SF_Passed && tHTCC_Passed) {

                    int n_trgFound = 0;
                    for (int iemTrg = 0; iemTrg < em_trg_sec.size(); iemTrg++) {

                        h_P_Goodem1->Fill(p);
                        h_Q2_Goodem1->Fill(Q2);

                        if (em_trg_sec.at(iemTrg) == sect_PCal) {

                            h_tVTP_HTCC1->Fill(t_HTCC, em_trg_time.at(iemTrg));

                            n_trgFound = n_trgFound + 1;
                        }

                    }

                    h_n_trgFound1->Fill(n_trgFound);

                    if (n_trgFound == 0) {
                        h_E_Tot_trgMissed1->Fill(Etot);
                        h_Pem_trgMissed1->Fill(p);

                        h_P_Goodem_NoTrg1->Fill(p);
                        h_Q2_Goodem_NoTrg1->Fill(Q2);

                        if (nphe < 3.2) {
                            h_P_Goodem_NoTrg2->Fill(p);
                            h_Q2_Goodem_NoTrg2->Fill(Q2);
                        } else {
                            h_P_Goodem_NoTrg3->Fill(p);
                            h_Q2_Goodem_NoTrg3->Fill(Q2);
                        }

                        if (Etot > 0.35) {
                            h_PCal_YXc_TrgMissed1->Fill(xPCal, yPCal);
                            h_Nphe_em_TrgMissed1->Fill(nphe);

                            if (nphe > 3.2) {
                                h_PCal_YXc_TrgMissed2->Fill(xPCal, yPCal);

                                h_tHTCC_TrgMissed1->Fill(t_HTCC);
                            }
                        }
                    }

                    // For some reason there are electron tracks, where no electron trigger worked
                    // Those are mostly low energy electrons, where the trigger indeed should not have worked,
                    // but the event is readout not from the e- trigger
                    if (!n_trgFound) {
                        continue;
                    }

                    h_sec_vz_em1->Fill(vz, sect_PCal);

                    if (vz > vzMin && vz < vzMax) {
                        h_Q2_sec1->Fill(Q2, sect_PCal);
                        if (sect_PCal != 0) {
                            h_th_P_em1->Fill(p, th);
                        }
                    }

                    int n_trgRoadsFound = 0;
                    for (int iemTrg = 0; iemTrg < dcroad_trg_sec.size(); iemTrg++) {

                        if (dcroad_trg_sec.at(iemTrg) == sect_PCal) {

                            h_tVTPRoads_HTCC1->Fill(t_HTCC, dcroad_trg_time.at(iemTrg));

                            n_trgRoadsFound = n_trgRoadsFound + 1;
                        }

                    }

                    h_n_RoadtrgFound1->Fill(n_trgRoadsFound);

                    h_n_RoadtrgFound_sec1->Fill(n_trgRoadsFound, sect_PCal);

                    if (n_trgRoadsFound == 0) {
                        h_E_Tot_RoadtrgMissed1->Fill(Etot);
                        h_Pem_RoadtrgMissed1->Fill(p);

                        h_sec_vz_em_RoadFail1->Fill(vz, sect_PCal);
                        h_sec_vz_em_RoadFailBigRange1->Fill(vz, sect_PCal);

                         //cout<<evNumber<<endl;
                        
                        if (vz > vzMin && vz < vzMax) {
                            h_Q2_sec_RoadFailed1->Fill(Q2, sect_PCal);

                            if (sect_PCal != 0) {
                                h_th_P_em_RoadFailed1->Fill(p, th);
                            }   
                        }
                    }


                }



                ind_em[n_em] = ipart;
                n_em = n_em + 1;
            }



        }

        h_n_em1->Fill(n_em);

        // ===== Loop over all electrons, and for a given electron, check if the corresponding sector trigger bit is fired
        // ===== It needs to be checked for e-, and e- with DC Roads
        for (int iem = 0; iem < n_em; iem++) {

        }

    }

    gDirectory->Write();
    file_out->Close();

    return 0;
}


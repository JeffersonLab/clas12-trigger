/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HTCC_Validate.cc
 * Author: rafopar
 *
 * Created on December 5, 2017, 2:25 PM
 */

#include <cstdlib>
#include "TDetTrue.hh"
#include "ECTrig.hh"
#include "ECGeom.hh"

#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TChain.h>
#include <evioUtil.hxx>
#include <evioFileChannel.hxx>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    const double r2d = 57.295780;
    const int HTCC_true_tag = 601;
    const int adcECvtp_tagmin = 100;
    const int adcECvtp_tagmax = 115;
    const int vtp_tag = 57634;
    const int FADC_Mode1_tag = 57601;
    const int n_sect = 6;

    int adcvtp_tag;

    TChain *ch1 = new TChain();

    if (argc < 2) {
        cout << "Please Specify input File name(s) " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    string inp_file_patttern = argv[1];
    cout << inp_file_patttern << endl;
    ch1->Add(inp_file_patttern.c_str());

    TObjArray *fname_list = ch1->GetListOfFiles();
    int n_files = fname_list->GetEntries();
    cout << "Number of Files is " << n_files << endl;

    const int run = 1894;
    
    //TFile *file_out = new TFile("HTCC_Validation.root", "Recreate");
    TFile *file_out = new TFile(Form("HTCC_Validation_%d.root", run), "Recreate");

    TH2D *h_n_HTCC_trig_true_bans = new TH2D("h_n_HTCC_trig_true_bans", "", 10, -0.5, 9.5, 10, -0.5, 9.5);
    TH1D *h_n_HTCC_masks1 = new TH1D("h_n_HTCC_masks1", "", 10, -0.5, 9.5);
    TH1D *h_n_HTCC_hits1 = new TH1D("h_n_HTCC_hits1", "", 10, -0.5, 9.5);

    TH2D *h_HTCC_True_yxc1 = new TH2D("h_HTCC_True_yxc1", "", 800, -220., 220., 800, -220., 220.);
    TH2D *h_HTCC_th_phi_true1 = new TH2D("h_HTCC_th_phi_true1", "", 200, 0., 360., 200, 60., 100.);
    TH2D *h_HTCC_th_phi_true2 = new TH2D("h_HTCC_th_phi_true2", "", 200, 0., 360., 200, 60., 100.);

    TH2D *h_HTCC_th_maskNo1 = new TH2D("h_HTCC_th_maskNo1", "", 49, -0.5, 48.5, 50, 60., 100.);
    TH2D *h_HTCC_phi_maskNo1 = new TH2D("h_HTCC_phi_maskNo1", "", 49, -0.5, 48.5, 200, 0., 360.);

    TH2D *h_HTCC_th_maskNo2 = new TH2D("h_HTCC_th_maskNo2", "", 49, -0.5, 48.5, 50, 60., 100.);
    TH2D *h_HTCC_phi_maskNo2 = new TH2D("h_HTCC_phi_maskNo2", "", 49, -0.5, 48.5, 200, 0., 360.);

    // =============== EC PCal Matching ==========================
    TH2D *h_PCal_EC_U1 = new TH2D("h_PCal_EC_U1", "", 300, 0., 300., 300, 0., 300);
    TH2D *h_PCal_EC_U2 = new TH2D("h_PCal_EC_U2", "", 300, 0., 300., 300, 0., 300);
    TH2D *h_PCal_EC_V1 = new TH2D("h_PCal_EC_V1", "", 300, 0., 300., 300, 0., 300);
    TH2D *h_PCal_EC_V2 = new TH2D("h_PCal_EC_V2", "", 300, 0., 300., 300, 0., 300);
    TH2D *h_PCal_EC_W1 = new TH2D("h_PCal_EC_W1", "", 300, 0., 300., 300, 0., 300);
    TH2D *h_PCal_EC_W2 = new TH2D("h_PCal_EC_W2", "", 300, 0., 300., 300, 0., 300);

    TH2D * h_PCal_EC_U1_[n_sect];
    TH2D * h_PCal_EC_V1_[n_sect];
    TH2D * h_PCal_EC_W1_[n_sect];

    for (int i_sect = 0; i_sect < n_sect; i_sect++) {
        h_PCal_EC_U1_[i_sect] = new TH2D(Form("h_PCal_EC_U_%d", i_sect), "", 300, 0., 300., 300, 0., 300);
        h_PCal_EC_V1_[i_sect] = new TH2D(Form("h_PCal_EC_V_%d", i_sect), "", 300, 0., 300., 300, 0., 300);
        h_PCal_EC_W1_[i_sect] = new TH2D(Form("h_PCal_EC_W_%d", i_sect), "", 300, 0., 300., 300, 0., 300);
    }




    try {

        for (int ifile = 0; ifile < n_files; ifile++) {

            evioFileChannel chan(fname_list->At(ifile)->GetTitle(), "r");
            cout << "Running the file " << fname_list->At(ifile)->GetTitle() << endl;
            chan.open();


            while (chan.read()) {

                TDetTrue htcc_true;
                vector<TECTrig> ec_trig;
                vector<TECTrig> pcal_trig;
                vector<TECTrig> htcc_trig;

                evioDOMTree tree(chan);

                evioDOMNodeListP nodelist1 = tree.getNodeList();


                for (std::list<evioDOMNode*>::iterator it = nodelist1.get()->begin(); it != nodelist1.get()->end(); it++) {

                    if ((*it)->tag == HTCC_true_tag && !(*it)->isLeaf()) {
                        int size_HTCC_bank = (*it)->getSize();
                        //cout<<"Kuku"<<size_HTCC_bank<<endl;
                        htcc_true.SetevioDOMNode(*it);

                    } else if ((*it)->tag >= adcECvtp_tagmin && (*it)->tag <= adcECvtp_tagmax) {
                        adcvtp_tag = (*it)->tag;

                    } else if ((*it)->tag == vtp_tag) {
                        TECTrig trig(*it, adcvtp_tag);

                        // Check if the detector is HTCC

                        switch (trig.GetDetector()) {
                            case 1: ec_trig.push_back(trig);
                                break;
                            case 2: pcal_trig.push_back(trig);
                                break;
                            case 4: htcc_trig.push_back(trig);
                                break;

                        }

                    }

                }

                int n_htcc_banks = htcc_trig.size();
                // ====== GEMC EC clusters
                int n_HTCCTrue = htcc_true.Npart();

                h_n_HTCC_trig_true_bans->Fill(n_HTCCTrue, n_htcc_banks);

                //   cout<<n_HTCCTrue<<endl;

                for (int i_true = 0; i_true < n_HTCCTrue; i_true++) {

                    //cout<<"HTCC pid = "<<htcc_true.PID(i_true)<<endl;

                    if (htcc_true.PID(i_true) == 0) {

                        double z_true = htcc_true.Zavg(i_true) / 10.;
                        double y_true = htcc_true.Yavg(i_true) / 10.;
                        double x_true = htcc_true.Xavg(i_true) / 10.;

                        //cout<<"Z_true = "<<z_true<<endl;

                        double th_true = atan(sqrt(x_true * x_true + y_true * y_true) / z_true) * r2d;
                        if (th_true < 0) {
                            th_true = th_true + 180.;
                        }
                        double phi_true = atan2(y_true, x_true) * r2d + 30.;
                        if (phi_true < 0.) {
                            phi_true = phi_true + 360.;
                        }

                        h_HTCC_True_yxc1->Fill(x_true, y_true);
                        h_HTCC_th_phi_true1->Fill(phi_true, th_true);


                        for (int i_htcc_trig = 0; i_htcc_trig < n_htcc_banks; i_htcc_trig++) {


                            int n_cur_htcc_masks = htcc_trig.at(i_htcc_trig).GetNHTCCMasks();

                            h_n_HTCC_masks1->Fill(n_cur_htcc_masks);

                            for (int imask = 0; imask < n_cur_htcc_masks; imask++) {

                                THTCC_mask *htcc_mask = htcc_trig.at(i_htcc_trig).GetHTCCMask(imask);

                                vector<int> hit_channels = htcc_mask->chan;

                                h_n_HTCC_hits1->Fill(hit_channels.size());

                                for (int i_chan = 0; i_chan < hit_channels.size(); i_chan++) {
                                    h_HTCC_phi_maskNo1->Fill(hit_channels.at(i_chan), phi_true);
                                    h_HTCC_th_maskNo1->Fill(hit_channels.at(i_chan), th_true);

                                    if (n_htcc_banks == 1 && n_HTCCTrue == 1 /*&& hit_channels.size() == 1 */) {

                                        h_HTCC_phi_maskNo2->Fill(hit_channels.at(i_chan), phi_true);
                                        h_HTCC_th_maskNo2->Fill(hit_channels.at(i_chan), th_true);
                                    }

                                }
                            }

                        }


                        if (n_htcc_banks == 0) {
                            h_HTCC_th_phi_true2->Fill(phi_true, th_true);

                        }


                    }


                }


                // ======================= EC - PCal matching ================


                int n_pcal_banks = pcal_trig.size();
                int n_ec_banks = ec_trig.size();


                // Now let's loop over pcal clusters, and inside EC clusters to see their correlations

                for (int i_pcal_trg = 0; i_pcal_trg < n_pcal_banks; i_pcal_trg++) {

                    int n_pcal_clust = pcal_trig.at(i_pcal_trg).GetNAllClust();

                    for (int i_pcal_cl = 0; i_pcal_cl < n_pcal_clust; i_pcal_cl++) {

                        double cl_U_pcal = double(pcal_trig.at(i_pcal_trg).GetECCluster(0, i_pcal_cl)->Ustrip);
                        double cl_V_pcal = double(pcal_trig.at(i_pcal_trg).GetECCluster(0, i_pcal_cl)->Vstrip);
                        double cl_W_pcal = double(pcal_trig.at(i_pcal_trg).GetECCluster(0, i_pcal_cl)->Wstrip);

                        int pcal_sect = pcal_trig.at(i_pcal_trg).GetSector();

                        for (int i_ec_trg = 0; i_ec_trg < n_ec_banks; i_ec_trg++) {

                            int n_ec_clust = ec_trig.at(i_ec_trg).GetNAllClust();

                            for (int i_ec_clust = 0; i_ec_clust < n_ec_clust; i_ec_clust++) {

                                double cl_U_ec = double(ec_trig.at(i_ec_trg).GetECCluster(0, i_ec_clust)->Ustrip);
                                double cl_V_ec = double(ec_trig.at(i_ec_trg).GetECCluster(0, i_ec_clust)->Vstrip);
                                double cl_W_ec = double(ec_trig.at(i_ec_trg).GetECCluster(0, i_ec_clust)->Wstrip);

                                int ec_sect = ec_trig.at(i_ec_trg).GetSector();

                                if (pcal_sect == ec_sect) {

                                    h_PCal_EC_U1->Fill(cl_U_ec, cl_U_pcal);
                                    h_PCal_EC_V1->Fill(cl_V_ec, cl_V_pcal);
                                    h_PCal_EC_W1->Fill(cl_W_ec, cl_W_pcal);

                                    h_PCal_EC_U1_[pcal_sect]->Fill(cl_U_ec, cl_U_pcal);
                                    h_PCal_EC_V1_[pcal_sect]->Fill(cl_V_ec, cl_V_pcal);
                                    h_PCal_EC_W1_[pcal_sect]->Fill(cl_W_ec, cl_W_pcal);
                                    
                                    
                                    if (n_pcal_clust == 1 && n_ec_clust) {

                                        h_PCal_EC_U2->Fill(cl_U_ec, cl_U_pcal);
                                        h_PCal_EC_V2->Fill(cl_V_ec, cl_V_pcal);
                                        h_PCal_EC_W2->Fill(cl_W_ec, cl_W_pcal);

                                    }

                                }


                            }

                        }

                    }


                }



            }

        }


    } catch (evioException e) {
        cerr << endl << e.toString() << endl;
        exit(EXIT_FAILURE);
    }


    gDirectory->Write();


    return 0;
}

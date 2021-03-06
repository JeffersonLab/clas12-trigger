#include <evioUtil.hxx>
#include <evioFileChannel.hxx>
#include <list>
#include <ECTrig.hh>
#include <ECGeom.hh>
#include <TPCalGeom.hh>
#include <TTrigBit.hh>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TStyle.h>

using namespace evio;
using namespace std;

// This program loops over events from the input file, given as an argument.
// It will search for banks with a tag "0xe122" ("57634" in decimal representation)
// Then will loop over all words inside the bank and decode all the information,
// e.g. which part of EC (in, or out), cluster coordinates (u, v, w), etc

int main(int argc, char **argv) {

    const double Dalitz_ECout_max = 0.0833333;
    const double Dalitz_ECout_min = -0.0555556;

    const double r2d = 57.2957795130823229;
    // ===== Put temporarly 2.75 for all
    const double U_conv = 2.75; // This converts U coordinate from the Trigger bank into coordinate real U coordinate
    const double V_conv = 3.; // This converts V coordinate from the Trigger bank into coordinate real V coordinate
    const double W_conv = 3.; // This converts W coordinate from the Trigger bank into coordinate real W coordinate

    const int n_sect = 6;
    const int n_view = 3;
    const int vtp_tag = 57634;
    const int adcECvtp_tagmin = 100;
    const int adcECvtp_tagmax = 112;

    const double ADC2GeV = 1. / 10000.;

    const double E_bin_width = 0.3;
    const int n_E_bins = 5;

    const int ftrig_crate_ID = 37;
    const int trig_bank_tag = 57610;

    int n_events_to_Analyze = 100000; // Default value
    //    const int adcECvtp_tagmin = 60000;
    //    const int adcECvtp_tagmax = 60115;

    TChain *ch1 = new TChain();

    if (argc < 2) {
        cout << "Please Specify input File name(s) " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    if( argc >= 3 ){
        n_events_to_Analyze = atoi(argv[2]);
    }
    
    string inp_file_patttern = argv[1];
    cout << inp_file_patttern << endl;
    ch1->Add(inp_file_patttern.c_str());

    TObjArray *fname_list = ch1->GetListOfFiles();
    int n_files = fname_list->GetEntries();
    cout << "Number of Files is " << n_files << endl;
    cout << "Number of Tot. events to analyze1 " << n_events_to_Analyze << endl;

    int run = 2118;
    //TFile *file_out = new TFile(Form("VTP_out_%s.root", argv[1]), "Recreate");
    TFile *file_out = new TFile(Form("Data/VTP_out_%d.root", run), "Recreate");

    TH1D *h_tr_bit_distr = new TH1D("h_tr_bit_distr", "", 33, -0.5, 32.5);

    TH2D * h_N_ECpeaks1_[n_view];
    TH2D * h_N_ECpeaks2_[n_view];
    TH2D * h_N_ECpeaks3_[n_view];
    TH2D * h_t_ECpeak1_[n_view];
    TH2D * h_coord_ECpeak1_[n_view];

    TH2D *h_N_ECClust1 = new TH2D("h_N_ECClust1", "", 11, -0.5, 10.5, 7, -0.5, 6.5);
    TH2D *h_N_ECClust2 = new TH2D("h_N_ECClust2", "", 11, -0.5, 10.5, 7, -0.5, 6.5);
    TH2D *h_ECcl_t1 = new TH2D("h_ECcl_t1", "", 21, -0.5, 20.5, 7, -0.5, 6.5);
    TH2D *h_ECcl_E1 = new TH2D("h_ECcl_E1", "", 200, 0., 3, 7, -0.5, 6.5);
    TH2D *h_ECcl_E2 = new TH2D("h_ECcl_E2", "", 200, 0., 3, 7, -0.5, 6.5);
    TH2D *h_ECcl_U1 = new TH2D("h_ECcl_U1", "", 41, -0.5, 40.5, 7, -0.5, 6.5);
    TH2D *h_ECcl_V1 = new TH2D("h_ECcl_V1", "", 41, -0.5, 40.5, 7, -0.5, 6.5);
    TH2D *h_ECcl_W1 = new TH2D("h_ECcl_W1", "", 41, -0.5, 40.5, 7, -0.5, 6.5);

    TH2D *h_EC_yxc1 = new TH2D("h_EC_yxc1", "", 200, -500., 500., 200, -500., 500.);
    TH2D *h_EC_yxc_UV1 = new TH2D("h_EC_yxc_UV1", "", 200, -500., 500., 200, -500., 500.);
    TH2D *h_EC_yxc_UW1 = new TH2D("h_EC_yxc_UW1", "", 200, -500., 500., 200, -500., 500.);
    TH2D *h_EC_yxc_VW1 = new TH2D("h_EC_yxc_VW1", "", 200, -500., 500., 200, -500., 500.);
    TH2D *h_EC_th_phi_cl1 = new TH2D("h_EC_th_phi_cl1", "", 360., 0., 360., 200, 0., 50.);

    TH2D * h_EC_th_phi_cl_[n_E_bins];

    for (int i = 0; i < n_E_bins; i++) {
        h_EC_th_phi_cl_[i] = new TH2D(Form("h_EC_th_phi_cl_%d", i), "", 360., 0., 360., 200, 0., 50.);
    }


    TH2D *h_PCal_yxc1 = new TH2D("h_PCal_yxc1", "", 200, -500., 500., 200, -500., 500.);
    TH2D *h_PCal_yxc2 = new TH2D("h_PCal_yxc2", "", 200, -500., 500., 200, -500., 500.);
    TH2D *h_PCal_yxc3 = new TH2D("h_PCal_yxc3", "", 200, -500., 500., 200, -500., 500.);
    TH2D *h_PCal_yxc4 = new TH2D("h_PCal_yxc4", "", 200, -500., 500., 200, -500., 500.);
    TH2D *h_PCal_yxc_UV1 = new TH2D("h_PCal_yxc_UV1", "", 200, -500., 500., 200, -500., 500.);
    TH2D *h_PCal_yxc_UW1 = new TH2D("h_PCal_yxc_UW1", "", 200, -500., 500., 200, -500., 500.);
    TH2D *h_PCal_yxc_VW1 = new TH2D("h_PCal_yxc_VW1", "", 200, -500., 500., 200, -500., 500.);


    TH2D *h_Dalitz_cl1 = new TH2D("h_Dalitz_cl1", "", 40, -0.5, 0.5, 7, -0.5, 6.5);
    TH2D *h_Dalitz_Peaks1 = new TH2D("h_Dalitz_Peaks1", "", 40, -0.5, 0.5, 7, -0.5, 6.5);
    TH2D *h_PCal_Dalitz_Peaks1 = new TH2D("h_PCal_Dalitz_Peaks1", "", 40, -0.5, 0.5, 7, -0.5, 6.5);
    TH2D *h_PCal_Dalitz_Clust1 = new TH2D("h_PCal_Dalitz_Clust1", "", 40, -0.5, 0.5, 7, -0.5, 6.5);

    TH2D * h_N_PCalpeaks1_[n_view];
    TH2D * h_N_PCalpeaks2_[n_view];
    TH2D * h_N_PCalpeaks3_[n_view];
    TH2D * h_t_PCalpeak1_[n_view];
    TH2D * h_coord_PCalpeak1_[n_view];

    TH2D *h_N_PCalClust1 = new TH2D("h_N_PCalClust1", "", 11, -0.5, 10.5, 7, -0.5, 6.5);
    TH2D *h_N_PCalClust2 = new TH2D("h_N_PCalClust2", "", 11, -0.5, 10.5, 7, -0.5, 6.5);
    TH2D *h_N_PCalClust3 = new TH2D("h_N_PCalClust3", "", 11, -0.5, 10.5, 7, -0.5, 6.5);
    TH2D *h_PCalcl_t1 = new TH2D("h_PCalcl_t1", "", 21, -0.5, 20.5, 7, -0.5, 6.5);
    TH2D *h_PCalcl_E1 = new TH2D("h_PCalcl_E1", "", 200, 0., 4., 7, -0.5, 6.5);
    TH2D *h_PCalcl_E2 = new TH2D("h_PCalcl_E2", "", 200, 0., 4., 7, -0.5, 6.5);
    TH2D *h_PCalcl_E3 = new TH2D("h_PCalcl_E3", "", 200, 0., 4., 7, -0.5, 6.5);
    TH2D *h_PCalcl_E4 = new TH2D("h_PCalcl_E4", "", 200, 0., 4., 7, -0.5, 6.5);
    TH2D *h_PCalcl_U1 = new TH2D("h_PCalcl_U1", "", 86, -0.5, 85.5, 7, -0.5, 6.5);
    TH2D *h_PCalcl_V1 = new TH2D("h_PCalcl_V1", "", 86, -0.5, 85.5, 7, -0.5, 6.5);
    TH2D *h_PCalcl_W1 = new TH2D("h_PCalcl_W1", "", 86, -0.5, 85.5, 7, -0.5, 6.5);
    TH2D *h_PCal_th_phi_cl1 = new TH2D("h_PCal_th_phi_cl1", "", 360., 0., 360., 200, 0., 50.);

    TH1D *h_PCal_dU_43 = new TH1D("h_PCal_dU_43", "", 600, -90., 90.);
    TH1D *h_PCal_dV_43 = new TH1D("h_PCal_dV_43", "", 600, -80., 80.);
    TH1D *h_PCal_dW_43 = new TH1D("h_PCal_dW_43", "", 600, -80., 80.);

    TH2D * h_PCal_th_phi_cl_[n_E_bins];

    for (int i = 0; i < n_E_bins; i++) {
        h_PCal_th_phi_cl_[i] = new TH2D(Form("h_pcal_th_phi_cl_%d", i), "", 360., 0., 360., 200, 0., 50.);
    }


    for (int i_view = 0; i_view < n_view; i_view++) {
        h_N_ECpeaks1_[i_view] = new TH2D(Form("h_N_ECpeaks1_%d", i_view), "", 11, -0.5, 10.5, 7, -0.5, 6.5);
        h_N_ECpeaks2_[i_view] = new TH2D(Form("h_N_ECpeaks2_%d", i_view), "", 11, -0.5, 10.5, 7, -0.5, 6.5);
        h_N_ECpeaks3_[i_view] = new TH2D(Form("h_N_ECpeaks3_%d", i_view), "", 11, -0.5, 10.5, 7, -0.5, 6.5);
        h_t_ECpeak1_[i_view] = new TH2D(Form("h_t_ECpeak1_%d", i_view), "", 21, -0.5, 20.5, 7, -0.5, 6.5);
        h_coord_ECpeak1_[i_view] = new TH2D(Form("h_coord_ECpeak1_%d", i_view), "", 41, -0.5, 40.5, 7, -0.5, 6.5);

        h_N_PCalpeaks1_[i_view] = new TH2D(Form("h_N_PCalpeaks1_%d", i_view), "", 11, -0.5, 10.5, 7, -0.5, 6.5);
        h_N_PCalpeaks2_[i_view] = new TH2D(Form("h_N_PCalpeaks2_%d", i_view), "", 11, -0.5, 10.5, 7, -0.5, 6.5);
        h_N_PCalpeaks3_[i_view] = new TH2D(Form("h_N_PCalpeaks3_%d", i_view), "", 11, -0.5, 10.5, 7, -0.5, 6.5);
        h_t_PCalpeak1_[i_view] = new TH2D(Form("h_t_PCalpeak1_%d", i_view), "", 21, -0.5, 20.5, 7, -0.5, 6.5);
        h_coord_PCalpeak1_[i_view] = new TH2D(Form("h_coord_PCalpeak1_%d", i_view), "", 86, -0.5, 85.5, 7, -0.5, 6.5);
    }


    TH1D *h_HTCC_time1 = new TH1D("h_HTCC_time1", "", 101, -0.5, 100.5);
    TH1D *h_n_HTCC_masks = new TH1D("h_n_HTCC_masks", "", 11, -0.5, 10.5);
    TH1D *h_n_HTCC_hits = new TH1D("h_n_HTCC_hits", "", 50, -0.5, 49.5);
    TH1D *h_HTCC_hit_chan1 = new TH1D("h_HTCC_hit_chan1", "", 50, -0.5, 49.5);

    TH2D *h_FTOF_time1 = new TH2D("h_FTOF_time1", "", 51, -0.5, 50.5, 7, -0.5, 6.5);
    TH2D *h_n_FTOF_masks = new TH2D("h_n_FTOF_masks", "", 11, -0.5, 10.5, 7, -0.5, 6.5);
    TH2D *h_n_FTOF_hits = new TH2D("h_n_FTOF_hits", "", 64, -0.5, 63.5, 7, -0.5, 6.5);
    TH2D *h_FTOF_hit_chan1 = new TH2D("h_FTOF_hit_chan1", "", 64, -0.5, 63.5, 7, -0.5, 6.5);


    int adcECvtp_tag;

    try {

        unsigned int i_ev = 0;

        for (int ifile = 0; ifile < n_files; ifile++) {

            evioFileChannel chan(fname_list->At(ifile)->GetTitle(), "r");
            cout << "Running the file " << fname_list->At(ifile)->GetTitle() << endl;
            chan.open();


            // evioFileChannel chan(argv[1], "r");
            // chan.open();

            while (chan.read()) {

                i_ev = i_ev + 1;

                evioDOMTree tree(chan);

                evioDOMNodeListP nodelist1 = tree.getNodeList();
		
		// ====== LET'S CHECK THE TRIGGER BIT SO IT WILL RUN OVER THE EVENT TWISE =====

		int crate_id_trig = -1;
		
		TTrigBit tr_bit;

		for (std::list<evioDOMNode*>::iterator it = nodelist1.get()->begin(); it != nodelist1.get()->end(); it++) {
		  
		  
		  if( (*it)->tag > 0 && (*it)->tag < 120 )
		    {
		      crate_id_trig = (*it)->tag;
		    }
		  
		  if( crate_id_trig == ftrig_crate_ID && (*it)->tag == trig_bank_tag ){
		    
		    tr_bit.SetevioDOMENodeCrateID(*it, crate_id_trig);

		    for( int i = 0; i < 32; i++ ){
		      h_tr_bit_distr->Fill(i, tr_bit.GetBit(i));
		    }

		  }

		}
		

                bool has_TOF = false;
                bool has_EC = false;
                bool has_PCal = false;
                bool has_HTCC = false;

                TECTrig trig; // adcECvtp_tag determines the vtp crate (or sector in another words)

                for (std::list<evioDOMNode*>::iterator it = nodelist1.get()->begin(); it != nodelist1.get()->end(); it++) {

                    if ((*it)->tag >= adcECvtp_tagmin && (*it)->tag <= adcECvtp_tagmax) {
                        adcECvtp_tag = (*it)->tag;
                    }

                    if ((*it)->tag == vtp_tag) {

                        //  TECTrig trig(*it, adcECvtp_tag); // adcECvtp_tag determines the vtp crate (or sector in another words)
                        trig.SetevioDOMENodeSect(*it, adcECvtp_tag);

                        int detector = trig.GetDetector();
                        int sector = trig.GetSector();
			
			if( sector >5 ){continue;}
			if( !tr_bit.El_Sec(sector) ){continue;}

                        int ev_number = trig.GetEvNumber();

                        if (detector == 1) { // ECal

                            vector<TEC_Peak*> v_Peaks_[3]; // 3 is U, V or W

                            // ====== EC Peaks ======
                            for (int i_view = 0; i_view < n_view; i_view++) {

                                int n_ECpeaks = trig.GetNPeaks(0, i_view);
                                h_N_ECpeaks1_[i_view]->Fill(n_ECpeaks, sector);

                                for (int i_peak = 0; i_peak < n_ECpeaks; i_peak++) {

                                    h_t_ECpeak1_[i_view]->Fill(trig.GetECPeak(0, i_view, i_peak)->time, sector);

                                    double coord = double(trig.GetECPeak(0, i_view, i_peak)->coord) / 8.;
                                    h_coord_ECpeak1_[i_view]->Fill(coord, sector);

                                    v_Peaks_[i_view].push_back(trig.GetECPeak(0, i_view, i_peak));
                                }
                            }

                            for (int iU = 0; iU < v_Peaks_[0].size(); iU++) {
                                for (int iV = 0; iV < v_Peaks_[1].size(); iV++) {
                                    for (int iW = 0; iW < v_Peaks_[2].size(); iW++) {

                                        //if( v_Peaks_[2].at(iW)->coord / 8. < 35 ){continue;}

                                        TECGeom ec_geom_peaks(v_Peaks_[0].at(iU)->coord / 8., v_Peaks_[1].at(iV)->coord / 8., v_Peaks_[2].at(iW)->coord / 8.);
                                        //TECGeom ec_geom_peaks(v_Peaks_[0].at(iU)->coord / 8., 15., 57 - v_Peaks_[0].at(iU)->coord / 8.);
                                        ec_geom_peaks.SetSector(sector);

                                        double hall_x_UV = ec_geom_peaks.GetHallX_UV();
                                        double hall_y_UV = ec_geom_peaks.GetHallY_UV();
                                        h_EC_yxc_UV1->Fill(hall_x_UV, hall_y_UV);

                                        double hall_x_UW = ec_geom_peaks.GetHallX_UW();
                                        double hall_y_UW = ec_geom_peaks.GetHallY_UW();
                                        h_EC_yxc_UW1->Fill(hall_x_UW, hall_y_UW);

                                        double hall_x_VW = ec_geom_peaks.GetHallX_VW();
                                        double hall_y_VW = ec_geom_peaks.GetHallY_VW();
                                        h_EC_yxc_VW1->Fill(hall_x_VW, hall_y_VW);

                                        double Dalitz_peaks = ec_geom_peaks.GetDalitz();

                                        h_Dalitz_Peaks1->Fill(Dalitz_peaks, sector);
                                    }

                                }

                            }


                            // ====== EC Clusters =======

                            int n_cl = trig.GetNClust(0); // Argument is the EC instance, but now it should be 0 all the time

                            h_N_ECClust1->Fill(n_cl, sector);
			    
			    int n_cl_in_1_tbin = 0;

                            for (int i_cl = 0; i_cl < n_cl; i_cl++) {
                                int cl_time = trig.GetECCluster(0, i_cl)->time;
                                double cl_U = double(trig.GetECCluster(0, i_cl)->Ustrip) / 8.;
                                double cl_V = double(trig.GetECCluster(0, i_cl)->Vstrip) / 8.;
                                double cl_W = double(trig.GetECCluster(0, i_cl)->Wstrip) / 8.;
                                double cl_E = double(trig.GetECCluster(0, i_cl)->energy) * ADC2GeV;

                                TECGeom ec_geom(cl_U, cl_V, cl_W);

                                ec_geom.SetSector(sector);

                                double hall_x_cl = ec_geom.GetHallX_UV();
                                double hall_y_cl = ec_geom.GetHallY_UV();
                                double hall_z_cl = ec_geom.GetHallZ_UV();

                                int E_bin = TMath::Min(int(cl_E / E_bin_width), n_E_bins - 1); // for not being out of range

                                double phi_cl = atan2(hall_y_cl, hall_x_cl) * r2d + 30.;
                                if (phi_cl < 0.) {
                                    phi_cl = phi_cl + 360.;
                                }
                                double th_cl = atan(sqrt(hall_x_cl * hall_x_cl + hall_y_cl * hall_y_cl) / hall_z_cl) * r2d;

                                h_EC_th_phi_cl1->Fill(phi_cl, th_cl);

                                h_EC_th_phi_cl_[E_bin]->Fill(phi_cl, th_cl);

                                h_EC_yxc1->Fill(hall_x_cl, hall_y_cl);
                                //cout<<"Ev. number is "<<ev_number<<"    n_cl is "<<n_cl<<"    sector is "<<sector<<"    cl energy is "<<trig.GetECCluster(0, i_cl)->energy<<endl;

                                double cl_Dalitz = ec_geom.GetDalitz();

                                h_Dalitz_cl1->Fill(cl_Dalitz, sector);

                                h_ECcl_t1->Fill(cl_time, sector);
                                h_ECcl_U1->Fill(cl_U, sector);
                                h_ECcl_V1->Fill(cl_V, sector);
                                h_ECcl_W1->Fill(cl_W, sector);
                                h_ECcl_E1->Fill(cl_E, sector);

				if(cl_time == 7){
				  n_cl_in_1_tbin = n_cl_in_1_tbin + 1;
				  h_ECcl_E2->Fill(cl_E, sector);
				}
                            }
			    
			    h_N_ECClust2->Fill(n_cl_in_1_tbin, sector);

                            //cout<<"n_upeaks = "<<n_upeaks<<endl;

                        } else if (detector == 2) { // PCal

                            vector<TEC_Peak*> v_Peaks_[3]; // 3 is U, V or W
			    int n_PCal_peaks_in1_timebin_[] = {0, 0, 0};

                            for (int i_view = 0; i_view < n_view; i_view++) {

                                int n_PCalpeaks = trig.GetNPeaks(0, i_view);
                                h_N_PCalpeaks1_[i_view]->Fill(n_PCalpeaks, sector);
				
                                for (int i_peak = 0; i_peak < n_PCalpeaks; i_peak++) {

                                    h_t_PCalpeak1_[i_view]->Fill(trig.GetECPeak(0, i_view, i_peak)->time, sector);
				    
				    if( trig.GetECPeak(0, i_view, i_peak)->time == 7 ){
				      n_PCal_peaks_in1_timebin_[i_view] = n_PCal_peaks_in1_timebin_[i_view] + 1;
				    }

                                    double coord_conv = 3.;
                                    if (i_view == 0) {
                                        coord_conv = 2.75;
                                    }
                                    double coord = double(trig.GetECPeak(0, i_view, i_peak)->coord) / coord_conv;
                                    h_coord_PCalpeak1_[i_view]->Fill(coord, sector);

                                    v_Peaks_[i_view].push_back(trig.GetECPeak(0, i_view, i_peak));
                                }
				
				h_N_PCalpeaks2_[i_view]->Fill(n_PCal_peaks_in1_timebin_[i_view], sector);
			    
				if( tr_bit.El_Sec(sector) ){
				  h_N_PCalpeaks3_[i_view]->Fill(n_PCal_peaks_in1_timebin_[i_view], sector);
				}
							    
                            }


                            for (int iU = 0; iU < v_Peaks_[0].size(); iU++) {
                                for (int iV = 0; iV < v_Peaks_[1].size(); iV++) {
                                    for (int iW = 0; iW < v_Peaks_[2].size(); iW++) {

                                        TPCalGeom pcal_geom_peaks(v_Peaks_[0].at(iU)->coord / U_conv, v_Peaks_[1].at(iV)->coord / V_conv,
                                                v_Peaks_[2].at(iW)->coord / W_conv);
                                        pcal_geom_peaks.SetSector(sector);

                                        //                       double hall_x_UV = ec_geom_peaks.GetHallX_UV();
                                        //                       double hall_y_UV = ec_geom_peaks.GetHallY_UV();
                                        //                       h_EC_yxc_UV1->Fill(hall_x_UV, hall_y_UV);
                                        //
                                        //                       double hall_x_UW = ec_geom_peaks.GetHallX_UW();
                                        //                       double hall_y_UW = ec_geom_peaks.GetHallY_UW();
                                        //                       h_EC_yxc_UW1->Fill(hall_x_UW, hall_y_UW);
                                        //
                                        //                       double hall_x_VW = ec_geom_peaks.GetHallX_VW();
                                        //                       double hall_y_VW = ec_geom_peaks.GetHallY_VW();
                                        //                       h_EC_yxc_VW1->Fill(hall_x_VW, hall_y_VW);

                                        double hall_x_UV = pcal_geom_peaks.GetHallX_UV();
                                        double hall_y_UV = pcal_geom_peaks.GetHallY_UV();
                                        h_PCal_yxc_UV1->Fill(hall_x_UV, hall_y_UV);
                                        double hall_x_UW = pcal_geom_peaks.GetHallX_UW();
                                        double hall_y_UW = pcal_geom_peaks.GetHallY_UW();
                                        h_PCal_yxc_UW1->Fill(hall_x_UW, hall_y_UW);
                                        double hall_x_VW = pcal_geom_peaks.GetHallX_VW();
                                        double hall_y_VW = pcal_geom_peaks.GetHallY_VW();
                                        h_PCal_yxc_VW1->Fill(hall_x_VW, hall_y_VW);

                                        double Dalitz_peaks = pcal_geom_peaks.GetDalitz();

                                        h_PCal_Dalitz_Peaks1->Fill(Dalitz_peaks, sector);
                                    }

                                }

                            }



                            // ====== PCal Clusters =======

                            int n_cl = trig.GetNClust(0); // Argument is the EC instance, but now it should be 0 all the time

                            h_N_PCalClust1->Fill(n_cl, sector);
			    
			    int n_cl_in_1_tbin = 0;
			    
			    vector<double> v_cl_E_1_tbin;
			    vector<double> v_cl_y_1_tbin;
			    vector<double> v_cl_x_1_tbin;
			    vector<double> v_cl_U_1_tbin;
			    vector<double> v_cl_V_1_tbin;
			    vector<double> v_cl_W_1_tbin;			    

                            for (int i_cl = 0; i_cl < n_cl; i_cl++) {

                                int cl_time = trig.GetECCluster(0, i_cl)->time;

                                // Temporarly all variables are set to 2.75
                                double u_coord_conv = 2.75;
                                double v_coord_conv = 3.;
                                double w_coord_conv = 3.;

                                double cl_U = double(trig.GetECCluster(0, i_cl)->Ustrip) / u_coord_conv;
                                double cl_V = double(trig.GetECCluster(0, i_cl)->Vstrip) / v_coord_conv;
                                double cl_W = double(trig.GetECCluster(0, i_cl)->Wstrip) / w_coord_conv;
                                double cl_E = double(trig.GetECCluster(0, i_cl)->energy) * ADC2GeV;

                                int E_bin = TMath::Min(int(cl_E / E_bin_width), n_E_bins - 1); // for not being out of range

                                TPCalGeom pcal_geom_clust(cl_U, cl_V, cl_W);
                                pcal_geom_clust.SetSector(sector);

                                double hall_x_cl = pcal_geom_clust.GetHallX_VW();
                                double hall_y_cl = pcal_geom_clust.GetHallY_VW();
                                double hall_z_cl = pcal_geom_clust.GetHallZ_VW();

                                double phi_cl = atan2(hall_y_cl, hall_x_cl) * r2d + 30.;
                                if (phi_cl < 0.) {
                                    phi_cl = phi_cl + 360.;
                                }
                                double th_cl = atan(sqrt(hall_x_cl * hall_x_cl + hall_y_cl * hall_y_cl) / hall_z_cl) * r2d;

                                h_PCal_yxc1->Fill(hall_x_cl, hall_y_cl);

                                h_PCal_th_phi_cl1->Fill(phi_cl, th_cl);
                                h_PCal_th_phi_cl_[E_bin]->Fill(phi_cl, th_cl);

                                double Dalitz = pcal_geom_clust.GetDalitz();

                                h_PCal_Dalitz_Clust1->Fill(Dalitz, sector);

                                //                            cout<<" \n\n\n\n ========== cluster info ============"<<endl;
                                //                            cout << "U: " << trig.GetECCluster(0, i_cl)->Ustrip<< "     " << cl_U << endl;
                                //                            cout << "V: " << trig.GetECCluster(0, i_cl)->Vstrip<< "     " << cl_V << endl;
                                //                            cout << "W: " << trig.GetECCluster(0, i_cl)->Wstrip<< "     " << cl_W << endl;
                                //                            cout<<"Dalitz = "<<Dalitz<<endl;

                                //cout<<"Ev. number is "<<ev_number<<"    n_cl is "<<n_cl<<"    sector is "<<sector<<"    cl energy is "<<trig.GetECCluster(0, i_cl)->energy<<endl;

                                h_PCalcl_t1->Fill(cl_time, sector);
                                h_PCalcl_U1->Fill(cl_U, sector);
                                h_PCalcl_V1->Fill(cl_V, sector);
                                h_PCalcl_W1->Fill(cl_W, sector);
                                h_PCalcl_E1->Fill(cl_E, sector);

				if(cl_time == 7){
				  n_cl_in_1_tbin = n_cl_in_1_tbin + 1;
				  h_PCalcl_E2->Fill(cl_E, sector);
				  h_PCal_yxc2->Fill(hall_x_cl, hall_y_cl);

				  v_cl_E_1_tbin.push_back(cl_E);
				  v_cl_y_1_tbin.push_back(hall_y_cl);
				  v_cl_x_1_tbin.push_back(hall_x_cl);

				  v_cl_U_1_tbin.push_back(cl_U);
				  v_cl_V_1_tbin.push_back(cl_V);
				  v_cl_W_1_tbin.push_back(cl_W);
				}

                            }
			    
			    h_N_PCalClust2->Fill(n_cl_in_1_tbin, sector);
			    
			    if( v_cl_E_1_tbin.size() ){
			      h_PCalcl_E3->Fill(v_cl_E_1_tbin[0], sector);
			      h_PCal_yxc3->Fill(v_cl_x_1_tbin[0], v_cl_y_1_tbin[0]);


			      if( v_cl_E_1_tbin.size() == 4 ){
				h_PCalcl_E4->Fill(v_cl_E_1_tbin[3], sector);
				h_PCal_yxc4->Fill(v_cl_x_1_tbin[3], v_cl_y_1_tbin[3]);

				double dU_43 = v_cl_U_1_tbin[3] - v_cl_U_1_tbin[2];
				double dV_43 = v_cl_V_1_tbin[3] - v_cl_V_1_tbin[2];
				double dW_43 = v_cl_W_1_tbin[3] - v_cl_W_1_tbin[2];
				
				h_PCal_dU_43->Fill(dU_43);
				h_PCal_dV_43->Fill(dV_43);
				h_PCal_dW_43->Fill(dW_43);
				
				// A temporary test, to check, if clusters ordered by energy

				if( v_cl_E_1_tbin[0] <= v_cl_E_1_tbin[1] ||  v_cl_E_1_tbin[1] <= v_cl_E_1_tbin[2] ||  v_cl_E_1_tbin[2] <= v_cl_E_1_tbin[3] ){
				  cout<<v_cl_E_1_tbin[0]<<"    "<<v_cl_E_1_tbin[1]<<"    "<<v_cl_E_1_tbin[2]<<"    "<<v_cl_E_1_tbin[3]<<"    "<<endl;
				}

			      }

			    }

			    //h_N_PCalClust3->Fill(n_cl_in_1_tbin, sector);


                        } else if (detector == 4) { // HTCC

                            int n_HTCC_masks = trig.GetNHTCCMasks();
                            h_n_HTCC_masks->Fill(n_HTCC_masks);

                            for (int i_htcc = 0; i_htcc < n_HTCC_masks; i_htcc++) {

                                THTCC_mask *cur_mask = trig.GetHTCCMask(i_htcc);

                                h_HTCC_time1->Fill(cur_mask->time);

                                int n_hits = cur_mask->chan.size();

                                h_n_HTCC_hits->Fill(n_hits);

                                for (int i_ch = 0; i_ch < n_hits; i_ch++) {

                                    h_HTCC_hit_chan1->Fill(cur_mask->chan.at(i_ch));
                                }
                            }

                        } else if (detector == 3) { // FTOF

                            int n_FTOF_masks = trig.GetNFTOFMasks();

                            h_n_FTOF_masks->Fill(n_FTOF_masks, sector);

                            for (int i_ftof = 0; i_ftof < n_FTOF_masks; i_ftof++) {

                                TFTOF_mask *cur_mask = trig.GetFTOFMask(i_ftof);
                                h_FTOF_time1->Fill(cur_mask->time, sector);

                                int n_hits = cur_mask->chan.size();

                                h_n_FTOF_hits->Fill(n_hits, sector);

                                for (int i_ch = 0; i_ch < n_hits; i_ch++) {
                                    h_FTOF_hit_chan1->Fill(cur_mask->chan.at(i_ch), sector);
                                }

                            }


                        }

                    }

                }



                if( i_ev >= n_events_to_Analyze ){ cout<<"Reached to the Limit of specified events to analyze"<<endl; break;}

            }

            if( i_ev >= n_events_to_Analyze ){ break;}
        }


    } catch (evioException e) {
        cerr << endl << e.toString() << endl;
        exit(EXIT_FAILURE);
    }

    gDirectory->Write();
}

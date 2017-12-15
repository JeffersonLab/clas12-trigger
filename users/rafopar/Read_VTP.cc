#include <evioUtil.hxx>
#include <evioFileChannel.hxx>
#include <list>
#include <ECTrig.hh>
#include <ECGeom.hh>
#include <TPCalGeom.hh>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
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

    // ===== Put temporarly 2.75 for all
    const double U_conv = 2.75; // This converts U coordinate from the Trigger bank into coordinate real U coordinate
    const double V_conv = 3.; // This converts V coordinate from the Trigger bank into coordinate real V coordinate
    const double W_conv = 3.; // This converts W coordinate from the Trigger bank into coordinate real W coordinate

    const int n_sect = 6;
    const int n_view = 3;
    const int vtp_tag = 57634;
     const int adcECvtp_tagmin = 100;
     const int adcECvtp_tagmax = 112;
//    const int adcECvtp_tagmin = 60000;
//    const int adcECvtp_tagmax = 60115;

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

    int run = 1894;
    //TFile *file_out = new TFile(Form("VTP_out_%s.root", argv[1]), "Recreate");
    TFile *file_out = new TFile(Form("Data/VTP_out_%d.root", run), "Recreate");

    TH2D * h_N_ECpeaks1_[n_view];
    TH2D * h_t_ECpeak1_[n_view];
    TH2D * h_coord_ECpeak1_[n_view];

    TH2D *h_N_ECClust1 = new TH2D("h_N_ECClust1", "", 11, -0.5, 10.5, 7, -0.5, 6.5);
    TH2D *h_ECcl_t1 = new TH2D("h_ECcl_t1", "", 21, -0.5, 20.5, 7, -0.5, 6.5);
    TH2D *h_ECcl_E1 = new TH2D("h_ECcl_E1", "", 200, 0., 30000., 7, -0.5, 6.5);
    TH2D *h_ECcl_U1 = new TH2D("h_ECcl_U1", "", 41, -0.5, 40.5, 7, -0.5, 6.5);
    TH2D *h_ECcl_V1 = new TH2D("h_ECcl_V1", "", 41, -0.5, 40.5, 7, -0.5, 6.5);
    TH2D *h_ECcl_W1 = new TH2D("h_ECcl_W1", "", 41, -0.5, 40.5, 7, -0.5, 6.5);

    TH2D *h_EC_yxc1 = new TH2D("h_EC_yxc1", "", 200, -500., 500., 200, -500., 500.);
    TH2D *h_EC_yxc_UV1 = new TH2D("h_EC_yxc_UV1", "", 200, -500., 500., 200, -500., 500.);
    TH2D *h_EC_yxc_UW1 = new TH2D("h_EC_yxc_UW1", "", 200, -500., 500., 200, -500., 500.);
    TH2D *h_EC_yxc_VW1 = new TH2D("h_EC_yxc_VW1", "", 200, -500., 500., 200, -500., 500.);

    TH2D *h_PCal_yxc1 = new TH2D("h_PCal_yxc1", "", 200, -500., 500., 200, -500., 500.);
    TH2D *h_PCal_yxc_UV1 = new TH2D("h_PCal_yxc_UV1", "", 200, -500., 500., 200, -500., 500.);
    TH2D *h_PCal_yxc_UW1 = new TH2D("h_PCal_yxc_UW1", "", 200, -500., 500., 200, -500., 500.);
    TH2D *h_PCal_yxc_VW1 = new TH2D("h_PCal_yxc_VW1", "", 200, -500., 500., 200, -500., 500.);


    TH2D *h_Dalitz_cl1 = new TH2D("h_Dalitz_cl1", "", 40, -0.5, 0.5, 7, -0.5, 6.5);
    TH2D *h_Dalitz_Peaks1 = new TH2D("h_Dalitz_Peaks1", "", 40, -0.5, 0.5, 7, -0.5, 6.5);
    TH2D *h_PCal_Dalitz_Peaks1 = new TH2D("h_PCal_Dalitz_Peaks1", "", 40, -0.5, 0.5, 7, -0.5, 6.5);
    TH2D *h_PCal_Dalitz_Clust1 = new TH2D("h_PCal_Dalitz_Clust1", "", 40, -0.5, 0.5, 7, -0.5, 6.5);

    TH2D * h_N_PCalpeaks1_[n_view];
    TH2D * h_t_PCalpeak1_[n_view];
    TH2D * h_coord_PCalpeak1_[n_view];

    TH2D *h_N_PCalClust1 = new TH2D("h_N_PCalClust1", "", 11, -0.5, 10.5, 7, -0.5, 6.5);
    TH2D *h_PCalcl_t1 = new TH2D("h_PCalcl_t1", "", 21, -0.5, 20.5, 7, -0.5, 6.5);
    TH2D *h_PCalcl_E1 = new TH2D("h_PCalcl_E1", "", 200, 0., 40000., 7, -0.5, 6.5);
    TH2D *h_PCalcl_U1 = new TH2D("h_PCalcl_U1", "", 86, -0.5, 85.5, 7, -0.5, 6.5);
    TH2D *h_PCalcl_V1 = new TH2D("h_PCalcl_V1", "", 86, -0.5, 85.5, 7, -0.5, 6.5);
    TH2D *h_PCalcl_W1 = new TH2D("h_PCalcl_W1", "", 86, -0.5, 85.5, 7, -0.5, 6.5);

    for (int i_view = 0; i_view < n_view; i_view++) {
        h_N_ECpeaks1_[i_view] = new TH2D(Form("h_N_ECpeaks1_%d", i_view), "", 11, -0.5, 10.5, 7, -0.5, 6.5);
        h_t_ECpeak1_[i_view] = new TH2D(Form("h_t_ECpeak1_%d", i_view), "", 21, -0.5, 20.5, 7, -0.5, 6.5);
        h_coord_ECpeak1_[i_view] = new TH2D(Form("h_coord_ECpeak1_%d", i_view), "", 41, -0.5, 40.5, 7, -0.5, 6.5);

        h_N_PCalpeaks1_[i_view] = new TH2D(Form("h_N_PCalpeaks1_%d", i_view), "", 11, -0.5, 10.5, 7, -0.5, 6.5);
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

      for (int ifile = 0; ifile < n_files; ifile++) {

	evioFileChannel chan(fname_list->At(ifile)->GetTitle(), "r");
	cout << "Running the file " << fname_list->At(ifile)->GetTitle() << endl;
	chan.open();
   
      
        // evioFileChannel chan(argv[1], "r");
        // chan.open();

        while (chan.read()) {

	  evioDOMTree tree(chan);

	  evioDOMNodeListP nodelist1 = tree.getNodeList();

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

		for (int i_cl = 0; i_cl < n_cl; i_cl++) {
		  int cl_time = trig.GetECCluster(0, i_cl)->time;
		  double cl_U = double(trig.GetECCluster(0, i_cl)->Ustrip) / 8.;
		  double cl_V = double(trig.GetECCluster(0, i_cl)->Vstrip) / 8.;
		  double cl_W = double(trig.GetECCluster(0, i_cl)->Wstrip) / 8.;
		  int cl_E = double(trig.GetECCluster(0, i_cl)->energy);

		  TECGeom ec_geom(cl_U, cl_V, cl_W);

		  ec_geom.SetSector(sector);

		  double hall_x_cl = ec_geom.GetHallX_UV();
		  double hall_y_cl = ec_geom.GetHallY_UV();

		  h_EC_yxc1->Fill(hall_x_cl, hall_y_cl);
		  //cout<<"Ev. number is "<<ev_number<<"    n_cl is "<<n_cl<<"    sector is "<<sector<<"    cl energy is "<<trig.GetECCluster(0, i_cl)->energy<<endl;

		  double cl_Dalitz = ec_geom.GetDalitz();

		  h_Dalitz_cl1->Fill(cl_Dalitz, sector);

		  h_ECcl_t1->Fill(cl_time, sector);
		  h_ECcl_U1->Fill(cl_U, sector);
		  h_ECcl_V1->Fill(cl_V, sector);
		  h_ECcl_W1->Fill(cl_W, sector);
		  h_ECcl_E1->Fill(cl_E, sector);
		}


		//cout<<"n_upeaks = "<<n_upeaks<<endl;

	      } else if (detector == 2) { // PCal

		vector<TEC_Peak*> v_Peaks_[3]; // 3 is U, V or W

		for (int i_view = 0; i_view < n_view; i_view++) {

		  int n_PCalpeaks = trig.GetNPeaks(0, i_view);
		  h_N_PCalpeaks1_[i_view]->Fill(n_PCalpeaks, sector);

		  for (int i_peak = 0; i_peak < n_PCalpeaks; i_peak++) {

		    h_t_PCalpeak1_[i_view]->Fill(trig.GetECPeak(0, i_view, i_peak)->time, sector);

		    double coord_conv = 3.;
		    if (i_view == 0) {
		      coord_conv = 2.75;
		    }
		    double coord = double(trig.GetECPeak(0, i_view, i_peak)->coord) / coord_conv;
		    h_coord_PCalpeak1_[i_view]->Fill(coord, sector);

		    v_Peaks_[i_view].push_back(trig.GetECPeak(0, i_view, i_peak));
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

		for (int i_cl = 0; i_cl < n_cl; i_cl++) {

		  int cl_time = trig.GetECCluster(0, i_cl)->time;

		  // Temporarly all variables are set to 2.75
		  double u_coord_conv = 2.75;
		  double v_coord_conv = 3.;
		  double w_coord_conv = 3.;

		  double cl_U = double(trig.GetECCluster(0, i_cl)->Ustrip) / u_coord_conv;
		  double cl_V = double(trig.GetECCluster(0, i_cl)->Vstrip) / v_coord_conv;
		  double cl_W = double(trig.GetECCluster(0, i_cl)->Wstrip) / w_coord_conv;
		  int cl_E = double(trig.GetECCluster(0, i_cl)->energy);


		  TPCalGeom pcal_geom_clust(cl_U, cl_V, cl_W);
		  pcal_geom_clust.SetSector(sector);

		  double hall_x_cl = pcal_geom_clust.GetHallX_VW();
		  double hall_y_cl = pcal_geom_clust.GetHallY_VW();

		  h_PCal_yxc1->Fill(hall_x_cl, hall_y_cl);

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
		}


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





        }

      }
       

    } catch (evioException e) {
        cerr << endl << e.toString() << endl;
        exit(EXIT_FAILURE);
    }

 gDirectory->Write();
}

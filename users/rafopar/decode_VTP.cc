#include <evioUtil.hxx>
#include <evioFileChannel.hxx>
#include <list>
#include <ECTrig.hh>
#include <ECGeom.hh>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TCanvas.h>

using namespace evio;
using namespace std;

// This program loops over events from the input file, given as an argument.
// It will search for banks with a tag "0xe122" ("57634" in decimal representation)
// Then will loop over all words inside the bank and decode all the information,
// e.g. which part of EC (in, or out), cluster coordinates (u, v, w), etc

int main(int argc, char **argv){

  const double Dalitz_ECin_max = 0.3333;
  const double Dalitz_ECin_min = -0.2222;

  const double Dalitz_ECout_max = 0.0833333;
  const double Dalitz_ECout_min = -0.0555556;

  const int vtp_tag = 57634;
  const int adcECvtp_tagmin = 100;
  const int adcECvtp_tagmax = 112;
  const int n_EC_inst = 2;
  const int n_EC_view = 3;
  const double t_max = 90.;
  const double t_min = 70.;
  int n_EC_Peaks_[n_EC_inst][n_EC_view];
  int adcECvtp_tag;

  TFile *file_out = new TFile(Form("vtp_analyze_%s.root", argv[1]), "Recreate");

  TH2D *h_ncl_n_peak = new TH2D("h_ncl_n_peak", "", 40, 0., 20., 40, 0., 20.);
  TH2D *h_n_incl_prodInPeaks = new TH2D("h_n_incl_prodInPeaks", "", 100, 0., 50., 100, 0., 50.);
  TH2D *h_n_incl_prodInPeaks_DalitzCut = new TH2D("h_n_incl_prodInPeaks_DalitzCut", "", 100, 0., 50., 100, 0., 50.);
  TH2D *h_n_outcl_prodOutPeaks_DalitzCut = new TH2D("h_n_outcl_prodOutPeaks_DalitzCut", "", 100, 0., 50., 100, 0., 50.);
  TH2D *h_n_incl_prodInPeaks_intime1 = new TH2D("h_n_incl_prodInPeaks_intime1", "", 100, 0., 50., 100, 0., 50.);
  TH2D *h_n_outcl_prodInPeaks = new TH2D("h_n_outcl_prodInPeaks", "", 100, 0., 50., 100, 0., 50.);
  TH2D *h_out_cl_yxc1 = new TH2D("h_out_cl_yxc1", "", 200, -40., 40., 200, 0., 50.);
  TH2D *h_in_cl_yxc1 = new TH2D("h_in_cl_yxc1", "", 200, -40., 40., 200, 0., 50.);
  TH2D *h_cl_yxc1 = new TH2D("h_cl_yxc1", "", 200, -40., 40., 200, 0., 50.);
  TH1D *h_cl_E1 = new TH1D("h_cl_E1", "", 200, 0., 10000);
  TH1D *h_EC_sect = new TH1D("h_EC_sect", "", 12, 0., 6.);
  TH1D *h_cl_t_in = new TH1D("h_cl_t_in", "", 400, 0., 200.);
  TH1D *h_t_Upeak_in1 = new TH1D("h_t_Upeak_in1", "", 400, 0., 200);
  TH1D *h_t_Vpeak_in1 = new TH1D("h_t_Vpeak_in1", "", 400, 0., 200);
  TH1D *h_t_Wpeak_in1 = new TH1D("h_t_Wpeak_in1", "", 400, 0., 200);
  TH1D *h_in_Ucoord1 = new TH1D("h_in_Ucoord1", "", 200, 0., 40.);
  TH1D *h_in_Vcoord1 = new TH1D("h_in_Vcoord1", "", 200, 0., 40.);
  TH1D *h_in_Wcoord1 = new TH1D("h_in_Wcoord1", "", 200, 0., 40.);
  TH1D *h_Dalitz1 = new TH1D("h_Dalitz1", "", 200, -2.1, 2.1);
  TH1D *h_out_Dalitz1 = new TH1D("h_out_Dalitz1", "", 200, -2.1, 2.1);

  TH1D *h_Trig_loc_time = new TH1D("h_Trig_loc_time", "", 200, 0., 200.);
  
  TH1D *h_n_EC_Peaks_[n_EC_inst][n_EC_view];
  for( int i_inst = 0; i_inst < n_EC_inst; i_inst++ ){
    for( int i_view = 0; i_view < n_EC_view; i_view++ ){
      h_n_EC_Peaks_[i_inst][i_view] = new TH1D(Form("h_n_EC_Peaks_%d_%d", i_inst, i_view), "", 20, 0., 10.);
    }
  }
  
  
  
  try{
    evioFileChannel chan(argv[1], "r");
 
    chan.open();

    int counter = 0;

    while( chan.read() ){
      
      evioDOMTree tree(chan);
      
      evioDOMNodeListP nodelist1 = tree.getNodeList();
      
      for( std::list<evioDOMNode*>::iterator it = nodelist1.get()->begin();  it != nodelist1.get()->end(); it++ ){

	if( (*it)->tag >= adcECvtp_tagmin && (*it)->tag <= adcECvtp_tagmax ){
	  adcECvtp_tag = (*it)->tag;
	}
	
	if( (*it)->tag == vtp_tag ){
	  
	  TECTrig trig(*it, adcECvtp_tag);

	  //cout<<" EV NUMBER and parent BANK tag   "<<trig.GetEvNumber()<<"     "<<trig.GetDetector()<<endl;
	  
	  if( trig.GetDetector() == 1 ){

	    int sect = trig.GetSector();
	    int n_peaks = trig.GetNAllPeaks();
	    int n_clust = trig.GetNAllClust();

	    int n_in_Upeaks = trig.GetNPeaks(0, 0);
	    int n_in_Vpeaks = trig.GetNPeaks(0, 1);
	    int n_in_Wpeaks = trig.GetNPeaks(0, 2);

	    int n_out_Upeaks = trig.GetNPeaks(1, 0);
	    int n_out_Vpeaks = trig.GetNPeaks(1, 1);
	    int n_out_Wpeaks = trig.GetNPeaks(1, 2);

	    int n_in_clust = trig.GetNClust(0);
	    int n_out_clust = trig.GetNClust(1);

	    // cout<<"N_All clust = "<<n_clust<<endl;
	    // cout<<"N_in clust = "<<n_in_clust<<endl;
	    // cout<<"N_out clust = "<<n_out_clust<<endl;


	    // This in principle should not happen, Number of clusters is equal to the product of the number of peaks
	    // in each view. i.e. N_cl = N_Upeak x N_Vpeak x N_Wpeak
	    // if(n_in_Upeaks*n_in_Vpeaks*n_in_Wpeaks < n_in_clust ){
	    //   cout<<"N_in_U = "<<n_in_Upeaks<<endl;
	    //   cout<<"N_in_V = "<<n_in_Vpeaks<<endl;
	    //   cout<<"N_in_W = "<<n_in_Wpeaks<<endl;
	    //   cout<<"N in clust = "<<n_in_clust<<endl;
	    //   cout<<"Event number is "<<trig.GetEvNumber()<<endl;
	    // }
	    
	    h_n_outcl_prodInPeaks->Fill( n_out_Upeaks*n_out_Vpeaks*n_out_Wpeaks, n_out_clust );
	    h_n_incl_prodInPeaks->Fill( n_in_Upeaks*n_in_Vpeaks*n_in_Wpeaks, n_in_clust );
	  
	    for( int i_inst = 0; i_inst < n_EC_inst; i_inst++ ){
	      for( int i_view = 0; i_view < n_EC_view; i_view++ ){
		n_EC_Peaks_[i_inst][i_view] = trig.GetNPeaks(i_inst, i_view);
		h_n_EC_Peaks_[i_inst][i_view]->Fill(n_EC_Peaks_[i_inst][i_view]);
	      }
	    }
	  
	    h_EC_sect->Fill(sect);
	    h_ncl_n_peak->Fill(n_peaks, n_clust);


	    for( int i_outcl = 0; i_outcl < n_out_clust; i_outcl++ ){

	      double y_cl = trig.GetECCluster(1, i_outcl)->coordY;
	      double x_cl = trig.GetECCluster(1, i_outcl)->coordX;
	      double E_cl = trig.GetECCluster(1, i_outcl)->energy;
	      
	      h_out_cl_yxc1->Fill(x_cl, y_cl);
	    }

	    // for( int i_cl = 0; i_cl < n_clust; i_cl++ ){
	    //   trig.PrintECCluster(i_cl);
	    // }
	    

	    int n_intime_in_cl = 0;
	    for( int i_incl = 0; i_incl < n_in_clust; i_incl++ ){

	      //	      trig.PrintECCluster(0, i_incl);
	      double y_cl = trig.GetECCluster(0, i_incl)->coordY;
	      double x_cl = trig.GetECCluster(0, i_incl)->coordX;
	      double E_cl = trig.GetECCluster(0, i_incl)->energy;
	      h_in_cl_yxc1->Fill(x_cl, y_cl);

	      // if( y_cl < -2. - sqrt(3.)*x_cl ){
	      // 	cout<<"Event number is "<<trig.GetEvNumber()<<endl;
	      // 	cout<<"x_cl = "<<x_cl<<endl;
	      // 	cout<<"y_cl = "<<y_cl<<endl;
	      // 	trig.PrintXMLData();
	      // }


	      double cl_t_in = trig.GetECCluster(0, i_incl)->time;
	      h_cl_t_in->Fill(cl_t_in);

	      if( cl_t_in > t_min && cl_t_in < t_max ){ n_intime_in_cl = n_intime_in_cl + 1; }
	    }

	    int n_intime_in_Upeaks = 0;
	    for( int ip = 0; ip < n_in_Upeaks; ip++ ){
	      double t_peak = trig.GetECPeak(0, 0, ip)->time;
	      h_t_Upeak_in1->Fill(t_peak);
	      if( t_peak > t_min && t_peak < t_max ) {n_intime_in_Upeaks = n_intime_in_Upeaks + 1;}
	    }

	    int n_intime_in_Vpeaks = 0;
	    for( int ip = 0; ip < n_in_Vpeaks; ip++ ){
	      double t_peak = trig.GetECPeak(0, 1, ip)->time;
	      h_t_Vpeak_in1->Fill(t_peak);
	      if( t_peak > t_min && t_peak < t_max ) {n_intime_in_Vpeaks = n_intime_in_Vpeaks + 1;}
	    }

	    int n_intime_in_Wpeaks = 0;
	    for( int ip = 0; ip < n_in_Wpeaks; ip++ ){
	      double t_peak = trig.GetECPeak(0, 2, ip)->time;
	      h_t_Wpeak_in1->Fill(t_peak);
	      if( t_peak > t_min && t_peak < t_max ) {n_intime_in_Wpeaks = n_intime_in_Wpeaks + 1;}
	    }

	    h_n_incl_prodInPeaks_intime1->Fill(n_in_Upeaks*n_in_Vpeaks*n_intime_in_Wpeaks, n_intime_in_cl);

	    for( int iU = 0; iU < n_in_Upeaks; iU++ ){
	      h_in_Ucoord1->Fill(trig.GetECPeak(0, 0, iU)->coord);
	    }

	    for( int iV = 0; iV < n_in_Vpeaks; iV++ ){
	      h_in_Vcoord1->Fill(trig.GetECPeak(0, 1, iV)->coord);
	    }

	    for( int iW = 0; iW < n_in_Wpeaks; iW++ ){
	      h_in_Wcoord1->Fill(trig.GetECPeak(0, 2, iW)->coord);
	    }

	  
	    // ===== Loop over inner peaks =====
	    int n_Dalitz_cut_clusters = 0;
	    for( int iU = 0; iU < n_in_Upeaks; iU++ ){
	      for( int iV = 0; iV < n_in_Vpeaks; iV++ ){
		for( int iW = 0; iW < n_in_Wpeaks; iW++ ){
		  TECGeom geom(trig.GetECPeak(0, 0, iU)->coord, trig.GetECPeak(0, 1, iV)->coord, trig.GetECPeak(0, 2, iW)->coord);
		  double Dalitz = geom.GetDalitz();

		  h_Dalitz1->Fill(Dalitz);

		  if( Dalitz > Dalitz_ECin_min && Dalitz < Dalitz_ECin_max ){
		    n_Dalitz_cut_clusters = n_Dalitz_cut_clusters + 1;
		  }
		}
	      }
	    }
	  
	    h_n_incl_prodInPeaks_DalitzCut->Fill( n_Dalitz_cut_clusters, n_in_clust);
	  

	    // ===== Loop over outer peaks =====
	    int n_out_Dalitz_cut_clusters = 0;
	    for( int iU = 0; iU < n_out_Upeaks; iU++ ){
	      for( int iV = 0; iV < n_out_Vpeaks; iV++ ){
		for( int iW = 0; iW < n_out_Wpeaks; iW++ ){
		  TECGeom geom(trig.GetECPeak(1, 0, iU)->coord, trig.GetECPeak(1, 1, iV)->coord, trig.GetECPeak(1, 2, iW)->coord);
		  double Dalitz = geom.GetDalitz();

		  h_out_Dalitz1->Fill(Dalitz);

		  if( Dalitz > Dalitz_ECout_min && Dalitz < Dalitz_ECout_max ){
		    n_out_Dalitz_cut_clusters = n_out_Dalitz_cut_clusters + 1;
		  }
		}
	      }
	    }
	  
	    h_n_outcl_prodOutPeaks_DalitzCut->Fill( n_out_Dalitz_cut_clusters, n_out_clust);	    
	  
	    for( int icl = 0; icl < n_clust; icl++ ){
	      double y_cl = trig.GetECCluster(icl)->coordY;
	      double x_cl = trig.GetECCluster(icl)->coordX;
	      double E_cl = trig.GetECCluster(icl)->energy;
	    
	      h_cl_yxc1->Fill(x_cl, y_cl);
	      h_cl_E1->Fill(E_cl);

	    }

	  } else if( trig.GetDetector() == 0 ){
	    h_Trig_loc_time->Fill(trig.GetLocalTrigTime());
	  }
	  
	}

      }
      
    }
  } catch(evioException e){
    cerr<<endl<<e.toString()<<endl;
    exit(EXIT_FAILURE);
  }

  gDirectory->Write();
  exit(EXIT_SUCCESS);
}

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


  const double Dalitz_ECout_max = 0.0833333;
  const double Dalitz_ECout_min = -0.0555556;


  const int n_sect = 6;
  const int vtp_tag = 57634;
  // const int adcECvtp_tagmin = 100;
  // const int adcECvtp_tagmax = 112;
  const int adcECvtp_tagmin = 60000;
  const int adcECvtp_tagmax = 60115;


  TFile *file_out = new TFile("VTP_out.root", "Recreate");
  TH1D *h_HTCC_time1 = new TH1D("h_HTCC_time1", "", 200, 0., 100);
  TH1D *h_n_HTCC_masks = new TH1D("h_n_HTCC_masks", "", 20, 0., 10);
  TH1D *h_n_HTCC_hits = new TH1D("h_n_HTCC_hits", "", 98, 0., 49);
  TH1D *h_HTCC_hit_chan1 = new TH1D("h_HTCC_hit_chan1", "", 98, 0., 49);

  TH2D *h_FTOF_time1 = new TH2D("h_FTOF_time1", "", 100, 0., 50, 12, 0., 6.);
  TH2D *h_n_FTOF_masks = new TH2D("h_n_FTOF_masks", "", 20, 0., 10., 12, 0., 6.);
  TH2D *h_n_FTOF_hits = new TH2D("h_n_FTOF_hits", "", 126, 0., 63., 12, 0., 6.);
  TH2D *h_FTOF_hit_chan1 = new TH2D("h_FTOF_hit_chan1", "", 126, 0., 63., 12, 0., 6.);
  
  
  int adcECvtp_tag;
  
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

	  int detector = trig.GetDetector();
	  int sector = trig.GetSector();
	  
	  if( detector == 1 ){ // ECal

	    int n_upeaks = trig.GetNPeaks(0, 0);
	    //cout<<"n_upeaks = "<<n_upeaks<<endl;
	    
	  }else if (detector == 4){ // HTCC

	    int n_HTCC_masks = trig.GetNHTCCMasks();
	    h_n_HTCC_masks->Fill(n_HTCC_masks);

	    for( int i_htcc = 0; i_htcc < n_HTCC_masks; i_htcc++ ){

	      THTCC_mask *cur_mask = trig.GetHTCCMask(i_htcc);

	      h_HTCC_time1->Fill(cur_mask->time);

	      int n_hits = cur_mask->chan.size();
	      
	      h_n_HTCC_hits->Fill(n_hits);

	      for( int i_ch = 0; i_ch < n_hits; i_ch++ ){
	      
		h_HTCC_hit_chan1->Fill(cur_mask->chan.at(i_ch));
	      }
	    }
	    
	  } else if( detector == 3 ){ // FTOF

	    int n_FTOF_masks = trig.GetNFTOFMasks();

	    h_n_FTOF_masks->Fill(n_FTOF_masks, sector);

	    for( int i_ftof = 0; i_ftof < n_FTOF_masks; i_ftof++ ){
	      
	      TFTOF_mask *cur_mask = trig.GetFTOFMask(i_ftof);
	      h_FTOF_time1->Fill(cur_mask->time, sector);

	      int n_hits = cur_mask->chan.size();

	      h_n_FTOF_hits->Fill(n_hits, sector);

	      for( int i_ch = 0; i_ch < n_hits; i_ch++ ){
		h_FTOF_hit_chan1->Fill(cur_mask->chan.at(i_ch), sector);
	      }
	      
	    }
	    

	  }
	  
	}

      }
      
    }

    gDirectory->Write();
    
  } catch(evioException e){
    cerr<<endl<<e.toString()<<endl;
    exit(EXIT_FAILURE);
  }
}

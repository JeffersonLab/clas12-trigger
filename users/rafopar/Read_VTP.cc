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

  const int vtp_tag = 57634;
  const int adcECvtp_tagmin = 100;
  const int adcECvtp_tagmax = 112;

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

	  if( trig.GetDetector() == 1 ){ // ECal

	    int n_upeaks = trig.GetNPeaks(0, 0);
	    cout<<"n_upeaks = "<<n_upeaks<<endl;
	    
	  }
	  
	}

      }
      
    }
  } catch(evioException e){
    cerr<<endl<<e.toString()<<endl;
    exit(EXIT_FAILURE);
  }
}

#include <evioUtil.hxx>
#include <evioFileChannel.hxx>
#include <list>
#include <bitset>         // std::bitset
#include <iomanip>
#include <vector>

#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include "ectrans.h"

#define GET_CHAR(b,i) b[i]; i+=1;
#define GET_SHORT(b,i) ((short *)(&b[i]))[0]; i+=2;
#define GET_INT(b,i) ((int *)(&b[i]))[0]; i+=4;
#define GET_L64(b,i) ((unsigned long long *)(&b[i]))[0]; i+=8;

#define FADC_1_BANK 57601
#define FADC_2_BANK 57602

using namespace evio;
using namespace std;

int main(int argc, char **argv){

  TCanvas *c1 = new TCanvas("c1", "", 750, 750);

  const int n_sect = 6;
  const int n_inst = 2;
  const int n_view = 3;
  const int n_strip = 36;


  map<int, int> fadc_detector = {
    {1, 0}, {7, 0}, {13, 0}, {19, 0}, {25, 0}, {31, 0},  // ECal
    {3, 1}, {9, 1}, {15, 1}, {21, 1}, {27, 1}, {33, 1},  // PCal
  };

  map<int, int> fadc_sect = {
    {1, 0}, {7, 1}, {13, 2}, {19, 3}, {25, 4}, {31, 5},  // ECal
    {3, 0}, {9, 1}, {15, 2}, {21, 3}, {27, 4}, {33, 5},  // PCal
  };

  vector<int> ECStrip[n_sect][n_inst][n_view];
  
  try{
    evioFileChannel chan(argv[1], "r");

    TFile *file_out = new TFile(Form("out_%s.root", argv[1]), "Recreate");
    TH1D *h_tdc1 = new TH1D("h_tdc1", "", 1500, 3000., 4500.);
    TH1D *h_time1 = new TH1D("h_time1", "", 1500, 46., 71.);
    TH1D *h_time2 = new TH1D("h_time2", "", 2000, 0., 4.);

    TH1D *h_ECSect = new TH1D("h_ECSect", "", 14, 0., 7.);
    TH1D *h_nch1 = new TH1D("h_nch1", "", 40, 0., 20.);
    TH1D *h_ns1 = new TH1D("h_ns1",  "", 500, 0., 250.);
    TH1D *h_FADC_1 = new TH1D("h_FADC_1", "", 200, 0., 100);

    TH1D *h_fADC_ECal_[n_sect][n_inst][n_view][n_strip];
    TH2D *h_fADC_ECal2_[n_sect][n_inst][n_view];

    
    for( int i_sect = 0; i_sect < n_sect; i_sect++ ){
      for( int i_inst = 0; i_inst < n_inst; i_inst++ ){
	for( int i_view = 0; i_view < n_view; i_view++ ){

	  h_fADC_ECal2_[i_sect][i_inst][i_view] = new TH2D(Form("h_fADC_ECal2_%d_%d_%d", i_sect, i_inst, i_view), "", 100, 0., 100., 72, 0., 36.);
	  
	  for( int i_strip = 0; i_strip < n_strip; i_strip++ ){
	    h_fADC_ECal_[i_sect][i_inst][i_view][i_strip] = new TH1D(Form("h_fADC_ECal_%d_%d_%d_%d", i_sect, i_inst, i_view, i_strip), "", 200, 0., 100.);
	  }

	}

      }

    }
  
    
    chan.open();

    int counter = 0;

    int detector; // 0 = ECal, 1 = PCal
    int sector; // 0, 1, 2, 3, 4, 5
    
    
    while( chan.read() ){
      evioDOMTree tree(chan);

      evioDOMNodeListP nodelist1 = tree.getNodeList();
      int node_list_size = nodelist1.get()->size();
      
      //cout<<tree.toString()<<endl;

      for( std::list<evioDOMNode*>::iterator it = nodelist1.get()->begin();  it != nodelist1.get()->end(); it++ ){
	// cout<<"   *******  Header  "<<(*it)->getHeader(0);
	// cout<<"   *******  tag  "<<(*it)->tag<<endl;
	// cout<<"   ***  Contenttype  "<<(*it)->getContentType()<<endl;
	// cout<<"   *********  Body  "<<(*it)->getBody(0)<<endl;
	// cout<<"   ********  Footer  "<<(*it)->getFooter(0);
	// cout<<"   **********  size  "<<(*it)->getSize()<<endl;


	if(fadc_detector.count((*it)->tag) == 1){
	  
	  detector = fadc_detector[(*it)->tag];
	  sector = fadc_sect[(*it)->tag];

	  h_ECSect->Fill(sector);

	} else if( (*it)->tag == 57634 ){
	  //vector<uint32_t> *data_values = (*it)->getVector();
	  vector<uint32_t> *data_values = (*it)->getVector<uint32_t>();

	  for( std::vector<uint32_t>::iterator it_data = data_values->begin(); it_data != data_values->end(); it_data++ ){
	    //cout<<setw(15)<<(*it_data)<<setw(36)<<bitset<32>(*it_data)<<endl;
	  }
	  //cout<<endl;
	} else if( (*it)->tag == FADC_2_BANK ){

	  int i = 0;
	  short tdc[1024];
	  int adc[1024];
	  short pulse_min[1024];
	  short pulse_max[1024];
	  
	  evioCompositeDOMLeafNode *fadc = (evioCompositeDOMLeafNode *)(*it);
	  unsigned char *p = (unsigned char *)fadc->data.data();
	  unsigned int len = fadc->data.size() * 4;

	  //cout<<"       len = "<<len<<endl;
	  
	  while(len-i>4)
	    {
	      unsigned char slot = GET_CHAR(p,i);
	      int trig_n = GET_INT(p,i);
	      long long trig_t = GET_L64(p,i);

	      // cout<<"Slot:                       "<<static_cast<unsigned>(slot)<<endl;
	      // cout<<"Trigger Number:             "<<trig_n<<endl;
	      //cout<<"Trigger time:               "<<trig_t<<endl;
	      
	      int nch = GET_INT(p,i);

	      //	      cout<<"Number of channels          "<<nch<<endl;

	      if(nch > 16) { printf("Error in %s: fadc mode 1 invalid nch\n", __func__); exit(1); }

	      while(nch--){

		int ch = GET_CHAR(p,i);

		//		cout<<"===Cheannel:                "<<ch<<endl;

		int npulse = GET_INT(p,i);
		
		//		cout<<"===Number of pulses         "<<npulse<<endl;
		for( int i_pulse = 0; i_pulse < npulse; i_pulse++  ){
		  tdc[i_pulse] = GET_SHORT(p,i);
		  adc[i_pulse] = GET_INT(p,i);
		  pulse_min[i_pulse] = GET_SHORT(p,i);
		  pulse_max[i_pulse] = GET_SHORT(p,i);

		  double time1 = double(tdc[i_pulse])/64.;
		  double time2 = time1/32.;
		  h_tdc1->Fill(tdc[i_pulse]);
		  h_time1->Fill(time1);
		  h_time2->Fill(time2);
		  

		  // cout<<"======tdc["<<i_pulse<<"]:        "<<tdc[i_pulse]<<endl;
		  // cout<<"======adc["<<i_pulse<<"]:        "<<adc[i_pulse]<<endl;
		  // cout<<"======pulse_min["<<i_pulse<<"]   "<<pulse_min[i_pulse]<<endl;
		  // cout<<"======pulse_max["<<i_pulse<<"]   "<<pulse_max[i_pulse]<<endl;
		}

		
	      }
	      
	    }
	} else if( (*it)->tag == FADC_1_BANK ){

	  evioCompositeDOMLeafNode *fadc = (evioCompositeDOMLeafNode *)(*it);
	  unsigned char *p = (unsigned char *)fadc->data.data();
	  unsigned int len = fadc->data.size() * 4;

	  int i = 0;
	  int adc[1024];
	  while(len-i>4)
	    {
	      unsigned char slot = GET_CHAR(p,i);
	      
	      int trig_n = GET_INT(p,i);
	      long long trig_t = GET_L64(p,i);

	      //cout<<"trig_t = "<<trig_t<<endl;

	      int nch = GET_INT(p,i);
	      h_nch1->Fill(nch);

	      if(nch > 16) { printf("Error in %s: fadc mode 1 invalid nch\n", __func__); exit(1); }
	      while(nch--)
		{
		  int ch = GET_CHAR(p,i);
		  int ns = GET_INT(p,i);
		  int np = 0;				
		  int x, y;

		  //int ecal_channel = fadcGetXY(slot, ch, roc, &x, &y);

		  //if( adclayerecal[slot][ch] == 0 ){continue;} // Need to make sure why we see such cases
		  
		  int view = (adclayerecal[slot][ch]-1)%3; // 0 = U, 1 = V, 2 = W
		  int inst = (adclayerecal[slot][ch]-1)/3; // 0 = U, 1 = V, 2 = W

		  int strip_N = adcstripecal[slot][ch] - 1;

		  // if( view >= 0 && detector == 0){
		  //   ECStrip[sector][inst][view].push_back(strip_N);
		  //   h_fADC_ECal_[sector][inst][view][strip_N]->Reset(); // Temporary
		  // }
		  
		  h_ns1->Fill(ns);

		  if(ns > sizeof(adc)/sizeof(adc[0]))
		    {
		      printf("Warning in %s: fadc mode 1: # samples (%d) > buffer (%d)\n", __func__, ns, (int)(sizeof(adc)/sizeof(adc[0])));
		      for(int n = 0; n < ns; n++) { GET_SHORT(p,i); }
		      continue;
		    }

		  for(int n = 0; n < ns; n++) {
		    adc[n] = GET_SHORT(p,i);
		    h_FADC_1->Fill(n, adc[n]);
		    
		    if( detector == 0 && view >= 0){
		      
		      // cout<<"slot = "<<int(slot)<<endl;
		      // cout<<"channel = "<<ch<<endl;
		      // cout<<"sect = "<<sector<<endl;
		      // cout<<"inst = "<<inst<<endl;
		      // cout<<"view = "<<view<<endl;
		      // cout<<"strip = "<<strip_N<<endl;

		      h_fADC_ECal_[sector][inst][view][strip_N]->Fill(n, adc[n]);
		      h_fADC_ECal2_[sector][inst][view]->Fill(n, strip_N, adc[n]);
		    }
		  }
		  // if( sector == 1 && inst == 0 && view == 1 && strip_N == 1 && detector == 0){
		    
		  //   h_fADC_ECal_[sector][inst][view][strip_N]->Draw("hist");
		  //   cout<<"Kuku"<<endl;
		  //   c1->Print("tmp.eps");
		  //   cin.ignore();
		  //   h_fADC_ECal_[sector][inst][view][strip_N]->Reset();
		  // }
		}
	    }

	  // for( int i_sect = 0; i_sect < n_sect; i_sect++ ){
	  //   for( int i_view = 0; i_view < n_view; i_view++ ){
	  //     if( h_fADC_ECal2_[i_sect][0][i_view]->GetMaximum() > 0 && sector == 1){
	  // 	cout<<"sector = "<<i_sect<<endl;
	  // 	cout<<"view = "<<i_view<<endl;
	  // 	gDirectory->Write("hist_Dir", TObject::kOverwrite);
	      
	  // 	cin.ignore();
	  // 	h_fADC_ECal2_[i_sect][0][i_view]->Reset();

	  // 	for( int i_strip = 0; i_strip < n_strip; i_strip++ ){
	  // 	  h_fADC_ECal_[i_sect][1][i_view][i_strip]->Reset();
	  // 	  h_fADC_ECal_[i_sect][0][i_view][i_strip]->Reset();
	  // 	}
	  //     }
	  //   }
	  // }
	  
	  
	  // if( h_fADC_ECal2_[0][0][0]->GetEntries()> 0 ){
	  //   c1->SetTheta(30);
	  //   c1->SetPhi(10);
	  //   h_fADC_ECal2_[0][0][0]->Draw("lego2");
	  //   gDirectory->Write("hist_Dir", TObject::kOverwrite);
	  //   c1->Print("tmp.eps");
	  //   cin.ignore();
	  //   h_fADC_ECal2_[0][0][0]->Reset();
	  // }
	  
	  // if( ECStrip[sector][0][0].size() > 0){
	  //   bool DrawFirst = true;
	  //   for( auto &strip: ECStrip[sector][0][0] ){
	  //     cout<<"Strip = "<<strip<<endl;
	  //     h_fADC_ECal_[sector][0][0][strip]->SetLineColor(strip+1);
	  //     if( DrawFirst ){
	  // 	h_fADC_ECal_[sector][0][0][strip]->Draw("hist"); DrawFirst = false;
	  // 	h_fADC_ECal_[sector][0][0][strip]->SetMaximum(3000.);
	  //     }
	  //     else{ h_fADC_ECal_[sector][0][0][strip]->Draw("hist Same"); }
	  //   }
	  //   c1->Print("tmp.eps");
	  //   cin.ignore();

	  //   ECStrip[sector][0][0].clear();
	  //   ECStrip[sector][0][0].shrink_to_fit();
	  // }

	}
	

	//	cout<<"   **********    **********   **********   **********   **********"<<endl;


      }
      // cout<<"Node list size = "<<node_list_size<<endl;
      // cout<<"counter = "<<counter<<endl;
      //cin.ignore();
      counter = counter + 1;
    }

    gDirectory->Write("hist_Dir", TObject::kOverwrite);
    file_out->Close();
      
    chan.close();
  } catch(evioException e){
    cerr<<endl<<e.toString()<<endl;
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}

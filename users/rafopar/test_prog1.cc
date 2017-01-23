#include <evioUtil.hxx>
#include <evioFileChannel.hxx>
#include <list>
#include <bitset>         // std::bitset
#include <iomanip>

#include <TFile.h>
#include <TH1D.h>

#define GET_CHAR(b,i) b[i]; i+=1;
#define GET_SHORT(b,i) ((short *)(&b[i]))[0]; i+=2;
#define GET_INT(b,i) ((int *)(&b[i]))[0]; i+=4;
#define GET_L64(b,i) ((unsigned long long *)(&b[i]))[0]; i+=8;

#define FADC_2_BANK 57602

using namespace evio;
using namespace std;

int main(int argc, char **argv){
  
  try{
    evioFileChannel chan(argv[1], "r");

    TFile *file_out = new TFile(Form("out_%s.root", argv[1]), "Recreate");
    TH1D *h_tdc1 = new TH1D("h_tdc1", "", 1500, 3000., 4500.);
    TH1D *h_time1 = new TH1D("h_time1", "", 1500, 46., 71.);
    TH1D *h_time2 = new TH1D("h_time2", "", 2000, 0., 4.);
    
    chan.open();

    int counter = 0;
    while( chan.read() ){
      evioDOMTree tree(chan);

      evioDOMNodeListP nodelist1 = tree.getNodeList();
      int node_list_size = nodelist1.get()->size();
      
      cout<<tree.toString()<<endl;

      for( std::list<evioDOMNode*>::iterator it = nodelist1.get()->begin();  it != nodelist1.get()->end(); it++ ){
	cout<<"   *******  Header  "<<(*it)->getHeader(0);
	cout<<"   *******  tag  "<<(*it)->tag<<endl;
	cout<<"   ***  Contenttype  "<<(*it)->getContentType()<<endl;
	cout<<"   *********  Body  "<<(*it)->getBody(0)<<endl;
	cout<<"   ********  Footer  "<<(*it)->getFooter(0);
	cout<<"   **********  size  "<<(*it)->getSize()<<endl;

	if( (*it)->tag == 57634 ){
	  //vector<uint32_t> *data_values = (*it)->getVector();
	  vector<uint32_t> *data_values = (*it)->getVector<uint32_t>();

	  for( std::vector<uint32_t>::iterator it_data = data_values->begin(); it_data != data_values->end(); it_data++ ){
	    cout<<setw(15)<<(*it_data)<<setw(36)<<bitset<32>(*it_data)<<endl;
	  }
	  cout<<endl;
	} else if( (*it)->tag == FADC_2_BANK ){

	  int i = 0;
	  short tdc[1024];
	  int adc[1024];
	  short pulse_min[1024];
	  short pulse_max[1024];
	  
	  evioCompositeDOMLeafNode *fadc = (evioCompositeDOMLeafNode *)(*it);
	  unsigned char *p = (unsigned char *)fadc->data.data();
	  unsigned int len = fadc->data.size() * 4;

	  cout<<"       len = "<<len<<endl;
	  
	  while(len-i>4)
	    {
	      unsigned char slot = GET_CHAR(p,i);
	      int trig_n = GET_INT(p,i);
	      long long trig_t = GET_L64(p,i);

	      cout<<"Slot:                       "<<static_cast<unsigned>(slot)<<endl;
	      cout<<"Trigger Number:             "<<trig_n<<endl;
	      cout<<"Trigger time:               "<<trig_t<<endl;
	      
	      int nch = GET_INT(p,i);

	      cout<<"Number of channels          "<<nch<<endl;

	      if(nch > 16) { printf("Error in %s: fadc mode 1 invalid nch\n", __func__); exit(1); }

	      while(nch--){

		int ch = GET_CHAR(p,i);

		cout<<"===Cheannel:                "<<ch<<endl;

		int npulse = GET_INT(p,i);
		
		cout<<"===Number of pulses         "<<npulse<<endl;
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
		  

		  cout<<"======tdc["<<i_pulse<<"]:        "<<tdc[i_pulse]<<endl;
		  cout<<"======adc["<<i_pulse<<"]:        "<<adc[i_pulse]<<endl;
		  cout<<"======pulse_min["<<i_pulse<<"]   "<<pulse_min[i_pulse]<<endl;
		  cout<<"======pulse_max["<<i_pulse<<"]   "<<pulse_max[i_pulse]<<endl;
		}

		
	      }
	      
	    }
	}
	

	cout<<"   **********    **********   **********   **********   **********"<<endl;
      }
      
      cout<<"Node list size = "<<node_list_size<<endl;
      cout<<"counter = "<<counter<<endl;
      cin.ignore();
      counter = counter + 1;
    }

    gDirectory->Write();
    file_out->Close();
      
    chan.close();
  } catch(evioException e){
    cerr<<endl<<e.toString()<<endl;
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}

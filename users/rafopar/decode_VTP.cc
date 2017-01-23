#include <evioUtil.hxx>
#include <evioFileChannel.hxx>
#include <list>
#include <ECTrig.hh>

using namespace evio;
using namespace std;

// This program loops over events from the input file, given as an argument.
// It will search for banks with a tag "0xe122" ("57634" in decimal representation)
// Then will loop over all words inside the bank and decode all the information,
// e.g. which part of EC (in, or out), cluster coordinates (u, v, w), etc

int main(int argc, char **argv){
 
  const int vtp_tag = 57634;

  try{
    evioFileChannel chan(argv[1], "r");
 
    chan.open();

    int counter = 0;

    while( chan.read() ){
      
      evioDOMTree tree(chan);
      
      evioDOMNodeListP nodelist1 = tree.getNodeList();
      
      for( std::list<evioDOMNode*>::iterator it = nodelist1.get()->begin();  it != nodelist1.get()->end(); it++ ){
	
	if( (*it)->tag == vtp_tag ){

	  TECTrig trig(*it);
	  // length of each data word is 32 bit
	  // vector<uint32_t> *data_values = (*it)->getVector<uint32_t>();

	  // for( std::vector<uint32_t>::iterator it_data = data_values->begin(); it_data != data_values->end(); it_data++ ){
	    
	  // }
	}

      }
      
    }
  } catch(evioException e){
    cerr<<endl<<e.toString()<<endl;
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}

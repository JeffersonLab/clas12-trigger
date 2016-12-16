#include <evioUtil.hxx>
#include <evioFileChannel.hxx>
#include <list>

using namespace evio;
using namespace std;

int main(int argc, char **argv){
  
  try{
    evioFileChannel chan(argv[1], "r");

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
	    cout<<(*it_data)<<"     ";
	  }
	  cout<<endl;
	}
	

	cout<<"   **********    **********   **********   **********   **********"<<endl;
      }
      
      cout<<"Node list size = "<<node_list_size<<endl;
      cout<<"counter = "<<counter<<endl;
      cin.ignore();
      counter = counter + 1;
    }

    chan.close();
  } catch(evioException e){
    cerr<<endl<<e.toString()<<endl;
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}

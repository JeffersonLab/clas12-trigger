#include <ECTrig.hh>
#include <evioUtil.hxx>
#include <evioFileChannel.hxx>
#include <bitset>         // std::bitset
#include <iomanip>

// using namespace evio;
// using namespace std;

TECTrig::TECTrig(){
  cout<<"Kuku"<<endl;
}

TECTrig::TECTrig( evio::evioDOMNode* it ){

  vector<uint32_t> *data_values = it->getVector<uint32_t>();

  for( std::vector<uint32_t>::iterator it_data = data_values->begin(); it_data != data_values->end(); it_data++ ){
    bool is_type_def =(*it_data)&chk_typedef;
    if( is_type_def ){
      cout<<"Type defining word"<<setw(15)<<(*it_data)<<setw(36)<<bitset<32>(*it_data)<<endl;

      unsigned short int data_type = ((*it_data)&typedef_bits)>>27;
      cout<<"Data type is "<<data_type<<endl;
      
      switch ( data_type ){
      case type_blk_head: ReadBlockHeader(); break;
      case type_blk_trail: ReadBlockTrailer(); break;
      case type_ev_head: ReadEventHeader(); break;
      case type_trig_time: ReadTriggerTime(); break;
      case type_ECtrig_peak: ReadECTriggerPeak(); break;
      case type_ECTrig_clust: ReadECTriggerCluster(); break;
      case type_trigger: ReadTrigger(); break;
      default: cout<<"Non defined data type, Exiting()"<<endl; exit(1); break;
      }
      
    }else{
      //cout<<"Data continuation word<<setw(15)"<<(*it_data)<<setw(36)<<bitset<32>(*it_data)<<endl;
    }

  }
  

}

void TECTrig::ReadBlockHeader(){
  
}

void TECTrig::ReadBlockTrailer(){
  
}

void TECTrig::ReadEventHeader(){
  //cout<<"  Case statement is working in type_ev_head"<<endl;
}

void TECTrig::ReadTriggerTime(){
  
}
void TECTrig::ReadECTriggerPeak(){
  
}

void TECTrig::ReadECTriggerCluster(){
  
}
void TECTrig::ReadTrigger(){
  
}

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

  for( fit_data = data_values->begin(); fit_data != data_values->end(); fit_data++ ){
    bool is_type_def =(*fit_data)&chk_typedef;
    if( is_type_def ){
      //cout<<"Type defining word"<<setw(15)<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;

      unsigned short int data_type = ((*fit_data)&typedef_bits)>>27;
      //cout<<"Data type is "<<data_type<<endl;
      
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
      //cout<<"Data continuation word<<setw(15)"<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;
    }

  }
  

}

void TECTrig::ReadBlockHeader(){
  fslotid = ((*fit_data)&SLOTID_bits)>>22;
  fblock_number = ((*fit_data)&BLOCK_NUMBER_bits)>>8;
  fblock_level = (*fit_data)&BLOCK_NUMBER_bits;
  cout<<"Slot id"<<setw(15)<<fslotid<<setw(36)<<bitset<32>(*fit_data)<<endl;
  
}

void TECTrig::ReadBlockTrailer(){
  
}

void TECTrig::ReadEventHeader(){
  //cout<<"  Case statement is working in type_ev_head"<<endl;
}

void TECTrig::ReadTriggerTime(){
  int timel = (*fit_data)&TIMEL_bits;
  //  cout<<"Type defining word"<<setw(15)<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;
  fit_data = std::next(fit_data, 1);
  //  cout<<"Type defining word"<<setw(15)<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;
  int timeh = (*fit_data)&TIMEL_bits;

  ftrig_time = timeh;
  ftrig_time = ftrig_time<<24;
  ftrig_time = ftrig_time|timel;
  // cout<<"timel           "<<bitset<48>(timel)<<endl;
  // cout<<"timeh           "<<bitset<48>(timeh)<<endl;
  // cout<<"ftrig_time      "<<bitset<48>(ftrig_time)<<endl;
  cout<<"Trigger time is "<<ftrig_time<<endl;
}
void TECTrig::ReadECTriggerPeak(){
  
}

void TECTrig::ReadECTriggerCluster(){
  
}
void TECTrig::ReadTrigger(){
  
}

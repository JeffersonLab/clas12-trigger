#include <ECTrig.hh>
#include <evioUtil.hxx>
#include <evioFileChannel.hxx>
#include <bitset>        // std::bitset
#include <iomanip>

// using namespace evio;
// using namespace std;

TECTrig::TECTrig(){
  cout<<"Kuku"<<endl;
}

TECTrig::TECTrig( evio::evioDOMNode* it ){
  
  vector<ap_int<32> > *data_values = (vector<ap_int<32>> *)it->getVector<uint32_t>();

  for( fit_data = data_values->begin(); fit_data != data_values->end(); fit_data++ ){

    ap_int<1> is_type_def = fit_data->range(31, 31);

    cout<<"The word is word"<<setw(15)<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;

    if( is_type_def ){
      cout<<"Type defining word"<<setw(15)<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;

      ap_int<4> data_type = fit_data->range(30, 27);

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
      cout<<"Data continuation word<<setw(15)"<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;
    }

  }
  
}

void TECTrig::ReadBlockHeader(){

  fslotid = fit_data->range(26, 22);
  fblock_number = fit_data->range(17, 8);
  fblock_level = fit_data->range(7, 0);
  cout<<"Slot id"<<setw(15)<<fslotid<<setw(36)<<bitset<32>(*fit_data)<<endl;
}

void TECTrig::ReadBlockTrailer(){
  fslotid = fit_data->range(26, 22);
  fnwords = fit_data->range(21, 0);
}

void TECTrig::ReadEventHeader(){
  fev_number = fit_data->range(26, 0);
}

void TECTrig::ReadTriggerTime(){

  int timel = fit_data->range(23, 0);
  cout<<"Type defining word"<<setw(15)<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;
  fit_data = std::next(fit_data, 1);
  cout<<"Type defining word"<<setw(15)<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;
  int timeh = fit_data->range(23, 0);
 
  ftrg_time = timeh;
  ftrg_time = ftrg_time<<24;
  ftrg_time = ftrg_time|timel;

  cout<<"size of ftrig_time = "<<sizeof(ftrg_time)<<endl;
  cout<<"timel           "<<bitset<48>(timel)<<endl;
  cout<<"timeh           "<<bitset<48>(timeh)<<endl;
  cout<<"ftrig_time      "<<bitset<48>(ftrg_time)<<endl;
  cout<<"Trigger time is "<<ftrg_time<<endl;

  test_var[0] = 15; test_var[1] = 75;
  cout<<"Addr1 = "<<&test_var[0]<<"     Addr2 = "<<&test_var[1]<<endl;
  cout<<"width of ftrig_time = "<<ftrg_time.getBitWidth()<<endl;
}
void TECTrig::ReadECTriggerPeak(){
  cout<<"  Data word is  "<<bitset<32>(fit_data->range(31, 0))<<endl;
  fpeak_inst = fit_data->range(26, 26);
  fpeak_view = fit_data->range(25, 24);
  //fpeak_coord = fit_data->range(23, 15);
  int dbl_intpart = fit_data->range(23, 18);
  int dbl_floatpart = fit_data->range(17, 15);
  fpeak_coord = double(dbl_intpart) + double(dbl_floatpart/10.);
  fpeak_energy = fit_data->range(14, 2);

  fit_data = std::next(fit_data, 1);   // Go to the next word
  // This should be data continuation word, if not then data format is not correct
  if( fit_data->range(31, 31) ) {printf("Wrong Data Format in %s Exiting", __func__); exit(0); }
  fpeak_time = fit_data->range(10, 0);
  cout<<"Data cont. word"<<setw(15)<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;
  cout<<"======= Inst = "<<fpeak_inst<<endl;
  cout<<"======= view = "<<fpeak_view<<endl;
  cout<<"======= The peak coordinate is "<<fpeak_coord<<endl;
  cout<<"======= The peak coordinate is "<<bitset<9>(fpeak_coord)<<endl;
  cout<<"======= Energy = "<<fpeak_energy<<endl;
  cout<<"======= Time = "<<fpeak_time<<endl;
}

void TECTrig::ReadECTriggerCluster(){
  cout<<" === === === === ECTrigCluster === === === ===  "<<endl;
  cout<<"  Data word is  "<<bitset<32>(fit_data->range(31, 0))<<endl;
  fclust_inst = fit_data->range(26, 26);
  int dbl_intpart = fit_data->range(25, 20);
  int dbl_floatpart = fit_data->range(19, 17);
  fclust_coord_W = double(dbl_intpart) + double(dbl_floatpart/10.);
  dbl_intpart = fit_data->range(16, 11);
  dbl_floatpart = fit_data->range(10, 8);
  fclust_coord_V = double(dbl_intpart) + double(dbl_floatpart/10.);

  dbl_intpart = fit_data->range(7, 2);

  int coordh = fit_data->range(1, 0);
  //cout<<"Type defining word"<<setw(15)<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;
  
  fit_data = std::next(fit_data, 1);   // Go to the next word
  //This should be data continuation word, if not then data format is not correct
  if( fit_data->range(31, 31) ) {printf("Wrong Data Format in %s Exiting", __func__); exit(0); }

  cout<<"Data cont. word"<<setw(15)<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;
  int coordl = fit_data->range(30, 30);

  dbl_floatpart = coordh<<1;
  dbl_floatpart = dbl_floatpart|coordl;
  fclust_coord_U = double(dbl_intpart) + double(dbl_floatpart)/10.;
  
  fclust_Energy = fit_data->range(29, 17);
  fclust_time = fit_data->range(10, 0);
  cout<<"coordh = "<<coordh<<endl;
  cout<<"coordl = "<<coordl<<endl;
  cout<<"dbl_floatpart = "<<dbl_floatpart<<endl;
  cout<<"double(dbl_floatpart)/10. = "<<double(dbl_floatpart)/10.<<endl;
  cout<<"flust_Ucord = "<<(double(dbl_intpart) + double(dbl_floatpart)/10.)<<endl;
  
  cout<<"W coordinate = "<<fclust_coord_W<<endl;
  cout<<"V coordinate = "<<fclust_coord_V<<endl;
  cout<<"U coordinate = "<<fclust_coord_U<<endl;
  cout<<"Cluster Energy = "<<fclust_Energy<<endl;
  cout<<"Cluster Time = "<<fclust_time<<endl;
  
  cout<<" === === === ===  End of ECTrigCluster === === === ===  "<<endl;
}



void TECTrig::ReadTrigger(){
  cout<<" === === === === Trigger === === === ===  "<<endl;
  cout<<"  Data word is  "<<bitset<32>(fit_data->range(31, 0))<<endl;

  ftrig_inst = fit_data->range(16, 16);
  ftrig_lane = fit_data->range(15, 11);
  ftrig_time = fit_data->range(10, 0);

  cout<<"ftrig_inst = "<<ftrig_inst<<endl;
  cout<<"ftrig_lane = "<<ftrig_lane<<endl;
  cout<<"ftrig_time = "<<ftrig_time<<endl;
  cout<<" === === === === End of Trigger === === === ===  "<<endl;
}

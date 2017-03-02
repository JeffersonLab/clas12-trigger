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

  // Reset all attributes, before reading the current event
  ResetAll(); 
  
  vector<ap_int<32> > *data_values = (vector<ap_int<32>> *)it->getVector<uint32_t>();

  cout<<"======******====== BEGINNIG OF VTP Hadrware Data ======******======"<<endl;

  for( fit_data = data_values->begin(); fit_data != data_values->end(); fit_data++ ){

    ap_int<1> is_type_def = fit_data->range(31, 31);

    cout<<endl;    cout<<endl;
    cout<<"The word is "<<setw(15)<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;

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
  cout<<"======******====== END OF VTP Hadrware Data ======******======"<<endl;
  fnPeaks = fv_ECPeaks.size();
  fnClusters = fv_ECClusters.size();
}

void TECTrig::ReadBlockHeader(){
  has_BlockHeader = true;
  fslotid = fit_data->range(26, 22);
  fblock_number = fit_data->range(17, 8);
  fblock_level = fit_data->range(7, 0);
  cout<<"Slot id"<<setw(15)<<fslotid<<setw(36)<<bitset<32>(*fit_data)<<endl;
}

void TECTrig::ReadBlockTrailer(){
  has_BlockTrailer = true;
  fslotid = fit_data->range(26, 22);
  fnwords = fit_data->range(21, 0);
}

void TECTrig::ReadEventHeader(){
  has_EventHeader = true;
  fev_number = fit_data->range(26, 0);
}

void TECTrig::ReadTriggerTime(){
  has_TrigTime = true;
  int timel = fit_data->range(23, 0);
  cout<<"Type defining word"<<setw(15)<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;
  fit_data = std::next(fit_data, 1);
  cout<<"Type defining word"<<setw(15)<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;
  int timeh = fit_data->range(23, 0);
 
  // ftrg_time = timeh;
  // ftrg_time = ftrg_time<<24;
  // ftrg_time = ftrg_time|timel;

  ftrg_time = 0; // Make sure all bits are 0
  ftrg_time = timeh;
  ftrg_time = ftrg_time<<24;
  ftrg_time = ftrg_time|timel;
 
  cout<<"size of ftrig_time = "<<sizeof(ftrg_time)<<endl;
  cout<<"timel           "<<bitset<48>(timel)<<endl;
  cout<<"timeh           "<<bitset<48>(timeh)<<endl;
  cout<<"ftrig_time       "<<bitset<48>(ftrg_time)<<endl;
  //cout<<"aftrig_time      "<<bitset<48>(aftrig_time)<<endl;
  cout<<"Trigger time is  "<<ftrg_time<<endl;
  //cout<<"aTrigger time is "<<aftrig_time<<endl;

  test_var[0] = 15; test_var[1] = 75;
  cout<<"Addr1 = "<<&test_var[0]<<"     Addr2 = "<<&test_var[1]<<endl;
  //cout<<"width of ftrig_time = "<<ftrg_time.getBitWidth()<<endl;
}


void TECTrig::ReadECTriggerPeak(){
  has_TrigPeak = true;
  cout<<"  Data word is  "<<bitset<32>(fit_data->range(31, 0))<<endl;
  TEC_Peak cur_peak;
  cur_peak.inst = fit_data->range(26, 26);
  cur_peak.view = fit_data->range(25, 24);
  fpeak_coord_hls(8, 0) = fit_data->range(23, 15);
  cur_peak.coord = fpeak_coord_hls.to_double();
  cur_peak.energy = fit_data->range(14, 2);

  fit_data = std::next(fit_data, 1);   // Go to the next word
  // This should be data continuation word, if not then data format is not correct
  if( fit_data->range(31, 31) ) {printf("Wrong Data Format in %s Exiting", __func__); exit(0); }
  
  cur_peak.time = fit_data->range(10, 0);

  fv_ECPeaks.push_back(cur_peak);
  
  cout<<"Data cont. word"<<setw(15)<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;
  cout<<"======= Inst = "<<cur_peak.inst<<endl;
  cout<<"======= view = "<<cur_peak.view<<endl;
  cout<<"======= The peak coordinate is "<<cur_peak.coord<<endl;
  cout<<"======= The peak coordinate is "<<bitset<9>(cur_peak.coord)<<endl;
  cout<<"======= Energy = "<<cur_peak.energy<<endl;
  cout<<"======= Time = "<<cur_peak.time<<endl;
}

void TECTrig::ReadECTriggerCluster(){
  has_TrigClust = true;
  cout<<" === === === === ECTrigCluster === === === ===  "<<endl;
  cout<<"  Data word is  "<<bitset<32>(fit_data->range(31, 0))<<endl;
  TEC_Cluster cur_clust;
  cur_clust.inst = fit_data->range(26, 26);
  fclust_coord_Y_hls(8, 0) = fit_data->range(25, 17);
  cur_clust.coordY = fclust_coord_Y_hls.to_double();
  fclust_coord_X_hls(8, 0) = fit_data->range(16, 8);
  cur_clust.coordX = fclust_coord_X_hls.to_double();
  
  //cout<<"Type defining word"<<setw(15)<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;

  // Go to the next word
  fit_data = std::next(fit_data, 1);
  
  // This should be data continuation word,
  // if not then data format is not correct
  if( fit_data->range(31, 31) ) {printf("Wrong Data Format in %s Exiting", __func__); exit(0); }

  cout<<"Data cont. word"<<setw(15)<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;
  
  cur_clust.energy = fit_data->range(29, 17);
  cur_clust.time = fit_data->range(10, 0);

  fv_ECClusters.push_back(cur_clust);
  
  cout<<"Y coordinate = "<<cur_clust.coordY<<endl;
  cout<<"X coordinate = "<<cur_clust.coordY<<endl;
  cout<<"Cluster Energy = "<<cur_clust.energy<<endl;
  cout<<"Cluster Time = "<<cur_clust.time<<endl;
  
  cout<<" === === === ===  End of ECTrigCluster === === === ===  "<<endl;
}



void TECTrig::ReadTrigger(){
  has_Trigger = true;
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


void TECTrig::ResetAll(){
  fSector=UNDEF;
  fslotid=UNDEF;
  fnwords=UNDEF;
  fev_number=UNDEF;
  fblock_number=UNDEF;
  fblock_level=UNDEF;
  
  ftrig_inst=UNDEF;
  ftrig_lane=UNDEF;
  ftrig_time=UNDEF;
  
  ftrg_time=0;

  fv_ECPeaks.clear();
  fv_ECPeaks.shrink_to_fit();
  fv_ECClusters.clear();
  fv_ECClusters.shrink_to_fit();
  fnPeaks = 0;
  fnClusters = 0;
  
  has_BlockHeader = false;
  has_BlockTrailer = false;
  has_EventHeader = false;
  has_TrigTime = false;
  has_TrigPeak = false;
  has_TrigClust = false;
  has_Trigger = false;
}

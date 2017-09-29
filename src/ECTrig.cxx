#include <ECTrig.hh>
#include <evioUtil.hxx>
#include <evioFileChannel.hxx>
#include <bitset>        // std::bitset
#include <iomanip>
#include <iterator>     // std::next
// using namespace evio;
// using namespace std;

map<int, int> TECTrig::EC_vtp_sector = {
  {100, 10}, // Global trigger
  {101, 0}, {102, 1}, {103, 2}, {104, 3}, {105, 4}, {106, 5},   // ECal
  {107, 0}, {108, 1}, {109, 2}, {110, 3}, {111, 4}, {112, 5}    // PCal
};

map<int, int> TECTrig::EC_vtp_Detector = {
  {100, 0}, // Global trigger
  {101, 1}, {102, 1}, {103, 1}, {104, 1}, {105, 1}, {106, 1},   // ECal
  {107, 2}, {108, 2}, {109, 2}, {110, 2}, {111, 2}, {112, 2}    // PCal
};

TECTrig::TECTrig(){
  cout<<"Kuku"<<endl;
}

TECTrig::TECTrig( evio::evioDOMNode* it, int a_adcECvtp_tag){

  // Reset all attributes, before reading the current event
  ResetAll();

  fhead_node = it;
  
  // Check if, the tag representing ROC id is correct, otherwise
  // exit the program
  if( a_adcECvtp_tag < adcECvtp_tagmin || a_adcECvtp_tag > adcECvtp_tagmax ){
    printf("Wrong tag number in %s, Exiting", __func__); exit(0);
  }

  // Sector number is identified from the roc id
  fECVTP_tag = a_adcECvtp_tag;
  fSector = EC_vtp_sector[fECVTP_tag];

  // Determine which detector is
  
  fDet = EC_vtp_Detector[fECVTP_tag];
  
  vector<ap_int<32> > *data_values = (vector<ap_int<32>> *)it->getVector<uint32_t>();

  for( fit_data = data_values->begin(); fit_data != data_values->end(); fit_data++ ){

    ap_int<1> is_type_def = fit_data->range(31, 31);

    if( is_type_def ){
      //cout<<"Type defining word"<<setw(15)<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;

      ap_int<4> data_type = fit_data->range(30, 27);

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
      //     cout<<"Data continuation word<<setw(15)"<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;
    }

  }
  //  cout<<"======******====== END OF VTP Hadrware Data ======******======"<<endl;
  fnAllPeaks = fv_ECAllPeaks.size();
  fnAllClusters = fv_ECAllClusters.size();
  
  for( int i = 0; i < n_inst; i++ ){
    fnClusters[i] = fv_ind_ECCluster[i].size();
    for( int j = 0; j < n_view; j++ ){
      fnPeaks[i][j] = fv_ind_ECPeak[i][j].size();
    }
  }
  
}

void TECTrig::ReadBlockHeader(){
  has_BlockHeader = true;
  fslotid = fit_data->range(26, 22);
  fblock_number = fit_data->range(17, 8);
  fblock_level = fit_data->range(7, 0);
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

  fit_data = std::next(fit_data, 1);

  int timeh = fit_data->range(23, 0);
 
  ftrg_time = 0; // Make sure all bits are 0
  ftrg_time = timeh;
  ftrg_time = ftrg_time<<24;
  ftrg_time = ftrg_time|timel;
}

void TECTrig::ReadECTriggerPeak(){
  has_TrigPeak = true;

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

  fv_ECAllPeaks.push_back(cur_peak);

  fv_ind_ECPeak[cur_peak.inst][cur_peak.view].push_back(fv_ECAllPeaks.size() - 1);
}

void TECTrig::ReadECTriggerCluster(){
  has_TrigClust = true;

  TEC_Cluster cur_clust;
  cur_clust.inst = fit_data->range(26, 26);
  fclust_coord_Y_hls(8, 0) = fit_data->range(25, 17);
  cur_clust.coordY = fclust_coord_Y_hls.to_double();
  fclust_coord_X_hls(8, 0) = fit_data->range(16, 8);
  cur_clust.coordX = fclust_coord_X_hls.to_double();


  // Go to the next word
  fit_data = std::next(fit_data, 1);
  
  // This should be data continuation word,
  // if not then data format is not correct
  if( fit_data->range(31, 31) ) {printf("Wrong Data Format in %s Exiting", __func__); exit(0); }

  // cout<<"Data cont. word"<<setw(15)<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;
  
  cur_clust.energy = fit_data->range(29, 17);
  cur_clust.time = fit_data->range(10, 0);

  fv_ECAllClusters.push_back(cur_clust);
  //fv_ECClusters[cur_clust.inst].push_back(&fv_ECAllClusters.back());
  fv_ind_ECCluster[cur_clust.inst].push_back(fv_ECAllClusters.size() - 1);
}



void TECTrig::ReadTrigger(){
  has_Trigger = true;

  ftrig_inst = fit_data->range(16, 16);
  ftrig_lane = fit_data->range(15, 11);
  ftrig_time = fit_data->range(10, 0);
}

TEC_Peak* TECTrig::GetECPeak( int aind){
  if( aind < fnAllPeaks ){
    return &fv_ECAllPeaks.at(aind);
  }
  else{
    printf("Request for out of range element in %s Exiting the program", __func__); exit(0);
  }
}

TEC_Peak* TECTrig::GetECPeak( int ainst, int aview, int aind){
  if( ainst >= 0 && ainst < n_inst && aview >= 0 && aview < n_view && aind >= 0 && aind < fnPeaks[ainst][aview] ){
    return &fv_ECAllPeaks.at(fv_ind_ECPeak[ainst][aview].at(aind)); 
  }
  else{
    printf("Request for out of range element in %s Exiting the program", __func__); exit(0);
  }
}

int TECTrig::GetNPeaks(int ainst, int aview){
    if( ainst >= 0 && ainst < n_inst && aview >= 0 && aview < n_view ){
      return fnPeaks[ainst][aview];
  }
    else{
    printf("Request for out of range element in %s Exiting the program", __func__); exit(0);
  }

}

int TECTrig::GetNClust( int ainst ){
  if( ainst >= 0 && ainst < n_inst){
    return fnClusters[ainst];
  }
}

TEC_Cluster* TECTrig::GetECCluster( int aind){
  if( aind < fnAllClusters ){
    return &fv_ECAllClusters.at(aind);
  }
  else{
    printf("Request for out of range element in %s Exiting the program", __func__); exit(0);
  }
}

TEC_Cluster* TECTrig::GetECCluster( int ainst, int aind){
  if( ainst >= 0 && ainst < n_inst && aind < fnClusters[ainst] ){
    return &fv_ECAllClusters.at(fv_ind_ECCluster[ainst].at(aind));
    //return fv_ECClusters[ainst].at(aind);
  }
  else{
    printf("Request for out of range element in %s Exiting the program", __func__); exit(0);
  }
}


void TECTrig::PrintECCluster( int aind){
  if( aind < fnAllClusters ){
    cout<<"fv_ECAllClusters.size() = "<<fv_ECAllClusters.size()<<endl;
    cout<<"Cluster index = "<<aind<<endl;
    cout<<"Cluster inst = "<<fv_ECAllClusters.at(aind).inst<<endl;
    cout<<"Cluster Address "<<&fv_ECAllClusters.at(aind)<<endl;
    cout<<"Cluster Y = "<<fv_ECAllClusters.at(aind).coordY<<endl;
    cout<<"Cluster X = "<<fv_ECAllClusters.at(aind).coordX<<endl;
    cout<<"Cluster E = "<<fv_ECAllClusters.at(aind).energy<<endl;
  }
  else{
    printf("Request for out of range element in %s Exiting the program", __func__); exit(0);
  }
}

void TECTrig::PrintECCluster( int ainst, int aind){
  if( ainst >= 0 && ainst < n_inst && aind < fnClusters[ainst] ){
    cout<<"fv_ind_ECCluster[ainst].size() = "<<fv_ind_ECCluster[ainst].size()<<endl;
    cout<<"Cluster instance in the argument = "<<ainst<<endl;
    cout<<"Cluster instance from the cluster structure = "<<(fv_ECAllClusters.at(fv_ind_ECCluster[ainst].at(aind))).inst<<endl;
    cout<<"Cluster Address "<<&fv_ECAllClusters.at(fv_ind_ECCluster[ainst].at(aind))<<endl;
    cout<<"Cluster index = "<<aind<<endl;
    cout<<"Cluster Y = "<<(fv_ECAllClusters.at(fv_ind_ECCluster[ainst].at(aind))).coordY<<endl;
    cout<<"Cluster X = "<<(fv_ECAllClusters.at(fv_ind_ECCluster[ainst].at(aind))).coordX<<endl;
    cout<<"Cluster E = "<<(fv_ECAllClusters.at(fv_ind_ECCluster[ainst].at(aind))).energy<<endl;

  }
  else{
    printf("Request for out of range element in %s Exiting the program", __func__); exit(0);
  }
}

void TECTrig::PrintXMLData(){
  cout<<"   *******  Header  "<<(fhead_node)->getHeader(0);
  cout<<"   *******  tag  "<<(fhead_node)->tag<<endl;
  cout<<"   ***  Contenttype  "<<(fhead_node)->getContentType()<<endl;
  cout<<"   *********  Body  "<<(fhead_node)->getBody(0)<<endl;
  cout<<"   ********  Footer  "<<(fhead_node)->getFooter(0);
  cout<<"   **********  size  "<<(fhead_node)->getSize()<<endl;
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

  for( int i = 0; i < n_inst; i++ ){

    fv_ind_ECCluster[i].clear();
    fv_ind_ECCluster[i].shrink_to_fit();
    fnClusters[i] = 0;
      
    for( int j = 0; j < n_view; j++ ){
      fv_ind_ECPeak[i][j].clear();
      fv_ind_ECPeak[i][j].shrink_to_fit();
      fnPeaks[i][j] = 0;
    }
  }
  
  ftrg_time=0;

  fv_ECAllPeaks.clear();
  fv_ECAllPeaks.shrink_to_fit();
  fv_ECAllClusters.clear();
  fv_ECAllClusters.shrink_to_fit();
  
  fnAllPeaks = 0;
  fnAllClusters = 0;
  
  has_BlockHeader = false;
  has_BlockTrailer = false;
  has_EventHeader = false;
  has_TrigTime = false;
  has_TrigPeak = false;
  has_TrigClust = false;
  has_Trigger = false;
}

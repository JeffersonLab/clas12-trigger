#ifndef __ECTrig__
#define __ECTrig__

 #include <evioUtil.hxx>
// #include <evioFileChannel.hxx>
//class evio::evioDOMNode;
#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_stream.h>

class TECTrig
{
public:
  TECTrig();
  TECTrig( evio::evioDOMNode*);
  int Sector() {return fSector;};
private:
  std::vector<ap_int<32> >::iterator fit_data;
  int fSector;
  int fslotid;
  int fnwords;
  int fev_number;
  int fblock_number;
  int fblock_level;
  
  int fpeak_inst;
  int fpeak_view;
  double fpeak_coord;
  ap_ufixed<9, 6> fpeak_coord_hls;
  //ap_ufixed<128,32> fpeak_coord;
  int fpeak_energy;
  int fpeak_time;

  int fclust_inst;
  ap_ufixed<9, 6> fclust_coord_Y_hls;
  ap_ufixed<9, 6> fclust_coord_X_hls;

  double fclust_coord_Y;
  double fclust_coord_X;

  int fclust_Energy;
  int fclust_time;

  int ftrig_inst;
  int ftrig_lane;
  int ftrig_time;
  
  //long long int ftrig_time;
  ap_int<48> ftrg_time;
  ap_int<33> test_var[2];

  void ResetAll();
  void ReadBlockHeader();
  void ReadBlockTrailer();
  void ReadEventHeader();
  void ReadTriggerTime();
  void ReadECTriggerPeak();
  void ReadECTriggerCluster();
  void ReadTrigger();

  static const unsigned short int type_blk_head = 0;
  static const unsigned short int type_blk_trail = 1;
  static const unsigned short int type_ev_head = 2;
  static const unsigned short int type_trig_time = 3;
  static const unsigned short int type_ECtrig_peak = 4;
  static const unsigned short int type_ECTrig_clust = 5;
  static const unsigned short int type_trigger = 6;
};

#endif

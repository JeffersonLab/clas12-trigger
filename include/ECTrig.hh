#ifndef __ECTrig__
#define __ECTrig__

#include <evioUtil.hxx>
#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_stream.h>
#include <vector>

using namespace std;

typedef struct{
  int inst;
  int view;
  double coord;
  int energy;
  int time;
} TEC_Peak;

typedef struct{
  int inst;
  double coordY;
  double coordX;
  int energy;
  int time;
} TEC_Cluster;

typedef struct{
  int inst;
  int lane;
  int time;
} TCLAS12Trigger;

class TECTrig
{
public:
  TECTrig();
  TECTrig( evio::evioDOMNode*);
  int Sector() {return fSector;};
  bool HasBlockHeader() {return has_BlockHeader;};
  bool HasBlockTrailer() {return has_BlockTrailer;};
  bool HasEventHeader() {return has_EventHeader;};
  bool HasTrigTime() {return has_TrigTime;};
  bool HasTrigPeak() {return has_TrigPeak;};
  bool HasTrigClust() {return has_TrigClust;};
  bool HasTrigger() {return has_Trigger;};

  int GetNwords() { return has_BlockTrailer ? fnwords: UNDEF; }
  int GetSlotID() { return (has_BlockHeader || has_BlockTrailer) ? fslotid : UNDEF; }
  int GetEvNumber() { return has_EventHeader ? fev_number : UNDEF; }
  int GetBlockNUmber() {return has_BlockHeader ? fblock_number: UNDEF; }
  int GetBlockLevel() {return has_BlockHeader ? fblock_level: UNDEF; }
  
  //-------  double GetPeakCoord() {return }
  
private:
  std::vector<ap_int<32> >::iterator fit_data;
  int fSector;
  int fslotid;
  int fnwords;
  int fev_number;
  int fblock_number;
  int fblock_level;

  vector<TEC_Peak> fv_ECPeaks;
  vector<TEC_Cluster> fv_ECClusters;

  int fnPeaks;
  int fnClusters;
  
  ap_ufixed<9, 6> fpeak_coord_hls;

  ap_ufixed<9, 6> fclust_coord_Y_hls;
  ap_ufixed<9, 6> fclust_coord_X_hls;

  int ftrig_inst;
  int ftrig_lane;
  int ftrig_time;

  long long int ftrg_time;
  //ap_int<48> ftrg_time;
  ap_int<33> test_var[2];

  void ResetAll();
  void ReadBlockHeader();
  void ReadBlockTrailer();
  void ReadEventHeader();
  void ReadTriggerTime();
  void ReadECTriggerPeak();
  void ReadECTriggerCluster();
  void ReadTrigger();
  
  bool has_BlockHeader;
  bool has_BlockTrailer;
  bool has_EventHeader;
  bool has_TrigTime;
  bool has_TrigPeak;
  bool has_TrigClust;
  bool has_Trigger;

  static const unsigned short int type_blk_head = 0;
  static const unsigned short int type_blk_trail = 1;
  static const unsigned short int type_ev_head = 2;
  static const unsigned short int type_trig_time = 3;
  static const unsigned short int type_ECtrig_peak = 4;
  static const unsigned short int type_ECTrig_clust = 5;
  static const unsigned short int type_trigger = 6;

  static const int UNDEF = -9999;
};

#endif

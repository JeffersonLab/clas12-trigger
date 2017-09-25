#ifndef __ECTrig__
#define __ECTrig__

#include <evioUtil.hxx>
#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_stream.h>
#include <vector>
#include <map>

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
  TECTrig( evio::evioDOMNode*, int);

  int GetDetector() {return fDet;};   // 0 = Global Trigger, 1 = EC, 2 = PCal
  int GetSector() {return fSector;};
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
  int GetNAllPeaks() {return fnAllPeaks;}
  int GetNPeaks(int, int); // Instance (0=in, 1 = out), view (0=U,1=V,2=W)
  int GetNAllClust() {return fnAllClusters;}
  int GetNClust( int );
  TEC_Peak *GetECPeak( int );
  TEC_Peak *GetECPeak( int, int, int ); // (instance(0,1), view(0, 1, 2), index  )
  TEC_Cluster *GetECCluster( int );
  TEC_Cluster *GetECCluster(int, int); // (instance(0.1), index )
  int GetTrigLane() {return ftrig_lane;}; // trigger number, i.e. which trigger is fired
  int GetLocalTrigTime() {return ftrig_time;}; // Trig time wrt the start of the event winfow beginning
  int GetTrigInst() {return ftrig_inst;}; // 0=EC_in, 1=EC_out

  // ====== Diagnostic functions =====
  void PrintECCluster( int );
  void PrintECCluster( int, int );
  void PrintXMLData();

  //ftrig_time
  //-------  double GetPeakCoord() {return }
  
private:
  static const int n_inst = 2;
  static const int n_view = 3;
  std::vector<ap_int<32> >::iterator fit_data;
  int fECVTP_tag;
  int fDet;       // The detector, 0 = global trigger, 1 = EC, 2 = PCal
  int fSector;    // sector
  int fslotid;    // slotid
  int fnwords;
  int fev_number;
  int fblock_number;
  int fblock_level;
  evio::evioDOMNode* fhead_node; //pointer to the head node of VTP bank

  vector<TEC_Peak> fv_ECAllPeaks;
  vector<int> fv_ind_ECPeak[n_inst][n_view]; // [i][j]; i: 0=EC_in, 1=EC_out j: 0=U, 1=V, 2=W
//  vector<TEC_Peak*> fv_ECPeaks[n_inst][n_view]; // [i][j]; i: 0=EC_in, 1=EC_out j: 0=U, 1=V, 2=W
  vector<TEC_Cluster> fv_ECAllClusters;
  vector<int> fv_ind_ECCluster[n_inst];
//  vector<TEC_Cluster*> fv_ECClusters[n_inst];
  
  int fnAllPeaks;
  int fnPeaks[n_inst][n_view];
  int fnAllClusters;
  int fnClusters[n_inst];
  
  ap_ufixed<9, 6> fpeak_coord_hls;

  ap_ufixed<9, 6> fclust_coord_Y_hls;
  ap_fixed<9, 6> fclust_coord_X_hls;

  int ftrig_inst;
  int ftrig_lane;
  int ftrig_time;

  long long int ftrg_time;
  //ap_int<48> ftrg_time;

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
  static const int adcECvtp_tagmax = 112;
  static const int adcECvtp_tagmin = 100;
  static map<int, int> EC_vtp_sector;   // Mapping tag number to the sector
  static map<int, int> EC_vtp_Detector;   // Mapping tag number to the Detector
};

#endif

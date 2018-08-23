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
  int coord;
  int energy;
  int time;
} TEC_Peak;

typedef struct{
  int inst;
  int Ustrip;   // U strip number
  int Vstrip;   // V strip number
  int Wstrip;   // W strip number
  int energy;
  int time;
} TEC_Cluster;

typedef struct{
  int inst;
  int lane;
  int time;
} TCLAS12Trigger;

typedef struct{
    vector<int> chan;               // Vector of channels that are fired 
    int time;                       // time shows the channel in the readout window
} T1DMask;

typedef struct{
    vector<int> sl;                 // Vector of SuperLayers that gave signal
    bool is_inbend;                 // Is the road inbending
    bool is_outbend;                // Is the road outbending
    bool is_valid;                  // Is the rad valid, i.e. did it match a lookup table
    int  time;
    vector<int> tof_match;          // Vector of channels in ftof that roads point to
} TDCRoad;

//typedef struct{
//    vector<int> chan;               // Vector of channels that are fired 
//    int time;                       // time shows the channel in the readout window
//} TPCalU_mask;
//
//typedef struct{
//    vector<int> chan;               // Vector of channels that are fired 
//    int time;                       // time shows the channel in the readout window
//} T1DMask;
//
//typedef struct{
//    vector<int> chan;               // Vector of channels that are fired 
//    int time;                       // time shows the channel in the readout window
//} TFTOF_mask;
//
//typedef struct{
//    vector<int> chan;               // Vector of channels that are fired 
//    int time;                       // time shows the channel in the readout window
//} TCTOF_mask;
//
//typedef struct{
//    vector<int> chan;               // Vector of channels that are fired 
//    int time;                       // time shows the channel in the readout window
//} TCND_mask;

typedef struct{
    int tr_time;                    // trigger time with the 4ns resolution
    ap_int<32> tr_word;             // The trigger word
}Trig_word;

class TECTrig
{
public:
  TECTrig();
  TECTrig( evio::evioDOMNode*, int);

  void SetevioDOMENodeSect(evio::evioDOMNode*, int);
  int GetDetector() {return fDet;};   // 0 = Global Trigger, 1 = EC, 2 = PCal
  int GetSector() {return fSector;};
  bool HasBlockHeader() {return has_BlockHeader;};
  bool HasBlockTrailer() {return has_BlockTrailer;};
  bool HasEventHeader() {return has_EventHeader;};
  bool HasTrigTime() {return has_TrigTime;};
  bool HasTrigPeak() {return has_TrigPeak;};
  bool HasTrigClust() {return has_TrigClust;};
  bool HasHTCCMask() {return has_HTCCMask ;};
  bool HasFTOFMask() {return has_FTOFMask ;};
  bool HasCTOFMask() {return has_CTOFMask ;};
  bool HasCNDMask() {return has_CNDMask ;};
  bool HasTrigger() {return has_Trigger;};
  bool HasDCRoad() {return has_DCRoad;};

  int GetNwords() { return has_BlockTrailer ? fnwords: UNDEF; }
  int GetSlotID() { return (has_BlockHeader || has_BlockTrailer) ? fslotid : UNDEF; }
  int GetEvNumber() { return has_EventHeader ? fev_number : UNDEF; }
  int GetBlockNUmber() {return has_BlockHeader ? fblock_number: UNDEF; }
  int GetBlockLevel() {return has_BlockHeader ? fblock_level: UNDEF; }
  int GetNAllPeaks() {return fnAllPeaks;}
  int GetNPeaks(int, int); // Instance (0=in, 1 = out), view (0=U,1=V,2=W)
  int GetNAllClust() {return fnAllClusters;}
  int GetNClust( int );
  int GetNPCalUMasks() {return fnPCalU_Masks;}    // Return number of THTCC_Hits objects
  int GetNHTCCMasks() {return fnHTCC_Masks;}    // Return number of THTCC_Hits objects
  int GetNFTOFMasks() {return fnFTOF_Masks;}    // Return number of FTOF masks (T1DMask objects)
  int GetNCTOFMasks() {return fnCTOF_Masks;}    // Return number of CTOF masks (T1DMask objects)
  int GetNCNDMasks() {return fnCND_Masks;}      // Return number of CND_mask (T1DMask objects)
  TEC_Peak *GetECPeak( int );
  TEC_Peak *GetECPeak( int, int, int ); // (instance(0,1), view(0, 1, 2), index  )
  TEC_Cluster *GetECCluster( int );
  TEC_Cluster *GetECCluster(int, int); // (instance(0.1), index )
  T1DMask *GetPCalUMask(int);        // Return pointer to the PCalU mask
  T1DMask *GetHTCCMask(int);         // Return pointer to the HTCC mask
  T1DMask *GetFTOFMask(int);         // Return pointer to the FTOF mask
  T1DMask *GetCTOFMask(int);         // Return pointer to the CTOF mask
  T1DMask *GetCNDMask(int);          // Return pointer to the CND mask
  Trig_word *GetTrigWord(int);         // Return pointer to the Trig word
  int GetNTrig() {return fnTrigWords;}; //Return number of triggers in the VTP Bank
  int GetTrigLane() {return ftrig_lane(31, 0);}; // trigger number, i.e. which trigger is fired
  int GetLocalTrigTime() {return ftrig_time;}; // Trig time wrt the start of the event window beginning
  int GetTrigInst() {return ftrig_inst;}; // 0=EC_in, 1=EC_out

  bool IsRoadInbending() {return fDCRoad.is_inbend;};
  bool IsRoadOutbending() {return fDCRoad.is_outbend;};
  bool IsRoadValid() {return fDCRoad.is_valid;};
  int  GetRoadTime() {return fDCRoad.time;};
  vector<int> *GetRoad_SLs() {return &(fDCRoad.sl) ;};                // Returns pointer of the vector of superlayers of roads
  vector<int> *GetRoad_FTOFMatch() {return &(fDCRoad.tof_match) ;};   // Returns the pointer to the vector of FTOF channels of ROADs
  
  // ====== Diagnostic functions =====
  void PrintECCluster( int );
  void PrintECCluster( int, int );
  void PrintXMLData();

  //ftrig_time
  //-------  double GetPeakCoord() {return }
  
private:
  static const int n_inst = 2;
  static const int n_view = 3;
  static const int n_PCalU_chan = 68;                           // NUmber of PCal U channels;
  static const int n_HTCC_chan = 48;                            // NUmber of HTCC channels;
  static const int n_CTOF_chan = 48;                            // NUmber of Max FTOF channels per sector/panel;
  static const int n_FTOF_chan = 62;                            // NUmber of Max FTOF channels per sector/panel;
  static const int n_CND_chan = 72;                             // Number of CND channels 24(chan per layer)*3 (layers)
  static const int n_max_DC_segments = 6;                       // Number of maximum DC segments
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
  vector<T1DMask> fv_PCalUMasks;
  vector<T1DMask> fv_HTCCMasks;
  vector<T1DMask> fv_FTOFMasks;
  vector<T1DMask> fv_CTOFMasks;
  vector<T1DMask> fv_CNDMasks;
  vector<Trig_word> fv_TrigWords;
  
  TDCRoad fDCRoad;  //TDCRoad object
  
  int fnAllPeaks;
  int fnPeaks[n_inst][n_view];
  int fnAllClusters;
  int fnClusters[n_inst];
  int fnTrigWords;      // Number of triggers in the current event readout
  
  int fpeak_coord_hls;

  ap_ufixed<9, 6> fclust_coord_Y_hls;
  ap_fixed<9, 6> fclust_coord_X_hls;

  int fnPCalU_Masks;
  int fnHTCC_Masks;
  int fnFTOF_Masks;
  int fnCTOF_Masks;
  int fnCND_Masks;
  
  int ftrig_inst;
  ap_int<32> ftrig_lane;
  int ftrig_time;

  long long int ftrg_time;
  //ap_int<48> ftrg_time;

  void ResetAll();
  void ReadBlockHeader();
  void ReadBlockTrailer();
  void ReadEventHeader();
  void ReadTriggerTime();
  void ReadECTriggerPeak();                  // This will read EC/PCal Trigger peaks
  void ReadECTriggerCluster();               // This will read EC/PCal Trigger clusters
  void ReadPCalU();                          // This will read U strips in PCal that are above threshold
  void ReadHTCCTrigMask();                   // This will read HTCC Trigger mask
  void ReadFTOFTrigMask();                   // This will read FTOF Trigger mask
  void ReadCTOFTrigMask();                   // This will read CTOF Trigger mask
  void ReadCNDTrigMask();                    // This will read CND Trigger mask
  void ReadTrigger();
  void Check2ndlvltype();                    // Since we ran out of types, for type "1100" next 4 bits will be used for checking types
  void ReadDCRoad();                         // This method will read DCRoad VTP bank
  
  bool has_BlockHeader;
  bool has_BlockTrailer;
  bool has_EventHeader;
  bool has_TrigTime;
  bool has_TrigPeak;
  bool has_TrigClust;
  bool has_PCalU;
  bool has_Trigger;
  bool has_HTCCMask;
  bool has_FTOFMask;
  bool has_CTOFMask;
  bool has_CNDMask;
  bool has_DCRoad;

  static const unsigned short int type_blk_head = 0;
  static const unsigned short int type_blk_trail = 1;
  static const unsigned short int type_ev_head = 2;
  static const unsigned short int type_trig_time = 3;
  static const unsigned short int type_ECtrig_peak = 4;
  static const unsigned short int type_ECTrig_clust = 5;
  static const unsigned short int type_HTCC_clust = 6;
  static const unsigned short int type_FT_clust = 7;
  static const unsigned short int type_FTOF_clust = 8;
  static const unsigned short int type_CTOF_CLUSTER = 9;
  static const unsigned short int type_CND_CLUSTER = 10;
  
  static const unsigned short int type_PCalU = 11;
  static const unsigned short int type_trigger = 13;
  
  static const unsigned short int type_switch2ndlvl = 12;
  static const unsigned short int type_2ndlvl_DCroad = 0;
  

  static const int UNDEF = -9999;
//==================== When MC ======================  
  static const int MCadcECvtp_tagmax = 61120;
  static const int MCadcECvtp_tagmin = 60090;
  static const int DataadcECvtp_tagmax = 125;
  static const int DataadcECvtp_tagmin = 80;

  //==================== When MC ======================
//  static const int adcECvtp_tagmax = 115; // VTP bank tags are in the range 100 - 112
//  static const int adcECvtp_tagmin = 100; // VTP bank tags are in the range 100 - 112

  static map<int, int> EC_vtp_sector;   // Mapping tag number to the sector
  static map<int, int> EC_vtp_Detector;   // Mapping tag number to the Detector
};

#endif

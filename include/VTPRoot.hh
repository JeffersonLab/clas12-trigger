/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VTPRoot.hh
 * Author: rafopar
 *
 * Created on January 6, 2018, 4:47 PM
 */

#ifndef VTPROOT_HH
#define VTPROOT_HH

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
} THTCC_mask;

typedef struct{
    vector<int> chan;               // Vector of channels that are fired 
    int time;                       // time shows the channel in the readout window
} TFTOF_mask;

typedef struct{
    int tr_time;                    // trigger time with the 4ns resolution
    ap_int<32> tr_word;             // The trigger word
}Trig_word;


typedef struct{
    vector<int> sl;                 // Vector of SuperLayers that gave signal
    bool is_inbend;                 // Is the road inbending
    bool is_outbend;                // Is the road outbending
    bool is_valid;                  // Is the rad valid, i.e. did it match a lookup table
    int  time;
    vector<int> tof_match;          // Vector of channels in ftof that roads point to
} TDCRoad;



class VTPRoot {
public:
    VTPRoot();
    VTPRoot(vector<long> *, vector<long> *); // The constructor with vectors of crate IDs and words
    void SetVectors(vector<long> *, vector<long> *); // Sets vectors of crateIDs and words
    
    int GetNwords() { return has_BlockTrailer ? fnwords: UNDEF; }
    int GetSlotID() { return (has_BlockHeader || has_BlockTrailer) ? fslotid : UNDEF; }
    int GetEvNumber() { return has_EventHeader ? fev_number : UNDEF; }
    int GetBlockNUmber() {return has_BlockHeader ? fblock_number: UNDEF; }
    int GetBlockLevel() {return has_BlockHeader ? fblock_level: UNDEF; }
    
    int GetNHTCCMasks() {return fnHTCCMasks;};
    int GetNTrigWords() {return fnTrigWords;};
    
    int GetNECClusters(int);            // Number of EC clusters in the sector
    int GetNPCalClusters(int);          // Number of PCal clusters in the sector
    int GetNFTOFMasks(int);             // Number of FTOF masks in a corresponding sector
    int GetNECPeaks(int, int);          // Number of EC peaks, 1st argument is the sector [0-5], 2nd is the view (0=U, 1=V, 2=W)
    int GetNPCalPeaks(int, int);        // Number of PCal peaks, 1st argument is the sector [0-5], 2nd is the view (0=U, 1=V, 2=W)
    
    int GetNDCRoads(int );        // Return number of DC Roads in the sector asec
    bool IsRoadInbending(int asec, int aind); // Is the road in sector asec and given index aind is Inbending
    bool IsRoadOutbending(int asec, int aind); // Is the road in sector asec and given index aind is Outbending
    bool IsRoadValid(int asec, int aind); // Is the road in sector asec and given index aind is  Valid
    int GetRoadTime(int asec, int aind); // TIme of the road at the given sector and given index
    vector<int> *GetRoad_SLs(int asec, int aind); // Returns pointer of the vector of superlayers of roads of a givens sector and given index of that sector
    vector<int> *GetRoad_FTOFMatch(int asec, int aind); // Returns the pointer to the vector of FTOF channels of ROADs from a sector asec and index aind
    
    
    
    // The reason for returning pointer instead of an actual object is that, for the later case it will copy the object
    // in a new address, which requires more memory and CPU resources.
    TEC_Peak *GetECPeak(int asec, int aview, int aind);             // Return the pointer to the aind-th EC TEC_Peak in the sector sec, view aview
    TEC_Peak *GetPCalPeak(int asec, int aview, int aind);           // Return the pointer to the aind-th PCal TEC_Peak in the sector sec, view aview
    TEC_Cluster *GetECCluster(int asec, int aind);                  // Return the pointer to the aind-th EC TEC_Cluster in the sector sec
    TEC_Cluster *GetPCalCluster(int asec, int aind);                // Return the pointer to the aind-th PCal TEC_Cluster in the sector sec
    TFTOF_mask *GetFTOFMask(int asec, int aind);                    // Return the pointer to the aind-th FTOF mask of sector asec
    THTCC_mask *GetHTCCMask(int aind);                              // Return the pointer to the aind-th HTCC mask
    Trig_word  *GetTrigWord(int aind);                              // Return the pointer to the aind-th Trigger word

    // VTPRoot(const VTPRoot& orig);
    virtual ~VTPRoot();
private:

    void ResetAll();
    // This method should read the data corresponding the the "crate Crate_ID"
    void ReadCrate(int, int, int); // Crate_ID, index of the iterator, number of words

    void ReadBlockHeader();
    void ReadBlockTrailer();
    void ReadEventHeader();
    void ReadTriggerTime();
    void ReadECTriggerPeak(); // This will read EC/PCal Trigger peaks
    void ReadECTriggerCluster(); // This will read EC/PCal Trigger clusters
    void ReadHTCCTrigMask(); // This will read HTCC Trigger mask
    void ReadFTOFTrigMask(); // This will read FTOF Trigger mask
    void ReadTrigger();
    void Check2ndlvltype(); // Since we ran out of types, for type "1100" next 4 bits will be used for checking types
    void ReadDCRoad(); // This method will read DCRoad VTP bank
    
    
    bool HasBlockHeader() {return has_BlockHeader;};
    bool HasBlockTrailer() {return has_BlockTrailer;};
    bool HasEventHeader() {return has_EventHeader;};
    bool HasTrigTime() {return has_TrigTime;};
    bool HasTrigPeak() {return has_TrigPeak;};
    bool HasTrigClust() {return has_TrigClust;};
    bool HasTrigger() {return has_Trigger;};
    
    
    bool has_BlockHeader;
    bool has_BlockTrailer;
    bool has_EventHeader;
    bool has_TrigTime;
    bool has_TrigPeak;
    bool has_TrigClust;
    bool has_Trigger;
    bool has_HTCCMask;
    bool has_FTOFMask;
    bool has_DCRoad;
    
    long long int ftrg_time;
    int fDet; // The detector, 0 = global trigger, 1 = EC, 2 = PCal
    int fSector; // sector
    int fslotid; // slotid
    int fnwords;
    int fev_number;
    int fblock_number;
    int fblock_level;


    static const int nSect = 6; // Number of sectors
    static const int nView = 3; // Number of views in the Calorimeter
    static const int n_HTCC_chan = 48; // NUmber of HTCC channels;
    static const int n_FTOF_chan = 62; // NUmber of Max FTOF channels per sector/panel;
    static const int n_max_DC_segments = 6;                       // Number of maximum DC segments

    vector<long>::iterator fit_crates;
    vector<ap_int < 64 >> ::iterator fit_words;

    vector<long> *fv_CrID;
    vector<ap_int < 64 >> *fv_words; // Because of some reason, rhipo3 converts ints and longs from hipo as long, so for now it will be ap_in<64>

    static const unsigned short int type_blk_head = 0;
    static const unsigned short int type_blk_trail = 1;
    static const unsigned short int type_ev_head = 2;
    static const unsigned short int type_trig_time = 3;
    static const unsigned short int type_ECtrig_peak = 4;
    static const unsigned short int type_ECTrig_clust = 5;
    static const unsigned short int type_HTCC_clust = 6;
    static const unsigned short int type_FT_clust = 7;
    static const unsigned short int type_FTOF_clust = 8;

    static const unsigned short int type_CND_CLUSTER = 10;
    static const unsigned short int type_trigger = 13;
    static const unsigned short int type_switch2ndlvl = 12;
    static const unsigned short int type_2ndlvl_DCroad = 0;

  
    static const int UNDEF = -9999;   

    static map<int, int> EC_vtp_sector; // Mapping tag number to the sector
    static map<int, int> EC_vtp_Detector; // Mapping tag number to the Detector

    vector<TEC_Peak> fv_PCalPeaks[nSect][nView];                        // Vector of PCal peaks for a corresponding sector and view
    vector<TEC_Peak> fv_ECPeaks[nSect][nView];                          // Vector of EC peaks for a corresponding sector and view

    vector<TEC_Cluster> fv_PCalClusters[nSect];                         // vector of PCal clusters for a corresponding sector
    vector<TEC_Cluster> fv_ECClusters[nSect];                           // vector of EC clusters for a corresponding sector

    vector<THTCC_mask> fv_HTCCMasks;                                    // vector of HTCC masks
    
    vector<TFTOF_mask> fv_FTOFMasks[nSect];                             // vector of FTOF masks for the corresponding sector 
    
    vector<Trig_word> fv_TrigWords;                                     // Vector of trigger words in this event
    vector<TDCRoad>   fv_DCRoad[nSect];                                 // Vector of DC Roads
    
    TDCRoad fDCRoad;  //TDCRoad object
    
    int fnTrigWords; // Number of triggers in the current event readout
    int fnHTCCMasks; // Number of masks in HTCC VTP crate
    int fnFTOFMasks[nSect]; // Number of masks in FTOF VTP crate for a corresponding sector
    int fnECClusters[nSect]; // Number of EC clusters in VTP crate for a corresponding sector
    int fnPCalClusters[nSect]; // Number of PCal clusters in VTP crate for a corresponding sector
    int fnECPeaks[nSect][nView]; // Number of EC peaks in VTTP crate for the corresponding sector and view (u, v, w)
    int fnPCalPeaks[nSect][nView]; // Number of PCal peaks in VTTP crate for the corresponding sector and view (u, v, w)
    int fNDCRoads[nSect];            // Number of DCRoads in the event from a given sector 
//    int fnPCalPeaks[nSect][nView];
//    int fnECPeaks[nSect][nView];
//    
//    int fnPCalClusters[nSect];
//    int fnECClusters[nSect];
//    int fnTrigWords; // Number of triggers in the current event readout
//
//    int fnHTCC_Masks;                                   // Number of masks in HTCC VTP crate
//    int fnFTOF_Masks[nSect];
   
};

#endif /* VTPROOT_HH */


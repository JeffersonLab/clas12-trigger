#ifndef __ECTrig__
#define __ECTrig__

 #include <evioUtil.hxx>
// #include <evioFileChannel.hxx>
//class evio::evioDOMNode;

class TECTrig
{
public:
  TECTrig();
  TECTrig( evio::evioDOMNode*);
  int Sector() {return fSector;};
private:
  std::vector<uint32_t>::iterator fit_data;
  int fSector;
  int fslotid;
  int fblock_number;
  int fblock_level;
  
  long long int ftrig_time;
  
  void ReadBlockHeader();
  void ReadBlockTrailer();
  void ReadEventHeader();
  void ReadTriggerTime();
  void ReadECTriggerPeak();
  void ReadECTriggerCluster();
  void ReadTrigger();
  static const uint32_t chk_typedef = 2147483648; // bit 32 is 1, and all others are 0
  static const uint32_t typedef_bits = 2013265920; // bits 31, 30, 29 and 28 are 1, all others are 0
  static const uint32_t SLOTID_bits = 130023424; // bits 26:22 are 1, all others a 0
  static const uint32_t BLOCK_NUMBER_bits = 261888;
  static const uint32_t BLOCK_LEVEL_bits = 255;
  static const uint32_t TIMEL_bits = 16777215;
  static const uint32_t TIMEH_bits = 16777215;
  static const unsigned short int type_blk_head = 0;
  static const unsigned short int type_blk_trail = 1;
  static const unsigned short int type_ev_head = 2;
  static const unsigned short int type_trig_time = 3;
  static const unsigned short int type_ECtrig_peak = 4;
  static const unsigned short int type_ECTrig_clust = 5;
  static const unsigned short int type_trigger = 6;
};

#endif

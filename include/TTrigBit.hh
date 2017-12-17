/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TTrigBit.hh
 * Author: rafopar
 *
 * Created on December 15, 2017, 6:51 PM
 */

#ifndef TTRIGBIT_HH
#define TTRIGBIT_HH

#include <evioUtil.hxx>
#include <evioFileChannel.hxx>

#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_stream.h>

class TTrigBit {
public:
    TTrigBit();
    TTrigBit(evio::evioDOMNode*, int);
    //TTrigBit(const TTrigBit& orig);

    bool Main() {return ftrword.range(0, 0);};  // Return whether the main trigger is fired
    bool El_Sec(int); // return true if the electron trigger in the sector is fired, sect should be in the (0-5) range
    bool HTCC_Sec(int); // return true if the HTCC trigger in the sector is fired, sect should be in the (0-5) range
    bool PCal_Sec(int); // return true if the PCal trigger in the sector is fired, sect should be in the (0-5) range
    bool EC_Sec(int); // return true if the EC trigger in the sector is fired, sect should be in the (0-5) range
    bool HTCCPCal() {return ftrword.range(25, 25);}; // return true if the HTCC-PCal coincidence trigger is fired
    bool HTCCEC(){return ftrword.range(26, 26);}; // return true if the HTCC-EC coincidence trigger is fired
    bool PCalEC(){return ftrword.range(27, 27);};; // return true if the PCal-EC coincidence trigger is fired
    bool Pulser(){return ftrword.range(31, 31);};; // return true if the pulser trigger is fired
    bool GetBit(int i_bit) {return ftrword.range(i_bit, i_bit);}; // return bit i_bit
    
    void SetevioDOMENodeCrateID(evio::evioDOMNode*, int);
    void ResetAll();
    virtual ~TTrigBit();

    ap_int<32> funprscaled_trword;
    ap_int<32> ftrword;

private:

    static const int ftrig_crat_ID = 37;

    std::vector<ap_int<32> >::iterator fit_data;


};

#endif /* TTRIGBIT_HH */


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TTrigBit.cxx
 * Author: rafopar
 * 
 * Created on December 15, 2017, 6:51 PM
 */

#include "TTrigBit.hh"

TTrigBit::TTrigBit() {
}

TTrigBit::TTrigBit(evio::evioDOMNode* it, int a_crate_tag) {

    SetevioDOMENodeCrateID(it, a_crate_tag);
}

void TTrigBit::SetevioDOMENodeCrateID(evio::evioDOMNode* it, int a_crate_tag) {

    if (ftrig_crat_ID != a_crate_tag) {
        printf("Wrong tag number in %s, tag is %d Exiting \n", __func__, a_crate_tag);
        exit(0);
    }

    vector<ap_int<32> > *data_values = (vector<ap_int < 32 >> *)it->getVector<uint32_t>();

    // THis bank should have 7 words

    if (data_values->size() != 7) {
        printf("Wrong number of words in %s, NUmber of words should be 7, but it is  %d Exiting \n", __func__, int(data_values->size()));
        exit(0);
    }

    funprscaled_trword(31, 0) = (data_values->at(6)).range(31, 0);
    ftrword(31, 0) = (data_values->at(4)).range(31, 0);
    ftrword2(31, 0) = (data_values->at(5)).range(31, 0);
    ftrig_time = (int)(data_values->at(2)).range(31, 0);
}

// return true if the electron trigger in the sector is fired, sect should be in the (0-5) range

bool TTrigBit::El_Sec(int a_sec) {

    if (a_sec < 0 || a_sec > 5) {
        printf("Wrong sector is given %s, Sector should be in thr (0-5) range, but it is  %d Exiting \n", __func__, a_sec);
        exit(0);
    }
    return ftrword.range(1 + a_sec, 1 + a_sec);
}


// return true if the HTCC trigger in the sector is fired, sect should be in the (0-5) range
bool TTrigBit::HTCC_Sec(int a_sec) {

    if (a_sec < 0 || a_sec > 5) {
        printf("Wrong sector is given %s, Sector should be in thr (0-5) range, but it is  %d Exiting \n", __func__, a_sec);
        exit(0);
    }

    return ftrword.range(7 + a_sec, 7 + a_sec);
}

// return true if the PCal trigger in the sector is fired, sect should be in the (0-5) range
bool TTrigBit::PCal_Sec(int a_sec) {

    if (a_sec < 0 || a_sec > 5) {
        printf("Wrong sector is given %s, Sector should be in thr (0-5) range, but it is  %d Exiting \n", __func__, a_sec);
        exit(0);
    }

    return ftrword.range(13 + a_sec, 13 + a_sec);
}

// return true if the PCal trigger in the sector is fired, sect should be in the (0-5) range
bool TTrigBit::EC_Sec(int a_sec) {

    if (a_sec < 0 || a_sec > 5) {
        printf("Wrong sector is given %s, Sector should be in thr (0-5) range, but it is  %d Exiting \n", __func__, a_sec);
        exit(0);
    }

    return ftrword.range(19 + a_sec, 19 + a_sec);
}


//TTrigBit::TTrigBit(const TTrigBit& orig) {//
//}

TTrigBit::~TTrigBit() {
}

void TTrigBit::ResetAll() {
    funprscaled_trword = 0;
    ftrword = 0;
}
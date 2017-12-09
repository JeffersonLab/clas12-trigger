/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TCLAS12Cherenkov.cxx
 * Author: rafopar
 * 
 * Created on November 3, 2017, 10:01 AM
 */

#include "TCLAS12Cherenkov.hh"
#include <TMath.h>

TCLAS12Cherenkov::TCLAS12Cherenkov(){
    nphe_set = false;
    coord_set = false;
    time_set = false;
    all_set = false;
    fCoord[0] = fCoord[1] = fCoord[2] = -999.;

    fsect = -999;
}

TCLAS12Cherenkov::TCLAS12Cherenkov(int nphe, double x, double y, double z, double t){
    
    if( nphe < 0 ){
        printf("Error in %s: Number of photoelectrons must be a positive number \n", __func__); exit(1);
    }

    fNphe = nphe;
    fCoord[0] = x;
    fCoord[1] = y;
    fCoord[2] = z;
    ftime = t;

    fPhi = atan2(y, x)*TMath::RadToDeg() + 30.;
    if( fPhi < 0. ) {fPhi = fPhi + 360.;}
    fsect = fPhi/60.;

    
}

TCLAS12Cherenkov::TCLAS12Cherenkov(const TCLAS12Cherenkov& orig) {
}

TCLAS12Cherenkov::~TCLAS12Cherenkov() {
}


void TCLAS12Cherenkov::SetNphe(int nphe){

    if( nphe < 0 ){
        printf("Error in %s: Number of photoelectrons must be a positive number \n", __func__); exit(1);
    }
    
fNphe = nphe;

nphe_set = true;

all_set = nphe_set*coord_set*time_set;

}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TRECHB_particle.cc
 * Author: rafopar
 * 
 * Created on September 28, 2017, 2:30 PM
 */

#include "TRECHB_particle.hh"
#include <cmath>
#include <iostream>
#include <TMath.h>

using namespace std;

TRECHB_particle::TRECHB_particle() {
}
TRECHB_particle::TRECHB_particle(int pid, double px, double py, double pz, double vx, double vy, double vz, int charge) {
    fPID = pid;
    fPx = px;
    fPy = py;
    fPz = pz;
    fVx = vx;
    fVy = vy;
    fVz = vz;
    fcharge = charge;
    
    fP = sqrt( fPx*fPx + fPy*fPy + fPz*fPz );
   
    fPhi = atan2(fPy, fPz)*TMath::RadToDeg() + 30.;
    if( fPhi < 0.) {fPhi = fPhi + 360.;}
    
    fSect = int(fPhi/60.);
}


//TRECHB_particle::TRECHB_particle(const TRECHB_particle& orig) {
//}

TRECHB_particle::~TRECHB_particle() {
}


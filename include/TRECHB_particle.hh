/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TRECHB_particle.hh
 * Author: rafopar
 *
 * Created on September 28, 2017, 2:30 PM
 */

#ifndef TRECHB_PARTICLE_HH
#define TRECHB_PARTICLE_HH

#include <iostream>

using namespace std;

class TRECHB_particle {
public:
    TRECHB_particle();
    TRECHB_particle(int pid, double px, double py, double pz, double vx, double vy, double vz, int charge);
 //   TRECHB_particle(const TRECHB_particle& orig);
    virtual ~TRECHB_particle();
    
    double P(){ return fP;};
    double Px(){return fPx;};
    double Py(){return fPy;};
    double Pz(){return fPz;};
    double Vx(){return fVx;};
    double Vy(){return fVy;};
    double Vz(){return fVz;};
    int Charge(){return fcharge;};
    int PID(){return fPID;};
    
private:
    double fP;
    double fPx, fPy, fPz;
    double fVx, fVy, fVz;
    int fPID;
    int fcharge;
    double fPhi, fTheta;
    int fSect;
};

#endif /* TRECHB_PARTICLE_HH */


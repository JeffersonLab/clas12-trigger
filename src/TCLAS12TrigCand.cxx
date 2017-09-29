/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TCLAS12TrigCand.cxx
 * Author: rafopar
 * 
 * Created on September 26, 2017, 4:39 PM
 */

#include "TCLAS12TrigCand.hh"
#include <iostream>

using namespace std;

// ======== Defining Trigger Bits ============
//
//   1st bit, passed PCal energy threshold
//   2nd bit, passed ECal energy threshold
//   3rd , passed total calo (EC + PCal) energy threshold
//
// ==========================================

// ====== Some very loose trigger conditions =====
double TCLAS12TrigCand::fPCal_Emin = 0.02;
double TCLAS12TrigCand::ftot_Emin = 0.09;
double TCLAS12TrigCand::fEC_Emin = 0.05;

TCLAS12TrigCand::TCLAS12TrigCand() {
    
    // Initialize all flags as false
    
    has_PCal = false;
    has_ECin = false;
    has_ECout = false;
    has_HTCC = false;
    particle_set = false;
    EC_thresholds_set = false;
    
    is_analyzed = false;
    
    // All energies are set to 0
    fEPCal = fEECin = fEECout = fEECinout = fEECTot = 0.;
    
    // Initialize trigger bits to 0
    trig_bits = 0;
    }

//TCLAS12TrigCand::TCLAS12TrigCand(const TCLAS12TrigCand& orig) {
//}

TCLAS12TrigCand::~TCLAS12TrigCand() {
}

void TCLAS12TrigCand::SetPCalResponce(TCLAS12PCal PCal_responce){
fPCal_responce = PCal_responce;
has_PCal = true;
}

void TCLAS12TrigCand::SetECinResponce(TCLAS12ECin ECin_responce){
fECin_responce = ECin_responce;
has_ECin = true;
}
void TCLAS12TrigCand::SetECoutResponce(TCLAS12ECout ECout_responce){
fECout_responce = ECout_responce;
has_ECout = true;
}

void TCLAS12TrigCand::SetRecParticle( TRECHB_particle rec_part ){
    fP = rec_part.P();
    fPx = rec_part.Px();
    fPy = rec_part.Py();
    fPz = rec_part.Pz();
    fVx = rec_part.Vx();
    fVy = rec_part.Vy();
    fVz = rec_part.Vz();
    fPID = rec_part.PID();
    fcharge = rec_part.Charge();       
    
    //std::cout<<"fP in the TCLAS12TrigCand = "<<fP<<endl;
    particle_set = true;
}

void TCLAS12TrigCand::SetCaloThresholds(double PCal_Emin, double Etot_min, double EC_min){

fPCal_Emin = PCal_Emin;
ftot_Emin = Etot_min;
fEC_Emin = EC_min;
    
EC_thresholds_set = true;
}

int32_t TCLAS12TrigCand::Analyze(){

        // Let's 1st check if the RECHB_particle is supplied
    if( !particle_set ){
        printf("Error in %s: Particle is not set, The program is exiting \n", __func__); exit(1);
    }
    
    // Check if we have a signal from PCal
    if( has_PCal ){
    fEPCal = fPCal_responce.E();
    fEECTot = fEECTot + fEPCal;
        
        // If The PCal threshold is passed, the set the corresponding bit
        if( fEPCal > fPCal_Emin ){
          trig_bits = trig_bits|1<<0;
        }
    }
    
    // Check if we have a signal from ECin
    if( has_ECin ){
        fEECin = fECin_responce.E();
        fEECTot = fEECTot + fEECin;
        fEECinout = fEECinout + fEECin;
    }
    
    // Check if we have a signal from ECout
    if( has_ECout ){
        fEECout = fECout_responce.E();
        fEECTot = fEECTot + fEECout;
        fEECinout = fEECinout + fEECout;
    }
    
    // If the total energy in the EC (excluding PCal) is more than the threshold, then set the corresponding bit
    if(fEECinout > fEC_Emin){
        trig_bits = trig_bits|1<<1;
    }
    
     // If the total energy in the whole calo (EC + PCal) is more than the threshold, then set the corresponding bit
    if(fEECinout > fEC_Emin){
        trig_bits = trig_bits|1<<2;
    }
   
    is_analyzed = true;
    
    return trig_bits;
}


int32_t TCLAS12TrigCand::GetBitset(){
    if( !is_analyzed ){
         printf("Error in %s: The TrigCandidate is not analyzed \n "
                 "Please 1st Analyze \"TCLAS12TrigCand::Analyze()\", The program is exiting \n", __func__); exit(1);
    }
    
    return trig_bits;
}
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TCLAS12TrigCand.hh
 * Author: rafopar
 *
 * Created on September 26, 2017, 4:39 PM
 */

#ifndef TCLAS12TRIGCAND_HH
#define TCLAS12TRIGCAND_HH

#include "TCLAS12Calo.hh"
#include <TRECHB_particle.hh>
#include <stdint.h>

// Although PCal ECin and ECout have same structure and are represented with the same
// CLASS, it is better to make a distinction between them for avoiding later confusion.
//typedef TCLAS12Calo TCLAS12PCal;
//typedef TCLAS12Calo TCLAS12ECin;
//typedef TCLAS12Calo TCLAS12ECout;

class TCLAS12TrigCand {
public:
    TCLAS12TrigCand();
    //TCLAS12TrigCand(const TCLAS12TrigCand& orig);
    virtual ~TCLAS12TrigCand();
    
    void SetPCalResponce(TCLAS12PCal);
    void SetECinResponce(TCLAS12ECin);
    void SetECoutResponce(TCLAS12ECout);
    
    void SetRecParticle(TRECHB_particle);
    
    void SetCaloThresholds(double, double, double); // PCal Emin, Etot_min, EC_min
    
    static double fPCal_Emin;  // Threshold for the PCal energy minimum
    static double ftot_Emin;   // Threshold for the total energy in PCal plus ECal
    static double fEC_Emin;     // Threshold for the total energy in EC only
    
    bool HasPCal() {return has_PCal;};
    bool HasECin() {return has_ECin;};
    bool HasECout() {return has_ECout;};
    bool HasHTCC() {return has_HTCC;};
    
    // This method should analyze the data supplied from different recon collections (e.g. RECHB_PCAL, RECHB_particle etc)
    // and should return integer representing the bitset of found triggers
    // 0 means no trigger is found
    int32_t Analyze();
    
    int32_t GetBitset();
    
    double P(){return fP;};
    double Px(){return fPx;};
    double Py(){return fPy;};
    double Pz(){return fPz;};
    double Vx(){return fVx;};
    double Vy(){return fVy;};
    double Vz(){return fVz;};
    int Charge(){return fcharge;};
    int PID(){return fPID;};

    double Etot(){return fEECTot;};
    double EPCal(){return fEPCal;};
    double EECinout(){return fEECinout;};
    double EECin(){return fEECin;};
    double EECout(){return fEECout;};
    
private:
    TCLAS12PCal fPCal_responce;
    TCLAS12ECin fECin_responce;
    TCLAS12ECout fECout_responce;

    bool EC_thresholds_set;
    bool has_PCal;
    bool has_ECin;
    bool has_ECout;
    bool has_HTCC;
    bool particle_set;  // Flag checking whether the particle info (px, py, pz, pid etc...) is set
    
    bool is_analyzed;
    
    // ====== Calorimeter related variables ======
    double fEPCal;   // Energy in the PCal
    double fEECin;   // Energy in the ECin
    double fEECout;  // Energy in the ECout
    double fEECinout;  // ENergy in the EC (Excluding PCal)
    double fEECTot;  // Total deposited energy in PCal and EC
    
    //======= REC particle related variables ===========
    double fP;
    double fPx, fPy, fPz;
    double fVx, fVy, fVz;
    int fPID;
    int fcharge;    

    
    
    int32_t trig_bits;  // The trigger bits
//
    
};

#endif /* TCLAS12TRIGCAND_HH */
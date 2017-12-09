/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TCLAS12Cherenkov.hh
 * Author: rafopar
 *
 * Created on November 3, 2017, 10:01 AM
 */

#ifndef TCLAS12CHERENKOV_HH
#define TCLAS12CHERENKOV_HH

#include <TCLAS12Detector.hh>

class TCLAS12Cherenkov: public TCLAS12Detector {
public:
    TCLAS12Cherenkov();
    TCLAS12Cherenkov(int, double, double, double, double);  // nphe, x, y, z, time
    TCLAS12Cherenkov(const TCLAS12Cherenkov& orig);
    virtual ~TCLAS12Cherenkov();
    
    void SetNphe(int);           // Sets the number of photoelectrons
    
    int Nphe() {return fNphe;}; // Return number of photoelectrons
    
private:
    
    int fsect;
    bool nphe_set;

    int fNphe;
};

typedef TCLAS12Cherenkov TCLAS12HTCC;

#endif /* TCLAS12CHERENKOV_HH */


#include <TCLAS12Calo.hh>
#include <TMath.h>
#include <cmath>

TCLAS12Calo::TCLAS12Calo(){
  Energy_set = false;
  coord_set = false;
  time_set = false;
  all_set = false;
  fCoord[0] = fCoord[1] = fCoord[2] = -999.;
  fE = -999.;
  fsect = -999;
}

TCLAS12Calo::TCLAS12Calo(double E, double x, double y, double z, double t){
  fE = E;
  fCoord[0] = x;
  fCoord[1] = y;
  fCoord[2] = z;
  ftime = t;

  fPhi = atan2(y, x)*TMath::RadToDeg() + 30.;
  if( fPhi < 0. ) {fPhi = fPhi + 360.;}
  fsect = fPhi/60.;

  coord_set = true;
  time_set = true;
  Energy_set = true;
  all_set = coord_set*time_set*Energy_set;
}

void TCLAS12Calo::SetEXYZT(double E, double x, double y , double z, double t){
    fE = E;
    fCoord[0] = x;
    fCoord[1] = y;
    fCoord[2] = z;
    ftime = t;

    fPhi = atan2(y, x)*TMath::RadToDeg() + 30.;
    if( fPhi < 0. ) {fPhi = fPhi + 360.;}
    fsect = fPhi/60.;

    coord_set = true;
    time_set = true;
    Energy_set = true;
    all_set = coord_set*time_set*Energy_set;

}


void TCLAS12Calo::SetXYZ( double x, double y , double z){

    fCoord[0] = x;
    fCoord[1] = y;
    fCoord[2] = z;
    
     fPhi = atan2(y, x)*TMath::RadToDeg() + 30.;
    if( fPhi < 0. ) {fPhi = fPhi + 360.;}

    coord_set = true;
    all_set = coord_set*time_set*Energy_set;
}

void TCLAS12Calo::SetE(double E){
  fE = E;
  Energy_set = true;
  all_set = coord_set*time_set*Energy_set;
}

void TCLAS12Calo::SetTime(double t){
  ftime = t;
  time_set = true;
  all_set = coord_set*time_set*Energy_set;
}

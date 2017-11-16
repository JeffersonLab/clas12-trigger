#include <ECGeom.hh>
#include <cmath>
#include <iostream>
#include <TMath.h>

using namespace std;

// Init some const static data members
const double TECGeom::fLU = 419.239839; // cm
const double TECGeom::fLV = 383.0062897; // cm
const double TECGeom::fLW = 419.239839; // cm
//const double TECGeom::fSCWidth = 10.; // cm
const double TECGeom::fdU = 10.366; // cm
const double TECGeom::fdV = 9.48; // cm
const double TECGeom::fdW = 9.48; // cm
const double TECGeom::fPhalf = 0.5*(TECGeom::fLU + TECGeom::fLV + TECGeom::fLU );
const double TECGeom::fS = sqrt(TECGeom::fPhalf*(TECGeom::fPhalf - TECGeom::fLU)*(TECGeom::fPhalf - TECGeom::fLV)
				*(TECGeom::fPhalf - TECGeom::fLW));

const double TECGeom::falpha_U = asin(2*TECGeom::fS/(TECGeom::fLU*TECGeom::fLW));
const double TECGeom::falpha_V = asin(2*TECGeom::fS/(TECGeom::fLV*TECGeom::fLU));
const double TECGeom::falpha_W = asin(2*TECGeom::fS/(TECGeom::fLW*TECGeom::fLV));

const double TECGeom::fy0_U = 0.;
const double TECGeom::fx0_U = 0.;
const double TECGeom::fy0_V = TECGeom::fLU*sin(TECGeom::falpha_V);
const double TECGeom::fx0_V = TECGeom::fLU*cos(TECGeom::falpha_V);
const double TECGeom::fy0_W = TECGeom::fLW*sin(TECGeom::falpha_W);
const double TECGeom::fx0_W = -TECGeom::fLW*cos(TECGeom::falpha_W);

const double TECGeom::d2r =  0.017453;
const double TECGeom::EC_angle = 25*TECGeom::d2r;
const double TECGeom::fy0 = 50.7601930;
const double TECGeom::fz0 = 786.4028205; // It is calculated as 7127.23/cos(25*TMath::DegToRad())

TECGeom::TECGeom(double aU, double aV, double aW){
    
  fSector = -1;
    
  fU = aU*fdU/sin(falpha_V);
  fV = aV*fdV/sin(falpha_W);
  fW = aW*fdW/sin(falpha_U);

  fDalitz = fU/fLU + fV/fLV + fW/fLW - 2.;

  // cout<<"ECGEOM fSCWidth "<<fSCWidth<<endl;
  // cout<<"ECGEOM "<<aU<<"  "<<aV<<"  "<<aW<<"  "<<fU<<"  "<<fV<<"  "<<fW<<"  "<<endl;
  // cout<<"ECGEOM ALPHAS "<<falpha_U*TMath::RadToDeg()<<"   "<<falpha_U*TMath::RadToDeg()<<"  "<<falpha_W*TMath::RadToDeg()<<"  "<<fDalitz<<endl;
  
  fx_UV = fx0_V - fV + (fLU - fU)*sin(falpha_V)/tan(falpha_W);
  fy_UV = fU*sin(falpha_V);

  fx_UW = fx0_V - (fLU - fU)*cos(falpha_V) - ( fLV - fW*(fLV/fLW) ); 
  //fx_UW = fx0_V - (fLV/fLW)*fW + fLU*cos(falpha_V)*(fLU - fU)/fLU;
  fy_UW = fU*sin(falpha_V);
  
  double u_calc = fLU*(2. - fV/fLV - fW/fLW);  // Using Dalitz rule calculate U, and then calculate x as UW
  //fx_VW = fx0_V - (fLV/fLW)*fW + fLU*cos(falpha_V)*(fLU - u_calc)/fLU;
  fx_VW = fx0_V - (fLU - u_calc)*cos(falpha_V) - ( fLV - fW*(fLV/fLW) );
  fy_VW = u_calc*sin(falpha_V);

  //====== According to Ben's algorithm the cluster coordinate is the mean of uv, uw and vw
  fy = (fy_UV + fy_UW + fy_VW)/3.;
  fx = (fx_UV + fx_UW + fx_VW)/3.;
}


void TECGeom::SetSector(int aSect){

    if( aSect < 0 || aSect > 5 ){
        printf("Wrong Sector is specified %s, Exiting", __func__);
        cout<<"Sector should be in the range between 0 and 5"<<endl;
        exit(0);
    }

    fSector = aSect;

   GetHallCoordinates(fx_UW, fy_UW, &fx_UW_Hall, &fy_UW_Hall, &fz_UW_Hall);
   GetHallCoordinates(fx_UV, fy_UV, &fx_UV_Hall, &fy_UV_Hall, &fz_UV_Hall);
   GetHallCoordinates(fx_VW, fy_UV, &fx_VW_Hall, &fy_VW_Hall, &fz_VW_Hall);
}

void TECGeom::GetHallCoordinates(double ax, double ay, double *out_x_glob, double *out_y_glob, double *out_z_glob){
    
    // ==== Going from local coordinates to L2 where, only EC is tilted by 25 deg
    double yl2 = (TECGeom::fy0 + ay)*cos(EC_angle);
    double xl2 = ax;
    double zl2 = fz0 - (TECGeom::fy0 + ay)*sin(EC_angle);
        
    // ==== Going from L2 to Global, this is basically rotation along the z axis
    
    double phi = (60*fSector - 90)*TECGeom::d2r;
    
    *out_x_glob = xl2*cos(phi) - yl2*sin(phi);
    *out_y_glob = xl2*sin(phi) + yl2*cos(phi);
    *out_z_glob = zl2;
}
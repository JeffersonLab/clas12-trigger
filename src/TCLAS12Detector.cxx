#include <TCLAS12Detector.hh>
#include <cmath>

using namespace std;

TCLAS12Detector::TCLAS12Detector(){
  all_set = false;
  coord_set = false;
  time_set = false;
  fPhi = -999.;
  ftime = -999.;
}

void TCLAS12Detector::SetXYZ(double x, double y, double z){
  fCoord[0] = x;
  fCoord[1] = y;
  fCoord[2] = z;

  fPhi = atan2(y, x) + 30.;
  if( fPhi < 0. ) {fPhi = fPhi + 360.;}
  coord_set = true;
}

void TCLAS12Detector::SetTime(double t){
  ftime = t;
  time_set = true;
}

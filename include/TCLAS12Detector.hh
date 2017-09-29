#ifndef __TCLAS12DETECTOR__
#define __TCLAS12DETECTOR__


class TCLAS12Detector{
  
public:
  TCLAS12Detector();

  void  SetXYZ(double, double, double); // Set the coordinated of the hit/cluster or a corresponding quantity for that detector
  void  SetTime(double);                // Set the time of the hit/cluster or a corresponding quantity for that detector
  
  double Time() {return ftime;};
  double* Coord() {return fCoord;};
  double X() {return fCoord[0];};
  double Y() {return fCoord[1];};
  double Z() {return fCoord[2];};

protected:
  double fCoord[3];      // coordinates of hit/cluster or a relative quantity
  double ftime;          // time of the hit/cluster or a relative quantity
  double fPhi;           // Azimuthal angle of the hit/cluster

  bool all_set;          // A flage that checks whether all the nencesarry information from that detector is set by the user
  bool coord_set;        // A flag that telles whether coordinates are set
  bool time_set;         // A flag that tells whether the time is set
};


#endif

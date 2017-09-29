#ifndef __TCLAS12CALO__
#define __TCLAS12CALO__

#include <TCLAS12Detector.hh>
 


class TCLAS12Calo: public TCLAS12Detector{

public:
  TCLAS12Calo();
  TCLAS12Calo(double, double, double, double, double); // E, X, Y, Z and t
  void SetE(double); // Set energy of the cluster
  double E() {return fE;};
  
private:

  bool Energy_set;
  double fE;
  int fsect;

};

typedef TCLAS12Calo TCLAS12PCal;
typedef TCLAS12Calo TCLAS12ECin;
typedef TCLAS12Calo TCLAS12ECout;


#endif

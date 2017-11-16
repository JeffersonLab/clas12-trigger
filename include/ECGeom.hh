#ifndef __ECGeom__
#define __ECGeom__

class TECGeom{

public:
  TECGeom(double, double, double); // U, V, W
  const double GetX() {return fx;}
  const double GetY() {return fy;}
  const double GetDalitz() {return fDalitz;}
  const double GetY_UV() {return fy_UV;}
  const double GetX_UV() {return fx_UV;}
  const double GetY_UW() {return fy_UW;}
  const double GetX_UW() {return fx_UW;}
  const double GetY_VW() {return fy_VW;}
  const double GetX_VW() {return fx_VW;}
  const double GetLU() {return fLU;} // Length of U side
  const double GetLV() {return fLV;} // Length of V side
  const double GetLW() {return fLW;} // Length of W side
  
  const double GetHallX_UV() {return fx_UV_Hall;};
  const double GetHallY_UV() {return fy_UV_Hall;};
  const double GetHallZ_UV() {return fz_UV_Hall;};
  const double GetHallX_UW() {return fx_UW_Hall;};
  const double GetHallY_UW() {return fy_UW_Hall;};
  const double GetHallZ_UW() {return fz_UW_Hall;};
  const double GetHallX_VW() {return fx_VW_Hall;};
  const double GetHallY_VW() {return fy_VW_Hall;};
  const double GetHallZ_VW() {return fz_VW_Hall;};
  void SetSector(int); // Sets the sector and integer in the range 0 - 5
  
private:

 void GetHallCoordinates(double, double, double *, double *, double*); // Using the sector, and local (x,y) calculate the global x coordinate in the Hall coordinate frame
    
    
  int fSector;
    
  double fx, fy;        // local variables
  double fU, fV, fW;    // U, V and W coordinates
  double fDalitz;       // Dalitz, note 2 is subtracted, so it is expected to be peaked at 0

  double fx_Hall, fy_Hall, fz_Hall; // x, y and z coordinates in the Hall Frame where (0., 0., 0) is the target center and z is along th beamline
  
  double fx_UV, fy_UV; // cluster coordinate calculated through U and V peaks
  double fx_UW, fy_UW; // cluster coordinate calculated through U and W peaks
  double fx_VW, fy_VW; // cluster coordinate calculated through V and W peaks

  double fx_UV_Hall, fy_UV_Hall, fz_UV_Hall; //cluster coordinate in the Hall Frame, calculated through U and V peaks
  double fx_UW_Hall, fy_UW_Hall, fz_UW_Hall; //cluster coordinate in the Hall Frame, calculated through U and V peaks
  double fx_VW_Hall, fy_VW_Hall, fz_VW_Hall; //cluster coordinate in the Hall Frame, calculated through U and V peaks

  static const double d2r;
  static const double EC_angle;
  static const double fy0;  // The distance from the U vertex and the beamline in the EC front plane
  static const double fz0;  // z coordinate of the intersection of the EC Plane and the beamline
  
  //========== Lengths of U, V and W sides =========
  static const double fLU;
  static const double fLV;
  static const double fLW;

  //========== Half od the perimeter, and the area of the triangle =======
  static const double fPhalf;
  static const double fS;

  //========== Angles of U, V and W vertexes =======
  static const double falpha_U;
  static const double falpha_V;
  static const double falpha_W;

  //========= coordinates of U, V and W vertexes =========
  static const double fx0_U;
  static const double fy0_U;
  static const double fx0_V;
  static const double fy0_V;
  static const double fx0_W;
  static const double fy0_W;

  //========= Width of a scintilliator =========
  static const double fSCWidth;
  static const double fdU;
  static const double fdV;
  static const double fdW;
};

#endif

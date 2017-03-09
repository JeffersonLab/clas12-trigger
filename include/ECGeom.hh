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
  
private:

  double fx, fy;
  double fU, fV, fW;
  double fDalitz;

  double fx_UV, fy_UV; // cluster coordinate calculated through U and V peaaks
  double fx_UW, fy_UW; // cluster coordinate calculated through U and W peaaks
  double fx_VW, fy_VW; // cluster coordinate calculated through V and W peaaks

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
};

#endif

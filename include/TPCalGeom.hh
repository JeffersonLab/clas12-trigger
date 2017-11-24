/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TPCalGeom.hh
 * Author: rafopar
 *
 * Created on November 19, 2017, 5:43 PM
 */

#ifndef TPCALGEOM_HH
#define TPCALGEOM_HH

class TPCalGeom
{
public:
    TPCalGeom(double, double, double); // U, V and W represent readout channel index

      const double GetDalitz(){return fDalitz;};
      const double GetY_UV() {return fy_UV;}
      const double GetX_UV() {return fx_UV;}
      const double GetY_UW() {return fy_UW;}
      const double GetX_UW() {return fx_UW;}
      const double GetY_VW() {return fy_VW;}
      const double GetX_VW() {return fx_VW;}

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
    // TPCalGeom(const TPCalGeom& orig);
    virtual ~TPCalGeom();

private:

    // Using the sector, and local (x,y) calculate the global x,y,z coordinates in the Hall coordinate frame
    void GetHallCoordinates(double, double, double *, double *, double*);

    static const double d2r;
    static const double alpha_base; // The angle between the base and scales of the triagle
    static const double PCal_angle; // The angle between the PCal plane and the beamline
    static const double fz0; // z coordinate of the intersection of the EC Plane and the beamline
    static const double fyShift; // to Shift Y local coordinates in a way, that y=0 will be in the beam level plane
    static const double fdU; // Average width of U strips
    static const double fdV; // Average width of V strips
    static const double fdW; // Average width of W strips

    static const int fNUStrips = 84; // Number of U strips
    static const int fNVStrips = 78; // Number of V strips
    static const int fNWStrips = 78; // Number of W strips
    static const int fNUsingle = 52; // Number of single readout strips in U
    static const int fNVsingle = 46; // Number of single readout strips in U
    static const int fNWsingle = 46; // Number of single readout strips in U

    // ==== Following variables are defined in the page 17 of PCal Geometry Note (Section 5)

    static const double fb; // Length of the base of the PCal (shortest side)
    static const double fside; // Length of the side of the PCal (length of a isoscele)
    static const double fh; // Height of the PCal triangle
    static const double fxl; // X Left
    static const double fxr; // X Right
    static const double fyh; // Y Low
    static const double fyl; // Y High

    // ==== Relevant Coordinates of shortest strips

    static const double fy0_U; // Y coordinate of the Shortest U strip
    static const double fx0_V; // X coordinate of the shortest V strip
    static const double fx0_W; // X coordinate of the shortest W strip

    // == sector
    int fSector;

    // == local coordinates, x, y in a Cartesian, and fU,fV, fW are along the edges of the triangle
    double fx, fy; // local variables
    double fU, fV, fW; // U, V and W coordinates
    double fyU; // Y coordinate of a U Strip On the side of the triangle (Actually All points in a U strip have the same Y)
    double fxV; // x coordinate of the V strip on the base of the triangle
    double fxW; // x coordinate of the W strip on the base of the triangle

    // == The Dalitz
    double fDalitz; // Dalitz, note 2 is subtracted, so it is expected to be peaked at 0

    double fx_UV, fy_UV; // cluster coordinate calculated through U and V peaks
    double fx_UW, fy_UW; // cluster coordinate calculated through U and W peaks
    double fx_VW, fy_VW; // cluster coordinate calculated through V and W peaks

    double fx_UV_Hall, fy_UV_Hall, fz_UV_Hall; //cluster coordinate in the Hall Frame, calculated through U and V peaks
    double fx_UW_Hall, fy_UW_Hall, fz_UW_Hall; //cluster coordinate in the Hall Frame, calculated through U and V peaks
    double fx_VW_Hall, fy_VW_Hall, fz_VW_Hall; //cluster coordinate in the Hall Frame, calculated through U and V peaks

};

#endif /* TPCALGEOM_HH */


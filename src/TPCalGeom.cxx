/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TPCalGeom.cxx
 * Author: rafopar
 * 
 * Created on November 19, 2017, 5:43 PM
 */

// The PCal Geometry properties are taken from the PCal Geometry note, accesible
// in this link "https://clasweb.jlab.org/wiki/images/d/d0/Pcal_geometry_note.pdf"

#include "TPCalGeom.hh"
#include <iostream>
#include <cmath>

using namespace std;

const double TPCalGeom::d2r = 0.017453;
const double TPCalGeom::alpha_base = 62.89 * TPCalGeom::d2r;
const double TPCalGeom::PCal_angle = 25 * TPCalGeom::d2r;
const double TPCalGeom::fdU = 4.52; // Average width of U strips in cm
const double TPCalGeom::fdV = 4.505; // Average width of V strips in cm
const double TPCalGeom::fdW = 4.51; // Average width of W strips in cm

const double TPCalGeom::fb = 394.2; // Length of the Base of the PCal triangle
const double TPCalGeom::fside = 0.5 * TPCalGeom::fb / cos(alpha_base); // The length of a side (սրունք) of a triangle
const double TPCalGeom::fh = 385.2; // Height of the PCal triangle
const double TPCalGeom::fxl = TPCalGeom::fb / 2.; // x coordinate of the left vertex of the triangle
const double TPCalGeom::fxr = -TPCalGeom::fb / 2.; // x coordinate of the Right vertex of the triangle
const double TPCalGeom::fyh = 94.4; // Y coordinate of the base of the triangle (All points have the same y)
const double TPCalGeom::fyl = -290.8; // Y coordinate of the vertex closest to the beamline

const double TPCalGeom::fy0_U = TPCalGeom::fyh - double(TPCalGeom::fNUStrips) * TPCalGeom::fdU; // Y coordinate of the Shortest U strip
const double TPCalGeom::fx0_V = TPCalGeom::fxl - double(TPCalGeom::fNVStrips) * TPCalGeom::fdV / sin(alpha_base); // X coordinate of the Shortest V strip 
const double TPCalGeom::fx0_W = TPCalGeom::fxr + double(TPCalGeom::fNWStrips) * TPCalGeom::fdW / sin(alpha_base); // X coordinate of the Shortest W strip 
const double TPCalGeom::fz0 = 764.1995467 + 5.; // It is calculated as 6926/cos(25*TMath::DegToRad()), 5 I coming from comparing with GEMC
const double TPCalGeom::fyShift = 322.9646840 + 9.220069; // It is calculated as 6926*tan(25*TMath::DegToRad()), 9.22 is obtained through comparing to GEM

TPCalGeom::TPCalGeom(double aU, double aV, double aW) // aU, aV, and aW represent the strip index
{

    fSector = -1;

    fU = aU * fdU / sin(alpha_base);
    fV = aV * fdV / sin(alpha_base);
    fW = aW * fdW / sin(alpha_base);

    //fDalitz = fU / fside + fV / fb + fW / fb - 2.;
    fDalitz = aU / double(fNUStrips) + aV / double(fNVStrips) + aW / double(fNWStrips) - 2.;

    fyU = fy0_U + aU * fdU;
    fxV = fx0_V + fV;
    fxW = fx0_W - fW;

    fy_UV = fyU;
    fx_UV = fxV - (fyh - fy_UV) / tan(alpha_base);

    fy_UW = fyU;
    fx_UW = fxW + (fyh - fy_UV) / tan(alpha_base);

    fx_VW = 0.5 * (fxV + fxW);
    fy_VW = fyh - (fxV - fx_VW) * tan(alpha_base);
}

//TPCalGeom::TPCalGeom(const TPCalGeom& orig) {
//}

TPCalGeom::~TPCalGeom() {
}

void TPCalGeom::GetHallCoordinates(double ax, double ay, double *out_x_glob, double *out_y_glob, double *out_z_glob) {

    // Note: Unlike EC, in the case of PCal, y coordinates represent 

    // ==== Going from local coordinates to L2 where, only PCal is tilted by 25 deg
    double yl1 = fyShift + ay;
    double yl2 = yl1 * cos(TPCalGeom::PCal_angle);
    double xl2 = ax;
    double zl2 = fz0 - yl2 * sin(TPCalGeom::PCal_angle);

    // ==== Going from L2 to Global, this is basically rotation along the z axis

    double phi = (60 * fSector - 90) * TPCalGeom::d2r;

    *out_x_glob = xl2 * cos(phi) - yl2 * sin(phi);
    *out_y_glob = xl2 * sin(phi) + yl2 * cos(phi);
    *out_z_glob = zl2;
}

void TPCalGeom::SetSector(int aSect) {
    if (aSect < 0 || aSect > 5) {
        printf("Wrong Sector is specified %s, Exiting", __func__);
        cout << "Sector should be in the range between 0 and 5" << endl;
        exit(0);
    }

    fSector = aSect;

    GetHallCoordinates(fx_UV, fy_UV, &fx_UV_Hall, &fy_UV_Hall, &fz_UV_Hall);
    GetHallCoordinates(fx_UW, fy_UW, &fx_UW_Hall, &fy_UW_Hall, &fz_UW_Hall);
    GetHallCoordinates(fx_VW, fy_VW, &fx_VW_Hall, &fy_VW_Hall, &fz_VW_Hall);
}
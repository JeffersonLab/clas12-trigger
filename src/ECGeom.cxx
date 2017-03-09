#include <ECGeom.hh>
#include <cmath>
using namespace std;

// Init some const static data members
const double TECGeom::fLU = 415.692;
const double TECGeom::fLV = 415.692;
const double TECGeom::fLW = 415.692;
const double TECGeom::fPhalf = 0.5*(TECGeom::fLU + TECGeom::fLV + TECGeom::fLU );
const double TECGeom::fS = sqrt(TECGeom::fPhalf*(TECGeom::fPhalf - TECGeom::fLU)*(TECGeom::fPhalf - TECGeom::fLV)
				*(TECGeom::fPhalf - TECGeom::fLW));

const double TECGeom::falpha_U = asin(2*TECGeom::fS/(TECGeom::fLU*TECGeom::fLW));
const double TECGeom::falpha_V = asin(2*TECGeom::fS/(TECGeom::fLV*TECGeom::fLU));
const double TECGeom::falpha_W = asin(2*TECGeom::fS/(TECGeom::fLW*TECGeom::fLV));

const double TECGeom::fy0_U = 0.;
const double TECGeom::fx0_U = 0.;
const double TECGeom::fy0_V = TECGeom::fLV*sin(TECGeom::falpha_V);
const double TECGeom::fx0_V = -TECGeom::fLV*cos(TECGeom::falpha_V);
const double TECGeom::fy0_W = TECGeom::fLW*sin(TECGeom::falpha_W);
const double TECGeom::fx0_W = TECGeom::fLW*cos(TECGeom::falpha_W);

TECGeom::TECGeom(double aU, double aV, double aW){
  fU = aU;
  fV = aV;
  fW = aW;

  fDalitz = fU/fLU + fV/fLV + fW/fLW - 2.;

  fx_UV = fx0_V + fV - (fLU - fU)*sin(falpha_V)/tan(falpha_W);
  fy_UV = fU*sin(falpha_V);

  fx_UW = fx0_V - (fLV/fLW)*fW + fLU*cos(falpha_V)*(fLU - fU)/fLU;
  fy_UW = fU*sin(falpha_V);
  
  double u_calc = fLU*(2. - fV/fLV - fW/fLW);  // Using Dalitz rule calculate U, and then calculate x as UW
  fx_VW = fx0_V - (fLV/fLW)*fW + fLU*cos(falpha_V)*(fLU - u_calc)/fLU;
  fy_VW = u_calc*sin(falpha_V);

  //====== According to Ben's algorithm the cluster coordinate is the mean of uv, uw and vw
  fy = (fy_UV + fy_UW + fy_VW)/3.;
  fx = (fx_UV + fx_UW + fx_VW)/3.;
}

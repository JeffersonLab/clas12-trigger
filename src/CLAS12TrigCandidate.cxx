#include <CLAS12TrigCandidate.hh>
#include <TMath.h>
#include <math.h>


// Default constructor
CLAS12TrigCandidate::CLAS12TrigCandidate(){
  fPCal_index = fECin_index = fECout_index = fSector = - 1;
  fPx = fPy = fPz = fP = -999.;
  is_ECalFully_initalized = false;
  ECal_indexes_known = false;
  has_CC = false;
}

CLAS12TrigCandidate::CLAS12TrigCandidate( int RECHB_index, int ind_PCal, int ind_ECin, int ind_ECout ){

  is_ECalFully_initalized = false;
  ECal_indexes_known = true;
  fRECHB_part_index = RECHB_index;
  fPCal_index = ind_PCal;
  fECin_index = ind_ECin;
  fECout_index = ind_ECout;
}

void CLAS12TrigCandidate::SetCalorimeterExyzt(vector<float> *E, vector<float> *x, vector<float> *y, vector<float> *z,  vector<float> *t){

  if( !ECal_indexes_known ){
    printf("Error in %s: ECal indexes are not set, Exiting \n", __func__); exit(1);
  }
  
  // ===== Energies ========
  fEnergy[0] = E->at(fPCal_index);
  fEnergy[1] = E->at(fECin_index);
  fEnergy[2] = E->at(fECout_index);

  fTotE = fEnergy[0] + fEnergy[1] + fEnergy[2];
    
  // ===== Coordinates X =====
  
  fx[0] = x->at(fPCal_index);
  fx[1] = x->at(fECin_index);
  fx[2] = x->at(fECout_index);

  // ===== Coordinates Y =====
  fy[0] = y->at(fPCal_index);
  fy[1] = y->at(fECin_index);
  fy[1] = y->at(fECout_index);
  
  // ===== Coordinates Z =====
  fz[0] = z->at(fPCal_index);
  fz[1] = z->at(fECin_index);
  fz[2] = z->at(fECout_index);

  // ===== Cluster times =====
  ft[0] = t->at(fPCal_index);
  ft[1] = t->at(fECin_index);
  ft[2] = t->at(fECout_index);

  double phi = atan2(fy[0], fx[0])*TMath::RadToDeg() + 30.;
  if( phi < 30. ) {phi = phi + 360.;}

  fSector = int(phi/60.);

  is_ECalFully_initalized = true;
}
// =========== Setting RECHB_Particle information ==========
void CLAS12TrigCandidate::SetPxPyPzQ(vector<float> *Px, vector<float> *Py, vector<float> *Pz,  vector<int> *q){
  fPx = Px->at(fRECHB_part_index);
  fPy = Py->at(fRECHB_part_index);
  fPz = Pz->at(fRECHB_part_index);

  fP = sqrt(fPx*fPx + fPy*fPy + fPz*fPz);

  fq = q->at(fRECHB_part_index);
}

// =========== Setting HTCC information =========
void CLAS12TrigCandidate::SetIndXYZNphTime(int ind, vector<float> *x, vector<float> *y, vector<float> *z, vector<int> *nphe, vector<float> *time ){
  fHTCC_ind = ind;
  fCC_x = x->at(fHTCC_ind);
  fCC_y = y->at(fHTCC_ind);
  fCC_z = z->at(fHTCC_ind);
  fCC_nphe = nphe->at(fHTCC_ind);
  fCC_time = time->at(fHTCC_ind);

  has_CC = true;
}

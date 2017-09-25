#ifndef __CLAS12TRIFCANDIDATE__
#define __CLAS12TRIFCANDIDATE__

#include <vector>

using namespace std;

class CLAS12TrigCandidate{

public:
CLAS12TrigCandidate();
CLAS12TrigCandidate(int, int, int, int); // fRECHB_part_index, PCal index, ECin index, ECout index

void SetCalorimeterExyzt(vector<float>*, vector<float> *, vector<float> *, vector<float>*,  vector<float>*);
void SetPxPyPzQ(vector<float>*, vector<float> *, vector<float> *, vector<int> *);
void SetIndXYZNphTime(int, vector<float>*, vector<float> *, vector<float> *, vector<int>*,  vector<float>*);
float * GetCaloEnergy(){ return fEnergy;};  // Array of three 1st element PCal energy, 2nd ECin energy and 3rd ECout energy
float * GetCaloX(){return fx;};        // X coordinat of the cluster. Array of three , PCal, ECin and ECout
float * GetCaloY(){return fy;};        // Y coordinat of the cluster. Array of three , PCal, ECin and ECout
float * GetCaloZ(){return fz;};        // Z coordinat of the cluster. Array of three , PCal, ECin and ECout
float * GetCaloTime(){return ft;};        // Time of the cluster. Array of three , PCal, ECin and ECout
float GetCaloTotalEnergy() {return fTotE;};
bool HasHTCC() {return has_CC;};

float P(){ return fP; }
float Px(){ return fPx; }
float Py(){ return fPy; }
float Pz(){ return fPz; }
float charge(){ return fq; }

private:

int fPCal_index;
int fECin_index;
int fECout_index;
int fRECHB_part_index;
int fHTCC_ind;
bool is_ECalFully_initalized;
bool ECal_indexes_known;
bool has_CC;

int  fSector;

// =========== 1st element of following arrays correspond to PCal, 2nd to ECin, and 3rd to ECout =============
float fEnergy[3], fx[3], fy[3], fz[3], ft[3];
float fTotE;
float fPx, fPy, fPz, fP; // particle momentum x,y,z components and the absalute value.
int fq; // particle charge

float fCC_x, fCC_y, fCC_z;
int fCC_nphe;
float fCC_time;
  
};

#endif

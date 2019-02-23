//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Feb 21 22:52:15 2019 by ROOT version 6.16/00
// from TChain stage1_study/
//////////////////////////////////////////////////////////

#ifndef stage1_study_h
#define stage1_study_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>

using namespace std;

class stage1_study {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   int frun;
   
// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<long>    *REC_Particle_pid;
   vector<long>    *REC_Particle_charge;
   vector<long>    *REC_Particle_status;
   vector<float>   *REC_Particle_px;
   vector<float>   *REC_Particle_py;
   vector<float>   *REC_Particle_pz;
   vector<float>   *REC_Particle_vx;
   vector<float>   *REC_Particle_vy;
   vector<float>   *REC_Particle_vz;
   vector<float>   *REC_Particle_beta;
   vector<float>   *REC_Particle_chi2pid;
   vector<long>    *HTCC_rec_id;
   vector<long>    *HTCC_rec_nhits;
   vector<long>    *HTCC_rec_ntheta;
   vector<long>    *HTCC_rec_nphi;
   vector<long>    *HTCC_rec_mintheta;
   vector<long>    *HTCC_rec_maxtheta;
   vector<long>    *HTCC_rec_minphi;
   vector<long>    *HTCC_rec_maxphi;
   vector<float>   *HTCC_rec_nphe;
   vector<float>   *HTCC_rec_time;
   vector<float>   *HTCC_rec_theta;
   vector<float>   *HTCC_rec_dtheta;
   vector<float>   *HTCC_rec_phi;
   vector<float>   *HTCC_rec_dphi;
   vector<float>   *HTCC_rec_x;
   vector<float>   *HTCC_rec_y;
   vector<float>   *HTCC_rec_z;
   vector<long>    *REC_ForwardTagger_index;
   vector<long>    *REC_ForwardTagger_pindex;
   vector<long>    *REC_ForwardTagger_detector;
   vector<long>    *REC_ForwardTagger_size;
   vector<long>    *REC_ForwardTagger_status;
   vector<float>   *REC_ForwardTagger_energy;
   vector<float>   *REC_ForwardTagger_time;
   vector<float>   *REC_ForwardTagger_path;
   vector<float>   *REC_ForwardTagger_chi2;
   vector<float>   *REC_ForwardTagger_x;
   vector<float>   *REC_ForwardTagger_y;
   vector<float>   *REC_ForwardTagger_z;
   vector<float>   *REC_ForwardTagger_dx;
   vector<float>   *REC_ForwardTagger_dy;
   vector<float>   *REC_ForwardTagger_radius;
   vector<long>    *REC_Event_NRUN;
   vector<long>    *REC_Event_NEVENT;
   vector<long>    *REC_Event_TYPE;
   vector<long>    *REC_Event_EvCAT;
   vector<long>    *REC_Event_NPGP;
   vector<long>    *REC_Event_TRG;
   vector<long>    *REC_Event_Helic;
   vector<float>   *REC_Event_EVNTime;
   vector<float>   *REC_Event_BCG;
   vector<float>   *REC_Event_LT;
   vector<float>   *REC_Event_STTime;
   vector<float>   *REC_Event_RFTime;
   vector<float>   *REC_Event_PTIME;
   vector<long>    *REC_Cherenkov_index;
   vector<long>    *REC_Cherenkov_pindex;
   vector<long>    *REC_Cherenkov_detector;
   vector<long>    *REC_Cherenkov_sector;
   vector<long>    *REC_Cherenkov_status;
   vector<float>   *REC_Cherenkov_nphe;
   vector<float>   *REC_Cherenkov_time;
   vector<float>   *REC_Cherenkov_path;
   vector<float>   *REC_Cherenkov_chi2;
   vector<float>   *REC_Cherenkov_x;
   vector<float>   *REC_Cherenkov_y;
   vector<float>   *REC_Cherenkov_z;
   vector<float>   *REC_Cherenkov_theta;
   vector<float>   *REC_Cherenkov_phi;
   vector<float>   *REC_Cherenkov_dtheta;
   vector<float>   *REC_Cherenkov_dphi;
   vector<long>    *REC_Scintillator_index;
   vector<long>    *REC_Scintillator_pindex;
   vector<long>    *REC_Scintillator_detector;
   vector<long>    *REC_Scintillator_sector;
   vector<long>    *REC_Scintillator_layer;
   vector<long>    *REC_Scintillator_component;
   vector<long>    *REC_Scintillator_status;
   vector<float>   *REC_Scintillator_energy;
   vector<float>   *REC_Scintillator_time;
   vector<float>   *REC_Scintillator_path;
   vector<float>   *REC_Scintillator_chi2;
   vector<float>   *REC_Scintillator_x;
   vector<float>   *REC_Scintillator_y;
   vector<float>   *REC_Scintillator_z;
   vector<float>   *REC_Scintillator_hx;
   vector<float>   *REC_Scintillator_hy;
   vector<float>   *REC_Scintillator_hz;
   vector<long>    *REC_Track_index;
   vector<long>    *REC_Track_pindex;
   vector<long>    *REC_Track_detector;
   vector<long>    *REC_Track_sector;
   vector<long>    *REC_Track_status;
   vector<long>    *REC_Track_q;
   vector<long>    *REC_Track_NDF;
   vector<long>    *REC_Track_NDF_nomm;
   vector<float>   *REC_Track_chi2;
   vector<float>   *REC_Track_px_nomm;
   vector<float>   *REC_Track_py_nomm;
   vector<float>   *REC_Track_pz_nomm;
   vector<float>   *REC_Track_vx_nomm;
   vector<float>   *REC_Track_vy_nomm;
   vector<float>   *REC_Track_vz_nomm;
   vector<float>   *REC_Track_chi2_nomm;
   vector<long>    *RAW_vtp_crate;
   vector<long>    *RAW_vtp_word;
   vector<long>    *RUN_config_run;
   vector<long>    *RUN_config_event;
   vector<long>    *RUN_config_unixtime;
   vector<long>    *RUN_config_trigger;
   vector<long>    *RUN_config_timestamp;
   vector<long>    *RUN_config_type;
   vector<long>    *RUN_config_mode;
   vector<float>   *RUN_config_torus;
   vector<float>   *RUN_config_solenoid;
   vector<long>    *REC_Calorimeter_index;
   vector<long>    *REC_Calorimeter_pindex;
   vector<long>    *REC_Calorimeter_detector;
   vector<long>    *REC_Calorimeter_sector;
   vector<long>    *REC_Calorimeter_layer;
   vector<long>    *REC_Calorimeter_status;
   vector<float>   *REC_Calorimeter_energy;
   vector<float>   *REC_Calorimeter_time;
   vector<float>   *REC_Calorimeter_path;
   vector<float>   *REC_Calorimeter_chi2;
   vector<float>   *REC_Calorimeter_x;
   vector<float>   *REC_Calorimeter_y;
   vector<float>   *REC_Calorimeter_z;
   vector<float>   *REC_Calorimeter_hx;
   vector<float>   *REC_Calorimeter_hy;
   vector<float>   *REC_Calorimeter_hz;
   vector<float>   *REC_Calorimeter_lu;
   vector<float>   *REC_Calorimeter_lv;
   vector<float>   *REC_Calorimeter_lw;
   vector<float>   *REC_Calorimeter_du;
   vector<float>   *REC_Calorimeter_dv;
   vector<float>   *REC_Calorimeter_dw;
   vector<float>   *REC_Calorimeter_m2u;
   vector<float>   *REC_Calorimeter_m2v;
   vector<float>   *REC_Calorimeter_m2w;
   vector<float>   *REC_Calorimeter_m3u;
   vector<float>   *REC_Calorimeter_m3v;
   vector<float>   *REC_Calorimeter_m3w;
   vector<long>    *ECAL_clusters_id;
   vector<long>    *ECAL_clusters_status;
   vector<long>    *ECAL_clusters_sector;
   vector<long>    *ECAL_clusters_layer;
   vector<long>    *ECAL_clusters_idU;
   vector<long>    *ECAL_clusters_idV;
   vector<long>    *ECAL_clusters_idW;
   vector<long>    *ECAL_clusters_coordU;
   vector<long>    *ECAL_clusters_coordV;
   vector<long>    *ECAL_clusters_coordW;
   vector<float>   *ECAL_clusters_x;
   vector<float>   *ECAL_clusters_y;
   vector<float>   *ECAL_clusters_z;
   vector<float>   *ECAL_clusters_energy;
   vector<float>   *ECAL_clusters_time;
   vector<float>   *ECAL_clusters_widthU;
   vector<float>   *ECAL_clusters_widthV;
   vector<float>   *ECAL_clusters_widthW;

   // List of branches
   TBranch        *b_REC_Particle_pid;   //!
   TBranch        *b_REC_Particle_charge;   //!
   TBranch        *b_REC_Particle_status;   //!
   TBranch        *b_REC_Particle_px;   //!
   TBranch        *b_REC_Particle_py;   //!
   TBranch        *b_REC_Particle_pz;   //!
   TBranch        *b_REC_Particle_vx;   //!
   TBranch        *b_REC_Particle_vy;   //!
   TBranch        *b_REC_Particle_vz;   //!
   TBranch        *b_REC_Particle_beta;   //!
   TBranch        *b_REC_Particle_chi2pid;   //!
   TBranch        *b_HTCC_rec_id;   //!
   TBranch        *b_HTCC_rec_nhits;   //!
   TBranch        *b_HTCC_rec_ntheta;   //!
   TBranch        *b_HTCC_rec_nphi;   //!
   TBranch        *b_HTCC_rec_mintheta;   //!
   TBranch        *b_HTCC_rec_maxtheta;   //!
   TBranch        *b_HTCC_rec_minphi;   //!
   TBranch        *b_HTCC_rec_maxphi;   //!
   TBranch        *b_HTCC_rec_nphe;   //!
   TBranch        *b_HTCC_rec_time;   //!
   TBranch        *b_HTCC_rec_theta;   //!
   TBranch        *b_HTCC_rec_dtheta;   //!
   TBranch        *b_HTCC_rec_phi;   //!
   TBranch        *b_HTCC_rec_dphi;   //!
   TBranch        *b_HTCC_rec_x;   //!
   TBranch        *b_HTCC_rec_y;   //!
   TBranch        *b_HTCC_rec_z;   //!
   TBranch        *b_REC_ForwardTagger_index;   //!
   TBranch        *b_REC_ForwardTagger_pindex;   //!
   TBranch        *b_REC_ForwardTagger_detector;   //!
   TBranch        *b_REC_ForwardTagger_size;   //!
   TBranch        *b_REC_ForwardTagger_status;   //!
   TBranch        *b_REC_ForwardTagger_energy;   //!
   TBranch        *b_REC_ForwardTagger_time;   //!
   TBranch        *b_REC_ForwardTagger_path;   //!
   TBranch        *b_REC_ForwardTagger_chi2;   //!
   TBranch        *b_REC_ForwardTagger_x;   //!
   TBranch        *b_REC_ForwardTagger_y;   //!
   TBranch        *b_REC_ForwardTagger_z;   //!
   TBranch        *b_REC_ForwardTagger_dx;   //!
   TBranch        *b_REC_ForwardTagger_dy;   //!
   TBranch        *b_REC_ForwardTagger_radius;   //!
   TBranch        *b_REC_Event_NRUN;   //!
   TBranch        *b_REC_Event_NEVENT;   //!
   TBranch        *b_REC_Event_TYPE;   //!
   TBranch        *b_REC_Event_EvCAT;   //!
   TBranch        *b_REC_Event_NPGP;   //!
   TBranch        *b_REC_Event_TRG;   //!
   TBranch        *b_REC_Event_Helic;   //!
   TBranch        *b_REC_Event_EVNTime;   //!
   TBranch        *b_REC_Event_BCG;   //!
   TBranch        *b_REC_Event_LT;   //!
   TBranch        *b_REC_Event_STTime;   //!
   TBranch        *b_REC_Event_RFTime;   //!
   TBranch        *b_REC_Event_PTIME;   //!
   TBranch        *b_REC_Cherenkov_index;   //!
   TBranch        *b_REC_Cherenkov_pindex;   //!
   TBranch        *b_REC_Cherenkov_detector;   //!
   TBranch        *b_REC_Cherenkov_sector;   //!
   TBranch        *b_REC_Cherenkov_status;   //!
   TBranch        *b_REC_Cherenkov_nphe;   //!
   TBranch        *b_REC_Cherenkov_time;   //!
   TBranch        *b_REC_Cherenkov_path;   //!
   TBranch        *b_REC_Cherenkov_chi2;   //!
   TBranch        *b_REC_Cherenkov_x;   //!
   TBranch        *b_REC_Cherenkov_y;   //!
   TBranch        *b_REC_Cherenkov_z;   //!
   TBranch        *b_REC_Cherenkov_theta;   //!
   TBranch        *b_REC_Cherenkov_phi;   //!
   TBranch        *b_REC_Cherenkov_dtheta;   //!
   TBranch        *b_REC_Cherenkov_dphi;   //!
   TBranch        *b_REC_Scintillator_index;   //!
   TBranch        *b_REC_Scintillator_pindex;   //!
   TBranch        *b_REC_Scintillator_detector;   //!
   TBranch        *b_REC_Scintillator_sector;   //!
   TBranch        *b_REC_Scintillator_layer;   //!
   TBranch        *b_REC_Scintillator_component;   //!
   TBranch        *b_REC_Scintillator_status;   //!
   TBranch        *b_REC_Scintillator_energy;   //!
   TBranch        *b_REC_Scintillator_time;   //!
   TBranch        *b_REC_Scintillator_path;   //!
   TBranch        *b_REC_Scintillator_chi2;   //!
   TBranch        *b_REC_Scintillator_x;   //!
   TBranch        *b_REC_Scintillator_y;   //!
   TBranch        *b_REC_Scintillator_z;   //!
   TBranch        *b_REC_Scintillator_hx;   //!
   TBranch        *b_REC_Scintillator_hy;   //!
   TBranch        *b_REC_Scintillator_hz;   //!
   TBranch        *b_REC_Track_index;   //!
   TBranch        *b_REC_Track_pindex;   //!
   TBranch        *b_REC_Track_detector;   //!
   TBranch        *b_REC_Track_sector;   //!
   TBranch        *b_REC_Track_status;   //!
   TBranch        *b_REC_Track_q;   //!
   TBranch        *b_REC_Track_NDF;   //!
   TBranch        *b_REC_Track_NDF_nomm;   //!
   TBranch        *b_REC_Track_chi2;   //!
   TBranch        *b_REC_Track_px_nomm;   //!
   TBranch        *b_REC_Track_py_nomm;   //!
   TBranch        *b_REC_Track_pz_nomm;   //!
   TBranch        *b_REC_Track_vx_nomm;   //!
   TBranch        *b_REC_Track_vy_nomm;   //!
   TBranch        *b_REC_Track_vz_nomm;   //!
   TBranch        *b_REC_Track_chi2_nomm;   //!
   TBranch        *b_RAW_vtp_crate;   //!
   TBranch        *b_RAW_vtp_word;   //!
   TBranch        *b_RUN_config_run;   //!
   TBranch        *b_RUN_config_event;   //!
   TBranch        *b_RUN_config_unixtime;   //!
   TBranch        *b_RUN_config_trigger;   //!
   TBranch        *b_RUN_config_timestamp;   //!
   TBranch        *b_RUN_config_type;   //!
   TBranch        *b_RUN_config_mode;   //!
   TBranch        *b_RUN_config_torus;   //!
   TBranch        *b_RUN_config_solenoid;   //!
   TBranch        *b_REC_Calorimeter_index;   //!
   TBranch        *b_REC_Calorimeter_pindex;   //!
   TBranch        *b_REC_Calorimeter_detector;   //!
   TBranch        *b_REC_Calorimeter_sector;   //!
   TBranch        *b_REC_Calorimeter_layer;   //!
   TBranch        *b_REC_Calorimeter_status;   //!
   TBranch        *b_REC_Calorimeter_energy;   //!
   TBranch        *b_REC_Calorimeter_time;   //!
   TBranch        *b_REC_Calorimeter_path;   //!
   TBranch        *b_REC_Calorimeter_chi2;   //!
   TBranch        *b_REC_Calorimeter_x;   //!
   TBranch        *b_REC_Calorimeter_y;   //!
   TBranch        *b_REC_Calorimeter_z;   //!
   TBranch        *b_REC_Calorimeter_hx;   //!
   TBranch        *b_REC_Calorimeter_hy;   //!
   TBranch        *b_REC_Calorimeter_hz;   //!
   TBranch        *b_REC_Calorimeter_lu;   //!
   TBranch        *b_REC_Calorimeter_lv;   //!
   TBranch        *b_REC_Calorimeter_lw;   //!
   TBranch        *b_REC_Calorimeter_du;   //!
   TBranch        *b_REC_Calorimeter_dv;   //!
   TBranch        *b_REC_Calorimeter_dw;   //!
   TBranch        *b_REC_Calorimeter_m2u;   //!
   TBranch        *b_REC_Calorimeter_m2v;   //!
   TBranch        *b_REC_Calorimeter_m2w;   //!
   TBranch        *b_REC_Calorimeter_m3u;   //!
   TBranch        *b_REC_Calorimeter_m3v;   //!
   TBranch        *b_REC_Calorimeter_m3w;   //!
   TBranch        *b_ECAL_clusters_id;   //!
   TBranch        *b_ECAL_clusters_status;   //!
   TBranch        *b_ECAL_clusters_sector;   //!
   TBranch        *b_ECAL_clusters_layer;   //!
   TBranch        *b_ECAL_clusters_idU;   //!
   TBranch        *b_ECAL_clusters_idV;   //!
   TBranch        *b_ECAL_clusters_idW;   //!
   TBranch        *b_ECAL_clusters_coordU;   //!
   TBranch        *b_ECAL_clusters_coordV;   //!
   TBranch        *b_ECAL_clusters_coordW;   //!
   TBranch        *b_ECAL_clusters_x;   //!
   TBranch        *b_ECAL_clusters_y;   //!
   TBranch        *b_ECAL_clusters_z;   //!
   TBranch        *b_ECAL_clusters_energy;   //!
   TBranch        *b_ECAL_clusters_time;   //!
   TBranch        *b_ECAL_clusters_widthU;   //!
   TBranch        *b_ECAL_clusters_widthV;   //!
   TBranch        *b_ECAL_clusters_widthW;   //!

   stage1_study(int, TTree *tree=0);
   virtual ~stage1_study();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef stage1_study_cxx
stage1_study::stage1_study(int arun, TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
       
       frun = arun;

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("stage1_study",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("stage1_study","");
      chain->Add(Form("Data/mon_clas_00%d.evio.*.root/hipo2root", frun));
      //chain->Add("Data/mon_clas_006299.evio.00000.root/hipo2root");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

stage1_study::~stage1_study()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t stage1_study::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t stage1_study::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void stage1_study::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   REC_Particle_pid = 0;
   REC_Particle_charge = 0;
   REC_Particle_status = 0;
   REC_Particle_px = 0;
   REC_Particle_py = 0;
   REC_Particle_pz = 0;
   REC_Particle_vx = 0;
   REC_Particle_vy = 0;
   REC_Particle_vz = 0;
   REC_Particle_beta = 0;
   REC_Particle_chi2pid = 0;
   HTCC_rec_id = 0;
   HTCC_rec_nhits = 0;
   HTCC_rec_ntheta = 0;
   HTCC_rec_nphi = 0;
   HTCC_rec_mintheta = 0;
   HTCC_rec_maxtheta = 0;
   HTCC_rec_minphi = 0;
   HTCC_rec_maxphi = 0;
   HTCC_rec_nphe = 0;
   HTCC_rec_time = 0;
   HTCC_rec_theta = 0;
   HTCC_rec_dtheta = 0;
   HTCC_rec_phi = 0;
   HTCC_rec_dphi = 0;
   HTCC_rec_x = 0;
   HTCC_rec_y = 0;
   HTCC_rec_z = 0;
   REC_ForwardTagger_index = 0;
   REC_ForwardTagger_pindex = 0;
   REC_ForwardTagger_detector = 0;
   REC_ForwardTagger_size = 0;
   REC_ForwardTagger_status = 0;
   REC_ForwardTagger_energy = 0;
   REC_ForwardTagger_time = 0;
   REC_ForwardTagger_path = 0;
   REC_ForwardTagger_chi2 = 0;
   REC_ForwardTagger_x = 0;
   REC_ForwardTagger_y = 0;
   REC_ForwardTagger_z = 0;
   REC_ForwardTagger_dx = 0;
   REC_ForwardTagger_dy = 0;
   REC_ForwardTagger_radius = 0;
   REC_Event_NRUN = 0;
   REC_Event_NEVENT = 0;
   REC_Event_TYPE = 0;
   REC_Event_EvCAT = 0;
   REC_Event_NPGP = 0;
   REC_Event_TRG = 0;
   REC_Event_Helic = 0;
   REC_Event_EVNTime = 0;
   REC_Event_BCG = 0;
   REC_Event_LT = 0;
   REC_Event_STTime = 0;
   REC_Event_RFTime = 0;
   REC_Event_PTIME = 0;
   REC_Cherenkov_index = 0;
   REC_Cherenkov_pindex = 0;
   REC_Cherenkov_detector = 0;
   REC_Cherenkov_sector = 0;
   REC_Cherenkov_status = 0;
   REC_Cherenkov_nphe = 0;
   REC_Cherenkov_time = 0;
   REC_Cherenkov_path = 0;
   REC_Cherenkov_chi2 = 0;
   REC_Cherenkov_x = 0;
   REC_Cherenkov_y = 0;
   REC_Cherenkov_z = 0;
   REC_Cherenkov_theta = 0;
   REC_Cherenkov_phi = 0;
   REC_Cherenkov_dtheta = 0;
   REC_Cherenkov_dphi = 0;
   REC_Scintillator_index = 0;
   REC_Scintillator_pindex = 0;
   REC_Scintillator_detector = 0;
   REC_Scintillator_sector = 0;
   REC_Scintillator_layer = 0;
   REC_Scintillator_component = 0;
   REC_Scintillator_status = 0;
   REC_Scintillator_energy = 0;
   REC_Scintillator_time = 0;
   REC_Scintillator_path = 0;
   REC_Scintillator_chi2 = 0;
   REC_Scintillator_x = 0;
   REC_Scintillator_y = 0;
   REC_Scintillator_z = 0;
   REC_Scintillator_hx = 0;
   REC_Scintillator_hy = 0;
   REC_Scintillator_hz = 0;
   REC_Track_index = 0;
   REC_Track_pindex = 0;
   REC_Track_detector = 0;
   REC_Track_sector = 0;
   REC_Track_status = 0;
   REC_Track_q = 0;
   REC_Track_NDF = 0;
   REC_Track_NDF_nomm = 0;
   REC_Track_chi2 = 0;
   REC_Track_px_nomm = 0;
   REC_Track_py_nomm = 0;
   REC_Track_pz_nomm = 0;
   REC_Track_vx_nomm = 0;
   REC_Track_vy_nomm = 0;
   REC_Track_vz_nomm = 0;
   REC_Track_chi2_nomm = 0;
   RAW_vtp_crate = 0;
   RAW_vtp_word = 0;
   RUN_config_run = 0;
   RUN_config_event = 0;
   RUN_config_unixtime = 0;
   RUN_config_trigger = 0;
   RUN_config_timestamp = 0;
   RUN_config_type = 0;
   RUN_config_mode = 0;
   RUN_config_torus = 0;
   RUN_config_solenoid = 0;
   REC_Calorimeter_index = 0;
   REC_Calorimeter_pindex = 0;
   REC_Calorimeter_detector = 0;
   REC_Calorimeter_sector = 0;
   REC_Calorimeter_layer = 0;
   REC_Calorimeter_status = 0;
   REC_Calorimeter_energy = 0;
   REC_Calorimeter_time = 0;
   REC_Calorimeter_path = 0;
   REC_Calorimeter_chi2 = 0;
   REC_Calorimeter_x = 0;
   REC_Calorimeter_y = 0;
   REC_Calorimeter_z = 0;
   REC_Calorimeter_hx = 0;
   REC_Calorimeter_hy = 0;
   REC_Calorimeter_hz = 0;
   REC_Calorimeter_lu = 0;
   REC_Calorimeter_lv = 0;
   REC_Calorimeter_lw = 0;
   REC_Calorimeter_du = 0;
   REC_Calorimeter_dv = 0;
   REC_Calorimeter_dw = 0;
   REC_Calorimeter_m2u = 0;
   REC_Calorimeter_m2v = 0;
   REC_Calorimeter_m2w = 0;
   REC_Calorimeter_m3u = 0;
   REC_Calorimeter_m3v = 0;
   REC_Calorimeter_m3w = 0;
   ECAL_clusters_id = 0;
   ECAL_clusters_status = 0;
   ECAL_clusters_sector = 0;
   ECAL_clusters_layer = 0;
   ECAL_clusters_idU = 0;
   ECAL_clusters_idV = 0;
   ECAL_clusters_idW = 0;
   ECAL_clusters_coordU = 0;
   ECAL_clusters_coordV = 0;
   ECAL_clusters_coordW = 0;
   ECAL_clusters_x = 0;
   ECAL_clusters_y = 0;
   ECAL_clusters_z = 0;
   ECAL_clusters_energy = 0;
   ECAL_clusters_time = 0;
   ECAL_clusters_widthU = 0;
   ECAL_clusters_widthV = 0;
   ECAL_clusters_widthW = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("REC_Particle_pid", &REC_Particle_pid, &b_REC_Particle_pid);
   fChain->SetBranchAddress("REC_Particle_charge", &REC_Particle_charge, &b_REC_Particle_charge);
   fChain->SetBranchAddress("REC_Particle_status", &REC_Particle_status, &b_REC_Particle_status);
   fChain->SetBranchAddress("REC_Particle_px", &REC_Particle_px, &b_REC_Particle_px);
   fChain->SetBranchAddress("REC_Particle_py", &REC_Particle_py, &b_REC_Particle_py);
   fChain->SetBranchAddress("REC_Particle_pz", &REC_Particle_pz, &b_REC_Particle_pz);
   fChain->SetBranchAddress("REC_Particle_vx", &REC_Particle_vx, &b_REC_Particle_vx);
   fChain->SetBranchAddress("REC_Particle_vy", &REC_Particle_vy, &b_REC_Particle_vy);
   fChain->SetBranchAddress("REC_Particle_vz", &REC_Particle_vz, &b_REC_Particle_vz);
   fChain->SetBranchAddress("REC_Particle_beta", &REC_Particle_beta, &b_REC_Particle_beta);
   fChain->SetBranchAddress("REC_Particle_chi2pid", &REC_Particle_chi2pid, &b_REC_Particle_chi2pid);
   fChain->SetBranchAddress("HTCC_rec_id", &HTCC_rec_id, &b_HTCC_rec_id);
   fChain->SetBranchAddress("HTCC_rec_nhits", &HTCC_rec_nhits, &b_HTCC_rec_nhits);
   fChain->SetBranchAddress("HTCC_rec_ntheta", &HTCC_rec_ntheta, &b_HTCC_rec_ntheta);
   fChain->SetBranchAddress("HTCC_rec_nphi", &HTCC_rec_nphi, &b_HTCC_rec_nphi);
   fChain->SetBranchAddress("HTCC_rec_mintheta", &HTCC_rec_mintheta, &b_HTCC_rec_mintheta);
   fChain->SetBranchAddress("HTCC_rec_maxtheta", &HTCC_rec_maxtheta, &b_HTCC_rec_maxtheta);
   fChain->SetBranchAddress("HTCC_rec_minphi", &HTCC_rec_minphi, &b_HTCC_rec_minphi);
   fChain->SetBranchAddress("HTCC_rec_maxphi", &HTCC_rec_maxphi, &b_HTCC_rec_maxphi);
   fChain->SetBranchAddress("HTCC_rec_nphe", &HTCC_rec_nphe, &b_HTCC_rec_nphe);
   fChain->SetBranchAddress("HTCC_rec_time", &HTCC_rec_time, &b_HTCC_rec_time);
   fChain->SetBranchAddress("HTCC_rec_theta", &HTCC_rec_theta, &b_HTCC_rec_theta);
   fChain->SetBranchAddress("HTCC_rec_dtheta", &HTCC_rec_dtheta, &b_HTCC_rec_dtheta);
   fChain->SetBranchAddress("HTCC_rec_phi", &HTCC_rec_phi, &b_HTCC_rec_phi);
   fChain->SetBranchAddress("HTCC_rec_dphi", &HTCC_rec_dphi, &b_HTCC_rec_dphi);
   fChain->SetBranchAddress("HTCC_rec_x", &HTCC_rec_x, &b_HTCC_rec_x);
   fChain->SetBranchAddress("HTCC_rec_y", &HTCC_rec_y, &b_HTCC_rec_y);
   fChain->SetBranchAddress("HTCC_rec_z", &HTCC_rec_z, &b_HTCC_rec_z);
   fChain->SetBranchAddress("REC_ForwardTagger_index", &REC_ForwardTagger_index, &b_REC_ForwardTagger_index);
   fChain->SetBranchAddress("REC_ForwardTagger_pindex", &REC_ForwardTagger_pindex, &b_REC_ForwardTagger_pindex);
   fChain->SetBranchAddress("REC_ForwardTagger_detector", &REC_ForwardTagger_detector, &b_REC_ForwardTagger_detector);
   fChain->SetBranchAddress("REC_ForwardTagger_size", &REC_ForwardTagger_size, &b_REC_ForwardTagger_size);
   fChain->SetBranchAddress("REC_ForwardTagger_status", &REC_ForwardTagger_status, &b_REC_ForwardTagger_status);
   fChain->SetBranchAddress("REC_ForwardTagger_energy", &REC_ForwardTagger_energy, &b_REC_ForwardTagger_energy);
   fChain->SetBranchAddress("REC_ForwardTagger_time", &REC_ForwardTagger_time, &b_REC_ForwardTagger_time);
   fChain->SetBranchAddress("REC_ForwardTagger_path", &REC_ForwardTagger_path, &b_REC_ForwardTagger_path);
   fChain->SetBranchAddress("REC_ForwardTagger_chi2", &REC_ForwardTagger_chi2, &b_REC_ForwardTagger_chi2);
   fChain->SetBranchAddress("REC_ForwardTagger_x", &REC_ForwardTagger_x, &b_REC_ForwardTagger_x);
   fChain->SetBranchAddress("REC_ForwardTagger_y", &REC_ForwardTagger_y, &b_REC_ForwardTagger_y);
   fChain->SetBranchAddress("REC_ForwardTagger_z", &REC_ForwardTagger_z, &b_REC_ForwardTagger_z);
   fChain->SetBranchAddress("REC_ForwardTagger_dx", &REC_ForwardTagger_dx, &b_REC_ForwardTagger_dx);
   fChain->SetBranchAddress("REC_ForwardTagger_dy", &REC_ForwardTagger_dy, &b_REC_ForwardTagger_dy);
   fChain->SetBranchAddress("REC_ForwardTagger_radius", &REC_ForwardTagger_radius, &b_REC_ForwardTagger_radius);
   fChain->SetBranchAddress("REC_Event_NRUN", &REC_Event_NRUN, &b_REC_Event_NRUN);
   fChain->SetBranchAddress("REC_Event_NEVENT", &REC_Event_NEVENT, &b_REC_Event_NEVENT);
   fChain->SetBranchAddress("REC_Event_TYPE", &REC_Event_TYPE, &b_REC_Event_TYPE);
   fChain->SetBranchAddress("REC_Event_EvCAT", &REC_Event_EvCAT, &b_REC_Event_EvCAT);
   fChain->SetBranchAddress("REC_Event_NPGP", &REC_Event_NPGP, &b_REC_Event_NPGP);
   fChain->SetBranchAddress("REC_Event_TRG", &REC_Event_TRG, &b_REC_Event_TRG);
   fChain->SetBranchAddress("REC_Event_Helic", &REC_Event_Helic, &b_REC_Event_Helic);
   fChain->SetBranchAddress("REC_Event_EVNTime", &REC_Event_EVNTime, &b_REC_Event_EVNTime);
   fChain->SetBranchAddress("REC_Event_BCG", &REC_Event_BCG, &b_REC_Event_BCG);
   fChain->SetBranchAddress("REC_Event_LT", &REC_Event_LT, &b_REC_Event_LT);
   fChain->SetBranchAddress("REC_Event_STTime", &REC_Event_STTime, &b_REC_Event_STTime);
   fChain->SetBranchAddress("REC_Event_RFTime", &REC_Event_RFTime, &b_REC_Event_RFTime);
   fChain->SetBranchAddress("REC_Event_PTIME", &REC_Event_PTIME, &b_REC_Event_PTIME);
   fChain->SetBranchAddress("REC_Cherenkov_index", &REC_Cherenkov_index, &b_REC_Cherenkov_index);
   fChain->SetBranchAddress("REC_Cherenkov_pindex", &REC_Cherenkov_pindex, &b_REC_Cherenkov_pindex);
   fChain->SetBranchAddress("REC_Cherenkov_detector", &REC_Cherenkov_detector, &b_REC_Cherenkov_detector);
   fChain->SetBranchAddress("REC_Cherenkov_sector", &REC_Cherenkov_sector, &b_REC_Cherenkov_sector);
   fChain->SetBranchAddress("REC_Cherenkov_status", &REC_Cherenkov_status, &b_REC_Cherenkov_status);
   fChain->SetBranchAddress("REC_Cherenkov_nphe", &REC_Cherenkov_nphe, &b_REC_Cherenkov_nphe);
   fChain->SetBranchAddress("REC_Cherenkov_time", &REC_Cherenkov_time, &b_REC_Cherenkov_time);
   fChain->SetBranchAddress("REC_Cherenkov_path", &REC_Cherenkov_path, &b_REC_Cherenkov_path);
   fChain->SetBranchAddress("REC_Cherenkov_chi2", &REC_Cherenkov_chi2, &b_REC_Cherenkov_chi2);
   fChain->SetBranchAddress("REC_Cherenkov_x", &REC_Cherenkov_x, &b_REC_Cherenkov_x);
   fChain->SetBranchAddress("REC_Cherenkov_y", &REC_Cherenkov_y, &b_REC_Cherenkov_y);
   fChain->SetBranchAddress("REC_Cherenkov_z", &REC_Cherenkov_z, &b_REC_Cherenkov_z);
   fChain->SetBranchAddress("REC_Cherenkov_theta", &REC_Cherenkov_theta, &b_REC_Cherenkov_theta);
   fChain->SetBranchAddress("REC_Cherenkov_phi", &REC_Cherenkov_phi, &b_REC_Cherenkov_phi);
   fChain->SetBranchAddress("REC_Cherenkov_dtheta", &REC_Cherenkov_dtheta, &b_REC_Cherenkov_dtheta);
   fChain->SetBranchAddress("REC_Cherenkov_dphi", &REC_Cherenkov_dphi, &b_REC_Cherenkov_dphi);
   fChain->SetBranchAddress("REC_Scintillator_index", &REC_Scintillator_index, &b_REC_Scintillator_index);
   fChain->SetBranchAddress("REC_Scintillator_pindex", &REC_Scintillator_pindex, &b_REC_Scintillator_pindex);
   fChain->SetBranchAddress("REC_Scintillator_detector", &REC_Scintillator_detector, &b_REC_Scintillator_detector);
   fChain->SetBranchAddress("REC_Scintillator_sector", &REC_Scintillator_sector, &b_REC_Scintillator_sector);
   fChain->SetBranchAddress("REC_Scintillator_layer", &REC_Scintillator_layer, &b_REC_Scintillator_layer);
   fChain->SetBranchAddress("REC_Scintillator_component", &REC_Scintillator_component, &b_REC_Scintillator_component);
   fChain->SetBranchAddress("REC_Scintillator_status", &REC_Scintillator_status, &b_REC_Scintillator_status);
   fChain->SetBranchAddress("REC_Scintillator_energy", &REC_Scintillator_energy, &b_REC_Scintillator_energy);
   fChain->SetBranchAddress("REC_Scintillator_time", &REC_Scintillator_time, &b_REC_Scintillator_time);
   fChain->SetBranchAddress("REC_Scintillator_path", &REC_Scintillator_path, &b_REC_Scintillator_path);
   fChain->SetBranchAddress("REC_Scintillator_chi2", &REC_Scintillator_chi2, &b_REC_Scintillator_chi2);
   fChain->SetBranchAddress("REC_Scintillator_x", &REC_Scintillator_x, &b_REC_Scintillator_x);
   fChain->SetBranchAddress("REC_Scintillator_y", &REC_Scintillator_y, &b_REC_Scintillator_y);
   fChain->SetBranchAddress("REC_Scintillator_z", &REC_Scintillator_z, &b_REC_Scintillator_z);
   fChain->SetBranchAddress("REC_Scintillator_hx", &REC_Scintillator_hx, &b_REC_Scintillator_hx);
   fChain->SetBranchAddress("REC_Scintillator_hy", &REC_Scintillator_hy, &b_REC_Scintillator_hy);
   fChain->SetBranchAddress("REC_Scintillator_hz", &REC_Scintillator_hz, &b_REC_Scintillator_hz);
   fChain->SetBranchAddress("REC_Track_index", &REC_Track_index, &b_REC_Track_index);
   fChain->SetBranchAddress("REC_Track_pindex", &REC_Track_pindex, &b_REC_Track_pindex);
   fChain->SetBranchAddress("REC_Track_detector", &REC_Track_detector, &b_REC_Track_detector);
   fChain->SetBranchAddress("REC_Track_sector", &REC_Track_sector, &b_REC_Track_sector);
   fChain->SetBranchAddress("REC_Track_status", &REC_Track_status, &b_REC_Track_status);
   fChain->SetBranchAddress("REC_Track_q", &REC_Track_q, &b_REC_Track_q);
   fChain->SetBranchAddress("REC_Track_NDF", &REC_Track_NDF, &b_REC_Track_NDF);
   fChain->SetBranchAddress("REC_Track_NDF_nomm", &REC_Track_NDF_nomm, &b_REC_Track_NDF_nomm);
   fChain->SetBranchAddress("REC_Track_chi2", &REC_Track_chi2, &b_REC_Track_chi2);
   fChain->SetBranchAddress("REC_Track_px_nomm", &REC_Track_px_nomm, &b_REC_Track_px_nomm);
   fChain->SetBranchAddress("REC_Track_py_nomm", &REC_Track_py_nomm, &b_REC_Track_py_nomm);
   fChain->SetBranchAddress("REC_Track_pz_nomm", &REC_Track_pz_nomm, &b_REC_Track_pz_nomm);
   fChain->SetBranchAddress("REC_Track_vx_nomm", &REC_Track_vx_nomm, &b_REC_Track_vx_nomm);
   fChain->SetBranchAddress("REC_Track_vy_nomm", &REC_Track_vy_nomm, &b_REC_Track_vy_nomm);
   fChain->SetBranchAddress("REC_Track_vz_nomm", &REC_Track_vz_nomm, &b_REC_Track_vz_nomm);
   fChain->SetBranchAddress("REC_Track_chi2_nomm", &REC_Track_chi2_nomm, &b_REC_Track_chi2_nomm);
   fChain->SetBranchAddress("RAW_vtp_crate", &RAW_vtp_crate, &b_RAW_vtp_crate);
   fChain->SetBranchAddress("RAW_vtp_word", &RAW_vtp_word, &b_RAW_vtp_word);
   fChain->SetBranchAddress("RUN_config_run", &RUN_config_run, &b_RUN_config_run);
   fChain->SetBranchAddress("RUN_config_event", &RUN_config_event, &b_RUN_config_event);
   fChain->SetBranchAddress("RUN_config_unixtime", &RUN_config_unixtime, &b_RUN_config_unixtime);
   fChain->SetBranchAddress("RUN_config_trigger", &RUN_config_trigger, &b_RUN_config_trigger);
   fChain->SetBranchAddress("RUN_config_timestamp", &RUN_config_timestamp, &b_RUN_config_timestamp);
   fChain->SetBranchAddress("RUN_config_type", &RUN_config_type, &b_RUN_config_type);
   fChain->SetBranchAddress("RUN_config_mode", &RUN_config_mode, &b_RUN_config_mode);
   fChain->SetBranchAddress("RUN_config_torus", &RUN_config_torus, &b_RUN_config_torus);
   fChain->SetBranchAddress("RUN_config_solenoid", &RUN_config_solenoid, &b_RUN_config_solenoid);
   fChain->SetBranchAddress("REC_Calorimeter_index", &REC_Calorimeter_index, &b_REC_Calorimeter_index);
   fChain->SetBranchAddress("REC_Calorimeter_pindex", &REC_Calorimeter_pindex, &b_REC_Calorimeter_pindex);
   fChain->SetBranchAddress("REC_Calorimeter_detector", &REC_Calorimeter_detector, &b_REC_Calorimeter_detector);
   fChain->SetBranchAddress("REC_Calorimeter_sector", &REC_Calorimeter_sector, &b_REC_Calorimeter_sector);
   fChain->SetBranchAddress("REC_Calorimeter_layer", &REC_Calorimeter_layer, &b_REC_Calorimeter_layer);
   fChain->SetBranchAddress("REC_Calorimeter_status", &REC_Calorimeter_status, &b_REC_Calorimeter_status);
   fChain->SetBranchAddress("REC_Calorimeter_energy", &REC_Calorimeter_energy, &b_REC_Calorimeter_energy);
   fChain->SetBranchAddress("REC_Calorimeter_time", &REC_Calorimeter_time, &b_REC_Calorimeter_time);
   fChain->SetBranchAddress("REC_Calorimeter_path", &REC_Calorimeter_path, &b_REC_Calorimeter_path);
   fChain->SetBranchAddress("REC_Calorimeter_chi2", &REC_Calorimeter_chi2, &b_REC_Calorimeter_chi2);
   fChain->SetBranchAddress("REC_Calorimeter_x", &REC_Calorimeter_x, &b_REC_Calorimeter_x);
   fChain->SetBranchAddress("REC_Calorimeter_y", &REC_Calorimeter_y, &b_REC_Calorimeter_y);
   fChain->SetBranchAddress("REC_Calorimeter_z", &REC_Calorimeter_z, &b_REC_Calorimeter_z);
   fChain->SetBranchAddress("REC_Calorimeter_hx", &REC_Calorimeter_hx, &b_REC_Calorimeter_hx);
   fChain->SetBranchAddress("REC_Calorimeter_hy", &REC_Calorimeter_hy, &b_REC_Calorimeter_hy);
   fChain->SetBranchAddress("REC_Calorimeter_hz", &REC_Calorimeter_hz, &b_REC_Calorimeter_hz);
   fChain->SetBranchAddress("REC_Calorimeter_lu", &REC_Calorimeter_lu, &b_REC_Calorimeter_lu);
   fChain->SetBranchAddress("REC_Calorimeter_lv", &REC_Calorimeter_lv, &b_REC_Calorimeter_lv);
   fChain->SetBranchAddress("REC_Calorimeter_lw", &REC_Calorimeter_lw, &b_REC_Calorimeter_lw);
   fChain->SetBranchAddress("REC_Calorimeter_du", &REC_Calorimeter_du, &b_REC_Calorimeter_du);
   fChain->SetBranchAddress("REC_Calorimeter_dv", &REC_Calorimeter_dv, &b_REC_Calorimeter_dv);
   fChain->SetBranchAddress("REC_Calorimeter_dw", &REC_Calorimeter_dw, &b_REC_Calorimeter_dw);
   fChain->SetBranchAddress("REC_Calorimeter_m2u", &REC_Calorimeter_m2u, &b_REC_Calorimeter_m2u);
   fChain->SetBranchAddress("REC_Calorimeter_m2v", &REC_Calorimeter_m2v, &b_REC_Calorimeter_m2v);
   fChain->SetBranchAddress("REC_Calorimeter_m2w", &REC_Calorimeter_m2w, &b_REC_Calorimeter_m2w);
   fChain->SetBranchAddress("REC_Calorimeter_m3u", &REC_Calorimeter_m3u, &b_REC_Calorimeter_m3u);
   fChain->SetBranchAddress("REC_Calorimeter_m3v", &REC_Calorimeter_m3v, &b_REC_Calorimeter_m3v);
   fChain->SetBranchAddress("REC_Calorimeter_m3w", &REC_Calorimeter_m3w, &b_REC_Calorimeter_m3w);
   fChain->SetBranchAddress("ECAL_clusters_id", &ECAL_clusters_id, &b_ECAL_clusters_id);
   fChain->SetBranchAddress("ECAL_clusters_status", &ECAL_clusters_status, &b_ECAL_clusters_status);
   fChain->SetBranchAddress("ECAL_clusters_sector", &ECAL_clusters_sector, &b_ECAL_clusters_sector);
   fChain->SetBranchAddress("ECAL_clusters_layer", &ECAL_clusters_layer, &b_ECAL_clusters_layer);
   fChain->SetBranchAddress("ECAL_clusters_idU", &ECAL_clusters_idU, &b_ECAL_clusters_idU);
   fChain->SetBranchAddress("ECAL_clusters_idV", &ECAL_clusters_idV, &b_ECAL_clusters_idV);
   fChain->SetBranchAddress("ECAL_clusters_idW", &ECAL_clusters_idW, &b_ECAL_clusters_idW);
   fChain->SetBranchAddress("ECAL_clusters_coordU", &ECAL_clusters_coordU, &b_ECAL_clusters_coordU);
   fChain->SetBranchAddress("ECAL_clusters_coordV", &ECAL_clusters_coordV, &b_ECAL_clusters_coordV);
   fChain->SetBranchAddress("ECAL_clusters_coordW", &ECAL_clusters_coordW, &b_ECAL_clusters_coordW);
   fChain->SetBranchAddress("ECAL_clusters_x", &ECAL_clusters_x, &b_ECAL_clusters_x);
   fChain->SetBranchAddress("ECAL_clusters_y", &ECAL_clusters_y, &b_ECAL_clusters_y);
   fChain->SetBranchAddress("ECAL_clusters_z", &ECAL_clusters_z, &b_ECAL_clusters_z);
   fChain->SetBranchAddress("ECAL_clusters_energy", &ECAL_clusters_energy, &b_ECAL_clusters_energy);
   fChain->SetBranchAddress("ECAL_clusters_time", &ECAL_clusters_time, &b_ECAL_clusters_time);
   fChain->SetBranchAddress("ECAL_clusters_widthU", &ECAL_clusters_widthU, &b_ECAL_clusters_widthU);
   fChain->SetBranchAddress("ECAL_clusters_widthV", &ECAL_clusters_widthV, &b_ECAL_clusters_widthV);
   fChain->SetBranchAddress("ECAL_clusters_widthW", &ECAL_clusters_widthW, &b_ECAL_clusters_widthW);
   Notify();
}

Bool_t stage1_study::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void stage1_study::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t stage1_study::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef stage1_study_cxx

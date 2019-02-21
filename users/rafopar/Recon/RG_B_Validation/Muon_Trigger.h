//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Feb 18 12:20:21 2019 by ROOT version 6.16/00
// from TChain Moun_Trigger/
//////////////////////////////////////////////////////////

#ifndef Muon_Trigger_h
#define Muon_Trigger_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>

using namespace std;

class Muon_Trigger {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

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
   vector<long>    *CTOF_adc_sector;
   vector<long>    *CTOF_adc_layer;
   vector<long>    *CTOF_adc_component;
   vector<long>    *CTOF_adc_order;
   vector<long>    *CTOF_adc_ADC;
   vector<long>    *CTOF_adc_ped;
   vector<float>   *CTOF_adc_time;
   vector<long>    *ECAL_peaks_id;
   vector<long>    *ECAL_peaks_status;
   vector<long>    *ECAL_peaks_sector;
   vector<long>    *ECAL_peaks_layer;
   vector<float>   *ECAL_peaks_energy;
   vector<float>   *ECAL_peaks_time;
   vector<float>   *ECAL_peaks_xo;
   vector<float>   *ECAL_peaks_yo;
   vector<float>   *ECAL_peaks_zo;
   vector<float>   *ECAL_peaks_xe;
   vector<float>   *ECAL_peaks_ye;
   vector<float>   *ECAL_peaks_ze;
   vector<float>   *ECAL_peaks_width;
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
   vector<long>    *FTOF_adc_sector;
   vector<long>    *FTOF_adc_layer;
   vector<long>    *FTOF_adc_component;
   vector<long>    *FTOF_adc_order;
   vector<long>    *FTOF_adc_ADC;
   vector<long>    *FTOF_adc_ped;
   vector<float>   *FTOF_adc_time;
   vector<long>    *FTHODO_hits_sector;
   vector<long>    *FTHODO_hits_layer;
   vector<long>    *FTHODO_hits_component;
   vector<long>    *FTHODO_hits_hitID;
   vector<long>    *FTHODO_hits_clusterID;
   vector<float>   *FTHODO_hits_x;
   vector<float>   *FTHODO_hits_y;
   vector<float>   *FTHODO_hits_z;
   vector<float>   *FTHODO_hits_energy;
   vector<float>   *FTHODO_hits_time;
   vector<long>    *FT_particles_id;
   vector<long>    *FT_particles_charge;
   vector<long>    *FT_particles_calID;
   vector<long>    *FT_particles_hodoID;
   vector<long>    *FT_particles_trkID;
   vector<float>   *FT_particles_energy;
   vector<float>   *FT_particles_cx;
   vector<float>   *FT_particles_cy;
   vector<float>   *FT_particles_cz;
   vector<float>   *FT_particles_time;
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
   vector<long>    *FTHODO_clusters_size;
   vector<long>    *FTHODO_clusters_id;
   vector<float>   *FTHODO_clusters_x;
   vector<float>   *FTHODO_clusters_y;
   vector<float>   *FTHODO_clusters_z;
   vector<float>   *FTHODO_clusters_widthX;
   vector<float>   *FTHODO_clusters_widthY;
   vector<float>   *FTHODO_clusters_radius;
   vector<float>   *FTHODO_clusters_time;
   vector<float>   *FTHODO_clusters_energy;
   vector<long>    *HTCC_adc_sector;
   vector<long>    *HTCC_adc_layer;
   vector<long>    *HTCC_adc_component;
   vector<long>    *HTCC_adc_order;
   vector<long>    *HTCC_adc_ADC;
   vector<long>    *HTCC_adc_ped;
   vector<float>   *HTCC_adc_time;
   vector<long>    *CND_hits_id;
   vector<long>    *CND_hits_status;
   vector<long>    *CND_hits_trkID;
   vector<long>    *CND_hits_sector;
   vector<long>    *CND_hits_layer;
   vector<long>    *CND_hits_component;
   vector<long>    *CND_hits_indexLadc;
   vector<long>    *CND_hits_indexRadc;
   vector<long>    *CND_hits_indexLtdc;
   vector<long>    *CND_hits_indexRtdc;
   vector<float>   *CND_hits_energy;
   vector<float>   *CND_hits_time;
   vector<float>   *CND_hits_energy_unc;
   vector<float>   *CND_hits_time_unc;
   vector<float>   *CND_hits_x;
   vector<float>   *CND_hits_y;
   vector<float>   *CND_hits_z;
   vector<float>   *CND_hits_x_unc;
   vector<float>   *CND_hits_y_unc;
   vector<float>   *CND_hits_z_unc;
   vector<float>   *CND_hits_tx;
   vector<float>   *CND_hits_ty;
   vector<float>   *CND_hits_tz;
   vector<float>   *CND_hits_tlength;
   vector<float>   *CND_hits_pathlength;
   vector<long>    *FTCAL_clusters_size;
   vector<long>    *FTCAL_clusters_id;
   vector<float>   *FTCAL_clusters_x;
   vector<float>   *FTCAL_clusters_y;
   vector<float>   *FTCAL_clusters_z;
   vector<float>   *FTCAL_clusters_widthX;
   vector<float>   *FTCAL_clusters_widthY;
   vector<float>   *FTCAL_clusters_radius;
   vector<float>   *FTCAL_clusters_time;
   vector<float>   *FTCAL_clusters_energy;
   vector<float>   *FTCAL_clusters_maxEnergy;
   vector<float>   *FTCAL_clusters_recEnergy;
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
   vector<long>    *FTHODO_adc_sector;
   vector<long>    *FTHODO_adc_layer;
   vector<long>    *FTHODO_adc_component;
   vector<long>    *FTHODO_adc_order;
   vector<long>    *FTHODO_adc_ADC;
   vector<long>    *FTHODO_adc_ped;
   vector<float>   *FTHODO_adc_time;
   vector<long>    *CND_adc_sector;
   vector<long>    *CND_adc_layer;
   vector<long>    *CND_adc_component;
   vector<long>    *CND_adc_order;
   vector<long>    *CND_adc_ADC;
   vector<long>    *CND_adc_ped;
   vector<float>   *CND_adc_time;
   vector<long>    *ECAL_hits_id;
   vector<long>    *ECAL_hits_status;
   vector<long>    *ECAL_hits_sector;
   vector<long>    *ECAL_hits_layer;
   vector<long>    *ECAL_hits_strip;
   vector<long>    *ECAL_hits_peakid;
   vector<float>   *ECAL_hits_energy;
   vector<float>   *ECAL_hits_time;
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
   vector<long>    *CTOF_hits_id;
   vector<long>    *CTOF_hits_status;
   vector<long>    *CTOF_hits_trkID;
   vector<long>    *CTOF_hits_sector;
   vector<long>    *CTOF_hits_layer;
   vector<long>    *CTOF_hits_component;
   vector<long>    *CTOF_hits_adc_idx1;
   vector<long>    *CTOF_hits_adc_idx2;
   vector<long>    *CTOF_hits_tdc_idx1;
   vector<long>    *CTOF_hits_tdc_idx2;
   vector<float>   *CTOF_hits_energy;
   vector<float>   *CTOF_hits_time;
   vector<float>   *CTOF_hits_energy_unc;
   vector<float>   *CTOF_hits_time_unc;
   vector<float>   *CTOF_hits_x;
   vector<float>   *CTOF_hits_y;
   vector<float>   *CTOF_hits_z;
   vector<float>   *CTOF_hits_x_unc;
   vector<float>   *CTOF_hits_y_unc;
   vector<float>   *CTOF_hits_z_unc;
   vector<float>   *CTOF_hits_tx;
   vector<float>   *CTOF_hits_ty;
   vector<float>   *CTOF_hits_tz;
   vector<float>   *CTOF_hits_pathLength;
   vector<float>   *CTOF_hits_pathLengthThruBar;
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
   vector<long>    *FTOF_hits_id;
   vector<long>    *FTOF_hits_status;
   vector<long>    *FTOF_hits_trackid;
   vector<long>    *FTOF_hits_sector;
   vector<long>    *FTOF_hits_layer;
   vector<long>    *FTOF_hits_component;
   vector<long>    *FTOF_hits_adc_idx1;
   vector<long>    *FTOF_hits_adc_idx2;
   vector<long>    *FTOF_hits_tdc_idx1;
   vector<long>    *FTOF_hits_tdc_idx2;
   vector<float>   *FTOF_hits_energy;
   vector<float>   *FTOF_hits_time;
   vector<float>   *FTOF_hits_energy_unc;
   vector<float>   *FTOF_hits_time_unc;
   vector<float>   *FTOF_hits_x;
   vector<float>   *FTOF_hits_y;
   vector<float>   *FTOF_hits_z;
   vector<float>   *FTOF_hits_x_unc;
   vector<float>   *FTOF_hits_y_unc;
   vector<float>   *FTOF_hits_z_unc;
   vector<float>   *FTOF_hits_tx;
   vector<float>   *FTOF_hits_ty;
   vector<float>   *FTOF_hits_tz;
   vector<float>   *FTOF_hits_pathLength;
   vector<float>   *FTOF_hits_pathLengthThruBar;

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
   TBranch        *b_CTOF_adc_sector;   //!
   TBranch        *b_CTOF_adc_layer;   //!
   TBranch        *b_CTOF_adc_component;   //!
   TBranch        *b_CTOF_adc_order;   //!
   TBranch        *b_CTOF_adc_ADC;   //!
   TBranch        *b_CTOF_adc_ped;   //!
   TBranch        *b_CTOF_adc_time;   //!
   TBranch        *b_ECAL_peaks_id;   //!
   TBranch        *b_ECAL_peaks_status;   //!
   TBranch        *b_ECAL_peaks_sector;   //!
   TBranch        *b_ECAL_peaks_layer;   //!
   TBranch        *b_ECAL_peaks_energy;   //!
   TBranch        *b_ECAL_peaks_time;   //!
   TBranch        *b_ECAL_peaks_xo;   //!
   TBranch        *b_ECAL_peaks_yo;   //!
   TBranch        *b_ECAL_peaks_zo;   //!
   TBranch        *b_ECAL_peaks_xe;   //!
   TBranch        *b_ECAL_peaks_ye;   //!
   TBranch        *b_ECAL_peaks_ze;   //!
   TBranch        *b_ECAL_peaks_width;   //!
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
   TBranch        *b_FTOF_adc_sector;   //!
   TBranch        *b_FTOF_adc_layer;   //!
   TBranch        *b_FTOF_adc_component;   //!
   TBranch        *b_FTOF_adc_order;   //!
   TBranch        *b_FTOF_adc_ADC;   //!
   TBranch        *b_FTOF_adc_ped;   //!
   TBranch        *b_FTOF_adc_time;   //!
   TBranch        *b_FTHODO_hits_sector;   //!
   TBranch        *b_FTHODO_hits_layer;   //!
   TBranch        *b_FTHODO_hits_component;   //!
   TBranch        *b_FTHODO_hits_hitID;   //!
   TBranch        *b_FTHODO_hits_clusterID;   //!
   TBranch        *b_FTHODO_hits_x;   //!
   TBranch        *b_FTHODO_hits_y;   //!
   TBranch        *b_FTHODO_hits_z;   //!
   TBranch        *b_FTHODO_hits_energy;   //!
   TBranch        *b_FTHODO_hits_time;   //!
   TBranch        *b_FT_particles_id;   //!
   TBranch        *b_FT_particles_charge;   //!
   TBranch        *b_FT_particles_calID;   //!
   TBranch        *b_FT_particles_hodoID;   //!
   TBranch        *b_FT_particles_trkID;   //!
   TBranch        *b_FT_particles_energy;   //!
   TBranch        *b_FT_particles_cx;   //!
   TBranch        *b_FT_particles_cy;   //!
   TBranch        *b_FT_particles_cz;   //!
   TBranch        *b_FT_particles_time;   //!
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
   TBranch        *b_FTHODO_clusters_size;   //!
   TBranch        *b_FTHODO_clusters_id;   //!
   TBranch        *b_FTHODO_clusters_x;   //!
   TBranch        *b_FTHODO_clusters_y;   //!
   TBranch        *b_FTHODO_clusters_z;   //!
   TBranch        *b_FTHODO_clusters_widthX;   //!
   TBranch        *b_FTHODO_clusters_widthY;   //!
   TBranch        *b_FTHODO_clusters_radius;   //!
   TBranch        *b_FTHODO_clusters_time;   //!
   TBranch        *b_FTHODO_clusters_energy;   //!
   TBranch        *b_HTCC_adc_sector;   //!
   TBranch        *b_HTCC_adc_layer;   //!
   TBranch        *b_HTCC_adc_component;   //!
   TBranch        *b_HTCC_adc_order;   //!
   TBranch        *b_HTCC_adc_ADC;   //!
   TBranch        *b_HTCC_adc_ped;   //!
   TBranch        *b_HTCC_adc_time;   //!
   TBranch        *b_CND_hits_id;   //!
   TBranch        *b_CND_hits_status;   //!
   TBranch        *b_CND_hits_trkID;   //!
   TBranch        *b_CND_hits_sector;   //!
   TBranch        *b_CND_hits_layer;   //!
   TBranch        *b_CND_hits_component;   //!
   TBranch        *b_CND_hits_indexLadc;   //!
   TBranch        *b_CND_hits_indexRadc;   //!
   TBranch        *b_CND_hits_indexLtdc;   //!
   TBranch        *b_CND_hits_indexRtdc;   //!
   TBranch        *b_CND_hits_energy;   //!
   TBranch        *b_CND_hits_time;   //!
   TBranch        *b_CND_hits_energy_unc;   //!
   TBranch        *b_CND_hits_time_unc;   //!
   TBranch        *b_CND_hits_x;   //!
   TBranch        *b_CND_hits_y;   //!
   TBranch        *b_CND_hits_z;   //!
   TBranch        *b_CND_hits_x_unc;   //!
   TBranch        *b_CND_hits_y_unc;   //!
   TBranch        *b_CND_hits_z_unc;   //!
   TBranch        *b_CND_hits_tx;   //!
   TBranch        *b_CND_hits_ty;   //!
   TBranch        *b_CND_hits_tz;   //!
   TBranch        *b_CND_hits_tlength;   //!
   TBranch        *b_CND_hits_pathlength;   //!
   TBranch        *b_FTCAL_clusters_size;   //!
   TBranch        *b_FTCAL_clusters_id;   //!
   TBranch        *b_FTCAL_clusters_x;   //!
   TBranch        *b_FTCAL_clusters_y;   //!
   TBranch        *b_FTCAL_clusters_z;   //!
   TBranch        *b_FTCAL_clusters_widthX;   //!
   TBranch        *b_FTCAL_clusters_widthY;   //!
   TBranch        *b_FTCAL_clusters_radius;   //!
   TBranch        *b_FTCAL_clusters_time;   //!
   TBranch        *b_FTCAL_clusters_energy;   //!
   TBranch        *b_FTCAL_clusters_maxEnergy;   //!
   TBranch        *b_FTCAL_clusters_recEnergy;   //!
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
   TBranch        *b_FTHODO_adc_sector;   //!
   TBranch        *b_FTHODO_adc_layer;   //!
   TBranch        *b_FTHODO_adc_component;   //!
   TBranch        *b_FTHODO_adc_order;   //!
   TBranch        *b_FTHODO_adc_ADC;   //!
   TBranch        *b_FTHODO_adc_ped;   //!
   TBranch        *b_FTHODO_adc_time;   //!
   TBranch        *b_CND_adc_sector;   //!
   TBranch        *b_CND_adc_layer;   //!
   TBranch        *b_CND_adc_component;   //!
   TBranch        *b_CND_adc_order;   //!
   TBranch        *b_CND_adc_ADC;   //!
   TBranch        *b_CND_adc_ped;   //!
   TBranch        *b_CND_adc_time;   //!
   TBranch        *b_ECAL_hits_id;   //!
   TBranch        *b_ECAL_hits_status;   //!
   TBranch        *b_ECAL_hits_sector;   //!
   TBranch        *b_ECAL_hits_layer;   //!
   TBranch        *b_ECAL_hits_strip;   //!
   TBranch        *b_ECAL_hits_peakid;   //!
   TBranch        *b_ECAL_hits_energy;   //!
   TBranch        *b_ECAL_hits_time;   //!
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
   TBranch        *b_CTOF_hits_id;   //!
   TBranch        *b_CTOF_hits_status;   //!
   TBranch        *b_CTOF_hits_trkID;   //!
   TBranch        *b_CTOF_hits_sector;   //!
   TBranch        *b_CTOF_hits_layer;   //!
   TBranch        *b_CTOF_hits_component;   //!
   TBranch        *b_CTOF_hits_adc_idx1;   //!
   TBranch        *b_CTOF_hits_adc_idx2;   //!
   TBranch        *b_CTOF_hits_tdc_idx1;   //!
   TBranch        *b_CTOF_hits_tdc_idx2;   //!
   TBranch        *b_CTOF_hits_energy;   //!
   TBranch        *b_CTOF_hits_time;   //!
   TBranch        *b_CTOF_hits_energy_unc;   //!
   TBranch        *b_CTOF_hits_time_unc;   //!
   TBranch        *b_CTOF_hits_x;   //!
   TBranch        *b_CTOF_hits_y;   //!
   TBranch        *b_CTOF_hits_z;   //!
   TBranch        *b_CTOF_hits_x_unc;   //!
   TBranch        *b_CTOF_hits_y_unc;   //!
   TBranch        *b_CTOF_hits_z_unc;   //!
   TBranch        *b_CTOF_hits_tx;   //!
   TBranch        *b_CTOF_hits_ty;   //!
   TBranch        *b_CTOF_hits_tz;   //!
   TBranch        *b_CTOF_hits_pathLength;   //!
   TBranch        *b_CTOF_hits_pathLengthThruBar;   //!
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
   TBranch        *b_FTOF_hits_id;   //!
   TBranch        *b_FTOF_hits_status;   //!
   TBranch        *b_FTOF_hits_trackid;   //!
   TBranch        *b_FTOF_hits_sector;   //!
   TBranch        *b_FTOF_hits_layer;   //!
   TBranch        *b_FTOF_hits_component;   //!
   TBranch        *b_FTOF_hits_adc_idx1;   //!
   TBranch        *b_FTOF_hits_adc_idx2;   //!
   TBranch        *b_FTOF_hits_tdc_idx1;   //!
   TBranch        *b_FTOF_hits_tdc_idx2;   //!
   TBranch        *b_FTOF_hits_energy;   //!
   TBranch        *b_FTOF_hits_time;   //!
   TBranch        *b_FTOF_hits_energy_unc;   //!
   TBranch        *b_FTOF_hits_time_unc;   //!
   TBranch        *b_FTOF_hits_x;   //!
   TBranch        *b_FTOF_hits_y;   //!
   TBranch        *b_FTOF_hits_z;   //!
   TBranch        *b_FTOF_hits_x_unc;   //!
   TBranch        *b_FTOF_hits_y_unc;   //!
   TBranch        *b_FTOF_hits_z_unc;   //!
   TBranch        *b_FTOF_hits_tx;   //!
   TBranch        *b_FTOF_hits_ty;   //!
   TBranch        *b_FTOF_hits_tz;   //!
   TBranch        *b_FTOF_hits_pathLength;   //!
   TBranch        *b_FTOF_hits_pathLengthThruBar;   //!

   Muon_Trigger(TTree *tree=0);
   virtual ~Muon_Trigger();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Muon_Trigger_cxx
Muon_Trigger::Muon_Trigger(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("Moun_Trigger",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("Moun_Trigger","");
      chain->Add("Data/skimmed_Muon_Trigger.root/hipo2root");
      //chain->Add("Data/mon_clas_006243.evio.*.root/hipo2root");
      //chain->Add("Data/mon_clas_006243.evio.00107.root/hipo2root");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

Muon_Trigger::~Muon_Trigger()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Muon_Trigger::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Muon_Trigger::LoadTree(Long64_t entry)
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

void Muon_Trigger::Init(TTree *tree)
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
   CTOF_adc_sector = 0;
   CTOF_adc_layer = 0;
   CTOF_adc_component = 0;
   CTOF_adc_order = 0;
   CTOF_adc_ADC = 0;
   CTOF_adc_ped = 0;
   CTOF_adc_time = 0;
   ECAL_peaks_id = 0;
   ECAL_peaks_status = 0;
   ECAL_peaks_sector = 0;
   ECAL_peaks_layer = 0;
   ECAL_peaks_energy = 0;
   ECAL_peaks_time = 0;
   ECAL_peaks_xo = 0;
   ECAL_peaks_yo = 0;
   ECAL_peaks_zo = 0;
   ECAL_peaks_xe = 0;
   ECAL_peaks_ye = 0;
   ECAL_peaks_ze = 0;
   ECAL_peaks_width = 0;
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
   FTOF_adc_sector = 0;
   FTOF_adc_layer = 0;
   FTOF_adc_component = 0;
   FTOF_adc_order = 0;
   FTOF_adc_ADC = 0;
   FTOF_adc_ped = 0;
   FTOF_adc_time = 0;
   FTHODO_hits_sector = 0;
   FTHODO_hits_layer = 0;
   FTHODO_hits_component = 0;
   FTHODO_hits_hitID = 0;
   FTHODO_hits_clusterID = 0;
   FTHODO_hits_x = 0;
   FTHODO_hits_y = 0;
   FTHODO_hits_z = 0;
   FTHODO_hits_energy = 0;
   FTHODO_hits_time = 0;
   FT_particles_id = 0;
   FT_particles_charge = 0;
   FT_particles_calID = 0;
   FT_particles_hodoID = 0;
   FT_particles_trkID = 0;
   FT_particles_energy = 0;
   FT_particles_cx = 0;
   FT_particles_cy = 0;
   FT_particles_cz = 0;
   FT_particles_time = 0;
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
   FTHODO_clusters_size = 0;
   FTHODO_clusters_id = 0;
   FTHODO_clusters_x = 0;
   FTHODO_clusters_y = 0;
   FTHODO_clusters_z = 0;
   FTHODO_clusters_widthX = 0;
   FTHODO_clusters_widthY = 0;
   FTHODO_clusters_radius = 0;
   FTHODO_clusters_time = 0;
   FTHODO_clusters_energy = 0;
   HTCC_adc_sector = 0;
   HTCC_adc_layer = 0;
   HTCC_adc_component = 0;
   HTCC_adc_order = 0;
   HTCC_adc_ADC = 0;
   HTCC_adc_ped = 0;
   HTCC_adc_time = 0;
   CND_hits_id = 0;
   CND_hits_status = 0;
   CND_hits_trkID = 0;
   CND_hits_sector = 0;
   CND_hits_layer = 0;
   CND_hits_component = 0;
   CND_hits_indexLadc = 0;
   CND_hits_indexRadc = 0;
   CND_hits_indexLtdc = 0;
   CND_hits_indexRtdc = 0;
   CND_hits_energy = 0;
   CND_hits_time = 0;
   CND_hits_energy_unc = 0;
   CND_hits_time_unc = 0;
   CND_hits_x = 0;
   CND_hits_y = 0;
   CND_hits_z = 0;
   CND_hits_x_unc = 0;
   CND_hits_y_unc = 0;
   CND_hits_z_unc = 0;
   CND_hits_tx = 0;
   CND_hits_ty = 0;
   CND_hits_tz = 0;
   CND_hits_tlength = 0;
   CND_hits_pathlength = 0;
   FTCAL_clusters_size = 0;
   FTCAL_clusters_id = 0;
   FTCAL_clusters_x = 0;
   FTCAL_clusters_y = 0;
   FTCAL_clusters_z = 0;
   FTCAL_clusters_widthX = 0;
   FTCAL_clusters_widthY = 0;
   FTCAL_clusters_radius = 0;
   FTCAL_clusters_time = 0;
   FTCAL_clusters_energy = 0;
   FTCAL_clusters_maxEnergy = 0;
   FTCAL_clusters_recEnergy = 0;
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
   FTHODO_adc_sector = 0;
   FTHODO_adc_layer = 0;
   FTHODO_adc_component = 0;
   FTHODO_adc_order = 0;
   FTHODO_adc_ADC = 0;
   FTHODO_adc_ped = 0;
   FTHODO_adc_time = 0;
   CND_adc_sector = 0;
   CND_adc_layer = 0;
   CND_adc_component = 0;
   CND_adc_order = 0;
   CND_adc_ADC = 0;
   CND_adc_ped = 0;
   CND_adc_time = 0;
   ECAL_hits_id = 0;
   ECAL_hits_status = 0;
   ECAL_hits_sector = 0;
   ECAL_hits_layer = 0;
   ECAL_hits_strip = 0;
   ECAL_hits_peakid = 0;
   ECAL_hits_energy = 0;
   ECAL_hits_time = 0;
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
   CTOF_hits_id = 0;
   CTOF_hits_status = 0;
   CTOF_hits_trkID = 0;
   CTOF_hits_sector = 0;
   CTOF_hits_layer = 0;
   CTOF_hits_component = 0;
   CTOF_hits_adc_idx1 = 0;
   CTOF_hits_adc_idx2 = 0;
   CTOF_hits_tdc_idx1 = 0;
   CTOF_hits_tdc_idx2 = 0;
   CTOF_hits_energy = 0;
   CTOF_hits_time = 0;
   CTOF_hits_energy_unc = 0;
   CTOF_hits_time_unc = 0;
   CTOF_hits_x = 0;
   CTOF_hits_y = 0;
   CTOF_hits_z = 0;
   CTOF_hits_x_unc = 0;
   CTOF_hits_y_unc = 0;
   CTOF_hits_z_unc = 0;
   CTOF_hits_tx = 0;
   CTOF_hits_ty = 0;
   CTOF_hits_tz = 0;
   CTOF_hits_pathLength = 0;
   CTOF_hits_pathLengthThruBar = 0;
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
   FTOF_hits_id = 0;
   FTOF_hits_status = 0;
   FTOF_hits_trackid = 0;
   FTOF_hits_sector = 0;
   FTOF_hits_layer = 0;
   FTOF_hits_component = 0;
   FTOF_hits_adc_idx1 = 0;
   FTOF_hits_adc_idx2 = 0;
   FTOF_hits_tdc_idx1 = 0;
   FTOF_hits_tdc_idx2 = 0;
   FTOF_hits_energy = 0;
   FTOF_hits_time = 0;
   FTOF_hits_energy_unc = 0;
   FTOF_hits_time_unc = 0;
   FTOF_hits_x = 0;
   FTOF_hits_y = 0;
   FTOF_hits_z = 0;
   FTOF_hits_x_unc = 0;
   FTOF_hits_y_unc = 0;
   FTOF_hits_z_unc = 0;
   FTOF_hits_tx = 0;
   FTOF_hits_ty = 0;
   FTOF_hits_tz = 0;
   FTOF_hits_pathLength = 0;
   FTOF_hits_pathLengthThruBar = 0;
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
   fChain->SetBranchAddress("CTOF_adc_sector", &CTOF_adc_sector, &b_CTOF_adc_sector);
   fChain->SetBranchAddress("CTOF_adc_layer", &CTOF_adc_layer, &b_CTOF_adc_layer);
   fChain->SetBranchAddress("CTOF_adc_component", &CTOF_adc_component, &b_CTOF_adc_component);
   fChain->SetBranchAddress("CTOF_adc_order", &CTOF_adc_order, &b_CTOF_adc_order);
   fChain->SetBranchAddress("CTOF_adc_ADC", &CTOF_adc_ADC, &b_CTOF_adc_ADC);
   fChain->SetBranchAddress("CTOF_adc_ped", &CTOF_adc_ped, &b_CTOF_adc_ped);
   fChain->SetBranchAddress("CTOF_adc_time", &CTOF_adc_time, &b_CTOF_adc_time);
   fChain->SetBranchAddress("ECAL_peaks_id", &ECAL_peaks_id, &b_ECAL_peaks_id);
   fChain->SetBranchAddress("ECAL_peaks_status", &ECAL_peaks_status, &b_ECAL_peaks_status);
   fChain->SetBranchAddress("ECAL_peaks_sector", &ECAL_peaks_sector, &b_ECAL_peaks_sector);
   fChain->SetBranchAddress("ECAL_peaks_layer", &ECAL_peaks_layer, &b_ECAL_peaks_layer);
   fChain->SetBranchAddress("ECAL_peaks_energy", &ECAL_peaks_energy, &b_ECAL_peaks_energy);
   fChain->SetBranchAddress("ECAL_peaks_time", &ECAL_peaks_time, &b_ECAL_peaks_time);
   fChain->SetBranchAddress("ECAL_peaks_xo", &ECAL_peaks_xo, &b_ECAL_peaks_xo);
   fChain->SetBranchAddress("ECAL_peaks_yo", &ECAL_peaks_yo, &b_ECAL_peaks_yo);
   fChain->SetBranchAddress("ECAL_peaks_zo", &ECAL_peaks_zo, &b_ECAL_peaks_zo);
   fChain->SetBranchAddress("ECAL_peaks_xe", &ECAL_peaks_xe, &b_ECAL_peaks_xe);
   fChain->SetBranchAddress("ECAL_peaks_ye", &ECAL_peaks_ye, &b_ECAL_peaks_ye);
   fChain->SetBranchAddress("ECAL_peaks_ze", &ECAL_peaks_ze, &b_ECAL_peaks_ze);
   fChain->SetBranchAddress("ECAL_peaks_width", &ECAL_peaks_width, &b_ECAL_peaks_width);
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
   fChain->SetBranchAddress("FTOF_adc_sector", &FTOF_adc_sector, &b_FTOF_adc_sector);
   fChain->SetBranchAddress("FTOF_adc_layer", &FTOF_adc_layer, &b_FTOF_adc_layer);
   fChain->SetBranchAddress("FTOF_adc_component", &FTOF_adc_component, &b_FTOF_adc_component);
   fChain->SetBranchAddress("FTOF_adc_order", &FTOF_adc_order, &b_FTOF_adc_order);
   fChain->SetBranchAddress("FTOF_adc_ADC", &FTOF_adc_ADC, &b_FTOF_adc_ADC);
   fChain->SetBranchAddress("FTOF_adc_ped", &FTOF_adc_ped, &b_FTOF_adc_ped);
   fChain->SetBranchAddress("FTOF_adc_time", &FTOF_adc_time, &b_FTOF_adc_time);
   fChain->SetBranchAddress("FTHODO_hits_sector", &FTHODO_hits_sector, &b_FTHODO_hits_sector);
   fChain->SetBranchAddress("FTHODO_hits_layer", &FTHODO_hits_layer, &b_FTHODO_hits_layer);
   fChain->SetBranchAddress("FTHODO_hits_component", &FTHODO_hits_component, &b_FTHODO_hits_component);
   fChain->SetBranchAddress("FTHODO_hits_hitID", &FTHODO_hits_hitID, &b_FTHODO_hits_hitID);
   fChain->SetBranchAddress("FTHODO_hits_clusterID", &FTHODO_hits_clusterID, &b_FTHODO_hits_clusterID);
   fChain->SetBranchAddress("FTHODO_hits_x", &FTHODO_hits_x, &b_FTHODO_hits_x);
   fChain->SetBranchAddress("FTHODO_hits_y", &FTHODO_hits_y, &b_FTHODO_hits_y);
   fChain->SetBranchAddress("FTHODO_hits_z", &FTHODO_hits_z, &b_FTHODO_hits_z);
   fChain->SetBranchAddress("FTHODO_hits_energy", &FTHODO_hits_energy, &b_FTHODO_hits_energy);
   fChain->SetBranchAddress("FTHODO_hits_time", &FTHODO_hits_time, &b_FTHODO_hits_time);
   fChain->SetBranchAddress("FT_particles_id", &FT_particles_id, &b_FT_particles_id);
   fChain->SetBranchAddress("FT_particles_charge", &FT_particles_charge, &b_FT_particles_charge);
   fChain->SetBranchAddress("FT_particles_calID", &FT_particles_calID, &b_FT_particles_calID);
   fChain->SetBranchAddress("FT_particles_hodoID", &FT_particles_hodoID, &b_FT_particles_hodoID);
   fChain->SetBranchAddress("FT_particles_trkID", &FT_particles_trkID, &b_FT_particles_trkID);
   fChain->SetBranchAddress("FT_particles_energy", &FT_particles_energy, &b_FT_particles_energy);
   fChain->SetBranchAddress("FT_particles_cx", &FT_particles_cx, &b_FT_particles_cx);
   fChain->SetBranchAddress("FT_particles_cy", &FT_particles_cy, &b_FT_particles_cy);
   fChain->SetBranchAddress("FT_particles_cz", &FT_particles_cz, &b_FT_particles_cz);
   fChain->SetBranchAddress("FT_particles_time", &FT_particles_time, &b_FT_particles_time);
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
   fChain->SetBranchAddress("FTHODO_clusters_size", &FTHODO_clusters_size, &b_FTHODO_clusters_size);
   fChain->SetBranchAddress("FTHODO_clusters_id", &FTHODO_clusters_id, &b_FTHODO_clusters_id);
   fChain->SetBranchAddress("FTHODO_clusters_x", &FTHODO_clusters_x, &b_FTHODO_clusters_x);
   fChain->SetBranchAddress("FTHODO_clusters_y", &FTHODO_clusters_y, &b_FTHODO_clusters_y);
   fChain->SetBranchAddress("FTHODO_clusters_z", &FTHODO_clusters_z, &b_FTHODO_clusters_z);
   fChain->SetBranchAddress("FTHODO_clusters_widthX", &FTHODO_clusters_widthX, &b_FTHODO_clusters_widthX);
   fChain->SetBranchAddress("FTHODO_clusters_widthY", &FTHODO_clusters_widthY, &b_FTHODO_clusters_widthY);
   fChain->SetBranchAddress("FTHODO_clusters_radius", &FTHODO_clusters_radius, &b_FTHODO_clusters_radius);
   fChain->SetBranchAddress("FTHODO_clusters_time", &FTHODO_clusters_time, &b_FTHODO_clusters_time);
   fChain->SetBranchAddress("FTHODO_clusters_energy", &FTHODO_clusters_energy, &b_FTHODO_clusters_energy);
   fChain->SetBranchAddress("HTCC_adc_sector", &HTCC_adc_sector, &b_HTCC_adc_sector);
   fChain->SetBranchAddress("HTCC_adc_layer", &HTCC_adc_layer, &b_HTCC_adc_layer);
   fChain->SetBranchAddress("HTCC_adc_component", &HTCC_adc_component, &b_HTCC_adc_component);
   fChain->SetBranchAddress("HTCC_adc_order", &HTCC_adc_order, &b_HTCC_adc_order);
   fChain->SetBranchAddress("HTCC_adc_ADC", &HTCC_adc_ADC, &b_HTCC_adc_ADC);
   fChain->SetBranchAddress("HTCC_adc_ped", &HTCC_adc_ped, &b_HTCC_adc_ped);
   fChain->SetBranchAddress("HTCC_adc_time", &HTCC_adc_time, &b_HTCC_adc_time);
   fChain->SetBranchAddress("CND_hits_id", &CND_hits_id, &b_CND_hits_id);
   fChain->SetBranchAddress("CND_hits_status", &CND_hits_status, &b_CND_hits_status);
   fChain->SetBranchAddress("CND_hits_trkID", &CND_hits_trkID, &b_CND_hits_trkID);
   fChain->SetBranchAddress("CND_hits_sector", &CND_hits_sector, &b_CND_hits_sector);
   fChain->SetBranchAddress("CND_hits_layer", &CND_hits_layer, &b_CND_hits_layer);
   fChain->SetBranchAddress("CND_hits_component", &CND_hits_component, &b_CND_hits_component);
   fChain->SetBranchAddress("CND_hits_indexLadc", &CND_hits_indexLadc, &b_CND_hits_indexLadc);
   fChain->SetBranchAddress("CND_hits_indexRadc", &CND_hits_indexRadc, &b_CND_hits_indexRadc);
   fChain->SetBranchAddress("CND_hits_indexLtdc", &CND_hits_indexLtdc, &b_CND_hits_indexLtdc);
   fChain->SetBranchAddress("CND_hits_indexRtdc", &CND_hits_indexRtdc, &b_CND_hits_indexRtdc);
   fChain->SetBranchAddress("CND_hits_energy", &CND_hits_energy, &b_CND_hits_energy);
   fChain->SetBranchAddress("CND_hits_time", &CND_hits_time, &b_CND_hits_time);
   fChain->SetBranchAddress("CND_hits_energy_unc", &CND_hits_energy_unc, &b_CND_hits_energy_unc);
   fChain->SetBranchAddress("CND_hits_time_unc", &CND_hits_time_unc, &b_CND_hits_time_unc);
   fChain->SetBranchAddress("CND_hits_x", &CND_hits_x, &b_CND_hits_x);
   fChain->SetBranchAddress("CND_hits_y", &CND_hits_y, &b_CND_hits_y);
   fChain->SetBranchAddress("CND_hits_z", &CND_hits_z, &b_CND_hits_z);
   fChain->SetBranchAddress("CND_hits_x_unc", &CND_hits_x_unc, &b_CND_hits_x_unc);
   fChain->SetBranchAddress("CND_hits_y_unc", &CND_hits_y_unc, &b_CND_hits_y_unc);
   fChain->SetBranchAddress("CND_hits_z_unc", &CND_hits_z_unc, &b_CND_hits_z_unc);
   fChain->SetBranchAddress("CND_hits_tx", &CND_hits_tx, &b_CND_hits_tx);
   fChain->SetBranchAddress("CND_hits_ty", &CND_hits_ty, &b_CND_hits_ty);
   fChain->SetBranchAddress("CND_hits_tz", &CND_hits_tz, &b_CND_hits_tz);
   fChain->SetBranchAddress("CND_hits_tlength", &CND_hits_tlength, &b_CND_hits_tlength);
   fChain->SetBranchAddress("CND_hits_pathlength", &CND_hits_pathlength, &b_CND_hits_pathlength);
   fChain->SetBranchAddress("FTCAL_clusters_size", &FTCAL_clusters_size, &b_FTCAL_clusters_size);
   fChain->SetBranchAddress("FTCAL_clusters_id", &FTCAL_clusters_id, &b_FTCAL_clusters_id);
   fChain->SetBranchAddress("FTCAL_clusters_x", &FTCAL_clusters_x, &b_FTCAL_clusters_x);
   fChain->SetBranchAddress("FTCAL_clusters_y", &FTCAL_clusters_y, &b_FTCAL_clusters_y);
   fChain->SetBranchAddress("FTCAL_clusters_z", &FTCAL_clusters_z, &b_FTCAL_clusters_z);
   fChain->SetBranchAddress("FTCAL_clusters_widthX", &FTCAL_clusters_widthX, &b_FTCAL_clusters_widthX);
   fChain->SetBranchAddress("FTCAL_clusters_widthY", &FTCAL_clusters_widthY, &b_FTCAL_clusters_widthY);
   fChain->SetBranchAddress("FTCAL_clusters_radius", &FTCAL_clusters_radius, &b_FTCAL_clusters_radius);
   fChain->SetBranchAddress("FTCAL_clusters_time", &FTCAL_clusters_time, &b_FTCAL_clusters_time);
   fChain->SetBranchAddress("FTCAL_clusters_energy", &FTCAL_clusters_energy, &b_FTCAL_clusters_energy);
   fChain->SetBranchAddress("FTCAL_clusters_maxEnergy", &FTCAL_clusters_maxEnergy, &b_FTCAL_clusters_maxEnergy);
   fChain->SetBranchAddress("FTCAL_clusters_recEnergy", &FTCAL_clusters_recEnergy, &b_FTCAL_clusters_recEnergy);
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
   fChain->SetBranchAddress("FTHODO_adc_sector", &FTHODO_adc_sector, &b_FTHODO_adc_sector);
   fChain->SetBranchAddress("FTHODO_adc_layer", &FTHODO_adc_layer, &b_FTHODO_adc_layer);
   fChain->SetBranchAddress("FTHODO_adc_component", &FTHODO_adc_component, &b_FTHODO_adc_component);
   fChain->SetBranchAddress("FTHODO_adc_order", &FTHODO_adc_order, &b_FTHODO_adc_order);
   fChain->SetBranchAddress("FTHODO_adc_ADC", &FTHODO_adc_ADC, &b_FTHODO_adc_ADC);
   fChain->SetBranchAddress("FTHODO_adc_ped", &FTHODO_adc_ped, &b_FTHODO_adc_ped);
   fChain->SetBranchAddress("FTHODO_adc_time", &FTHODO_adc_time, &b_FTHODO_adc_time);
   fChain->SetBranchAddress("CND_adc_sector", &CND_adc_sector, &b_CND_adc_sector);
   fChain->SetBranchAddress("CND_adc_layer", &CND_adc_layer, &b_CND_adc_layer);
   fChain->SetBranchAddress("CND_adc_component", &CND_adc_component, &b_CND_adc_component);
   fChain->SetBranchAddress("CND_adc_order", &CND_adc_order, &b_CND_adc_order);
   fChain->SetBranchAddress("CND_adc_ADC", &CND_adc_ADC, &b_CND_adc_ADC);
   fChain->SetBranchAddress("CND_adc_ped", &CND_adc_ped, &b_CND_adc_ped);
   fChain->SetBranchAddress("CND_adc_time", &CND_adc_time, &b_CND_adc_time);
   fChain->SetBranchAddress("ECAL_hits_id", &ECAL_hits_id, &b_ECAL_hits_id);
   fChain->SetBranchAddress("ECAL_hits_status", &ECAL_hits_status, &b_ECAL_hits_status);
   fChain->SetBranchAddress("ECAL_hits_sector", &ECAL_hits_sector, &b_ECAL_hits_sector);
   fChain->SetBranchAddress("ECAL_hits_layer", &ECAL_hits_layer, &b_ECAL_hits_layer);
   fChain->SetBranchAddress("ECAL_hits_strip", &ECAL_hits_strip, &b_ECAL_hits_strip);
   fChain->SetBranchAddress("ECAL_hits_peakid", &ECAL_hits_peakid, &b_ECAL_hits_peakid);
   fChain->SetBranchAddress("ECAL_hits_energy", &ECAL_hits_energy, &b_ECAL_hits_energy);
   fChain->SetBranchAddress("ECAL_hits_time", &ECAL_hits_time, &b_ECAL_hits_time);
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
   fChain->SetBranchAddress("CTOF_hits_id", &CTOF_hits_id, &b_CTOF_hits_id);
   fChain->SetBranchAddress("CTOF_hits_status", &CTOF_hits_status, &b_CTOF_hits_status);
   fChain->SetBranchAddress("CTOF_hits_trkID", &CTOF_hits_trkID, &b_CTOF_hits_trkID);
   fChain->SetBranchAddress("CTOF_hits_sector", &CTOF_hits_sector, &b_CTOF_hits_sector);
   fChain->SetBranchAddress("CTOF_hits_layer", &CTOF_hits_layer, &b_CTOF_hits_layer);
   fChain->SetBranchAddress("CTOF_hits_component", &CTOF_hits_component, &b_CTOF_hits_component);
   fChain->SetBranchAddress("CTOF_hits_adc_idx1", &CTOF_hits_adc_idx1, &b_CTOF_hits_adc_idx1);
   fChain->SetBranchAddress("CTOF_hits_adc_idx2", &CTOF_hits_adc_idx2, &b_CTOF_hits_adc_idx2);
   fChain->SetBranchAddress("CTOF_hits_tdc_idx1", &CTOF_hits_tdc_idx1, &b_CTOF_hits_tdc_idx1);
   fChain->SetBranchAddress("CTOF_hits_tdc_idx2", &CTOF_hits_tdc_idx2, &b_CTOF_hits_tdc_idx2);
   fChain->SetBranchAddress("CTOF_hits_energy", &CTOF_hits_energy, &b_CTOF_hits_energy);
   fChain->SetBranchAddress("CTOF_hits_time", &CTOF_hits_time, &b_CTOF_hits_time);
   fChain->SetBranchAddress("CTOF_hits_energy_unc", &CTOF_hits_energy_unc, &b_CTOF_hits_energy_unc);
   fChain->SetBranchAddress("CTOF_hits_time_unc", &CTOF_hits_time_unc, &b_CTOF_hits_time_unc);
   fChain->SetBranchAddress("CTOF_hits_x", &CTOF_hits_x, &b_CTOF_hits_x);
   fChain->SetBranchAddress("CTOF_hits_y", &CTOF_hits_y, &b_CTOF_hits_y);
   fChain->SetBranchAddress("CTOF_hits_z", &CTOF_hits_z, &b_CTOF_hits_z);
   fChain->SetBranchAddress("CTOF_hits_x_unc", &CTOF_hits_x_unc, &b_CTOF_hits_x_unc);
   fChain->SetBranchAddress("CTOF_hits_y_unc", &CTOF_hits_y_unc, &b_CTOF_hits_y_unc);
   fChain->SetBranchAddress("CTOF_hits_z_unc", &CTOF_hits_z_unc, &b_CTOF_hits_z_unc);
   fChain->SetBranchAddress("CTOF_hits_tx", &CTOF_hits_tx, &b_CTOF_hits_tx);
   fChain->SetBranchAddress("CTOF_hits_ty", &CTOF_hits_ty, &b_CTOF_hits_ty);
   fChain->SetBranchAddress("CTOF_hits_tz", &CTOF_hits_tz, &b_CTOF_hits_tz);
   fChain->SetBranchAddress("CTOF_hits_pathLength", &CTOF_hits_pathLength, &b_CTOF_hits_pathLength);
   fChain->SetBranchAddress("CTOF_hits_pathLengthThruBar", &CTOF_hits_pathLengthThruBar, &b_CTOF_hits_pathLengthThruBar);
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
   fChain->SetBranchAddress("FTOF_hits_id", &FTOF_hits_id, &b_FTOF_hits_id);
   fChain->SetBranchAddress("FTOF_hits_status", &FTOF_hits_status, &b_FTOF_hits_status);
   fChain->SetBranchAddress("FTOF_hits_trackid", &FTOF_hits_trackid, &b_FTOF_hits_trackid);
   fChain->SetBranchAddress("FTOF_hits_sector", &FTOF_hits_sector, &b_FTOF_hits_sector);
   fChain->SetBranchAddress("FTOF_hits_layer", &FTOF_hits_layer, &b_FTOF_hits_layer);
   fChain->SetBranchAddress("FTOF_hits_component", &FTOF_hits_component, &b_FTOF_hits_component);
   fChain->SetBranchAddress("FTOF_hits_adc_idx1", &FTOF_hits_adc_idx1, &b_FTOF_hits_adc_idx1);
   fChain->SetBranchAddress("FTOF_hits_adc_idx2", &FTOF_hits_adc_idx2, &b_FTOF_hits_adc_idx2);
   fChain->SetBranchAddress("FTOF_hits_tdc_idx1", &FTOF_hits_tdc_idx1, &b_FTOF_hits_tdc_idx1);
   fChain->SetBranchAddress("FTOF_hits_tdc_idx2", &FTOF_hits_tdc_idx2, &b_FTOF_hits_tdc_idx2);
   fChain->SetBranchAddress("FTOF_hits_energy", &FTOF_hits_energy, &b_FTOF_hits_energy);
   fChain->SetBranchAddress("FTOF_hits_time", &FTOF_hits_time, &b_FTOF_hits_time);
   fChain->SetBranchAddress("FTOF_hits_energy_unc", &FTOF_hits_energy_unc, &b_FTOF_hits_energy_unc);
   fChain->SetBranchAddress("FTOF_hits_time_unc", &FTOF_hits_time_unc, &b_FTOF_hits_time_unc);
   fChain->SetBranchAddress("FTOF_hits_x", &FTOF_hits_x, &b_FTOF_hits_x);
   fChain->SetBranchAddress("FTOF_hits_y", &FTOF_hits_y, &b_FTOF_hits_y);
   fChain->SetBranchAddress("FTOF_hits_z", &FTOF_hits_z, &b_FTOF_hits_z);
   fChain->SetBranchAddress("FTOF_hits_x_unc", &FTOF_hits_x_unc, &b_FTOF_hits_x_unc);
   fChain->SetBranchAddress("FTOF_hits_y_unc", &FTOF_hits_y_unc, &b_FTOF_hits_y_unc);
   fChain->SetBranchAddress("FTOF_hits_z_unc", &FTOF_hits_z_unc, &b_FTOF_hits_z_unc);
   fChain->SetBranchAddress("FTOF_hits_tx", &FTOF_hits_tx, &b_FTOF_hits_tx);
   fChain->SetBranchAddress("FTOF_hits_ty", &FTOF_hits_ty, &b_FTOF_hits_ty);
   fChain->SetBranchAddress("FTOF_hits_tz", &FTOF_hits_tz, &b_FTOF_hits_tz);
   fChain->SetBranchAddress("FTOF_hits_pathLength", &FTOF_hits_pathLength, &b_FTOF_hits_pathLength);
   fChain->SetBranchAddress("FTOF_hits_pathLengthThruBar", &FTOF_hits_pathLengthThruBar, &b_FTOF_hits_pathLengthThruBar);
   Notify();
}

Bool_t Muon_Trigger::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Muon_Trigger::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Muon_Trigger::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Muon_Trigger_cxx

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VTPRoot.cxx
 * Author: rafopar
 * 
 * Created on January 6, 2018, 4:47 PM
 */

/*
 * This class should be similar to ECTrig, which is supposed to decode VTP
 * banks from EVIO data, while this one should decode VTP banks from the
 * offline root files, which are created through hipo2root rhipo3 package
 * 
 * Of course there are some differences because of different formats in EVIO and
 * Root.
 */


#include "VTPRoot.hh"

map<int, int> VTPRoot::EC_vtp_sector = {
    {100, 10}, // Global trigger

    // ================= GEMC ==============
    {60101, 0},    {60102, 1},    {60103, 2},    {60104, 3},    {60105, 4},    {60106, 5}, // ECal
    {60107, 0},    {60108, 1},    {60109, 2},    {60110, 3},    {60111, 4},    {60112, 5}, // PCal
    {60094, 0},    {60095, 1},    {60096, 2},    {60097, 3},    {60098, 4},    {60099, 5}, // FTOF
    {60093, 7}, // HTCC
    // ================= Data ==============
    {113, 0},     {114, 1},     {115, 2},     {116, 3},     {117, 4},     {118, 5}, // DC Region3
    {118, 0},     {119, 1},     {120, 2},     {121, 3},     {122, 4},     {123, 5}, // DC Region1
    {86, 0},      {87, 1},      {88, 2},      {89, 3},      {90, 4},      {91, 5}, // DC Region2    
    {101, 0},    {102, 1},    {103, 2},    {104, 3},    {105, 4},    {106, 5}, // ECal
    {107, 0},    {108, 1},    {109, 2},    {110, 3},    {111, 4},    {112, 5}, // PCal
    {94, 0},     {95, 1},     {96, 2},     {97, 3},     {98, 4},     {99, 5},  // PCal
    {93, 7} // HTCC

};

map<int, int> VTPRoot::EC_vtp_Detector = {
    // ================= GEMC ==============
    {100, 0}, // Global trigger
    {60101, 1},    {60102, 1},    {60103, 1},    {60104, 1},    {60105, 1},    {60106, 1}, // ECal
    {60107, 2},    {60108, 2},    {60109, 2},    {60110, 2},    {60111, 2},    {60112, 2}, // PCal
    {60094, 3},    {60095, 3},    {60096, 3},    {60097, 3},    {60098, 3},    {60099, 3}, // FTOF
    {60093, 4}, // HTCC
    // ================= Data ==============
    {101, 1},    {102, 1},    {103, 1},    {104, 1},    {105, 1},    {106, 1}, // ECal
    {107, 2},    {108, 2},    {109, 2},    {110, 2},    {111, 2},    {112, 2}, // PCal
    {94, 3},     {95, 3},     {96, 3},     {97, 3},     {98, 3},     {99, 3},  // FTOF
    {93, 4}, // HTCC
    {92, 5}, // CND    
    {113, 6},     {114, 6},     {115, 6},     {116, 6},     {117, 6},     {118, 6}, // DC Region 3
    {86, 7},      {87, 7},      {88, 7},      {89, 7},      {90, 7},      {91, 7},  // DC Region 2
    {119, 8},     {120, 8},     {121, 8},     {122, 8},     {123, 8},     {124, 8}  // DC Region 1    
};

VTPRoot::VTPRoot() {
}

VTPRoot::VTPRoot( vector<long> *v_crID, vector<long> *v_words ) {
    
    SetVectors(v_crID, v_words);
}


void VTPRoot::SetVectors(vector<long> *v_crID, vector<long> *v_words){

    // Since a new vectors are supplied we should reset all the variables,
    // and start the decoding from the scratch
    ResetAll();
    
    fv_CrID = v_crID;
    fv_words = (vector<ap_int<64>>*)v_words;

    for( fit_words = fv_words->begin(); fit_words != fv_words->end(); ){
        int n_words = fit_words->range(31,0);
        int ind = std::distance(fv_words->begin(), fit_words);
        
        int crate_id = v_crID->at(ind);

      //  cout<<"cr_ID,  ind,   n_words:  "<<crate_id<<"    " <<ind<<"    "<<n_words<<endl;
        
        ReadCrate(crate_id, ind, n_words );
    }
    
    
    /* At this point reading of a VTP bank is complete 
     * Now we can determine different quantities, e.g. number of clusters
     * number of peks, etc.
     */
    
    fnTrigWords = fv_TrigWords.size();
    fnHTCCMasks = fv_HTCCMasks.size();

    for (int iSec = 0; iSec < nSect; iSec++) {
        fnFTOFMasks[iSec] = fv_FTOFMasks[iSec].size();
        fnECClusters[iSec] = fv_ECClusters[iSec].size();
        fnPCalClusters[iSec] = fv_PCalClusters[iSec].size();
        fNDCRoads[iSec] = fv_DCRoad[iSec].size();
        
        for (int iView = 0; iView < nView; iView++) {
            fnECPeaks[iSec][iView] = fv_ECPeaks[iSec][iView].size();
            fnPCalPeaks[iSec][iView] = fv_PCalPeaks[iSec][iView].size();
        }
    }

    
}

void VTPRoot::ReadCrate( int CrateID, int ind, int nWords ){

    fDet = EC_vtp_Detector[CrateID];
    fSector = EC_vtp_sector[CrateID];
    
    for (fit_words = fv_words->begin() + ind + 2; fit_words < fv_words->begin() + ind + nWords + 1; fit_words++) {
        //ap_int<32> cur_word = ap_int<32>(*fit_words);

        ap_int<1> is_type_def = fit_words->range(31, 31);

        if (is_type_def) {

            ap_uint<4> data_type = fit_words->range(30, 27);

            switch (data_type) {

                case type_blk_head: ReadBlockHeader();
                    break;
                case type_blk_trail: ReadBlockTrailer();
                    break;
                case type_ev_head: ReadEventHeader();
                    break;
                case type_trig_time: ReadTriggerTime();
                    break;
                case type_ECtrig_peak: ReadECTriggerPeak();
                    break;
                case type_ECTrig_clust: ReadECTriggerCluster();
                    break;
                case type_trigger: ReadTrigger();
                    break;
                case type_HTCC_clust: ReadHTCCTrigMask();
                    break;
                case type_FTOF_clust: ReadFTOFTrigMask();
                    break;
                case type_switch2ndlvl: Check2ndlvltype();
                    break;                    
                   
            }


        } else {
            //     cout<<"Data continuation word<<setw(15)"<<(*fit_words)<<setw(36)<<bitset<32>(*fit_words)<<endl;
        }
        
    }
    

}


void VTPRoot::Check2ndlvltype(){
  
    ap_uint<4> type_2ndlvl = fit_words->range(26, 23);

    switch (type_2ndlvl) {

        case type_2ndlvl_DCroad: ReadDCRoad();
            break;

    }

    
}


void VTPRoot::ReadBlockHeader() {
    has_BlockHeader = true;
    fslotid = fit_words->range(26, 22);
    fblock_number = fit_words->range(17, 8);
    fblock_level = fit_words->range(7, 0);
}


void VTPRoot::ReadBlockTrailer() {
    has_BlockTrailer = true;
    fslotid = fit_words->range(26, 22);
    fnwords = fit_words->range(21, 0);
}

void VTPRoot::ReadEventHeader() {
    has_EventHeader = true;
    fev_number = fit_words->range(26, 0);
    //cout<<"Ev is "<<fev_number<<endl;
}

void VTPRoot::ReadTriggerTime() {
    has_TrigTime = true;
    int timel = fit_words->range(23, 0);

    fit_words = std::next(fit_words, 1);

    int timeh = fit_words->range(23, 0);

    ftrg_time = 0; // Make sure all bits are 0
    ftrg_time = timeh;
    ftrg_time = ftrg_time << 24;
    ftrg_time = ftrg_time | timel;
}


void VTPRoot::ReadECTriggerPeak() {
    has_TrigPeak = true;

    //    cout<<"Kukukuku  VTP tag is "<<fECVTP_tag<<endl;
    //    cout<<"the peak word is "<<fit_words->range(29, 0)<<endl;

    TEC_Peak cur_peak;
    cur_peak.inst = fit_words->range(26, 26);

    // ====== Test why no events in ECout are visible ====
    //    if( cur_peak.inst ){
    //        cout<<"Kuku inst is "<<cur_peak.inst<<endl;
    //    }
    //    else{
    //        //cout<<"=============== Bobo inst is "<<cur_peak.inst<<endl;
    //    }

    cur_peak.view = fit_words->range(25, 24);

    cur_peak.time = fit_words->range(23, 16);

    // If the data is MC, bits (13, 7) and (6, 0) represent strip1, and stripn, 
    // but this is not that urgent now, sit will try to implement this later.  

    fit_words = std::next(fit_words, 1); // Go to the next word
    // This should be data continuation word, if not then data format is not correct
    // Also bist 30 to 26 should be 0 as well 
    if (fit_words->range(31, 26)) {
        printf("Wrong Data Format in %s Exiting \n", __func__);
        cout << "Data is " << fit_words->range(31, 26) << endl;
        cout << *fit_words << endl;

        throw "Wrong Data format in the ReadECTriggerPeak";
        //        exit(0);
    }

    cur_peak.coord = fit_words->range(25, 16);
    cur_peak.energy = fit_words->range(15, 0);

    //cout<<"  view = "<<cur_peak.view<<endl;
    
    if( fSector < 0 || fSector > 5 ){
        cout<<"Sector is "<<fSector<<endl;
        cout<<"It should be in the [0-5] range "<<endl;
        cout<<"Exiting"<<endl;
        exit(1);
    }
    
       
    if( fDet == 2 ){
        fv_PCalPeaks[fSector][cur_peak.view].push_back(cur_peak);
    } else if( fDet == 1 ){
        fv_ECPeaks[fSector][cur_peak.view].push_back(cur_peak);
    } else{
        cout<<"Detector "<<fDet<<endl;
        cout<<"It should be 1 (EC) or 2 (PCal) "<<endl;
        cout<<"Exiting"<<endl;
        exit(1);
    }
    
//    fv_ECAllPeaks.push_back(cur_peak);
//    fv_ind_ECPeak[cur_peak.inst][cur_peak.view].push_back(fv_ECAllPeaks.size() - 1);
}

void VTPRoot::ReadDCRoad() {

    has_DCRoad = true;
    
    TDCRoad cur_road;

    ap_int<n_max_DC_segments> dc_segm_mask = fit_words->range(22, 17);

     // Now lets check which segments of the road exist
    for (int i = 0; i < n_max_DC_segments; i++) {
        if( dc_segm_mask(i, i) ){
            (cur_road.sl).push_back(i);
        }
    }
    
    cur_road.is_inbend = fit_words->range(11, 11);
    cur_road.is_outbend = fit_words->range(10, 10);
    cur_road.is_valid = fit_words->range(9, 9);
    cur_road.time = fit_words->range(8, 0);
    
     // Go to the next word
    fit_words = std::next(fit_words, 1);
    
    ap_int<n_FTOF_chan> Road_FTOF_mask;
    Road_FTOF_mask(61, 31) = fit_words->range(30, 0);
    
    // Go to the next word
    fit_words = std::next(fit_words, 1);

    Road_FTOF_mask(30, 0) = fit_words->range(30, 0);
    
    for( int i = 0; i < n_FTOF_chan; i++ ) {
        if (Road_FTOF_mask(i, i)) {
            cur_road.tof_match.push_back(i);
        }

    }
    
    if( fSector < 0 || fSector > 5 ){
        cout<<"Sector is "<<fSector<<endl;
        cout<<"It should be in the [0-5] range "<<endl;
        cout<<"Exiting"<<endl;
        exit(1);
    }    
    
    fv_DCRoad[fSector].push_back(cur_road);
}

void VTPRoot::ReadECTriggerCluster() {
    has_TrigClust = true;

    TEC_Cluster cur_clust;
    cur_clust.inst = fit_words->range(26, 26);

    if (fit_words->range(25, 24)) {
        printf("Wrong Data Format in %s, bits (25, 24) should be 0. Exiting", __func__);
        exit(0);
    }

    cur_clust.time = fit_words->range(23, 16);
    cur_clust.energy = fit_words->range(15, 0);

    // Go to the next word
    fit_words = std::next(fit_words, 1);

    // This should be data continuation word,
    // if not then data format is not correct
    if (fit_words->range(31, 30)) {
        printf("Wrong Data Format in %s, In the 2nd word, bits(31,30) should be 0. Exiting", __func__);
        exit(0);
    }

    cur_clust.Wstrip = fit_words->range(29, 20);
    cur_clust.Vstrip = fit_words->range(19, 10);
    cur_clust.Ustrip = fit_words->range(9, 0);

    // cout<<"Data cont. word"<<setw(15)<<(*fit_words)<<setw(36)<<bitset<32>(*fit_words)<<endl;

    if( fSector < 0 || fSector > 5 ){
        cout<<"Sector is "<<fSector<<endl;
        cout<<"It should be in the [0-5] range "<<endl;
        cout<<"Exiting"<<endl;
        exit(1);
    }
    
    if (fDet == 2) {
        fv_PCalClusters[fSector].push_back(cur_clust);
    } else if (fDet == 1) {
        fv_ECClusters[fSector].push_back(cur_clust);
    } else {
        cout << "Detector " << fDet << endl;
        cout << "It should be 1 (EC) or 2 (PCal) " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

}



void VTPRoot::ReadHTCCTrigMask() {
    has_HTCCMask = true;
    THTCC_mask cur_mask;

    cur_mask.time = fit_words->range(26, 16);

    // std::cout << "1st Word of HTCC " << (bitset<32>(*fit_words)) << endl;

    // Go to the next word
    fit_words = std::next(fit_words, 1);

    // HTCC mask is a 48 bit word, each bit tells whether that channel is fired
    // Highst 17 bits of the mask are in one word (16, 0),
    // and the rest 31 are in another word
    ap_int<n_HTCC_chan> HTCC_mask;

    //std::cout << "2nd Word " << (bitset<32>(*fit_words)) << endl;

    HTCC_mask(47, 31) = fit_words->range(16, 0);

    // Go to the next word
    fit_words = std::next(fit_words, 1);

    //std::cout << "3rd Word " << (bitset<32>(*fit_words)) << endl;

    HTCC_mask(30, 0) = fit_words->range(30, 0);

    // std::cout << "HTCC Mask is " << (bitset<48>(HTCC_mask)) << endl;

    // Now lets check which channels are fired
    for (int i = 0; i < n_HTCC_chan; i++) {
        if (HTCC_mask(i, i)) {
            cur_mask.chan.push_back(n_HTCC_chan - i - 1);
        }
    }

    fv_HTCCMasks.push_back(cur_mask);
}



void VTPRoot::ReadFTOFTrigMask() {
    has_FTOFMask = true;

    TFTOF_mask cur_mask;
    cur_mask.time = fit_words->range(26, 16);

    //    std::cout << "1st Word of FTOF " << (bitset<32>(*fit_words)) << endl;

    // Go to the next word
    fit_words = std::next(fit_words, 1);

    // FTOF mask is a 62 bit word, each bit tells whether that channel is fired
    // Highst 31 bits of the mask are in one word (30, 0),
    // and the rest 31 are in another word (30, 0)

    ap_int<n_FTOF_chan> FTOF_mask;
    FTOF_mask(61, 31) = fit_words->range(30, 0);

    //  std::cout << "2nd Word of FTOF " << (bitset<32>(*fit_words)) << endl;

    // Go to the next word
    fit_words = std::next(fit_words, 1);

    FTOF_mask(30, 0) = fit_words->range(30, 0);

    //std::cout << "3rd Word of FTOF " << (bitset<32>(*fit_words)) << endl;

    // Now lets check which channels are fired
    for (int i = 0; i < n_FTOF_chan; i++) {
        if (FTOF_mask(i, i)) {
            cur_mask.chan.push_back(n_FTOF_chan - i - 1);
        }
    }
    
    if( fSector < 0 || fSector > nSect ){
        printf("Request for out of range element in %s", __func__);
        cout<<"Sector is "<<fSector<<endl;
        cout<<"It should be in the [0-5] range "<<endl;
        cout<<"Exiting"<<endl;
        exit(1);
    }
   

    fv_FTOFMasks[fSector].push_back(cur_mask);
}


void VTPRoot::ReadTrigger() {
    has_Trigger = true;

    Trig_word cur_trg;
    
    cur_trg.tr_time = fit_words->range(26, 16);
    cur_trg.tr_word(15, 0) = fit_words->range(15, 0);
    // Go to the next word
    fit_words = std::next(fit_words, 1);

    cur_trg.tr_word(31, 16) = fit_words->range(15, 0);
    
    fv_TrigWords.push_back(cur_trg);
    
    fnTrigWords = fnTrigWords + 1;
}


int VTPRoot::GetNECClusters(int sec){
    if( sec < 0 || sec >= nSect ){
        printf("Request for out of range element in %s", __func__);
        cout<<"Sector is "<<sec<<endl;
        cout<<"It should be in the [0-5] range "<<endl;
        cout<<"Exiting"<<endl;
        exit(1);
    }
    
    return fnECClusters[sec];
}


int VTPRoot::GetNPCalClusters(int sec){
    if( sec < 0 || sec >= nSect ){
        printf("Request for out of range element in %s", __func__);
        cout<<"Sector is "<<sec<<endl;
        cout<<"It should be in the [0-5] range "<<endl;
        cout<<"Exiting"<<endl;
        exit(1);
    }
    
    return fnPCalClusters[sec];
}

int VTPRoot::GetNFTOFMasks(int sec){
    if( sec < 0 || sec >= nSect ){
        printf("Request for out of range element in %s", __func__);
        cout<<"Sector is "<<sec<<endl;
        cout<<"It should be in the [0-5] range "<<endl;
        cout<<"Exiting"<<endl;
        exit(1);
    }
    
    return fnFTOFMasks[sec];
}

int VTPRoot::GetNECPeaks(int sec, int view) {
    if (sec < 0 || sec >= nSect) {
        printf("Request for out of range element in %s", __func__);
        cout << "Sector is " << sec << endl;
        cout << "It should be in the [0-5] range " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }
    
    if( view < 0 || view > 2 ){
        printf("Request for out of range element in %s", __func__);
        cout << "View is " << view << endl;
        cout << "It should be in the 0, 1 or 2 " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }
    
    return fnECPeaks[sec][view];
}

int VTPRoot::GetNPCalPeaks(int sec, int view) {
    if (sec < 0 || sec >= nSect) {
        printf("Request for out of range element in %s", __func__);
        cout << "Sector is " << sec << endl;
        cout << "It should be in the [0-5] range " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }
    
    if( view < 0 || view > 2 ){
        printf("Request for out of range element in %s", __func__);
        cout << "View is " << view << endl;
        cout << "It should be in the 0, 1 or 2 " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }
    
    return fnPCalPeaks[sec][view];
}

TEC_Peak *VTPRoot::GetECPeak(int sec, int view, int ind) {
    if (sec < 0 || sec >= nSect) {
        printf("Request for out of range element in %s", __func__);
        cout << "Sector is " << sec << endl;
        cout << "It should be in the [0-5] range " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    if (view < 0 || view > 2) {
        printf("Request for out of range element in %s", __func__);
        cout << "View is " << view << endl;
        cout << "It should be in the 0, 1 or 2 " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    if( ind < 0 || ind >= fnECPeaks[sec][view] ){
        printf("Request for out of range element in %s", __func__);
        cout << "Index is " << ind << endl;
        cout << "Total number of EC peaks in this sector is"<<fnECPeaks[sec][view]<< endl;
        cout << "Exiting" << endl;
        exit(1);       
    }

    return &fv_ECPeaks[sec][view].at(ind);
}


TEC_Peak *VTPRoot::GetPCalPeak(int sec, int view, int ind) {
    
    if (sec < 0 || sec >= nSect) {
        printf("Request for out of range element in %s", __func__);
        cout << "Sector is " << sec << endl;
        cout << "It should be in the [0-5] range " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    if (view < 0 || view > 2) {
        printf("Request for out of range element in %s", __func__);
        cout << "View is " << view << endl;
        cout << "It should be in the 0, 1 or 2 " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }
                          
    if( ind < 0 || ind >= fnPCalPeaks[sec][view] ){
        printf("Request for out of range element in %s", __func__);
        cout << "Index is " << ind << endl;
        cout << "Total number of PCal peaks in this sector is"<<fnPCalPeaks[sec][view]<< endl;
        cout << "Exiting" << endl;
        exit(1);       
    }
    
    return &fv_PCalPeaks[sec][view].at(ind);
}

TEC_Cluster * VTPRoot::GetECCluster(int sec, int ind) {
 
    if (sec < 0 || sec >= nSect) {
        printf("Request for out of range element in %s", __func__);
        cout << "Sector is " << sec << endl;
        cout << "It should be in the [0-5] range " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    if (ind < 0 || ind >= fnECClusters[sec]) {
        printf("Request for out of range element in %s", __func__);
        cout << "Index is " << ind << endl;
        cout << "Total number of EC clusters in this sector is" << fnECClusters[sec] << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    return &fv_ECClusters[sec].at(ind);
}

TEC_Cluster * VTPRoot::GetPCalCluster(int sec, int ind) {
 
    if (sec < 0 || sec >= nSect) {
        printf("Request for out of range element in %s", __func__);
        cout << "Sector is " << sec << endl;
        cout << "It should be in the [0-5] range " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    if (ind < 0 || ind >= fnPCalClusters[sec]) {
        printf("Request for out of range element in %s", __func__);
        cout << "Index is " << ind << endl;
        cout << "Total number of PCal clusters in this sector is" << fnPCalClusters[sec] << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    return &fv_PCalClusters[sec].at(ind);
}

TFTOF_mask * VTPRoot::GetFTOFMask(int sec, int ind){
    if (sec < 0 || sec >= nSect) {
        printf("Request for out of range element in %s", __func__);
        cout << "Sector is " << sec << endl;
        cout << "It should be in the [0-5] range " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }
 
    if (ind < 0 || ind >= fnFTOFMasks[sec] ) {
        printf("Request for out of range element in %s", __func__);
        cout << "Index is " << ind << endl;
        cout << "Total number of FTOF masks in this sector is" << fnFTOFMasks[sec] << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    return &fv_FTOFMasks[sec].at(ind);    
}


THTCC_mask* VTPRoot::GetHTCCMask(int ind){

    if (ind < 0 || ind >= fnHTCCMasks ) {
        printf("Request for out of range element in %s", __func__);
        cout << "Index is " << ind << endl;
        cout << "Total number of HTCC masks is" << fnHTCCMasks << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

   return  &fv_HTCCMasks.at(ind);
}

Trig_word* VTPRoot::GetTrigWord(int ind) {

    if (ind < 0 || ind >= fnTrigWords) {
        printf("Request for out of range element in %s", __func__);
        cout << "Index is " << ind << endl;
        cout << "Total number of Trig words is" << fnTrigWords << endl;
        cout << "Exiting" << endl;
        exit(1);
    }
    
    return &fv_TrigWords.at(ind);
}

int VTPRoot::GetNDCRoads(int asec) {
    if (asec < 0 || asec >= nSect) {
        printf("Request for out of range element in %s", __func__);
        cout << "Sector is " << asec << endl;
        cout << "It should be in the [0-5] range " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

}       

bool VTPRoot::IsRoadInbending(int asec, int aind){
    
    if (asec < 0 || asec >= nSect) {
        printf("Request for out of range element in %s", __func__);
        cout << "Sector is " << asec << endl;
        cout << "It should be in the [0-5] range " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }
    

    if(aind >= fNDCRoads[asec]){
        printf("Request for out of range element in %s Exiting the program", __func__);
        exit(1);
    }
    
    return fv_DCRoad[asec].at(aind).is_inbend;
}

bool VTPRoot::IsRoadOutbending(int asec, int aind){
    
    if (asec < 0 || asec >= nSect) {
        printf("Request for out of range element in %s", __func__);
        cout << "Sector is " << asec << endl;
        cout << "It should be in the [0-5] range " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }
    

    if(aind >= fNDCRoads[asec]){
        printf("Request for out of range element in %s Exiting the program", __func__);
        exit(1);
    }
    
    return fv_DCRoad[asec].at(aind).is_outbend ;
}

bool VTPRoot::IsRoadValid(int asec, int aind){
    
    if (asec < 0 || asec >= nSect) {
        printf("Request for out of range element in %s", __func__);
        cout << "Sector is " << asec << endl;
        cout << "It should be in the [0-5] range " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }
    

    if(aind >= fNDCRoads[asec]){
        printf("Request for out of range element in %s Exiting the program", __func__);
        exit(1);
    }
    
    return fv_DCRoad[asec].at(aind).is_valid;
}

int VTPRoot::GetRoadTime(int asec, int aind){
    
    if (asec < 0 || asec >= nSect) {
        printf("Request for out of range element in %s", __func__);
        cout << "Sector is " << asec << endl;
        cout << "It should be in the [0-5] range " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }
    

    if(aind >= fNDCRoads[asec]){
        printf("Request for out of range element in %s Exiting the program", __func__);
        exit(1);
    }
    
    return fv_DCRoad[asec].at(aind).time;
}

vector<int> *VTPRoot::GetRoad_SLs(int asec, int aind){
    if (asec < 0 || asec >= nSect) {
        printf("Request for out of range element in %s", __func__);
        cout << "Sector is " << asec << endl;
        cout << "It should be in the [0-5] range " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }
    

    if(aind >= fNDCRoads[asec]){
        printf("Request for out of range element in %s Exiting the program", __func__);
        exit(1);
    }

    return &fv_DCRoad[asec].at(aind).sl;
}


vector<int> *VTPRoot::GetRoad_FTOFMatch(int asec, int aind){
    if (asec < 0 || asec >= nSect) {
        printf("Request for out of range element in %s", __func__);
        cout << "Sector is " << asec << endl;
        cout << "It should be in the [0-5] range " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }
    

    if(aind >= fNDCRoads[asec]){
        printf("Request for out of range element in %s Exiting the program", __func__);
        exit(1);
    }

    return &fv_DCRoad[asec].at(aind).tof_match;
}



//VTPRoot::VTPRoot(const VTPRoot& orig) {
//}

VTPRoot::~VTPRoot() {
}


void VTPRoot::ResetAll() {
    fSector = UNDEF;
    fslotid = UNDEF;
    fnwords = UNDEF;
    fev_number = UNDEF;
    fblock_number = UNDEF;
    fblock_level = UNDEF;

    
    ftrg_time = 0;
    
    fv_HTCCMasks.clear();
    fv_HTCCMasks.shrink_to_fit();
    fnHTCCMasks = 0;

    fv_TrigWords.clear();
    fv_TrigWords.shrink_to_fit();
    fnTrigWords = 0;

    for( int iSect = 0; iSect < nSect; iSect++ ){
    
        fv_PCalClusters[iSect].clear();
        fv_PCalClusters[iSect].shrink_to_fit();
        fnPCalClusters[iSect] = 0;
        
        fv_ECClusters[iSect].clear();
        fv_ECClusters[iSect].shrink_to_fit();
        fnECClusters[iSect] = 0;
        
        fv_FTOFMasks[iSect].clear();
        fv_FTOFMasks[iSect].shrink_to_fit();
        fnFTOFMasks[iSect] = 0;

        fv_DCRoad[iSect].clear();
        fv_DCRoad[iSect].shrink_to_fit();

    for( int iview = 0; iview < nView; iview++ ){
            fv_PCalPeaks[iSect][iview].clear();
            fv_PCalPeaks[iSect][iview].shrink_to_fit();
            fnPCalPeaks[iSect][iview] = 0;
            
            fv_ECPeaks[iSect][iview].clear();
            fv_ECPeaks[iSect][iview].shrink_to_fit();
            fnPCalPeaks[iSect][iview] = 0;
        }
    }

    
    has_BlockHeader = false;
    has_BlockTrailer = false;
    has_EventHeader = false;
    has_TrigTime = false;
    has_TrigPeak = false;
    has_TrigClust = false;
    has_Trigger = false;
    has_HTCCMask = false;
}

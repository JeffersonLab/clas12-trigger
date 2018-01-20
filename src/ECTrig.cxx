#include <ECTrig.hh>
#include <evioUtil.hxx>
#include <evioFileChannel.hxx>
#include <bitset>        // std::bitset
#include <iomanip>
#include <iterator>     // std::next
// using namespace evio;
// using namespace std;

// ================= WHEN MC ====================

map<int, int> TECTrig::EC_vtp_sector = {
    {100, 10}, // Global trigger

    // ================= GEMC ==============
    {60101, 0},    {60102, 1},    {60103, 2},    {60104, 3},    {60105, 4},    {60106, 5}, // ECal
    {60107, 0},    {60108, 1},    {60109, 2},    {60110, 3},    {60111, 4},    {60112, 5}, // PCal
    {60094, 0},    {60095, 1},    {60096, 2},    {60097, 3},    {60098, 4},    {60099, 5}, // FTOF
    {60093, 7}, // HTCC
    // ================= Data ==============
    {101, 0},    {102, 1},    {103, 2},    {104, 3},    {105, 4},    {106, 5}, // ECal
    {107, 0},    {108, 1},    {109, 2},    {110, 3},    {111, 4},    {112, 5}, // PCal
    {94, 0},    {95, 1},    {96, 2},    {97, 3},    {98, 4},    {99, 5}, // PCal
    {93, 7} // HTCC

};

map<int, int> TECTrig::EC_vtp_Detector = {
    // ================= GEMC ==============    
    {100, 0}, // Global trigger
    {60101, 1},    {60102, 1},    {60103, 1},    {60104, 1},    {60105, 1},    {60106, 1}, // ECal
    {60107, 2},    {60108, 2},    {60109, 2},    {60110, 2},    {60111, 2},    {60112, 2}, // PCal
    {60094, 3},    {60095, 3},    {60096, 3},    {60097, 3},    {60098, 3},    {60099, 3}, // FTOF
    {60093, 4}, // HTCC
    // ================= Data ==============
    {101, 1},    {102, 1},    {103, 1},    {104, 1},    {105, 1},    {106, 1}, // ECal
    {107, 2},    {108, 2},    {109, 2},    {110, 2},    {111, 2},    {112, 2}, // PCal
    {94, 3},    {95, 3},    {96, 3},    {97, 3},    {98, 3},    {99, 3}, // FTOF
    {93, 4} // HTCC
};

// ================= WHEN Data ====================
//map<int, int> TECTrig::EC_vtp_sector = {
//    {100, 10}, // Global trigger
//    {101, 0},    {102, 1},    {103, 2},    {104, 3},    {105, 4},    {106, 5}, // ECal
//    {107, 0},    {108, 1},    {109, 2},    {110, 3},    {111, 4},    {112, 5}, // PCal
//    {94, 0},     {95, 1},     {96, 2},     {97, 3},     {98, 4},     {99, 5}, // PCal
//    {93, 7} // HTCC
//};
//
//map<int, int> TECTrig::EC_vtp_Detector = {
//    {100, 0}, // Global trigger
//    {101, 1},    {102, 1},    {103, 1},    {104, 1},    {105, 1},    {106, 1}, // ECal
//    {107, 2},    {108, 2},    {109, 2},    {110, 2},    {111, 2},    {112, 2}, // PCal
//    {94, 3},     {95, 3},     {96, 3},     {97, 3},     {98, 3},     {99, 3}, // FTOF
//    {93, 4} // HTCC, CTOF
//};

TECTrig::TECTrig() {
    //cout << "Kuku Kaka Kuku" << endl;
}

TECTrig::TECTrig(evio::evioDOMNode* it, int a_adcECvtp_tag) {
    SetevioDOMENodeSect(it, a_adcECvtp_tag);
}

void TECTrig::SetevioDOMENodeSect(evio::evioDOMNode* it, int a_adcECvtp_tag) {
    // Reset all attributes, before reading the current event
    ResetAll();

    fhead_node = it;

    // Check if, the tag representing ROC id is correct, otherwise
    // exit the program
    if (!((a_adcECvtp_tag > MCadcECvtp_tagmin && a_adcECvtp_tag < MCadcECvtp_tagmax) ||
            (a_adcECvtp_tag > DataadcECvtp_tagmin && a_adcECvtp_tag < DataadcECvtp_tagmax))) {
        printf("Wrong tag number in %s, tag is %d Exiting \n", __func__, a_adcECvtp_tag);
        exit(0);
    }

    // Sector number is identified from the roc id
    fECVTP_tag = a_adcECvtp_tag;
    fSector = EC_vtp_sector[fECVTP_tag];

    // Determine which detector is

    fDet = EC_vtp_Detector[fECVTP_tag];

    vector<ap_int<32> > *data_values = (vector<ap_int < 32 >> *)it->getVector<uint32_t>();

    for (fit_data = data_values->begin(); fit_data != data_values->end(); fit_data++) {

        ap_int<1> is_type_def = fit_data->range(31, 31);

        if (is_type_def) {
            //cout<<"Type defining word"<<setw(15)<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;

            ap_uint<4> data_type = fit_data->range(30, 27);

            //cout<<"Data type is "<<data_type<<endl;

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
                case type_CTOF_CLUSTER: ReadCTOFTrigMask();
                    break;
            }

        } else {
            //     cout<<"Data continuation word<<setw(15)"<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;
        }

    }
    //cout<<"======******====== END OF VTP Hadrware Data ======******======"<<endl;
    fnAllPeaks = fv_ECAllPeaks.size();
    fnAllClusters = fv_ECAllClusters.size();

    for (int i = 0; i < n_inst; i++) {
        fnClusters[i] = fv_ind_ECCluster[i].size();
        for (int j = 0; j < n_view; j++) {
            fnPeaks[i][j] = fv_ind_ECPeak[i][j].size();
            // cout<<"fnpeaks["<<i<<"]["<<j<<"] = "<<fnPeaks[i][j]<<endl;
        }
    }


    fnHTCC_Masks = fv_HTCCMasks.size();
    fnFTOF_Masks = fv_FTOFMasks.size();
    fnCTOF_Masks = fv_FTOFMasks.size();
}

void TECTrig::ReadBlockHeader() {
    has_BlockHeader = true;
    fslotid = fit_data->range(26, 22);
    fblock_number = fit_data->range(17, 8);
    fblock_level = fit_data->range(7, 0);
}

void TECTrig::ReadBlockTrailer() {
    has_BlockTrailer = true;
    fslotid = fit_data->range(26, 22);
    fnwords = fit_data->range(21, 0);
}

void TECTrig::ReadEventHeader() {
    has_EventHeader = true;
    fev_number = fit_data->range(26, 0);
    //cout<<"Ev is "<<fev_number<<endl;
}

void TECTrig::ReadTriggerTime() {
    has_TrigTime = true;
    int timel = fit_data->range(23, 0);

    fit_data = std::next(fit_data, 1);

    int timeh = fit_data->range(23, 0);

    ftrg_time = 0; // Make sure all bits are 0
    ftrg_time = timeh;
    ftrg_time = ftrg_time << 24;
    ftrg_time = ftrg_time | timel;
}

void TECTrig::ReadECTriggerPeak() {
    has_TrigPeak = true;

    //    cout<<"Kukukuku  VTP tag is "<<fECVTP_tag<<endl;
    //    cout<<"the peak word is "<<fit_data->range(29, 0)<<endl;

    TEC_Peak cur_peak;
    cur_peak.inst = fit_data->range(26, 26);

    // ====== Test why no events in ECout are visible ====
    //    if( cur_peak.inst ){
    //        cout<<"Kuku inst is "<<cur_peak.inst<<endl;
    //    }
    //    else{
    //        //cout<<"=============== Bobo inst is "<<cur_peak.inst<<endl;
    //    }

    cur_peak.view = fit_data->range(25, 24);

    cur_peak.time = fit_data->range(23, 16);

    // If the data is MC, bits (13, 7) and (6, 0) represent strip1, and stripn, 
    // but this is not that urgent now, sit will try to implement this later.  

    fit_data = std::next(fit_data, 1); // Go to the next word
    // This should be data continuation word, if not then data format is not correct
    // Also bist 30 to 26 should be 0 as well 
    if (fit_data->range(31, 26)) {
        printf("Wrong Data Format in %s Exiting \n", __func__);
        cout << "Data is " << fit_data->range(31, 26) << endl;
        cout << *fit_data << endl;

        throw "Wrong Data format in the ReadECTriggerPeak";
        //        exit(0);
    }

    cur_peak.coord = fit_data->range(25, 16);
    cur_peak.energy = fit_data->range(15, 0);

    //cout<<"  view = "<<cur_peak.view<<endl;
    fv_ECAllPeaks.push_back(cur_peak);
    fv_ind_ECPeak[cur_peak.inst][cur_peak.view].push_back(fv_ECAllPeaks.size() - 1);
}

void TECTrig::ReadECTriggerCluster() {
    has_TrigClust = true;

    TEC_Cluster cur_clust;
    cur_clust.inst = fit_data->range(26, 26);

    if (fit_data->range(25, 24)) {
        printf("Wrong Data Format in %s, bits (25, 24) should be 0. Exiting", __func__);
        exit(0);
    }

    cur_clust.time = fit_data->range(23, 16);
    cur_clust.energy = fit_data->range(15, 0);

    // Go to the next word
    fit_data = std::next(fit_data, 1);

    // This should be data continuation word,
    // if not then data format is not correct
    if (fit_data->range(31, 30)) {
        printf("Wrong Data Format in %s, In the 2nd word, bits(31,30) should be 0. Exiting", __func__);
        exit(0);
    }

    cur_clust.Wstrip = fit_data->range(29, 20);
    cur_clust.Vstrip = fit_data->range(19, 10);
    cur_clust.Ustrip = fit_data->range(9, 0);

    // cout<<"Data cont. word"<<setw(15)<<(*fit_data)<<setw(36)<<bitset<32>(*fit_data)<<endl;

    fv_ECAllClusters.push_back(cur_clust);
    //fv_ECClusters[cur_clust.inst].push_back(&fv_ECAllClusters.back());
    fv_ind_ECCluster[cur_clust.inst].push_back(fv_ECAllClusters.size() - 1);
}

void TECTrig::ReadHTCCTrigMask() {
    has_HTCCMask = true;
    THTCC_mask cur_mask;

    cur_mask.time = fit_data->range(26, 16);

    // std::cout << "1st Word of HTCC " << (bitset<32>(*fit_data)) << endl;

    // Go to the next word
    fit_data = std::next(fit_data, 1);

    // HTCC mask is a 48 bit word, each bit tells whether that channel is fired
    // Highst 17 bits of the mask are in one word (16, 0),
    // and the rest 31 are in another word
    ap_int<n_HTCC_chan> HTCC_mask;

    //std::cout << "2nd Word " << (bitset<32>(*fit_data)) << endl;

    HTCC_mask(47, 31) = fit_data->range(16, 0);

    // Go to the next word
    fit_data = std::next(fit_data, 1);

    //std::cout << "3rd Word " << (bitset<32>(*fit_data)) << endl;

    HTCC_mask(30, 0) = fit_data->range(30, 0);

    // std::cout << "HTCC Mask is " << (bitset<48>(HTCC_mask)) << endl;

    // Now lets check which channels are fired
    for (int i = 0; i < n_HTCC_chan; i++) {
        if (HTCC_mask(i, i)) {
            cur_mask.chan.push_back(n_HTCC_chan - i - 1);
        }
    }

    fv_HTCCMasks.push_back(cur_mask);
}

void TECTrig::ReadFTOFTrigMask() {
    has_FTOFMask = true;

    TFTOF_mask cur_mask;
    cur_mask.time = fit_data->range(26, 16);

    //    std::cout << "1st Word of FTOF " << (bitset<32>(*fit_data)) << endl;

    // Go to the next word
    fit_data = std::next(fit_data, 1);

    // FTOF mask is a 62 bit word, each bit tells whether that channel is fired
    // Highst 31 bits of the mask are in one word (30, 0),
    // and the rest 31 are in another word (30, 0)

    ap_int<n_FTOF_chan> FTOF_mask;
    FTOF_mask(61, 31) = fit_data->range(30, 0);

    //  std::cout << "2nd Word of FTOF " << (bitset<32>(*fit_data)) << endl;

    // Go to the next word
    fit_data = std::next(fit_data, 1);

    FTOF_mask(30, 0) = fit_data->range(30, 0);

    //std::cout << "3rd Word of FTOF " << (bitset<32>(*fit_data)) << endl;

    // Now lets check which channels are fired
    for (int i = 0; i < n_FTOF_chan; i++) {
        if (FTOF_mask(i, i)) {
            cur_mask.chan.push_back(n_FTOF_chan - i - 1);
        }
    }

    fv_FTOFMasks.push_back(cur_mask);
}

void TECTrig::ReadCTOFTrigMask(){
    has_CTOFMask = true;
    
    TCTOF_mask cur_mask;
    cur_mask.time = fit_data->range(26, 16);

    //    std::cout << "1st Word of CTOF " << (bitset<32>(*fit_data)) << endl;

    // Go to the next word
    fit_data = std::next(fit_data, 1);

    // CTOF mask is a 48 bit word, each bit tells whether that channel is fired
    // Highest 17 bits of the mask are in one word (16, 0),
    // and the rest 31 are in subsequent word (30, 0)

    ap_int<n_CTOF_chan> CTOF_mask;
    CTOF_mask(47, 31) = fit_data->range(16, 0);

    //  std::cout << "2nd Word of CTOF " << (bitset<32>(*fit_data)) << endl;

    // Go to the next word
    fit_data = std::next(fit_data, 1);

    CTOF_mask(30, 0) = fit_data->range(30, 0);

    //std::cout << "3rd Word of CTOF " << (bitset<32>(*fit_data)) << endl;

    // Now lets check which channels are fired
    for (int i = 0; i < n_CTOF_chan; i++) {
        if (CTOF_mask(i, i)) {
            cur_mask.chan.push_back(n_CTOF_chan - i - 1);
        }
    }

    fv_CTOFMasks.push_back(cur_mask);    
}

void TECTrig::ReadCNDTrigMask(){
    has_CNDMask = true;
    
    TCND_mask cur_mask;
    cur_mask.time = fit_data->range(26, 16);
    
    // CND mask is a 72 bit word (24 chan/layer * 3 layers), 
    // 1st 24 bits is a coincidence between L1 and L2
    // 2nd 24 bits is a coincidence between L2 and L3
    // 3rd 24 bits is a coincidence between L1 and L2 and L3
    
    ap_int<n_CND_chan> CND_mask;
    CND_mask(71, 62) = fit_data->range(9, 0);
    
    // Go to the next word
    fit_data = std::next(fit_data, 1);
    CND_mask(61, 31) = fit_data->range(30, 0);

    // Go to the next word
    fit_data = std::next(fit_data, 1);
    CND_mask(30, 0) = fit_data->range(30, 0);
    
        for (int i = 0; i < n_CND_chan; i++) {
        if (CND_mask(i, i)) {
            cur_mask.chan.push_back(n_CND_chan - i - 1);
        }
    }

    fv_CNDMasks.push_back(cur_mask);
}

void TECTrig::ReadTrigger() {
    has_Trigger = true;

    Trig_word cur_trg;
    
    cur_trg.tr_time = fit_data->range(26, 16);
    cur_trg.tr_word(15, 0) = fit_data->range(15, 0);
    // Go to the next word
    fit_data = std::next(fit_data, 1);

    cur_trg.tr_word(31, 16) = fit_data->range(15, 0);
    
    fv_TrigWords.push_back(cur_trg);
    
    fnTrigWords = fnTrigWords + 1;
}

TEC_Peak* TECTrig::GetECPeak(int aind) {
    if (aind < fnAllPeaks) {
        return &fv_ECAllPeaks.at(aind);
    } else {
        printf("Request for out of range element in %s Exiting the program", __func__);
        exit(0);
    }
}

TEC_Peak* TECTrig::GetECPeak(int ainst, int aview, int aind) {
    if (ainst >= 0 && ainst < n_inst && aview >= 0 && aview < n_view && aind >= 0 && aind < fnPeaks[ainst][aview]) {
        return &fv_ECAllPeaks.at(fv_ind_ECPeak[ainst][aview].at(aind));
    } else {
        printf("Request for out of range element in %s Exiting the program", __func__);
        exit(0);
    }
}

Trig_word *TECTrig::GetTrigWord(int aind){

    if( aind < fnTrigWords){
        return &fv_TrigWords.at(aind);
    } else {
        printf("Request for out of range element in %s Exiting the program", __func__);
        exit(0);
    }
    
}

int TECTrig::GetNPeaks(int ainst, int aview) {
    if (ainst >= 0 && ainst < n_inst && aview >= 0 && aview < n_view) {
        return fnPeaks[ainst][aview];
    } else {
        printf("Request for out of range element in %s Exiting the program", __func__);
        exit(0);
    }

}

int TECTrig::GetNClust(int ainst) {
    if (ainst >= 0 && ainst < n_inst) {
        return fnClusters[ainst];
    }
}

TEC_Cluster* TECTrig::GetECCluster(int aind) {
    if (aind < fnAllClusters) {
        return &fv_ECAllClusters.at(aind);
    } else {
        printf("Request for out of range element in %s Exiting the program", __func__);
        exit(0);
    }
}

TEC_Cluster* TECTrig::GetECCluster(int ainst, int aind) {
    if (ainst >= 0 && ainst < n_inst && aind < fnClusters[ainst]) {
        return &fv_ECAllClusters.at(fv_ind_ECCluster[ainst].at(aind));
        //return fv_ECClusters[ainst].at(aind);
    } else {
        printf("Request for out of range element in %s Exiting the program", __func__);
        exit(0);
    }
}

THTCC_mask* TECTrig::GetHTCCMask(int aind) {
    if (aind >= fv_HTCCMasks.size()) {
        printf("Request for out of range element in %s Exiting the program", __func__);
        exit(1);
    }

    if (fDet != 4) {
        cout << "Requesting for HTCC mask, but this seems, is not HTCC VTP data, " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    return &fv_HTCCMasks.at(aind);
}

TFTOF_mask* TECTrig::GetFTOFMask(int aind) {
    if (aind >= fv_FTOFMasks.size()) {
        printf("Request for out of range element in %s Exiting the program", __func__);
        exit(1);
    }

    return &fv_FTOFMasks.at(aind);

}

TCTOF_mask* TECTrig::GetCTOFMask(int aind) {
    if (aind >= fv_CTOFMasks.size()) {
        printf("Request for out of range element in %s Exiting the program", __func__);
        exit(1);
    }

    return &fv_CTOFMasks.at(aind);
}

TCND_mask* TECTrig::GetCNDMask(int aind){
    
     if (aind >= fv_CNDMasks.size()) {
        printf("Request for out of range element in %s Exiting the program", __func__);
        exit(1);
    }

    return &fv_CNDMasks.at(aind);
}

void TECTrig::PrintECCluster(int aind) {
    if (aind < fnAllClusters) {
        cout << "fv_ECAllClusters.size() = " << fv_ECAllClusters.size() << endl;
        cout << "Cluster index = " << aind << endl;
        cout << "Cluster inst = " << fv_ECAllClusters.at(aind).inst << endl;
        cout << "Cluster Address " << &fv_ECAllClusters.at(aind) << endl;
        cout << "Cluster U = " << fv_ECAllClusters.at(aind).Ustrip << endl;
        cout << "Cluster V = " << fv_ECAllClusters.at(aind).Vstrip << endl;
        cout << "Cluster W = " << fv_ECAllClusters.at(aind).Wstrip << endl;
        cout << "Cluster E = " << fv_ECAllClusters.at(aind).energy << endl;
    } else {
        printf("Request for out of range element in %s Exiting the program", __func__);
        exit(0);
    }
}

void TECTrig::PrintECCluster(int ainst, int aind) {
    if (ainst >= 0 && ainst < n_inst && aind < fnClusters[ainst]) {
        cout << "fv_ind_ECCluster[ainst].size() = " << fv_ind_ECCluster[ainst].size() << endl;
        cout << "Cluster instance in the argument = " << ainst << endl;
        cout << "Cluster instance from the cluster structure = " << (fv_ECAllClusters.at(fv_ind_ECCluster[ainst].at(aind))).inst << endl;
        cout << "Cluster Address " << &fv_ECAllClusters.at(fv_ind_ECCluster[ainst].at(aind)) << endl;
        cout << "Cluster index = " << aind << endl;
        cout << "Cluster U = " << (fv_ECAllClusters.at(fv_ind_ECCluster[ainst].at(aind))).Ustrip << endl;
        cout << "Cluster V = " << (fv_ECAllClusters.at(fv_ind_ECCluster[ainst].at(aind))).Vstrip << endl;
        cout << "Cluster W = " << (fv_ECAllClusters.at(fv_ind_ECCluster[ainst].at(aind))).Wstrip << endl;
        cout << "Cluster E = " << (fv_ECAllClusters.at(fv_ind_ECCluster[ainst].at(aind))).energy << endl;

    } else {
        printf("Request for out of range element in %s Exiting the program", __func__);
        exit(0);
    }
}

void TECTrig::PrintXMLData() {
    cout << "   *******  Header  " << (fhead_node)->getHeader(0);
    cout << "   *******  tag  " << (fhead_node)->tag << endl;
    cout << "   ***  Contenttype  " << (fhead_node)->getContentType() << endl;
    cout << "   *********  Body  " << (fhead_node)->getBody(0) << endl;
    cout << "   ********  Footer  " << (fhead_node)->getFooter(0);
    cout << "   **********  size  " << (fhead_node)->getSize() << endl;
}

void TECTrig::ResetAll() {
    fSector = UNDEF;
    fslotid = UNDEF;
    fnwords = UNDEF;
    fev_number = UNDEF;
    fblock_number = UNDEF;
    fblock_level = UNDEF;

    ftrig_inst = UNDEF;
    ftrig_lane = UNDEF;
    ftrig_time = UNDEF;

    for (int i = 0; i < n_inst; i++) {

        fv_ind_ECCluster[i].clear();
        fv_ind_ECCluster[i].shrink_to_fit();
        fnClusters[i] = 0;

        for (int j = 0; j < n_view; j++) {
            fv_ind_ECPeak[i][j].clear();
            fv_ind_ECPeak[i][j].shrink_to_fit();
            fnPeaks[i][j] = 0;
        }
    }

    fv_HTCCMasks.clear();
    fv_HTCCMasks.shrink_to_fit();
    fv_FTOFMasks.clear();
    fv_FTOFMasks.shrink_to_fit();
    fv_CTOFMasks.clear();
    fv_CTOFMasks.shrink_to_fit();

    ftrg_time = 0;

    fv_ECAllPeaks.clear();
    fv_ECAllPeaks.shrink_to_fit();
    fv_ECAllClusters.clear();
    fv_ECAllClusters.shrink_to_fit();

    fv_TrigWords.clear();
    fv_TrigWords.shrink_to_fit();
    
    fnAllPeaks = 0;
    fnAllClusters = 0;
    fnHTCC_Masks = 0;
    fnTrigWords = 0;

    has_BlockHeader = false;
    has_BlockTrailer = false;
    has_EventHeader = false;
    has_TrigTime = false;
    has_TrigPeak = false;
    has_TrigClust = false;
    has_Trigger = false;
    has_HTCCMask = false;
    has_FTOFMask = false;
    has_CTOFMask = false;
}

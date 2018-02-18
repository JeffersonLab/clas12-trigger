/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TDetTrue.cxx
 * Author: rafopar
 * 
 * Created on November 23, 2017, 8:01 PM
 */

#include "TDetTrue.hh"

#include <evioUtil.hxx>
#include <evioFileChannel.hxx>
#include <evioTypedefs.hxx>

using namespace std;
using namespace evio;

TDetTrue::TDetTrue() {
    Reset();
}

TDetTrue::TDetTrue(evio::evioDOMNode* it) {
    SetevioDOMNode(it);
}

void TDetTrue::SetevioDOMNode(evio::evioDOMNode* it) {

    if (!(it->tag == ECTrueTag || it->tag == PCalTrueTag || it->tag == HTCCTrueTag || it->tag == FTOFTrueTag || it->tag == CTOFTrueTag)) {
        cout << "Sorry this doesn't seem to be an EC, PCal, HTCC or FTOF True bank " << endl;
        cout << "The EC/PCal/HTCC/FTOF bank tag should be " << ECTrueTag << ", " << PCalTrueTag<<" , "<< HTCCTrueTag<<"   , "<< FTOFTrueTag<<endl;
        cout << "The Program is exiting " << endl;
        exit(1);
    }

    // For some reason in HTCC True bank, mother id is never 0, I guess it only treats optical
    // photons, which are originated from the generated particle, that is why, a new ad hoc
    // variable will created, for track id for Mother particle, and for HTCC it will
    // be equal to 1, and for PCal and EC, (probably all non Cherenkov Detectors) be 0.
    
    int mother_tid_value = 0;
    if( it->tag == HTCCTrueTag ){ mother_tid_value = 1; }
    
    
    fTrueTag = it->tag;

    Reset();
    evioDOMNodeList *leaf_list = it->getChildList();

    //cout<<"leaf_size = "<<leaf_list->size()<<endl;

    int data_size = 0;


    // Getting leafs, which are different types of truth informations
    // NOTE: all of these vectors have the same size
    for (fTrueList = leaf_list->begin(); fTrueList != leaf_list->end(); fTrueList++) {

        int num = (*fTrueList)->num;

        switch (num) {

            case 1: fPID_raw = (*fTrueList)->getVector<int>();
                break;
            case 3: ftid_raw = (*fTrueList)->getVector<int>();
                data_size = ftid_raw->size();
                break;
            case 4: fmtid_raw = (*fTrueList)->getVector<int>();
                break;
            case 6: fE_raw = (*fTrueList)->getVector<double>();
                break;
            case 8: favgX_raw = (*fTrueList)->getVector<double>();
                break;
            case 9: favgY_raw = (*fTrueList)->getVector<double>();
                break;
            case 10: favgZ_raw = (*fTrueList)->getVector<double>();
                break;
            case 14: fPx_raw = (*fTrueList)->getVector<double>();
                break;
            case 15: fPy_raw = (*fTrueList)->getVector<double>();
                break;
            case 16: fPz_raw = (*fTrueList)->getVector<double>();
                break;
            default: break;
        }
    }

    // ====== Now we want to select from the above tracks those, that are not
    // a secondary. 

    if (data_size == 0) {
        cout << "Wrong MC Data format. True bank" << fTrueTag << " has no data in it" << endl;
    }


    double E_em_max = -1.;

      for (int i = 0; i < data_size; i++) {

        if (fmtid_raw->at(i) == mother_tid_value) {

            map<int, int>::iterator it_tid = fmap_tr_id.find(ftid_raw->at(i));

            // Check if this "track_id" track is already processed
            // If no, then add this track to the max
            if (it_tid == fmap_tr_id.end()) {
                fmap_tr_id[ftid_raw->at(i)] = i;
                fmap_Emax[ftid_raw->at(i)] = fE_raw->at(i);
            } else {

                // If the track_id is already processed, then check
                // if the energy of this one is higher than the
                // maximum energy of all previous ones

                if (fE_raw->at(i) > fmap_Emax[ftid_raw->at(i)]) {
                    //fmap_tr_id[ftid_raw->at(i)] = i;
                    fmap_tr_id[it_tid->first] = i;
                    fmap_Emax[ftid_raw->at(i)] = fE_raw->at(i);
                }

            }


        }
    }


    // At this point all data in the GEMC True bank is processed,
    // and it is already determined Original track ids, and their 
    // corresponding enrgy and coordinates at the ECal face.

    fn_part = fmap_tr_id.size();

    for (map<int, int>::iterator it = fmap_tr_id.begin(); it != fmap_tr_id.end(); it++) {

        //cout<<"fPx_raw->at(it->second) = "<<fPx_raw->at(it->second)<<endl;
        fPx.push_back(fPx_raw->at(it->second));
        fPy.push_back(fPy_raw->at(it->second));
        fPz.push_back(fPz_raw->at(it->second));

        fE.push_back(fE_raw->at(it->second));

        favgX.push_back(favgX_raw->at(it->second));
        favgY.push_back(favgY_raw->at(it->second));
        favgZ.push_back(favgZ_raw->at(it->second));

        fPID.push_back(fPID_raw->at(it->second));
    }


}

void TDetTrue::Print() {

    cout << "========== EC True information =========" << endl;

    cout << "PID " << setw(20) << " Px " << setw(20) << " Py " << setw(20) << " Pz " << setw(20) << " E " << setw(20) <<
            " avgX " << setw(20) << " avgY " << setw(20) << " avgZ " << endl;
    for (int i = 0; i < fE.size(); i++) {
        cout << fPID.at(i) << setw(20) << fPx.at(i) << setw(20) << fPy.at(i) << setw(20) << fPz.at(i) << setw(20) <<
                fE.at(i) << setw(20) << favgX.at(i) << setw(20) << favgY.at(i) << setw(20) << favgZ.at(i) << endl;
    }
    cout << endl << endl;
}

const int TDetTrue::PID(int aind) {

    if (aind < 0 || aind >= fn_part) {
        cout << "Index is out of a range" << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    return fPID.at(aind);
}

const double TDetTrue::E(int aind) {

    if (aind < 0 || aind >= fn_part) {
        cout << "Index is out of a range" << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    return fE.at(aind);
}

const double TDetTrue::Xavg(int aind) {

    if (aind < 0 || aind >= fn_part) {
        cout << "Index is out of a range" << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    return favgX.at(aind);
}

const double TDetTrue::Yavg(int aind) {

    if (aind < 0 || aind >= fn_part) {
        cout << "Index is out of a range" << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    return favgY.at(aind);
}

const double TDetTrue::Zavg(int aind) {

    if (aind < 0 || aind >= fn_part) {
        cout << "Index is out of a range" << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    return favgZ.at(aind);
}

void TDetTrue::Reset() {

    fPx.clear();
    fPx.shrink_to_fit();
    fPy.clear();
    fPy.shrink_to_fit();
    fPz.clear();
    fPz.shrink_to_fit();

    fE.clear();
    fE.shrink_to_fit();

    favgX.clear();
    favgX.shrink_to_fit();
    favgY.clear();
    favgY.shrink_to_fit();
    favgZ.clear();
    favgZ.shrink_to_fit();

    fPID.clear();
    fPID.shrink_to_fit();

    fmap_tr_id.clear();
    fmap_Emax.clear();
    fn_part = 0;

    fPx_raw = NULL;
    fPy_raw = NULL;
    fPz_raw = NULL;
    fE_raw = NULL;
    favgX_raw = NULL;
    favgY_raw = NULL;
    favgZ_raw = NULL;
    fPID_raw = NULL;
    ftid_raw = NULL;
    fmtid_raw = NULL;
}

TDetTrue::TDetTrue(const TDetTrue& orig) {


    fn_part = orig.fn_part;
    fPx = orig.fPx;
    fPy = orig.fPy;
    fPz = orig.fPz;
    fE = orig.fE;
    favgX = orig.favgX;
    favgY = orig.favgY;
    favgZ = orig.favgZ;
    fPID = orig.fPID;

    fPx_raw = orig.fPx_raw;
    fPy_raw = orig.fPy_raw;
    fPz_raw = orig.fPz_raw;
    fE_raw = orig.fE_raw;
    favgX_raw = orig.favgX_raw;
    favgY_raw = orig.favgY_raw;
    favgZ_raw = orig.favgZ_raw;
    fPID_raw = orig.fPID_raw;
    ftid_raw = orig.ftid_raw;
    fmtid_raw = orig.fmtid_raw;
    fmap_tr_id = orig.fmap_tr_id;
    fmap_Emax = orig.fmap_Emax;

    fTrueList = orig.fTrueList;
}

TDetTrue::~TDetTrue() {

}
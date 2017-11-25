/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TECTrue.cxx
 * Author: rafopar
 * 
 * Created on November 23, 2017, 8:01 PM
 */

#include "TECTrue.hh"

#include <evioUtil.hxx>
#include <evioFileChannel.hxx>
#include <evioTypedefs.hxx>

using namespace std;
using namespace evio;

TECTrue::TECTrue() {
    Reset();
}

TECTrue::TECTrue(evio::evioDOMNode* it) {
    SetevioDOMNode(it);
}

void TECTrue::SetevioDOMNode(evio::evioDOMNode* it) {

    if (it->tag != ECTrueTag) {
        cout << "Sorry this doesn't seem to be an ECTrue bank " << endl;
        cout << "The ECTrue bank tag should be " << ECTrueTag << endl;
        cout << "The Program is exiting " << endl;
        exit(1);
    }

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
        cout << "Wrong MC Data format. True bank" << ECTrueTag << " has no data in it" << endl;
    }


    double E_em_max = -1.;

    for (int i = 0; i < data_size; i++) {

        if (fmtid_raw->at(i) == 0) {

            map<int, int>::iterator it_tid = fmap_tr_id.find(ftid_raw->at(i));

            // Check if this "track_id" track is already processed
            // If no, the add this track to the max
            if (it_tid == fmap_tr_id.end()) {
                fmap_tr_id[ftid_raw->at(i)] = i;
                fmap_Emax[ftid_raw->at(i)] = fE_raw->at(i);
            } else {

                // If the track_id is already processed, then check
                // if the energy of this one is higher than the
                // maximum energy of all previous ones

                if (fE_raw->at(i) > fmap_Emax[ftid_raw->at(i)]) {
                    fmap_tr_id[ftid_raw->at(i)] = i;
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

void TECTrue::Print() {

    cout << "========== EC True information =========" << endl;

    cout << "PID " << setw(20) << " Px " << setw(20) << " Py " << setw(20) << " Pz " << setw(20) << " E " << setw(20) <<
            " avgX " << setw(20) << " avgY " << setw(20) << " avgZ " << endl;
    for (int i = 0; i < fE.size(); i++) {
        cout << fPID.at(i) << setw(20) << fPx.at(i) << setw(20) << fPy.at(i) << setw(20) << fPz.at(i) << setw(20) <<
                fE.at(i) << setw(20) << favgX.at(i) << setw(20) << favgY.at(i) << setw(20) << favgZ.at(i) << endl;
    }
    cout << endl << endl;
}

const int TECTrue::PID(int aind) {

    if (aind < 0 || aind >= fn_part) {
        cout << "Index is out of a range" << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    return fPID.at(aind);
}

const double TECTrue::E(int aind) {

    if (aind < 0 || aind >= fn_part) {
        cout << "Index is out of a range" << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    return fE.at(aind);
}

const double TECTrue::Xavg(int aind) {

    if (aind < 0 || aind >= fn_part) {
        cout << "Index is out of a range" << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    return favgX.at(aind);
}

const double TECTrue::Yavg(int aind) {

    if (aind < 0 || aind >= fn_part) {
        cout << "Index is out of a range" << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    return favgY.at(aind);
}

const double TECTrue::Zavg(int aind) {

    if (aind < 0 || aind >= fn_part) {
        cout << "Index is out of a range" << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    return favgZ.at(aind);
}

void TECTrue::Reset() {

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

TECTrue::TECTrue(const TECTrue& orig) {

 
    fn_part = orig.fn_part;
    fPx = orig.fPx;
    fPy = orig.fPy;
    fPz = orig.fPz;
    fE = orig.fE;
    favgX = orig.favgX;
    favgY = orig.favgY;
    favgZ = orig.favgZ;
    fPID = orig.fPID;

//    fPx_raw = new vector<double>;
//    *fPx_raw = *orig.fPx_raw;
//    fPy_raw = new vector<double>;
//    *fPy_raw = *orig.fPy_raw;
//    fPz_raw = new vector<double>;
//    *fPz_raw = *orig.fPz_raw;
//    fE_raw = new vector<double>;
//    *fE_raw = *orig.fE_raw;
//    favgX_raw = new vector<double>;
//    *favgX_raw = *orig.favgX_raw;
//    favgY_raw = new vector<double>;
//    *favgY_raw = *orig.favgY_raw;
//    favgZ_raw = new vector<double>;
//    *favgZ_raw = *orig.favgZ_raw;
//    fPID_raw = new vector<int>;
//    *fPID_raw = *orig.fPID_raw;
//    ftid_raw = new vector<int>;
//    *ftid_raw = *orig.ftid_raw;
//    fmtid_raw = new vector<int>;
//    *fmtid_raw = *orig.fmtid_raw;

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

TECTrue::~TECTrue() {

//    cout << "Destructor TECTRUE1" << endl;
//    //cout<<"fPx_raw = "<<fPx_raw<<endl;
//    delete fPx_raw;
//    cout << "Destructor TECTRUE1_1" << endl;
//    delete fPy_raw;
//    delete fPz_raw;
//    delete fE_raw;
//    delete favgX_raw;
//    delete favgY_raw;
//    delete favgZ_raw;
//    delete fPID_raw;
//    delete ftid_raw;
//    delete fmtid_raw;
//    cout << "Destructor TECTRUE2" << endl;
}
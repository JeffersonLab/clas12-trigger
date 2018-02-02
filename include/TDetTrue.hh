/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TDetTrue.hh
 * Author: rafopar
 *
 * Created on November 23, 2017, 8:01 PM
 */

#ifndef TECTRUE_HH
#define TECTRUE_HH

#include <evioUtil.hxx>


using namespace evio;

class TDetTrue {
public:
    TDetTrue();
    TDetTrue( evio::evioDOMNode*);
    TDetTrue(const TDetTrue& orig);
    
    void Reset();
    void SetevioDOMNode(evio::evioDOMNode*);
    void Print();
    const int Npart() {return fn_part;}
    const int PID(int);
    const double E(int);
    const double Xavg(int);
    const double Yavg(int);
    const double Zavg(int);
    virtual ~TDetTrue();
private:

    static const int ECTrueTag = 1601;
    static const int PCalTrueTag = 1501;
    static const int FTOFTrueTag = 1001;
    static const int HTCCTrueTag = 601;
    static const int em_pid = 11;
    static const int ep_pid = -11;
    static const int gamma_pid = 22;
    static const int prot_pid = 2212;
 
    int fn_part;
    
    int fTrueTag;
    vector<double> *fPx_raw;
    vector<double> *fPy_raw;
    vector<double> *fPz_raw;
    vector<double> *fE_raw;
    vector<double> *favgX_raw;
    vector<double> *favgY_raw;
    vector<double> *favgZ_raw;
    vector<int> *fPID_raw;
    vector<int> *ftid_raw;
    vector<int> *fmtid_raw;
    
    vector<double> fPx;
    vector<double> fPy;
    vector<double> fPz;
    vector<double> fE;
    vector<double> favgX;
    vector<double> favgY;
    vector<double> favgZ;
    vector<int> fPID;
    
    map<int, int> fmap_tr_id;     // This should identify indexes of original tracks
    map<int, double> fmap_Emax;   // This shows Max energy of 
    
    evioDOMNodeList::iterator fTrueList;
};

#endif /* TECTRUE_HH */


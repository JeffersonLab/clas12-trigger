/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   run_Muon_Trg_Eff.cc
 * Author: rafopar
 *
 * Created on February 19, 2019, 10:51 PM
 */

#include "Moun_Trg_Eff.C"

#include <cstdlib>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    if( argc < 2 ){
        cout<<"Exiting please providr a run number"<<endl;
        exit(1);
    }
    
    int run = atoi(argv[1]);
    
     Moun_Trg_Eff t(run);
    
     t.Loop();
    
    return 0;
}


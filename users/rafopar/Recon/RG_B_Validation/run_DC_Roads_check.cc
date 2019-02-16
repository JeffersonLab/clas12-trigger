/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   run_DC_Roads_check.cc
 * Author: rafopar
 *
 * Created on February 13, 2019, 11:06 PM
 */

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "DC_Roads_check.C"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    
    if( argc < 2 ){
        cout<<"Please provide the run number "<<endl;
        cout<<"Exiting "<<endl;
        exit(1);
    }
    
    int run = atoi(argv[1]);
    
    DC_Roads_check t(run);
    t.Loop();

    return 0;
}


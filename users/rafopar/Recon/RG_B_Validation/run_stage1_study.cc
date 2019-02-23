/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   run_stage1_study.cc
 * Author: rafopar
 *
 * Created on February 21, 2019, 10:56 PM
 */

#include <cstdlib>
#include "stage1_study.C"

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

    stage1_study t(run);
    t.Loop();

    return 0;
}


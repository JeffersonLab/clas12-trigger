/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   run_Muon_Trigger.cc
 * Author: rafopar
 *
 * Created on February 18, 2019, 12:25 PM
 */

#include <cstdlib>
#include "Muon_Trigger.C"


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    Muon_Trigger t;
    t.Loop();
    
    return 0;
}


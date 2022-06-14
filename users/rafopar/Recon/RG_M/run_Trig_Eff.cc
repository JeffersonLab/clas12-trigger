#include "Trig_Eff.C"
#include <iostream>

using namespace std;


int main(int argc, char **argv){

  if( argc <2 ){
    cout<<"Please specify the run number"<<endl;
    exit(1);
  }

  int run = atoi(argv[1]);
  
  Trig_Eff t(run);
  t.Loop();  
}

#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_stream.h>

#include <bitset>

using namespace std;

int main(){
  ap_uint<20> *ii = new ap_uint<20>(321331);
  cout<<"Bits of ii is "<<bitset<20>(*ii)<<endl;
  cout<<" ii(18, 3) = "<<ii->range(18, 3)<<endl;
    
  cout.precision(10);
  ap_ufixed<18, 15> cc;
  cc(17, 0) = ii->range(17, 0);
  //cc = ii(17, 0);            // THIS IS WRONG!!!
  double cc_double = cc.to_double();
  cout<<"cc bits = "<<bitset<32>(cc)<<endl;
  cout<<"cc = "<<cc<<endl;
  cout<<"cc_double = "<<cc_double<<endl;

  cout<<"================== Testing \"ap_uint<9> addr = (peakDetect.view, peakDetect.t(9,3));\" statement =========="<<endl;

  ap_uint<11> tt = 1690;
  ap_uint<2> view = 0;
  ap_uint<9> addr = (view, tt(9, 3));

  cout<<"Bits of tt =      "<<bitset<11>(tt)<<endl;
  cout<<"Bits of view =    "<<bitset<11>(view)<<endl;
  cout<<"Bits of addr =    "<<bitset<11>(addr)<<endl;

  
  
}

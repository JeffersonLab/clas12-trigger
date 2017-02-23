#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_stream.h>

#include <bitset>

using namespace std;

int main(){
  ap_int<20> a = 926;

  cout<<"a = "<<a<<"     a<20> bits = "<<bitset<20>(a)<<endl;
  cout<<"checking Bit select operator []:"<<endl;

  for( int ii = 0; ii < 20; ii++ ){
    cout<<" bit["<<20 - ii - 1<<"] = "<<a[20 - ii - 1]<<endl;
  }

  ap_int<20> *bb = new ap_int<20>(4919);
  cout<<"bb = "<<*bb<<"     bb<20> bits = "<<bitset<20>(*bb)<<endl;

  cout<<"Range b(1, 3) is "<<bb->range(3, 1)<<endl;

  cout.precision(10);
  ap_ufixed<9, 6> cc = 30.3;
  double cc_double = cc.to_double();
  cout<<"cc bits = "<<bitset<20>(cc)<<endl;
  cout<<"cc = "<<cc<<endl;
  cout<<"cc_double = "<<cc_double<<endl;
}

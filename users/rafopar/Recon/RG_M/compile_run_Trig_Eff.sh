#g++ run_Trig_Eff.cc -o run_Trig_Eff.exe `root-config --cflags --libs` -I/Work/apps/Vivado_HLS/2015.4/include -I$CLAS12Trig/include -L$CLAS12Trig_LIB -lTrigDiag -L$CODA/Linux-x86_64/lib -levioxx -levio -lexpat -lpthread

g++ run_Trig_Eff.cc -o run_Trig_Eff.exe `root-config --cflags --libs` -I/Work/apps/Vivado_HLS/2015.4/include -I$CLAS12Trig/include -L$CLAS12Trig_LIB -lTrigDiag -L$CODA/Linux-x86_64/lib -levioxx -levio -lexpat -lpthread

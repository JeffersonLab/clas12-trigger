g++ run_Muon_Trigger.cc -o run_Muon_Trigger.exe `root-config --cflags --libs` -I/Work/apps/Vivado_HLS/2015.4/include -I$CLAS12Trig/include -L$CLAS12Trig_LIB -lTrigDiag -L$CODA/Linux-x86_64/lib -levioxx -levio -lexpat -lpthread

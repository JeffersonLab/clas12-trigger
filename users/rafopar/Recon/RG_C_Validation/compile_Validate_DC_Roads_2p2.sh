g++ Validate_DC_Roads_2p2.cc -o Validate_DC_Roads_2p2.exe `root-config --cflags --libs` -I/local/work/builds/Vivado_HLS/2015.4/include/ -I$CLAS12Trig/include -L$CLAS12Trig_LIB -lTrigDiag -L$EVIO/lib -levioxx -levio -lexpat -lpthread -L$HIPODIR/lib -lhipo4 -llz4 -I$HIPODIR/hipo4 -I$CLAS12AnaTools/include -L$CLAS12AnaTools/lib -lclas12AnaTools
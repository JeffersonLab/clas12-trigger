g++ decode_VTP.cc -o decode_VTP.exe `root-config --cflags --libs` -I$CODA/Linux-x86_64/include -I$CLAS12Trig/include -I/Work/apps/Vivado_HLS/2015.4/include -L$CLAS12Trig_LIB -lTrigDiag -L$CODA/Linux-x86_64/lib -levioxx -levio -lexpat -lpthread
#
#g++ decode_VTP.cc -o decode_VTP.exe -I$CODA/Linux-x86_64/include -I$CLAS12Trig/include -I/Work/apps/Vivado_HLS/2015.4/include -L$CLAS12Trig_LIB -lTrigDiag -L$CODA/Linux-x86_64/lib -levioxx -levio -lexpat -lpthread

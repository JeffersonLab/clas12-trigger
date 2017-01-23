#g++ test_prog1.cc -o test_prog1.exe -I$CODA/Linux-x86_64/include -L$CODA/Linux-x86_64/lib -levioxx -levio -lexpat -lpthread
g++ test_prog1.cc -o test_prog1.exe `root-config --cflags --libs` -I$CODA/Linux-x86_64/include -L$CODA/Linux-x86_64/lib -levioxx -levio -lexpat -lpthread

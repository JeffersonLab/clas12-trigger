CC              = g++
CC_OBJ_FLAGS    = -c -fPIC
CC_Shared_FLAGS = -shared -Wl,-soname,libTrigDiag.so
ROOT_CFLAGS     = $(shell /usr/local/apps/root/root/bin/root-config --cflags)
ROOT_LIBS       = $(shell /usr/local/apps/root/root/bin/root-config --libs)
CODA_FLAGS	= -I${CODA}/Linux-x86_64/include
HLS_FLAGS 	= -I/Work/apps/Vivado_HLS/2015.4/include
libTrigDIAG	= libTrigDiag

all:		ECTrig.o ECGeom.o TCLAAS12Detector.o TCLAS12Calo.o TRECHB_particle.o TCLAS12TrigCand.o TCLAS12Cherenkov.o ECGeom.o PCalGeom.o TECTrue.o
		rm -f ${libTrigDIAG}.so*
		$(CC) $(CC_Shared_FLAGS) -o lib/${libTrigDIAG}.so.1.0.1 $?
		cd lib;\
		ln -sf ${libTrigDIAG}.so.1.0.1 ${libTrigDIAG}.so.1; ln -sf ${libTrigDIAG}.so.1.0.1 ${libTrigDIAG}.so


ECTrig.o:	src/ECTrig.cxx include/ECTrig.hh
		$(CC) $(CC_OBJ_FLAGS) src/ECTrig.cxx -o $@ $(ROOT_CFLAGS) $(CODA_FLAGS) $(HLS_FLAGS) -I./include

ECGeom.o:	src/ECGeom.cxx include/ECGeom.hh
		$(CC) $(CC_OBJ_FLAGS) src/ECGeom.cxx -o $@ $(ROOT_CFLAGS) $(CODA_FLAGS) $(HLS_FLAGS) -I./include
	
PCalGeom.o:	src/TPCalGeom.cxx include/TPCalGeom.hh
		$(CC) $(CC_OBJ_FLAGS) src/TPCalGeom.cxx -o $@ $(ROOT_CFLAGS) $(CODA_FLAGS) $(HLS_FLAGS) -I./include

TECTrue.o:	src/TECTrue.cxx include/TECTrue.hh
		$(CC) $(CC_OBJ_FLAGS) src/TECTrue.cxx -o $@ $(ROOT_CFLAGS) $(CODA_FLAGS) $(HLS_FLAGS) -I./include


TRECHB_particle.o:  src/TRECHB_particle.cc include/TRECHB_particle.hh
		    $(CC) $(CC_OBJ_FLAGS) src/TRECHB_particle.cc -o $@ $(ROOT_CFLAGS) $(CODA_FLAGS) -I./include


TCLAS12TrigCand.o:	src/TCLAS12TrigCand.cxx include/TCLAS12TrigCand.hh
		$(CC) $(CC_OBJ_FLAGS) src/TCLAS12TrigCand.cxx -o $@  $(ROOT_CFLAGS) -I./include

TCLAAS12Detector.o:	src/TCLAS12Detector.cxx include/TCLAS12Detector.hh
			$(CC) $(CC_OBJ_FLAGS) src/TCLAS12Detector.cxx -o $@ $(ROOT_CFLAGS) -I./include

TCLAS12Calo.o:	src/TCLAS12Calo.cxx include/TCLAS12Calo.hh
		$(CC) $(CC_OBJ_FLAGS) src/TCLAS12Calo.cxx -o $@ $(ROOT_CFLAGS) -I./include

TCLAS12Cherenkov.o:	src/TCLAS12Cherenkov.cxx include/TCLAS12Cherenkov.hh
			$(CC) $(CC_OBJ_FLAGS) src/TCLAS12Cherenkov.cxx -o $@ $(ROOT_CFLAGS) -I./include

clean:
		rm -f lib/*.so.* lib/*.so *.o

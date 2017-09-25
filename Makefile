CC              = g++
CC_OBJ_FLAGS    = -c -fPIC
CC_Shared_FLAGS = -shared -Wl,-soname,libTrigDiag.so
ROOT_CFLAGS     = $(shell root-config --cflags)
ROOT_LIBS       = $(shell root-config --libs)
CODA_FLAGS	= -I${CODA}/Linux-x86_64/include
HLS_FLAGS 	= -I/Work/apps/Vivado_HLS/2015.4/include

libTrigDiag:	ECTrig.o ECGeom.o TrigCandid.o
		rm -f libTrigDiag.so*
		$(CC) $(CC_Shared_FLAGS) -o lib/$@.so.1.0.1 $?
		cd lib;\
		ln -sf $@.so.1.0.1 $@.so.1; ln -sf $@.so.1.0.1 $@.so


ECTrig.o:	src/ECTrig.cxx include/ECTrig.hh
		$(CC) $(CC_OBJ_FLAGS) src/ECTrig.cxx -o $@ $(ROOT_CFLAGS) $(CODA_FLAGS) $(HLS_FLAGS) -I./include

ECGeom.o:	src/ECGeom.cxx include/ECGeom.hh
		$(CC) $(CC_OBJ_FLAGS) src/ECGeom.cxx -o $@ $(ROOT_CFLAGS) $(CODA_FLAGS) $(HLS_FLAGS) -I./include


TrigCandid.o:	src/CLAS12TrigCandidate.cxx include/CLAS12TrigCandidate.hh
		$(CC) $(CC_OBJ_FLAGS) src/CLAS12TrigCandidate.cxx -o $@  $(ROOT_CFLAGS) -I./include

clean:
		rm -f lib/*.so.* lib/*.so *.o

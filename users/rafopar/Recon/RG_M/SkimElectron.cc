/* 
 * File:   SkimElectron.cc
 * Author: rafopar
 *
 * Created on November 21, 2021, 8:42 PM
 */

#include <string>
#include <cstdlib>
#include <math.h>

#include <TH2D.h>
#include <TH1D.h>
#include <TFile.h>

// ===== Hipo headers =====
#include <reader.h>
#include <writer.h>
#include <dictionary.h>


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    std::cout << " reading file example program (HIPO) " << __cplusplus << std::endl;

    int run, fNum;
    char inputFile[256];

    string fnameBase = "rec_clas_000000.evio.00000.hipo";

    if (argc > 2) {

        run = atoi(argv[1]);
        fNum = atoi(argv[2]);

        int nDgtRun = int(log10(run));
        int nDgtfNum = int(log10(fNum));

        fnameBase.replace(14 - nDgtRun, nDgtRun + 1, argv[1]);
        fnameBase.replace(25 - nDgtfNum, nDgtfNum + 1, argv[2   ]);
        //sprintf(outputFile,"%s",argv[2]);
    } else {
        std::cout << " *** please provide Run number and the file name" << std::endl;
        exit(0);
    }

    cout << "Input File Name is " << fnameBase << endl;

    hipo::reader reader;
    reader.open( Form("Data/%s", fnameBase.c_str() ));

    hipo::dictionary factory;

    reader.readDictionary(factory);

    factory.show();

    hipo::event event;
    int counter = 0;

    hipo::bank bRunConfig(factory.getSchema("RUN::config"));
    hipo::bank bVTP(factory.getSchema("RAW::vtp"));
    hipo::bank bECalClusters(factory.getSchema("ECAL::clusters"));
    hipo::bank bRecCal(factory.getSchema("REC::Calorimeter"));
    hipo::bank bRecCherenkov(factory.getSchema("REC::Cherenkov"));
    hipo::bank bRecEvent(factory.getSchema("REC::Event"));
    hipo::bank bHTCCRec(factory.getSchema("HTCC::rec"));
    hipo::bank bRecPart(factory.getSchema("REC::Particle"));



    hipo::writer writer;
    writer.getDictionary().addSchema(factory.getSchema("RUN::config"));
    writer.getDictionary().addSchema(factory.getSchema("RAW::vtp"));
    writer.getDictionary().addSchema(factory.getSchema("ECAL::clusters"));
    writer.getDictionary().addSchema(factory.getSchema("REC::Calorimeter"));
    writer.getDictionary().addSchema(factory.getSchema("REC::Cherenkov"));
    writer.getDictionary().addSchema(factory.getSchema("REC::Event"));
    writer.getDictionary().addSchema(factory.getSchema("HTCC::rec"));
    writer.getDictionary().addSchema(factory.getSchema("REC::Particle"));
    writer.open(Form("skim_em_%d_%d.hipo", run, fNum));

    int evCounter = 0;

    try {

        while (reader.next() == true) {
            reader.read(event);

            evCounter = evCounter + 1;

            if (evCounter % 10000 == 0) {
                cout.flush() << "Processed " << evCounter << " events \r";
            }

            event.getStructure(bRecPart);
            event.getStructure(bHTCCRec);
            event.getStructure(bRecEvent);
            event.getStructure(bRecCherenkov);
            event.getStructure(bRecCal);
            event.getStructure(bECalClusters);
            event.getStructure(bVTP);
            event.getStructure(bRunConfig);

            bool skimSatisfy = false;
            for( int i = 0; i < bRecPart.getRows(); i++ ){
                int pid = bRecPart.getInt("pid", i);
                int status = bRecPart.getInt("status", i);
                
                if( pid == 11 && abs(status) >= 2000 && abs(status) < 4000 ){
                    skimSatisfy = true;
                    //break;
                }
            }
            
            if( skimSatisfy ){
                writer.addEvent(event);
            }

        }
    } catch (const char *msg) {
        cerr << msg << endl;
    }


    writer.close();
    
    return 0;
}


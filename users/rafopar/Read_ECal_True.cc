#include <evioUtil.hxx>
#include <evioFileChannel.hxx>
#include <list>
#include <ECTrig.hh>
#include <ECGeom.hh>
#include <TECTrue.hh>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TObjArray.h>
#include <TChain.h>
#include <TStyle.h>

using namespace evio;
using namespace std;

// This program loops over events from the input file, given as an argument.
// It will search for banks with a tag "0xe122" ("57634" in decimal representation)
// Then will loop over all words inside the bank and decode all the information,
// e.g. which part of EC (in, or out), cluster coordinates (u, v, w), etc

int main(int argc, char **argv)
{

    const int EC_true_tag = 1601;

    TChain *ch1 = new TChain();

    if (argc < 2)
    {
        cout << "Please Specify input File name(s) " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    string inp_file_patttern = argv[1];
    cout << inp_file_patttern << endl;
    ch1->Add(inp_file_patttern.c_str());

    TObjArray *fname_list = ch1->GetListOfFiles();
    int n_files = fname_list->GetEntries();
    cout << "Number of Files is " << n_files << endl;


    TFile *file_out = new TFile("EC_True.root", "Recreate");

    TH2D *h_EC_mvyxc1 = new TH2D("h_EC_mvyxc1", "", 200, -5000., 5000., 200, -5000., 5000.);
    TH2D *h_EC_vyxc1 = new TH2D("h_EC_vyxc1", "", 200, -5000., 5000., 200, -5000., 5000.);
    TH2D *h_EC_vyxc2 = new TH2D("h_EC_vyxc2", "", 200, -5000., 5000., 200, -5000, 5000.);
    TH2D *h_EC_avg_yxc1 = new TH2D("h_EC_avg_yxc1", "", 200, -5000., 5000., 200, -5000., 5000.);
    TH2D *h_EC_avg_yxc2 = new TH2D("h_EC_avg_yxc2", "", 200, -5000., 5000., 200, -5000., 5000.);
    TH2D *h_EC_avg_yxc3 = new TH2D("h_EC_avg_yxc3", "", 200, -5000., 5000., 200, -5000., 5000.);
    TH2D *h_EC_avg_yxc4 = new TH2D("h_EC_avg_yxc4", "", 200, -5000., 5000., 200, -5000., 5000.);
    TH2D *h_EC_avg_yxc5 = new TH2D("h_EC_avg_yxc5", "", 200, -5000., 5000., 200, -5000., 5000.);

    TH2D *h_EC_avg_yxc_em0 = new TH2D("h_EC_avg_yxc_em0", "", 200, -5000., 5000., 200, -5000., 5000.);
    TH1D *h_EC_E1 = new TH1D("h_EC_E1", "", 200, 0., 12000.);
    TH1D *h_EC_E2 = new TH1D("h_EC_E2", "", 200, 0., 12000.);
    TH1D *h_EC_E3 = new TH1D("h_EC_E3", "", 200, 0., 12000.);
    TH1D *h_EC_E4 = new TH1D("h_EC_E4", "", 200, 0., 12000.);
    TH1D *h_EC_E5 = new TH1D("h_EC_E5", "", 200, 0., 12000.);

    try
    {

        for (int ifile = 0; ifile < n_files; ifile++)
        {

           evioFileChannel chan(fname_list->At(ifile)->GetTitle(), "r");
           cout<<"Runnin the file "<<fname_list->At(ifile)->GetTitle()<<endl;
            chan.open();
            int counter = 0;

            while (chan.read())
            {

                evioDOMTree tree(chan);

                evioDOMNodeListP nodelist1 = tree.getNodeList();

                vector<int> *ec_pid;
                bool is_ECpid = false;
                vector<int> *ec_tid;
                bool is_ECtid = false;
                vector<int> *ec_mtid;
                bool is_ECmtid = false;
                vector<double> *ec_E;
                bool is_ECE = false;

                vector<double> *ec_avg_x;
                bool is_EC_avgx = false;
                vector<double> *ec_avg_y;
                vector<double> *ec_avg_z;

                vector<double> *ec_px;
                bool is_ECpx = false;
                vector<double> *ec_py;
                bool is_ECpy = false;
                vector<double> *ec_pz;
                bool is_ECpz = false;

                vector<double> *ec_vx;
                bool is_ECvx = false;
                vector<double> *ec_vy;
                vector<double> *ec_vz;

                vector<double> *ec_mvx;
                bool is_ECmvx = false;
                vector<double> *ec_mvy;
                vector<double> *ec_mvz;


                for(std::list<evioDOMNode*>::iterator it = nodelist1.get()->begin(); it != nodelist1.get()->end(); it++)
                {

                    if ((*it)->tag == EC_true_tag && !(*it)->isLeaf()){
                        int size_EC_bank = (*it)->getSize();
                        //cout<<"size_EC_bank = "<<size_EC_bank<<endl;
                        
                       TECTrue ec_true(*it);
                       //ec_true.Print();
                    }
                    
                    
                    if ((*it)->tag == EC_true_tag && (*it)->isLeaf())
                    {

                        int size = (*it)->getSize();

                        int num = (*it)->num;

                        switch (num)
                        {

                        case 1: ec_pid = (vector<int>*)(*it)->getVector<int>();
                            is_ECpid = true;
                            break;
                        case 3: ec_tid = (vector<int>*)(*it)->getVector<int>();
                            is_ECtid = true;
                            break;
                        case 4: ec_mtid = (vector<int>*)(*it)->getVector<int>();
                            is_ECmtid = true;
                            break;
                        case 6: ec_E = (vector<double>*)(*it)->getVector<double>();
                            is_ECE = true;
                            break;

                        case 8: ec_avg_x = (vector<double>*)(*it)->getVector<double>();
                            is_EC_avgx = true;
                            break;
                        case 9: ec_avg_y = (vector<double>*)(*it)->getVector<double>();
                            break;
                        case 10: ec_avg_z = (vector<double>*)(*it)->getVector<double>();
                            break;

                        case 14: ec_px = (vector<double>*)(*it)->getVector<double>();
                            is_ECpx = true;
                            break;
                        case 15: ec_py = (vector<double>*)(*it)->getVector<double>();
                            is_ECpy = true;
                            break;
                        case 16: ec_pz = (vector<double>*)(*it)->getVector<double>();
                            is_ECpz = true;
                            break;

                        case 17: ec_vx = (vector<double>*)(*it)->getVector<double>();
                            is_ECvx = true;
                            break;
                        case 18: ec_vy = (vector<double>*)(*it)->getVector<double>();
                            break;
                        case 19: ec_vz = (vector<double>*)(*it)->getVector<double>();
                            break;

                        case 20: ec_mvx = (vector<double>*)(*it)->getVector<double>();
                            is_ECmvx = true;
                            break;
                        case 21: ec_mvy = (vector<double>*)(*it)->getVector<double>();
                            break;
                        case 22: ec_mvz = (vector<double>*)(*it)->getVector<double>();
                            break;
                        default: break;

                        }

                    }


                }

                if (is_ECmvx)
                {
                    int size_EC = ec_mvx->size();

                    bool has_em = false;
                    double E_max_em = -1.;
                    int ind_em_Max = -1.; // Index of e- with Max energy

                    for (int i = 0; i < size_EC; i++)
                    {
                        h_EC_mvyxc1->Fill(ec_mvx->at(i), ec_mvy->at(i));
                        h_EC_vyxc1->Fill(ec_vx->at(i), ec_vy->at(i));
                        h_EC_avg_yxc1->Fill(ec_avg_x->at(i), ec_avg_y->at(i));
                        h_EC_E1->Fill(ec_E->at(i));

                        if (ec_mtid->at(i) == 0)
                        {
                            h_EC_vyxc2->Fill(ec_vx->at(i), ec_vy->at(i));
                            h_EC_avg_yxc2->Fill(ec_avg_x->at(i), ec_avg_y->at(i));
                            h_EC_E2->Fill(ec_E->at(i));
                            //cout<<"ECtid = "<<ec_tid->at(i)<<"       ECmtid = "<<ec_mtid->at(i)<<"      E = "<<ec_E->at(i)<<"     x = "<<ec_avg_x->at(i)
                            //<<"    px = "<<ec_px->at(i)<<"    py = "<<ec_py->at(i)<<"    pz = "<<ec_pz->at(i)<<endl;

                            if (ec_pid->at(i) == 11)
                            {
                                h_EC_avg_yxc3->Fill(ec_avg_x->at(i), ec_avg_y->at(i));
                                h_EC_E3->Fill(ec_E->at(i));

                                if (ec_E->at(i) > E_max_em)
                                {
                                    E_max_em = ec_E->at(i);
                                    ind_em_Max = i;
                                }
                                has_em = true;
                            }
                            else if (ec_pid->at(i) == -11)
                            {
                                h_EC_avg_yxc4->Fill(ec_avg_x->at(i), ec_avg_y->at(i));
                                h_EC_E4->Fill(ec_E->at(i));
                            }
                            else if (ec_pid->at(i) == 2212)
                            {
                                h_EC_avg_yxc5->Fill(ec_avg_x->at(i), ec_avg_y->at(i));
                                h_EC_E5->Fill(ec_E->at(i));
                            }
                        }

                    }

                    //====

                    if (has_em)
                    {
                        h_EC_avg_yxc_em0->Fill(ec_avg_x->at(ind_em_Max), ec_avg_y->at(ind_em_Max));
                    }
                }

            }
            
            chan.close();

        }

    }
    catch (evioException e)
    {
        cerr << endl << e.toString() << endl;
        exit(EXIT_FAILURE);
    }

    gDirectory->Write();

}

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>

#include "TTree.h"
#include "TFile.h"

using namespace std;

bool IsOpt( string tmp ){
    if( tmp.size()>1 ){
        if( tmp[0]=='-'){
            if(tmp[1]=='-' || isalpha(tmp[1])>0 )
                return true;
        }
    }
    return false;
}

typedef vector<string> Parameter;
typedef map<string, Parameter> ParameterMap;

class Commandline{

public:

    Commandline( int argc, char* argv[]){
        Parse( argc, argv);
    }

    ~Commandline(){}

    void Parse( int argc, char* argv[]){

        map.clear();

        string key;
        string tmp;

        for( unsigned int i=0; i<argc; i++){

            tmp = string( argv[i] );
    
            if( IsOpt(tmp) || i==0 ){
                key = tmp;
                map[key] = Parameter();
            }
            else{
                map[key].push_back(tmp);
            }
        }
    }

    bool Find( string key ){ return map.find(key)!=map.end(); }
    
    vector<string> Get( string key ){ return map[key]; }

    void Print(){
        ParameterMap::iterator itr;
        for( itr=map.begin(); itr!=map.end(); itr++ ){
            cout << itr->first << ":";
            for( Parameter::iterator itr2 = itr->second.begin(); itr2!=itr->second.end(); itr2++ ){
                cout << " " << *itr2;
            }
            cout << endl;
        }
    }

    int Size(){ return map.size(); }

private:

    ParameterMap map;
};


int main( int argc, char* argv[]){ 

    Commandline cmdl( argc, argv);

    if( cmdl.Size()==1 || cmdl.Find("-h") || cmdl.Find("--help") ){
        cout << "\nusage: " << argv[0] << "[--active x y z] --voi u v w --input f0.root f1.root ... --output foo.root\n\n";
        return 0;
    }
/*
    string output_name = argv[argc-1];
    TFile* outfile = new TFile( output_name.c_str(), "NEW");
    if( !outfile ){
        cout << "Error creating file " << output_name << endl;
        return -2;
    }

    TTree* tree = new TTree( "events", "MC simulation for Compton scattering");
    EventInfo wdata;   // data for writing

    tree->Branch( "file", &wdata.file_name, "file[128]/C");
    tree->Branch( "ID", &wdata.ID, "ID/I");
    tree->Branch( "evtID", &wdata.evtID, "evtID/I");
    tree->Branch( "Edep", &wdata.edep, "Edep/D" );
    tree->Branch( "time", &wdata.time, "time/D");
    

    // ************************** //
    // * Process the input file * //
    // ************************** //


    for( int t = 1; t<argc-1; t++ ){

        string filename( argv[t] );
        TFile* infile = TFile::Open( filename.c_str(), "READ");

        if( !infile ){
            cout << "ERROR reading file " << filename << endl;
        }
        else{
            cout << "Processing " << filename << endl;
        }

        strncpy( wdata.file_name, argv[t], 128);

        TTree* events = (TTree*)infile->Get("events");
        int nentries = events->GetEntries();

        TrackInfo data;    // data for reading
        events -> SetBranchAddress("eventID", &data.eventID);
        events -> SetBranchAddress("trackID", &data.trackID);
        events -> SetBranchAddress("parentID", &data.parentID);
        events -> SetBranchAddress("particle", &data.particle_name);
        events -> SetBranchAddress("volume", &data.volume_name);
        events -> SetBranchAddress("Eki", &data.Eki);
        events -> SetBranchAddress("Ekf", &data.Ekf);
        events -> SetBranchAddress("Edep", &data.Edep);
        events -> SetBranchAddress("t", &data.time);
        events -> SetBranchAddress("process", &data.proc_name);


        // ************************** //
        // * Process the input file * //
        // ************************** //

        int evt_counter = -1;
        for( unsigned int i=0; i<nentries; i++){
            
            events->GetEntry(i);

            bool fillTree = false;

            if(  ( strncmp( data.proc_name, "newEvent", 8)==0 ) )
                fillTree = true;
            else if(  ( strncmp( data.proc_name, "timeReset", 9)==0 ) )
                fillTree = true;
            else if(i==nentries-1 )
                fillTree = true;
            else if(  ( data.parentID==0 && strncmp( data.proc_name, "initStep", 8)==0 ) )
                fillTree = true;

            if( fillTree==true ){

                if( i!=0 ){
                    ProcessEventInfo( &wdata );
                    //cout << wdata.edep_he_n << endl;
                    tree->Fill();
                    evt_counter++;
                    ResetEventInfo( &wdata );
                }
                
                wdata.ID = evt_counter;
                wdata.evtID = data.eventID;
            }
            else{
                string volume_name = data.volume_name;

                Hit hit;
                hit.parentID = data.parentID;
                hit.particle = data.particle_name;
                hit.process = data.proc_name;
                hit.volume = data.volume_name;
                hit.edep = data.Edep;
                hit.time = data.time;

                wdata.hit_collection.push_back( hit );
            }

        }

        infile->Close();
    }

    outfile->cd();
    tree->Write();
    outfile->Close();
*/
    return 0;
}



#ifndef TRACKREADER_H
#define TRACKREADER_H 1

#include <string>
#include <vector>
#include <map>

using namespace std;

class TrackReader{

public:

    // Constructor
    TrackReader(){}

    // Destructor
    ~TrackReader(){;}

    void Reset(){}

    // Add an active volume
    void SetActiveVolume( vector<string> name){ arrayAV = name;}
        // Active volume is by which event clustering will be performed

    // Add a volume of interest.
    void SetVoI( vector<string> name ){ arrayVOI = name; }
        // A volume of interest is by definition volume which energy deposit will be summed and recorded

    // Sets the (hypothetical) DAQ window in microsecond.
    void SetDAQWindow( float win = 1){ daqWindow = win;}
        // Events ocurring within this window is regarded as the same event.

    float GetDAQWindow(){ return daqWindow; }

    // Sets the coincidence window in microseconds
    void SetCoinWindow( float win = 1){ coinWindow = win;}
        // Events ocurring within this window from an event in active volume will be recorded.
    
    float GetCoinWindow(){ return coinWindow; }

    // Process the tracks in input and write output as a ROOT TTree in output.
    void Process( string output, vector<string> inputs );

private:

    static const unsigned int MAX_FILENAME_LEN = 128;

    double daqWindow;
    double coinWindow;

    vector<string> arrayAV;
        // This array holds the active volumes.
    vector<string> arrayVOI;
        // This array holds the volumes of interest.
        // If it's zero, will treat all volumes as volume of interest.

    vector<string> GetVOIFromFile( vector<string> inputName){}
        // Iterate through given files to generate a list of volumes involved.

    // Set branch variables to the default values.
    void InitializeBranchVariables(){
        map<string, double>::iterator itr;
        for( itr = energyDeposit.begin(); itr!=energyDeposit.end(); itr++ ){
            itr->second = 0;
        }
        for( itr = timeStamp.begin(); itr!=timeStamp.end(); itr++ ){
            itr->second = -1;
        }
    }

    char inputFileNameChar[ MAX_FILENAME_LEN ];
        // name of the file to which this event belongs to
    unsigned int ID;
        // global ID of the event processed
    unsigned int eventID;
        // event ID in its own run.
    unsigned int clusterIndex;
        // index of the event cluster when multiple event occurred in the DAQ window.

    map<string, double> energyDeposit;
    map<string, double> timeStamp;

    /*
    map<string, vector<Hit>> hitArrayActive;
    map<string, vector<Hit>> hitArrayActiveSum;
    map<string, vector<Hit>> hitArrayVOI;
    map<string, vector<Hit>> hitArrayVOISum;
        // Contains hit for each volume
        // Hit class contains particle name, edep and time.
    */
};

/*
class HitArray{

public:

    HitArray();

    ~HitArray();

    void Sort(){ std::sort( array.begin(), array.end()); }

    void Cluster( double time){
        Hit tmp;
        tmp.time = time;
    }

    void ResetIterator(){ header = array.begin(); }
private:

    vector<Hit> array;

    vector<Hit>::iterator header;

};

struct Hit{

    double time;

    double edep;

    string particle;

    bool operator <( const Hit& b){
        return time < b.time;
    }

};
*/

#endif

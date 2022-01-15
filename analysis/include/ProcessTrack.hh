
#include <string>
#include <map>

using namespace std;


enum MODE { VOI, ALL };


class TrackReader{

public:

    // Constructor
    TrackReader();

    // Destructor
    ~TrackReader();

    // Add a volume of interest.
    void AddVoI( string name );
        // A volume of interest is by definition volume which energy deposit will be summed and recorded

    // Add an active volume
    void SetActiveVolume( string name);
        // Active volume is by which event clustering will be performed

    // Add a type of particle for separate recording.
    void AddPID( string name );

    // Sets the (hypothetical) DAQ window in microsecond.
    void SetDAQWindow( float win = 1){ daqWindow = win;}
        // Events ocurring within this window is regarded as the same event.

    // Sets the coincidence window in microseconds
    void SetCoinWindow( float win = 1){ coinWindow = win;}
        // Events ocurring within this window from an event in active volume will be recorded.

    // Process the tracks in input and write output as a ROOT TTree in output.
    void ProcessFile(string input_name, string output_name);

    // Set branch variables to the default values.
    void InitializeBranchVariables(){
        map<string,double>::iterator itr;
        for( itr = edep.begin(); itr!=edep.end(); itr++ ){
            *(itr.second) = 0;
        }
        for( itr = timestamp.begin(); itr!=timestamp.end(); itr++ ){
            *(itr.second) = -1;
        }

    }

private:

    string activeVolumeName;

    vector<string> arrayPID;
        // Energy summed independently by particle type.

    vector<string> arrayVOI;
        // This array holds the volumes of interest.
        // If this array is non-empty, will record only energy deposits in VOI.
        // If it's zero, will treat all volumes as volume of interest.

    vector<string> GetVOIFromFile( vector<string> inputName);
        // Iterate through given files to generate a list of volumes involved.


    char inputFileNameChar[128];
        // name of the file to which this event belongs to
    unsigned int ID;
        // global ID of the event processed
    unsigned int eventID;
        // event ID in its own run.
    unsigned int clusterIndex;
        // index of the event cluster when multiple event occurred in the DAQ window.

    map<string, double> edep;
    map<string, double> timestamp;
    map<string, vector<Hit>> hitArrayActive;
    map<string, vector<Hit>> hitArrayActiveSum;
    map<string, vector<Hit>> hitArrayVOI;
    map<string, vector<Hit>> hitArrayVOISum;
        // Contains hit for each volume
        // Hit class contains particle name, edep and time.
};


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

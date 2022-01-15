
#include "ProcessTrack.h"

void ProcessFile( string outputFileNameStr, vector<string> inputs ){

    // ==================================================
    // Create ROOT file
    // ==================================================
    //
    TFile* file = new TFile( outputFileNameStr, "NEW");

    if( !file ){
        cerr << "Error creating output file " << outputFileNameStr << endl;
        return;
    }

    // ==================================================
    // Prepare VOI and PSD for writing trees
    // ==================================================
    //
    // If no volume-of-interest is specified, iterate over the file to get all the volumes involved.
    if( arrayVOI.empty()==true ){
    
    }

    // If no particle discrimination is specified, do nothing.
    // Later this will be used to create a global edep variable to contain the total edep.
    if( arrayPID.empty()==true ){
        usePID = false;
    }

    // ==================================================
    // Create ROOT TTree and initialize branches.
    // ==================================================
    //
    TTree* tree = new TTree("events", "Event-level information for MC simulated tracks.");

    tree->Branch( "file", &outputFileNameChar, "file[128]/C");
    tree->Branch( "ID", &ID, "ID/I");
    tree->Branch( "eventID", &eventID, "eventID/I");
    tree->Branch( "clusterIndex", &clusterIndex, "clusterIndex/I");
    
    // Generate energy deposition array for volumes of interest.
    for( vector<string>::iterator itr1 = arrayVOI.begin(); itr1!=arrayVOI.end(); itr1++ ){
        
        string volumeName = *itr1;
        vector<Hit> hit;

        string edepName = string("edep_") + *itr1;
        string rootName = edepName+"/D";
            // rootName is name + ROOT data format.

        energyDeposit[ name ] = 0;
        timeStamp[ name ] = -1;
        hitArray[ volumeName ] = hit;

        // Set address for ROOT tree branch
        tree->Branch( edepName, &energyDeposit[name], rootName.c_str() );
        tree->Branch( "timeStamp", &timeStamp[name], "timeStamp/D" );
    }

    ID = 0;

    for( vector<string>::iterator itr = inputs.begin(); itr!=inputs.end(); itr++ ){
        
        // ==================================================
        // Open the ROOT file to read and set branch variables
        // ==================================================
        //
        string inputFileName = *itr;
        TFile* inputFile = TFile::Open( inputFileName.c_str(), "READ");

        if( !inputFile ){
            cerr << "ERROR reading file " << inputFileName << endl;
            cerr << "Skipping...\n";
            continue;
        }
        else{
            cout << "Processing " << inputFileName << endl;
        }


        // Retrieve the tree
        TTree* inputTree = (TTree*)inputFile->Get("events");
        unsigned int nEntries = inputTree->GetEntries();
            // remember max of 4 billion

        // Set branch variables.
        //
        strncpy( inputFileNameChar, inputFileName.c_str(), 128-1 );

        // data for reading/input
        // Check branch names!
        //
        TrackInfo rdata;
        inputTree -> SetBranchAddress("eventID", &rdata.eventID);
        inputTree -> SetBranchAddress("trackID", &rdata.trackID);
        inputTree -> SetBranchAddress("parentID", &rdata.parentID);
        inputTree -> SetBranchAddress("particle", &rdata.particle_name);
        inputTree -> SetBranchAddress("volume", &rdata.volume_name);
        inputTree -> SetBranchAddress("Eki", &rdata.Eki);
        inputTree -> SetBranchAddress("Ekf", &rdata.Ekf);
        inputTree -> SetBranchAddress("Edep", &rdata.Edep);
        inputTree -> SetBranchAddress("t", &rdata.time);
        inputTree -> SetBranchAddress("process", &rdata.proc_name);

        for( unsigned int n = 1; n<nEntries; n++ ){
            
            inputTree->GetEntry(n);

            // If current event is a new event or the last event, fill the previous event and initialize.
            if( IsNewEvent()==true || n==nEntries-1 ){

                ProcessHitArray();
                ID++;

                // Initialize variables for next event.
                InitBranchVariables();
                InitHitArray();
                clusterIndex = 0;
            }

            // If not new event flag, then it's a regular step.
            // Check if it falls in one of the active volumes.
            // If yes, then put it in the energy deposit array to be processed later.
            //ProcessTrack( rdata );

            string volumeName = string(rdata.volume_name);
            string particleName = string(rdata.volume_name);

            if( hitArrayActive.find(volumeName)!=hitArrayActive.end() ){
                Hit hit( particleName, rdata.Edep, rdata.t );
                hitArrayActive[volumeName].push_back(hit);
            }
            else if( hitArrayVOI.find(volumeName)!=hitArrayVOI.end() ){
                Hit hit( particleName, rdata.Edep, rdata.t );
                hitArrayVOI[volumeName].push_back(hit);
            }

            // Warning: currently, the coincidence window and DAQ window is not implemented.
        }
        
    }
    

}

void ProcessHitArray(){
    
    // First, sort hit array of active volumes by chronological order:
    for( map<string, vector<Hit>>::iterator itr = hitArrayActive.begin(); itr!=hitArrayActive.end(); itr++ ){
        std::sort( itr->second.begin(), itr->second.end() );
    }

    // Next, go through each array and cluster energy deposits in active volumes
    string activeVolumeName;
    vector<Hit>& tmpArray = hitArrayActive[activeVolumeName];

    Hit tmpHit;
    double prevTimeStamp = -1;

    if( tmpArray.size()>0 ){

        tmpHit = tmpArray[0];
        prevTimeStamp = tmpHit.time;

        for( unsigned int i=1; i<tmpArray.size(); i++){
            if( tmpArray[i].time - prevTimeStamp > daqWindow ){
                hitArrayActiveSum.push_back( tmpHit );
                tmpHit = tmpArray[i];
            }
            else{
                tmpHit += tmpArray[i];
            }
        }

        hitArrayActiveSum.push_back( tmpHit );
    }



}






bool IsNewEvent( char* name ){
    if (strncmp( name, "newEvent", 8)==0 ){
        return true;
    }
    else if( strncmp( name, "timeReset", 9)==0 ){
        return true;
    }
    //else if( data.parentID==0 && strncmp( data.proc_name, "initStep", 8)==0 ){
    //    return true;
    //}
    return false;
}


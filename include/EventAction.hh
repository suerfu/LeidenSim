/*
    Author:  Burkhant Suerfu
    Date:    November 18, 2021
    Contact: suerfu@berkeley.edu
*/

/// \file EventAction.hh
/// \brief Definition of the EventAction class

#ifndef EVENTACTION_H
#define EVENTACTION_H 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "StepInfo.hh"
#include "RunAction.hh"


/// EventAction is responsible for processing the events.
/// The process mainly includes iterating over the tracks/steps and write them into a ROOT file.

class EventAction : public G4UserEventAction{

public:

    EventAction( RunAction* runaction );
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void PrintEventStatistics() const;
    
    vector<StepInfo>& GetStepCollection();
        //!< A vector that contains each steps in this event.

private:
    
    RunAction* fRunAction;
        //!< Pointer to RunAction to get output filename, etc.

    CommandlineArguments* cmdl;
        //!< Pointer to commandline arguments so that EventAction can access commandline parameters.

    vector<StepInfo> stepCollection;
    
    TTree* data_tree;
        //!< Pointer to a ROOT TTree object.

    int max_char_len;
        //!< Maximum character length to store in ROOT. Using char[] insteat of string will speed up things.

    char particleName[16];
    char volumeName[16];
    char processName[16];

    G4String tmp_particleName;
    G4String tmp_volumeName;
    G4String tmp_processName;
    
    G4ThreeVector position;
    G4ThreeVector momentum;

    StepInfo wStep;
        //!< StepInfo for writing to ROOT output.
};


#endif

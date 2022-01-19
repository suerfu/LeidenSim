/*
    Author:  Burkhant Suerfu
    Date:    November 18, 2021
    Contact: suerfu@berkeley.edu
*/

#include "StepInfo.hh"

#include "globals.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
#include "G4ThreeVector.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"

using namespace std;

using CLHEP::mm;
using CLHEP::ns;
using CLHEP::keV;

StepInfo::StepInfo()
  : eventID(-1),
    trackID(-1),
    stepID(-1),
    parentID(-1),
    particleName(""),
    volumeName(""),
    volumeCopyNumber(0),
    Eki(0),
    Ekf(0),
    Edep(0),
    position(0),
    momentumDir(0),
    globalTime(0),
    processName("")
{}


StepInfo::StepInfo( const G4Step* step )
  : eventID(-1),
    trackID(-1),
    stepID(-1),
    parentID(-1),
    particleName(""),
    volumeName(""),
    volumeCopyNumber(0),
    Eki(0),
    Ekf(0),
    Edep(0),
    position(0),
    momentumDir(0),
    globalTime(0),
    processName("")
{

    // From the input step, get necessary pointers to steps and tracks.
    //
    G4StepPoint* postStep = step->GetPostStepPoint();
    G4StepPoint* preStep = step->GetPreStepPoint();
    G4Track* track = step->GetTrack();

    // Set various IDs
    //
    SetEventID( G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID() );
    SetTrackID( track->GetTrackID() );
    SetStepID( track->GetCurrentStepNumber() );
    SetParentID( track->GetParentID() );

    SetParticleName( track->GetParticleDefinition()->GetParticleName() );

    // If postStep is not pointing to any physical volume, set a special flag.
    if(!postStep->GetPhysicalVolume()){
        SetVolumeName( "OutOfWorld" );
        SetVolumeCopyNumber( 0 );
    }
    else {
        SetVolumeName( postStep->GetPhysicalVolume()->GetName() );
        SetVolumeCopyNumber( postStep->GetPhysicalVolume()->GetCopyNo() );
    }

    // Retrieve kinematic information.
    //
    SetPosition( postStep->GetPosition() );
    SetMomentumDir(postStep->GetMomentumDirection() );
    SetGlobalTime( postStep->GetGlobalTime() );

    SetEki( preStep->GetKineticEnergy() );
    SetEkf( postStep->GetKineticEnergy() );
    SetEdep( step->GetTotalEnergyDeposit() );

    // If this is a first step in the series, set process name to be a special flag.
    //
    if(!postStep->GetProcessDefinedStep()){
        SetProcessName( "initStep" );
    } 
    else {
        SetProcessName( postStep->GetProcessDefinedStep()->GetProcessName() );
    }
}


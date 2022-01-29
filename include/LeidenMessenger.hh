/*
    Author:  Burkhant Suerfu
    Date:    November 18, 2021
    Contact: suerfu@berkeley.edu
*/

/// \file LeidenMessenger.hh
/// \brief Definition of the LeidenMessenger class

#ifndef LeidenMessenger_h
#define LeidenMessenger_h 1

#include "globals.hh"
#include "CLHEP/Units/PhysicalConstants.h"
#include "G4UImessenger.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"

class Leiden;


class LeidenMessenger: public G4UImessenger{

public:

    LeidenMessenger( Leiden* );

    virtual ~LeidenMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

private:

    Leiden* detector;

    G4UIdirectory* directory;
    
    G4UIcmdWithADoubleAndUnit* cmdActiveLength;
    G4UIcmdWithADoubleAndUnit* cmdCellDiameter;
    G4UIcmdWithADoubleAndUnit* cmdCellHeight;
    G4UIcmdWithADoubleAndUnit* cmdWallThickness;
    G4UIcmdWithADoubleAndUnit* cmdLHe;
    G4UIcmdWithADoubleAndUnit* cmdLN2;
        // Orientation of the target

    //G4UIcommand* place_detector;
        // Place the actual object

    G4String name = "target";
    G4String dirname = G4String("/")+name+"/";
};

#endif

/*
    Author:  Burkhant Suerfu
    Date:    November 18, 2021
    Contact: suerfu@berkeley.edu
*/

/// \file GeometryConstruction.hh
/// \brief Definition of the GeometryConstruction class

#ifndef GEOMETRYCONSTRUCTION_H
#define GEOMETRYCONSTRUCTION_H 1

#include "G4VUserDetectorConstruction.hh"
//<<<<<<< HEAD
#include "GeoManager.hh"
//#include "RunAction.hh"

//=======
//#include "GeometryManager.hh"

#include "SimpleCube.hh"
#include "FarsideDetectorMessenger.hh"

//>>>>>>> master
#include "globals.hh"


class GeometryConstructionMessenger;


/// Detector construction class to define materials and geometry.



class GeometryConstruction : public G4VUserDetectorConstruction{

public:

//<<<<<<< HEAD
    GeometryConstruction();
//=======
//    GeometryConstruction( GeometryManager* man );
//>>>>>>> master

    virtual ~GeometryConstruction();

public:

    virtual G4VPhysicalVolume* Construct();
        // This method calls DefineMaterials and DefineVolumes successively.

    G4VPhysicalVolume* ConstructWorld();

    void ConstructUserVolumes();

    //G4VIStore* CreateImportanceStore();


private:

//<<<<<<< HEAD
    //RunAction* fRunAction;
    GeometryConstructionMessenger* fDetectorMessenger;
    
//=======
//    GeometryManager* fGeometryManager;
//    GeometryConstructionMessenger* fDetectorMessenger;

    FarsideDetectorMessenger* fFarsideMessenger;

//>>>>>>> master
    bool fCheckOverlaps;

    G4double world_x;
    G4double world_y;
    G4double world_z;

    SimpleCube* simple_cube;

};


#endif

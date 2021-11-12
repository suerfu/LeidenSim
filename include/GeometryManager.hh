#ifndef GEOMETRYMANAGER_H
#define GEOMETRYMANAGER_H 1

#include <map>
#include <utility>

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "CLHEP/Units/PhysicalConstants.h"
#include "G4NistManager.hh"

#define M_PI 3.1415926535

using namespace CLHEP;

class GeometryManager{

public:

    GeometryManager();

    ~GeometryManager();

    void Add( G4String name, G4LogicalVolume* log, G4VPhysicalVolume* phys);

    G4LogicalVolume* GetLogicalVolume( G4String name );

    G4VPhysicalVolume* GetPhysicalVolume( G4String name );

    G4NistManager* GetMaterialManager();

    G4Material* GetMaterial(G4String name);

private:

    std::map< G4String, std::pair<G4LogicalVolume*, G4VPhysicalVolume*> > dictionary;

    G4NistManager* material_man;

    /// User should define all materials to be used in this function.
    void DefineMaterials();

};


#endif

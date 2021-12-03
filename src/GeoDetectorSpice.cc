
#include "GeoDetectorSpice.hh"

#include "G4Box.hh"
#include "G4VSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"

GeoDetectorSpice::GeoDetectorSpice( ){


    fCheckOverlaps = false;

}


void GeoDetectorSpice::Construct(){
    
    G4LogicalVolume* motherLogic = GeometryManager::Get()->GetLogicalVolume("world");
    if( motherLogic==0 ){
        G4cerr << "Cannot find the logical volume of world." << G4endl;
        return;
    }
}

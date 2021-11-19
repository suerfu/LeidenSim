
#include "GeoDetectorHerald.hh"

#include "G4Box.hh"
#include "G4VSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"

GeoDetectorHerald::GeoDetectorHerald(){


    fCheckOverlaps = false;

}


void GeoDetectorHerald::Construct(){
    
    G4LogicalVolume* motherLogic = GeoManager::Get()->GetLogicalVolume("world");
    if( motherLogic==0 ){
        G4cerr << "Cannot find the logical volume of world." << G4endl;
        return;
    }

    //GeoManager::Get()->Add( name, box_lv, box_pv);
}

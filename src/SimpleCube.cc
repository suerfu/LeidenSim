
#include "SimpleCube.hh"
#include "SimpleCubeMessenger.hh"

#include "G4Box.hh"
#include "G4VSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"

SimpleCube::SimpleCube(){

    L_in = 5 * cm;
    L_out = 10 * cm;

    fCheckOverlaps = false;

    fSimpleCubeMessenger = new SimpleCubeMessenger( this );
}


void SimpleCube::Construct(){
    
    G4LogicalVolume* motherLogic = GeoManager::Get()->GetLogicalVolume("world");
    if( motherLogic==0 ){
        G4cerr << "Cannot find the logical volume of world." << G4endl;
        return;
    }

    G4String name = "cube";

    G4Box* box1_solid = new G4Box( name+"1_solid", L_out/2, L_out/2, L_out/2);
    G4Box* box2_solid = new G4Box( name+"2_solid", L_in/2, L_in/2, L_in/2);
    G4VSolid* box_solid = new G4SubtractionSolid("cube_solid", box1_solid, box2_solid);

    G4Material* tungsten = GeoManager::Get()->GetMaterial("G4_W");
    G4LogicalVolume* box_lv = new G4LogicalVolume( box_solid, tungsten, name+"_lv");

    G4VPhysicalVolume* box_pv = new G4PVPlacement( 0, G4ThreeVector(0,0,0), box_lv, name, motherLogic, false, 0, fCheckOverlaps);

	GeoManager::Get()->Add( name, box_lv, box_pv);
}

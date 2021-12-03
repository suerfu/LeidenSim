/*
    Author:  Burkhant Suerfu
    Date:    November 18, 2021
    Contact: suerfu@berkeley.edu
*/
#include "SimpleCube.hh"
#include "SimpleCubeMessenger.hh"

#include "G4Box.hh"
#include "G4VSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"

SimpleCube::SimpleCube(){

    thisName = "target";

    L_in = 5 * cm;
    L_out = 10 * cm;

    fCheckOverlaps = false;

    fSimpleCubeMessenger = new SimpleCubeMessenger( this );

}


SimpleCube::~SimpleCube(){
    delete fSimpleCubeMessenger;
}


void SimpleCube::Construct(){
    
    G4LogicalVolume* motherLogic = GeoManager::Get()->GetLogicalVolume("world");
    if( motherLogic==0 ){
        G4cerr << "Cannot find the logical volume of world." << G4endl;
        return;
    }

    G4Box* box1_solid = new G4Box( thisName+"1_solid", L_out/2, L_out/2, L_out/2);
    G4Box* box2_solid = new G4Box( thisName+"2_solid", L_in/2, L_in/2, L_in/2);
    G4VSolid* box_solid = new G4SubtractionSolid("cube_solid", box1_solid, box2_solid);

//<<<<<<< HEAD
//    G4Material* tungsten = GeoManager::Get()->GetMaterial("G4_W");
//    G4LogicalVolume* box_lv = new G4LogicalVolume( box_solid, tungsten, name+"_lv");
//
//    G4VPhysicalVolume* box_pv = new G4PVPlacement( 0, G4ThreeVector(0,0,0), box_lv, name, motherLogic, false, 0, fCheckOverlaps);
//
//	GeoManager::Get()->Add( name, box_lv, box_pv);
//=======
    G4Material* tungsten = GeoManager::Get()->GetMaterial("G4_W");
    G4LogicalVolume* box_lv = new G4LogicalVolume( box_solid, tungsten, thisName+"_lv");

    new G4PVPlacement( 0, G4ThreeVector(0,0,0), box_lv, thisName, motherLogic, false, 0, fCheckOverlaps);

}


void SimpleCube::SetMaterial( G4String material_name ){
    G4Material* material = GeoManager::Get()->GetMaterial( material_name );
    if( material!=0 ){
        G4LogicalVolume* cube_lv = GeoManager::Get()->GetLogicalVolume( thisName );
        if( cube_lv ){
            cube_lv->SetMaterial( material );
			GeoManager::Get()->GeometryHasBeenModified();
        }
    }
}


void SimpleCube::SetPosition( G4ThreeVector s){
    
    G4VPhysicalVolume* cube_pv = GeoManager::Get()->GetPhysicalVolume( thisName );
    if( cube_pv ){
        cube_pv->SetTranslation(s);
		GeoManager::Get()->GeometryHasBeenModified();
    }
    
}


void SimpleCube::RotateX( G4double a){
    
    G4VPhysicalVolume* cube_pv = GeoManager::Get()->GetPhysicalVolume( thisName );

    if( cube_pv ){
        G4RotationMatrix* rot = cube_pv->GetRotation();
        if( !rot ){
            rot = new G4RotationMatrix;
        }

        rot->rotateX(a);
        cube_pv->SetRotation( rot );

		GeoManager::Get()->GeometryHasBeenModified();
    }    
}


void SimpleCube::RotateY( G4double a){
    
    G4VPhysicalVolume* cube_pv = GeoManager::Get()->GetPhysicalVolume( thisName );

    if( cube_pv ){
        G4RotationMatrix* rot = cube_pv->GetRotation();
        if( !rot ){
            rot = new G4RotationMatrix;
        }

        rot->rotateY(a);
        cube_pv->SetRotation( rot );

		GeoManager::Get()->GeometryHasBeenModified();
    }
}


void SimpleCube::RotateZ( G4double a){

    
    G4VPhysicalVolume* cube_pv = GeoManager::Get()->GetPhysicalVolume( thisName );

    if( cube_pv ){
        G4RotationMatrix* rot = cube_pv->GetRotation();
        if( !rot ){
            rot = new G4RotationMatrix;
        }

        rot->rotateZ(a);
        cube_pv->SetRotation( rot );

		GeoManager::Get()->GeometryHasBeenModified();
    }
//>>>>>>> master
}

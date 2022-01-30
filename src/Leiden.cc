/*
    Author:  Burkhant Suerfu
    Date:    November 18, 2021
    Contact: suerfu@berkeley.edu
*/
#include "Leiden.hh"
#include "LeidenMessenger.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4VSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"

Leiden::Leiden(){

    fCheckOverlaps = false;

    fLeidenMessenger = new LeidenMessenger( this );
}


Leiden::~Leiden(){
    delete fLeidenMessenger;
}


void Leiden::Construct(){
    
    G4LogicalVolume* motherLogic = GeometryManager::Get()->GetLogicalVolume("world");
    if( motherLogic==0 ){
        G4cerr << "Cannot find the logical volume of world." << G4endl;
        return;
    }

    G4Material* LHe = GeometryManager::Get()->GetMaterial("LHe");
    G4Material* LN2 = GeometryManager::Get()->GetMaterial("LN2");
    G4Material* SS = GeometryManager::Get()->GetMaterial("SS");
    G4Material* Cu = GeometryManager::Get()->GetMaterial("Cu");
    
    thisName = "cellEnclosure";
    G4Box* enclosure_solid = new G4Box( thisName+"_solid", (cellDiameter+wallThickness*2)/2, (cellDiameter+wallThickness*2)/2, (cellDiameter+wallThickness*2)/2);
    G4LogicalVolume* enclosure_lv = new G4LogicalVolume( enclosure_solid, Cu, thisName+"_lv");
    new G4PVPlacement( 0, G4ThreeVector(0,0,0), enclosure_lv, thisName, motherLogic, false, 0, fCheckOverlaps);

    thisName = "cellBuffer";

    G4Box* bufferVolume_solid = new G4Box( thisName+"_solid", cellDiameter/2, cellDiameter/2, cellDiameter/2);
    G4LogicalVolume* bufferVolume_lv = new G4LogicalVolume( bufferVolume_solid, LHe, thisName+"_lv");
    new G4PVPlacement( 0, G4ThreeVector(0,0,0), bufferVolume_lv, thisName, enclosure_lv, false, 0, fCheckOverlaps);

    thisName = "cellWall";
    G4Box* cellWall_solid = new G4Box( thisName+"_solid", (activeLength+2*mm)/2, (activeLength+2*mm)/2, (activeLength+2*mm)/2);
    G4LogicalVolume* cellWall_lv = new G4LogicalVolume( cellWall_solid, Cu, thisName+"_lv");
    new G4PVPlacement( 0, G4ThreeVector(0,0,0), cellWall_lv, thisName, bufferVolume_lv, false, 0, fCheckOverlaps);

    thisName = "cellActive";

    G4Box* activeVolume_solid = new G4Box( thisName+"_solid", activeLength/2, activeLength/2, activeLength/2);
    G4LogicalVolume* activeVolume_lv = new G4LogicalVolume( activeVolume_solid, LHe, thisName+"_lv");
    new G4PVPlacement( 0, G4ThreeVector(0,0,0), activeVolume_lv, thisName, cellWall_lv, false, 0, fCheckOverlaps);


    G4cout << "Constructing IVC" << G4endl;

    G4double inch = 2.54 * cm;

    G4double IVC_ID = 6.59 * inch * 2;
    G4double IVC_wall = 0.09 * inch;
    G4double IVC_OD = 6.59 * inch * 2 + IVC_wall * 2;

    thisName = "IVC";

    G4Tubs* ivc_solid = new G4Tubs( thisName+"_solid", IVC_ID/2, IVC_OD/2, 1*m, 0, CLHEP::twopi );
    G4LogicalVolume* ivc_lv = new G4LogicalVolume( ivc_solid, SS, thisName+"_lv");
    new G4PVPlacement( 0, G4ThreeVector(0,0,0), ivc_lv, thisName, motherLogic, false, 0, fCheckOverlaps);


    G4double HeBath_ID = IVC_OD;
    G4double HeBath_OD = 15.942 * inch - 2*0.028*inch;
    
    thisName = "HeBath";

    G4Tubs* HeBath_solid = new G4Tubs( thisName+"_solid", HeBath_ID/2, HeBath_OD/2, 1*m, 0, CLHEP::twopi );
    G4LogicalVolume* HeBath_lv = new G4LogicalVolume( HeBath_solid, LHe, thisName+"_lv");
    new G4PVPlacement( 0, G4ThreeVector(0,0,0), HeBath_lv, thisName, motherLogic, false, 0, fCheckOverlaps);


    G4double HeCryo_ID = 15.942 * inch - 2*0.028*inch;
    G4double HeCryo_OD = 15.942 * inch;
    
    thisName = "HeCryo";

    G4Tubs* HeCryo_solid = new G4Tubs( thisName+"_solid", HeCryo_ID/2, HeCryo_OD/2, 1*m, 0, CLHEP::twopi );
    G4LogicalVolume* HeCryo_lv = new G4LogicalVolume( HeCryo_solid, SS, thisName+"_lv");
    new G4PVPlacement( 0, G4ThreeVector(0,0,0), HeCryo_lv, thisName, motherLogic, false, 0, fCheckOverlaps);


    G4double LN2_ID = 18 * inch - 2*0.105*inch;
    G4double LN2_OD = 18 * inch;
    
    thisName = "LN2Cryo1";

    G4Tubs* LN2Cryo1_solid = new G4Tubs( thisName+"_solid", LN2_ID/2, LN2_OD/2, 1*m, 0, CLHEP::twopi );
    G4LogicalVolume* LN2Cryo1_lv = new G4LogicalVolume( LN2Cryo1_solid, SS, thisName+"_lv");
    new G4PVPlacement( 0, G4ThreeVector(0,0,0), LN2Cryo1_lv, thisName, motherLogic, false, 0, fCheckOverlaps);


    LN2_ID = 18 * inch;
    LN2_OD = 20 * inch - 2*0.105*inch;
    
    thisName = "LN2";

    G4Tubs* LN2_solid = new G4Tubs( thisName+"_solid", LN2_ID/2, LN2_OD/2, 1*m, 0, CLHEP::twopi );
    G4LogicalVolume* LN2_lv = new G4LogicalVolume( LN2_solid, LN2, thisName+"_lv");
    new G4PVPlacement( 0, G4ThreeVector(0,0,0), LN2_lv, thisName, motherLogic, false, 0, fCheckOverlaps);


    LN2_ID = 20 * inch - 2*0.105*inch;
    LN2_OD = 20 * inch + 2*0.105*inch;
    
    thisName = "LN2Cryo2";

    G4Tubs* LN2Cryo2_solid = new G4Tubs( thisName+"_solid", LN2_ID/2, LN2_OD/2, 1*m, 0, CLHEP::twopi );
    G4LogicalVolume* LN2Cryo2_lv = new G4LogicalVolume( LN2Cryo2_solid, SS, thisName+"_lv");
    new G4PVPlacement( 0, G4ThreeVector(0,0,0), LN2Cryo2_lv, thisName, motherLogic, false, 0, fCheckOverlaps);

}




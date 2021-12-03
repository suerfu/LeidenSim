
#include "GeoShielding.hh"
#include "GeometryManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4VSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"

GeoShielding::GeoShielding( ){

//    L_in = 5 * cm;
//    L_out = 10 * cm;

    fCheckOverlaps = GeometryManager::Get()->GetCheckOverlaps();

 //   fGeoShieldingMessenger = new GeoShieldingMessenger( this );
}


void GeoShielding::Construct(){
    
    G4LogicalVolume* worldLogic = GeometryManager::Get()->GetLogicalVolume("world");
    if( worldLogic==0 ){
        G4cerr << "Cannot find the logical volume of world." << G4endl;
        return;
    }

    G4String name = "Shield";
	
	G4double boxWidth     = GeometryManager::Get()->GetDimensions("shieldWidth");
	G4double boxHeight    = GeometryManager::Get()->GetDimensions("shieldHeight");
	G4double SSThickness  = GeometryManager::Get()->GetDimensions("SSThickness");
	G4double PbThickness  = GeometryManager::Get()->GetDimensions("PbThickness");
	G4double PEThickness  = GeometryManager::Get()->GetDimensions("PEThickness");
	G4double cavityRadius = GeometryManager::Get()->GetDimensions("cavityRadius");
	G4double cavityOffset = GeometryManager::Get()->GetDimensions("cavityOffset");
	G4double neckRadius   = GeometryManager::Get()->GetDimensions("neckRadius");

	//SS Layer
	//Basic solids
	G4Tubs* cavityTubs = new G4Tubs( name+"Cavity", 0, cavityRadius, 
											boxHeight/2, 
											0, 2*M_PI);
    G4Box* SSBox = new G4Box( name+"SSBox", boxWidth/2, 
											boxWidth/2, 
											boxHeight/2);
	//Subtractions of the cavity for the cryostate
	G4VSolid * SSBoxSub = new G4SubtractionSolid( name+"SSBoxSub", SSBox, cavityTubs, 
			  									0, G4ThreeVector(0, 0, cavityOffset));
	//Logic volumes
	G4LogicalVolume* SSLogic = new G4LogicalVolume( SSBoxSub, 
													GeometryManager::Get()->GetMaterial("SS"),
													name+"SSBoxLV");
	//Placements
	G4VPhysicalVolume* SSPhysical = new G4PVPlacement( 0, 
													G4ThreeVector(0,0,0), 
													SSLogic, 
													name+"SSBoxPhysical",
													worldLogic,
													false,
													0,
													fCheckOverlaps);
	if(neckRadius<cavityRadius){
		G4Tubs* neckSSTubs = new G4Tubs( name+"NeckSSTubs", neckRadius, cavityRadius, 
												SSThickness/2, 
												0, 2*M_PI);
		G4LogicalVolume* neckSSLogic = new G4LogicalVolume( neckSSTubs,
														GeometryManager::Get()->GetMaterial("SS"),
														name+"NeckSSLV");
		G4VPhysicalVolume* neckSSPhysical = new G4PVPlacement( 0, 
														G4ThreeVector(0,0,boxHeight - SSThickness/2), 
														neckSSLogic, 
														name+"neckSSPhysical",
														worldLogic,
														false,
														0,
														fCheckOverlaps);
	}
	boxWidth -= SSThickness*2;
	boxHeight -= SSThickness*2;


	//Pb layer
	//Basic solids
    G4Box* PbBox = new G4Box( name+"PbBox", boxWidth/2, 
											boxWidth/2, 
											boxHeight/2);
	//Subtractions of the cavity for the cryostate
	G4VSolid * PbBoxSub = new G4SubtractionSolid( name+"PbBoxSub", PbBox, cavityTubs, 
			  									0, G4ThreeVector(0, 0, cavityOffset));
	//Logic volumes
	G4LogicalVolume* PbLogic = new G4LogicalVolume( PbBoxSub, 
													GeometryManager::Get()->GetMaterial("Pb"),
													name+"PbBoxLV");
	//Placements
	G4VPhysicalVolume* PbPhysical = new G4PVPlacement( 0, 
													G4ThreeVector(0,0,0), 
													PbLogic, 
													name+"PbBoxPhysical",
													SSLogic, //Inside SS!
													false,
													0,
													fCheckOverlaps);
	//Neck extension
	if(neckRadius<cavityRadius){
		G4Tubs* neckPbTubs = new G4Tubs( name+"NeckPbTubs", neckRadius, cavityRadius, 
												PbThickness/2, 
												0, 2*M_PI);
		G4LogicalVolume* neckPbLogic = new G4LogicalVolume( neckPbTubs,
														GeometryManager::Get()->GetMaterial("Pb"),
														name+"NeckPbLV");
		G4VPhysicalVolume* neckPbPhysical = new G4PVPlacement( 0, 
														G4ThreeVector(0,0,boxHeight - PbThickness/2), 
														neckPbLogic, 
														name+"neckPbPhysical",
														worldLogic,
														false,
														0,
														fCheckOverlaps);
	}
	boxWidth -= PbThickness*2;
	boxHeight -= PbThickness*2;

	//PE layer
	//Basic solids
    G4Box* PEBox = new G4Box( name+"PEBox", boxWidth/2, 
											boxWidth/2, 
											boxHeight/2);
	//Subtractions of the cavity for the cryostate
	G4VSolid * PEBoxSub = new G4SubtractionSolid( name+"PEBoxSub", PEBox, cavityTubs, 
			  									0, G4ThreeVector(0, 0, cavityOffset));
	//Logic volumes
	G4LogicalVolume* PELogic = new G4LogicalVolume( PEBoxSub, 
													GeometryManager::Get()->GetMaterial("PE"),
													name+"PEBoxLV");
	//Placements
	G4VPhysicalVolume* PEPhysical = new G4PVPlacement( 0, 
													G4ThreeVector(0,0,0), 
													PELogic, 
													name+"PEBoxPhysical",
													PbLogic, //Inside Pb!
													false,
													0,
													fCheckOverlaps);
	//Neck extension
	if(neckRadius<cavityRadius){
		G4Tubs* neckPETubs = new G4Tubs( name+"NeckPETubs", neckRadius, cavityRadius, 
												PEThickness/2, 
												0, 2*M_PI);
		G4LogicalVolume* neckPELogic = new G4LogicalVolume( neckPETubs,
														GeometryManager::Get()->GetMaterial("PE"),
														name+"NeckPELV");
		G4VPhysicalVolume* neckPEPhysical = new G4PVPlacement( 0, 
														G4ThreeVector(0,0,boxHeight - PEThickness/2), 
														neckPELogic, 
														name+"neckPEPhysical",
														worldLogic,
														false,
														0,
														fCheckOverlaps);
	}
	boxWidth -= PEThickness*2;
	boxHeight -= PEThickness*2;

}

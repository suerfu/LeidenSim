
#include "GeoShielding.hh"
#include "GeoShieldingMessenger.hh"

#include "G4Box.hh"
#include "G4VSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"

GeoShielding::GeoShielding( ){

//    L_in = 5 * cm;
//    L_out = 10 * cm;

    fCheckOverlaps = GeoManager::Get()->GetCheckOverlaps();

 //   fGeoShieldingMessenger = new GeoShieldingMessenger( this );
}


void GeoShielding::Construct(){
    
    G4LogicalVolume* worldLogic = GeoManager::Get()->GetLogicalVolume("world");
    if( worldLogic==0 ){
        G4cerr << "Cannot find the logical volume of world." << G4endl;
        return;
    }

    G4String name = "Shield";
	
	G4double boxWidth     = GeoManager::Get()->GetDimensions("shieldWidth");
	G4double boxHeight    = GeoManager::Get()->GetDimensions("shieldHeight");
	G4double SSThickness  = GeoManager::Get()->GetDimensions("SSThickness");
	G4double PbThickness  = GeoManager::Get()->GetDimensions("PbThickness");
	G4double cavityRadius = GeoManager::Get()->GetDimensions("cavityRadius");
	G4double cavityOffset = GeoManager::Get()->GetDimensions("cavityOffset");
	G4double neckRadius   = GeoManager::Get()->GetDimensions("neckRadius");

	//SS Layer
	//Basic solids
	G4Tubs* cavityTubs = new G4Tubs( name+"Cavity", 0, cavityRadius, 
											boxHeight, 
											0, 2*MY_PI);
    G4Box* SSBox = new G4Box( name+"SSBox", boxWidth/2, 
											boxWidth/2, 
											boxHeight/2);
	//Subtractions of the cavity for the cryostate
	G4VSolid * SSBoxSub = new G4SubtractionSolid( name+"SSBoxSub", SSBox, cavityTubs, 
			  									0, G4ThreeVector(0, 0, cavityOffset));
	//Logic volumes
	G4LogicalVolume* SSLogic = new G4LogicalVolume( SSBoxSub, 
													GeoManager::Get()->GetMaterial("SS"),
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
    GeoManager::Get()->Add( name+"SS", SSLogic, SSPhysical);
	//Neck extension
	if(neckRadius<cavityRadius){
		G4Tubs* neckSSTubs = new G4Tubs( name+"NeckSSTubs", neckRadius, cavityRadius, 
												SSThickness/2, 
												0, 2*MY_PI);
		G4LogicalVolume* neckSSLogic = new G4LogicalVolume( neckSSTubs,
														GeoManager::Get()->GetMateriial("SS"),
														name+"NeckSSLV");
		G4VPhysicalVolume* neckSSPhysical = new G4PVPlacement( 0, 
														G4ThreeVector(0,0,boxHeight - SSThickness/2), 
														neckSSLogic, 
														name+"neckSSPhysical",
														worldLogic,
														false,
														0,
														fCheckOverlaps);
		GeoManager::Get()->Add( name+"NeckSS", neckSSLogic, neckSSPhysical);
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
													GeoManager::Get()->GetMaterial("Pb"),
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
    GeoManager::Get()->Add( name+"Pb", PbLogic, PbPhysical);
	//Neck extension
	if(neckRadius<cavityRadius){
		G4Tubs* neckPbTubs = new G4Tubs( name+"NeckPbTubs", neckRadius, cavityRadius, 
												PbThickness/2, 
												0, 2*MY_PI);
		G4LogicalVolume* neckPbLogic = new G4LogicalVolume( neckPbTubs,
														GeoManager::Get()->GetMateriial("Pb"),
														name+"NeckPbLV");
		G4VPhysicalVolume* neckPbPhysical = new G4PVPlacement( 0, 
														G4ThreeVector(0,0,boxHeight - PbThickness/2), 
														neckPbLogic, 
														name+"neckPbPhysical",
														worldLogic,
														false,
														0,
														fCheckOverlaps);
		GeoManager::Get()->Add( name+"NeckPb", neckPbLogic, neckPbPhysical);
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
													GeoManager::Get()->GetMaterial("PE"),
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
    GeoManager::Get()->Add( name+"PE", PELogic, PEPhysical);
	//Neck extension
	if(neckRadius<cavityRadius){
		G4Tubs* neckPETubs = new G4Tubs( name+"NeckPETubs", neckRadius, cavityRadius, 
												PEThickness/2, 
												0, 2*MY_PI);
		G4LogicalVolume* neckPELogic = new G4LogicalVolume( neckPETubs,
														GeoManager::Get()->GetMateriial("PE"),
														name+"NeckPELV");
		G4VPhysicalVolume* neckPEPhysical = new G4PVPlacement( 0, 
														G4ThreeVector(0,0,boxHeight - PEThickness/2), 
														neckPELogic, 
														name+"neckPEPhysical",
														worldLogic,
														false,
														0,
														fCheckOverlaps);
		GeoManager::Get()->Add( name+"NeckPE", neckPELogic, neckPEPhysical);
	}
	boxWidth -= PEThickness*2;
	boxHeight -= PEThickness*2;

}

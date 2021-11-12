
#include "GeoCryostat.hh"
#include "GeoCryostatMessenger.hh"

#include "G4Box.hh"
#include "G4VSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"

GeoCryostat::GeoCryostat( ){


    fCheckOverlaps = GeoManager::Get()->GetCheckOverlaps();
}


void GeoCryostat::Construct(){
    
	G4String motherName="world";
    motherLogic = gman->GetLogicalVolume(motherName);
    if( motherLogic==0 ){
        G4cerr << "Cannot find the mother volume "<<motherName<< G4endl;
        return;
    }

	ConstructTanks();
	ConstructColdParts();
}

void GeoCryostat::ConstructTanks(){
	//300K, 50K, 4K, still
	G4String names[4] = {"Cryostat300K", "Cryostat50K", "Cryostat4K", "CryostatStill"};
	for(int i=0; i<4; i++){
		G4int nP = GeoManager::Get()->GetCryostatCoordinateNP(i);
		G4double* r =  GeoManager::Get()->GetCryostatCoordinateR(i);
		G4double* z =  GeoManager::Get()->GetCryostatCoordinateZ(i);
		G4Polycone* cryostatSolid = new G4Polycone(names[i], 0, 2*MY_PI, nP, r, z);
		G4LogicalVolume* cryostatLogic = new G4LogicalVolume( cryostatSolid,
																GeoManager::Get()->GetMaterial("Titanium"),
																names[i]+"LV");
		G4VPhysicalVolume* cryostatPhysical = new G4VPhysicalVolume(0,
																G4ThreeVector(0,0,0),
																cryostatLogic,
																name[i]+"Physical",
																motherLogic,
																false,
																0,
																fCheckOverlaps);
		GeoManager::Get()->Add( name[i], cryostatLogic, cryostatPhysical);
	}
}

void GeoCryostat::ConstructColdParts(){
	G4String name = "Cryostat";
	//Still plate
	G4Tubs* stillPlateSolid = new G4Tubs( name+"StillPlateTubs", 
										0, 
										Geomanager::Get()->GetDimensions("stillPlateRadius"),
										0, 2*MY_PI);
	G4LogicalVolume * 
	
}


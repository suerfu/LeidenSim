
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

	//Drills
	G4int nDrillSizes = GeoManager::Get()->GetDrillChart()->size();
	G4Tubs** drills = new G4Tubs*[nDrillSizes];
	for(int ih=0; ih<nDrillSizes; ih++){
		drills[ih] = new G4Tubs( name+"Drill",
								0, 
								GeoManager::Get()->GetDrillChart()[ih],
								GeoManager::Get()->GetDimensions("maxPlateThickness")/2,//make sure to drill through all plates.
								0, 2*MY_PI);
	}
	//Plate with holes
	for(int ip=0; ip<GeoManager::Get()->GetNumberOfCryoPlates(); ip++){
		G4String plateName = GeoManager::Get()->GetCryoPlateName(ip);
		G4Tubs* plate = new G4Tubs( name+plateName, 
									0, 
									GeoManager::Get()->GetCryoPlateR(ip),
									GeoManager::Get()->GetCryoPlateH(ip)/2,
									0, 2*MY_PI);
		G4VSolid* plateWithHoles = plate;
		auto holes = GeoManager::Get()->GetCryoPlateHoles(ip);
		//drill holes
		for(auto ih = holes->begin(); ih != holes->end(); ++ih){
			plateWithHoles = new G4SubtractionSolid( name+plateName,
													plateWithHoles, 
													drills[it->first],
													0,
													it->second,
													);
		}
		G4LogicalVolume * plateLogic = new G4LogicalVolume( plateWithHoles,
													GeoManager::Get()->GetCryoPlateMaterial(ip),
													name+plateName+"LV");
		G4VPhysicalVolume* platePhysical = new G4PVPlacement(0,
													G4ThreeVector(0,0,GeoManager::Get()->GetCryoPlateZ(ip)),
													plateLogic,
													name+plateName+"Physical",
													motherLogic,
													false,
													0,
													fCheckOverlaps);
		GeoManager::Get()->Add( name+plateName,
								plateLogic, platePhysical);
	}
	//Support beams
	for(int ib=0; ib<GeoManager::Get()->GetNumberOfCryoBeams(); ip++){
		G4String beamName = GeoManager::Get()->GetCryoBeamName(ip);
		G4Tubs* beam = new G4Tubs( name+beamName,
									GeoManager::Get()->GetCryoBeamRI(ib),
									GeoManager::Get()->GetCryoBeamRO(ib),
									GeoManager::Get()->GetCryoBeamL(ib)/2,
									0, 2*MY_PI);
		G4LogicalVolume * beamLogic = new G4LogicalVolume( beam,
									GeoManager::Get()->GetCryoBeamMaterial(ib),
									name+beamName+"LV");
		G4VPhysicalVolume* beamPhysical = new G4PVPlacement(0,
									GeoManager::Get()->GetCryoBeamPos(ib),
									beamLogic,
									name+beamName+"Physical",
									motherLogic,
									false,
									0,
									fCheckOverlaps);
		GeoManager::Get()->Add( name+beamName,
								beamLogic, beamPhysical);
	}
	//Mixing chammber (inner most shield). Top and bottom are placed as "plates with holes"!
	G4Tubs* MXCWallTubs = new G4Tubs( name+"MXCWallTubs", 
									GeoManager::Get()->GetDimensions("MXCWallInnerRadius"),
									GeoManager::Get()->GetDimensions("MXCWallOuterRadius"),
									GeoManager::Get()->GetDimensions("MXCWallHeight")/2,
									0, 2*MY_PI);
	G4LogicalVolume * MXCWallLogic = new G4LogicalVolume( MXCWallTubs, 
									GeoManager::Get()->GetMaterial("Cu"),
									name+"MXCWallLV");
	G4VPhysicalVolume* MXCWallPhysical = new G4PVPlacement(0,
									G4ThreeVector(0, 0, GeoManager::Get()->GetDimensions("detectorZOffset")),
									MXCWallLogic,
									name + "MXCWallPhysical",
									motherLogic,
									false,
									0,
									fCheckOverlaps);
	
}


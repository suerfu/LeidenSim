
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

	//Holes
	G4int nHoleSizes = GeoManager::Get()->GetNumberOfHoleSizes();
	G4Tubs** holes = new G4Tubs*[nHoleSizes];
	for(int ih=0; ih<nHoleSizes; ih++){
		holes[ih] = new G4Tubs( name+"Hole",
								0, 
								GeoManager::Get()->GetHoleRadius(ih),
								GeoManager::Get()->GetDimensions("maxPlateThickness")/2,//make sure to drill through all plates.
								0, 2*MY_PI);
	}
	//Plate with holes
	for(int ip=0; ip<GeoManager::Get()->GetNumberOfCryoPlates(); ip++){
		G4Tubs* plate = new G4Tubs( name+GeoManager::Get()->GetCryoPlateName(ip), 
									0, 
									GeoManager::Get()->GetDimensions(GeoManager::Get()->GetCryoPlateName(ip)+"Radius"),
									GeoManager::Get()->GetDimensions(GeoManager::Get()->GetCryoPlateName(ip)+"Thickness")/2,
									0, 2*MY_PI);
		G4VSolid* plateWithHoles = plate;
		G4int nHoles = GeoManager::Get()->GetNumberOfCryoPlateHoles(ip);
		//drill holes
		for(int ih=0; ih<nHoles; i++){
			plateWithHoles = new G4SubtractionSolid( name+GeoManager::Get()->GetCryoPlateName(ip),
													plateWithHoles, 
													holes[GeoManager::Get()->GetCryoPlateHoleSize(ip,ih)],
													0,
													GeoManager::Get()->GetCryoPlateHolePos(ip, ih),
													);
		}
		G4LogicalVolume * plateLogic = new G4LogicalVolume( plateWithHoles,
													GeoManager::Get()->GetCryoPlateMaterial(ip),
													name+GeoManager::Get()->GetCryoPlateName(ip)+"LV");
		G4VPhysicalVolume* platePhysical = new G4PVPlacement(0,
													G4ThreeVector(0,0,GeoManager::Get()->GetCryoPlateZ(ip)),
													plateLogic,
													name+GeoManager::Get()->GetCryoPlateName(ip)+"Physical",
													motherLogic,
													false,
													0,
													fCheckOverlaps);
		GeoManager::Get()->Add( name+GeoManager::Get()->GetCryoPlateName(ip),
								plateLogic, platePhysical);
	}
	//Support beams
	for(int ib=0; ib<GeoManager::Get()->GetNumberOfCryoBeams(); ip++){
		G4Tubs* beam = new G4Tubs( name+GeoManager::Get()->GetCryoBeamName(ip),
									0,
									GeoManager::Get()->GetDimensions(GeoManager::Get()->GetCryoBeamName(ib)+"Radius"),
									GeoManager::Get()->GetDimensions(GeoManager::Get()->GetCryoBeamName(ib)+"Height")/2,
									0, 2*MY_PI);
		G4LogicalVolume * beamLogic = new G4LogicalVolume( beam,
									GeoManager::Get()->GetCryoBeamMaterial(ib),
									name+GeoManager::Get()->GetCryoBeamName(ib)+"LV");
		G4VPhysicalVolume* beamPhysical = new G4PVPlacement(0,
									GeoManager::Get()->GetCryoBeamPos(ib),
									beamLogic,
									name+GeoManager::Get()->GetCryoBeamName(ib)+"Physical",
									motherLogic,
									false,
									0,
									fCheckOverlaps);
		GeoManager::Get()->Add( name+GeoManager::Get()->GetCryoBeamName(ib),
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


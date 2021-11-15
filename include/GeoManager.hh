#ifndef GEOMANAGER_H
#define GEOMANAGER_H 1

#include <map>
#include <vector>
#include <utility>
#include <fstream>

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "CLHEP/Units/PhysicalConstants.h"
#include "G4NistManager.hh"
#include "SystemOfUnits.h"

#define M_PI 3.1415926535

using namespace CLHEP;

class GeoManager{
private:
	GeoManager();
	static GeoManager *me;
public:
	sstatic GeoManager* Get();
    ~GeoManager();

    void Add( G4String name, G4LogicalVolume* log, G4VPhysicalVolume* phys);

    G4LogicalVolume* GetLogicalVolume( G4String name );

    G4VPhysicalVolume* GetPhysicalVolume( G4String name );

    G4NistManager* GetMaterialManager();

    G4Material* GetMaterial(G4String name);

	G4double GetDimensions(G4String name);

	bool GetCheckOverlaps(){
		return fCheckOverlaps;
	}

	//Cryostat walls
	G4int     GetCryostatCoordinateNP(int ithLayer);
	G4double* GetCryostatCoordinateR (int ithLayer);
	G4double* GetCryostatCoordinateZ (int ithLayer);

	//Plates in cold stages
	std::vector<G4double>*  GetDrillChart(){return fDrillChart;};
	G4int  GetNumberOfCryoPlates(){return fCryoPlates.size();};
	G4String  GetCryoPlateName(int ip);
	G4Material* GetCryoPlateMaterial(int ip);
	G4double GetCryoPlateR(int ip);
	G4double GetCryoPlateH(int ip);
	G4double GetCryoPlateZ(int ip);
	std::vector< std::pair<G4int, G4ThreeVector> >*  GetCryoPlateHoles(int ip);
	//Beams in cold stages
	G4int GetNumberOfCryoBeams(){return fCryoBeams.size();};
	G4String  GetCryoBeamName(int ib);
	G4Material* GetCryoBeamMaterial(int ib);
	G4double GetCryoBeamR(int ib);
	G4double GetCryoBeamL(int ib);
	G4ThreeVector GetCryoBeamPos(int ib);



private:

    std::map< G4String, std::pair<G4LogicalVolume*, G4VPhysicalVolume*> > dictionary;

	//dimensions
	//General
	std::map< G4String, G4double > dimensions;
	//Polycone for crystat walls
	G4int    fCryostatCoordinateNP[4];
	G4double* fCryostatCoordinateR[4];
	G4double* fCryostatCoordinateZ[4];
	//Plates in cold stages
	struct CryoPlate{
		G4String name;
		G4double r;
		G4double thickness;
		G4double z;
		G4Material* material;
		std::vector< std::pair<G4int, G4ThreeVector> >* holes;
	}
	std::vector<G4double>* fDrillChart;
	std::vector<CryoPlate> fCryoPlates;
	//Beams in cold stages
	struct CryoBeam{
		G4Stringn name;
		G4double rI;//inner radius
		G4double rO;//outer radius
		G4double l;
		G4ThreeVector pos;
		G4Material* material;
	}
//FIXME copy constructor?? or vector of pointers??
	std::vector<CryoBeam> fCryoBeams;



	bool fCheckOverlaps;

    G4NistManager* material_man;

    /// User should define all materials to be used in this function.
    void DefineMaterials();

	//Load dimensions
	void LoadDimensions();
	//Specifically, the special volumes
	void LoadCryoWalls();
	void LoadCryoPlate();
	void LoadCryoBeam ();

};


#endif

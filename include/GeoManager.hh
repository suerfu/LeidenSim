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
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4RunManager.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"

using namespace CLHEP;

class GeoManager{
private:
	GeoManager();
	static GeoManager *me;
public:
	static GeoManager* Get();
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

	void SetGeometryType(int type){fGeometryType = type;};
	G4int GetGeometryType(){return fGeometryType;};
	void SetFilePath(G4String file, G4String pathAndName);
	// call it in GeometryConstruction::ConstructUserVolume(), 
	// which is after all dimension file names being set.
	// The dimensions will be loaded the next time GeoManager::Get() is called
	void GeometryTypeAndFilesSet(){fDimensionFilesSet = true;};
	// read the files
	void LoadDimensions();

	//Cryostat walls
	G4int     GetCryostatCoordinateNP(int ithLayer);
	G4double* GetCryostatCoordinateRI (int ithLayer);
	G4double* GetCryostatCoordinateRO (int ithLayer);
	G4double* GetCryostatCoordinateZ (int ithLayer);

	//Plates in cold stages
	std::vector<G4double>*  GetDrillChart(){return fDrillChart;};
	G4int  GetNumberOfCryoPlates(){return fCryoPlates.size();};
	G4String  GetCryoPlateName(int ip);
	G4String GetCryoPlateMaterial(int ip);
	G4double GetCryoPlateR(int ip);
	G4double GetCryoPlateH(int ip);
	G4double GetCryoPlateZ(int ip);
	std::vector< std::pair<G4int, G4ThreeVector> >*  GetCryoPlateHoles(int ip);
	//Beams in cold stages
	G4int GetNumberOfCryoBeams(){return fCryoBeams.size();};
	G4String  GetCryoBeamName(int ib);
	G4String GetCryoBeamMaterial(int ib);
	G4double GetCryoBeamRI(int ib);
	G4double GetCryoBeamRO(int ib);
	G4double GetCryoBeamL(int ib);
	G4ThreeVector GetCryoBeamPos(int ib);


	void SetVisAttributes();
	void GeometryHasBeenModified(){
		G4RunManager::GetRunManager()->GeometryHasBeenModified();
	};




private:

	//Genereal for all geometries
    std::map< G4String, std::pair<G4LogicalVolume*, G4VPhysicalVolume*> > dictionary;
	std::map< G4String, G4double > dimensions;
	std::map< G4String, G4String > dimensionFiles;
	std::map< G4String,  G4Color > materialColor;
	bool fCheckOverlaps;

	//Load dimensions
	bool fDimensionFilesSet;
	bool fDimensionsLoaded;
	//Tag to configur different geometries. Default 0.
	// 0 -> TESSERACT physics detector with shield, cryostat, and inner detector.
	// 1 -> ...
	// 2 -> ...
	// New GeoXXX classes should be defined for each entry. 
	// Modify LoadDimensions() accordingly to add interface to new classes. If dimensions are hard coded, this step is not necessary.
	// GeometryConstruction::ConstructUserVolume() calls the specific GeoXXX::Construct() according to this tag.
	int  fGeometryType; 

	//G4String fDimensionFile, fCryostatWallFile, fCryoPlateFile, fCryoBeamFile;
	//Specifically, the special volumes
	void LoadCryoWalls();
	void LoadCryoPlate();
	void LoadCryoBeam ();

	//dimensions
	//Polycone for crystat walls
	G4int    fCryostatCoordinateNP[4];
	G4double* fCryostatCoordinateRI[4];
	G4double* fCryostatCoordinateRO[4];
	G4double* fCryostatCoordinateZ[4];
	//Plates in cold stages
	struct CryoPlate{
		G4String name;
		G4double r;
		G4double thickness;
		G4double z;
		G4String material;
		std::vector< std::pair<G4int, G4ThreeVector> >* holes;
	};
	std::vector< G4double > * fDrillChart;
	std::vector<CryoPlate> fCryoPlates;
	//Beams in cold stages
	struct CryoBeam{
		G4String name;
		G4double rI;//inner radius
		G4double rO;//outer radius
		G4double l;
		G4ThreeVector pos;
		G4String material;
	};
//FIXME copy constructor?? or vector of pointers??
	std::vector<CryoBeam> fCryoBeams;


	/// Materials
    G4NistManager* material_man;

    /// User should define all materials to be used in this function.
    void DefineMaterials();

};


#endif

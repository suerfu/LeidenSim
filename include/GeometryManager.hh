/*
    Author:  Burkhant Suerfu
    Date:    November 18, 2021
    Contact: suerfu@berkeley.edu
*/

#ifndef GEOMETRYMANAGER_H
#define GEOMETRYMANAGER_H 1

#include <map>
#include <vector>
#include <utility>
#include <fstream>

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
//#include "CLHEP/Units/PhysicalConstants.h"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4ThreeVector.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"

using namespace CLHEP;

/// This class will be a singleton class.
/// It manages different attributes of geometry such as dimensions, color, material, etc.
/// All geometry-related classes should obtain information from this class.
class GeometryManager{

private:

	GeometryManager();

	static GeometryManager *me;

public:
	
    static GeometryManager* Get();

    ~GeometryManager();

    G4LogicalVolume* GetLogicalVolume( G4String name );

    G4VPhysicalVolume* GetPhysicalVolume( G4String name );

    G4NistManager* GetMaterialManager();

    G4Material* GetMaterial( G4String name );

    void GeometryHasBeenModified();
	
	//Search dimension values by name. Names noted on drawings
    G4double GetDimensions(G4String name);

	bool GetCheckOverlaps(){return fCheckOverlaps;}

	// Switch between structually different geometries.
	void SetGeometryType(int type){fGeometryType = type;};

	G4int GetGeometryType(){return fGeometryType;};

	void SetFilePath(G4String file, G4String pathAndName);

	// call it in GeometryConstruction::ConstructUserVolume(), 
	// The dimensions will be loaded the next time GeometryManager::LoadDimensions() is called
	void GeometryTypeAndFilesSet(){fDimensionFilesSet = true;};

	// read the files
	void LoadDimensions();

	void SetVisAttributes();

private:

    G4NistManager* material_man;

    /// User should define all materials to be used in this function.
    void DefineMaterials();

	//Genereal for all geometries
	std::map< G4String, G4double > dimensions;
	std::map< G4String, G4String > dimensionFiles;
	std::map< G4String,  G4Color > materialColor;
	bool fCheckOverlaps;

	//Load dimensions
	bool fDimensionFilesSet;
	bool fDimensionsLoaded;

	//Tag to configure different geometries. Default 0.
	// 0 -> TESSERACT physics detector with shield, cryostat, and inner detector.
	// 1 -> ...
	// 2 -> ...
	// New GeoXXX classes should be defined for each type. Each type can be a class or a combination of several classes.
	// GeometryConstruction::ConstructUserVolume() calls the specific GeoXXX::Construct() according to this tag.
	int  fGeometryType; 

	////////////////////////////////////////
	//         Variables in type 0        //
	////////////////////////////////////////
public:
	//Cryostat wall coordinates.
	//NP number of points
	//RI inner radius at the edge of each section
	//RO outer radius at the edge of each section
	//Z  Z of the edge of each section.
	//Origin of the coordinates is the center of the logical volume.
	G4int     GetCryostatCoordinateNP(int ithLayer);
	G4double* GetCryostatCoordinateRI (int ithLayer);
	G4double* GetCryostatCoordinateRO (int ithLayer);
	G4double* GetCryostatCoordinateZ (int ithLayer);

	//Plates in cold stages. Cylindrical structure with holes should be constructed here.
	std::vector<G4double>*  GetDrillChart(){return fDrillChart;};
	G4int  GetNumberOfCryoPlates(){return fCryoPlates.size();};
	G4String  GetCryoPlateName(int ip);
	G4String GetCryoPlateMaterial(int ip);
	G4double GetCryoPlateR(int ip);
	G4double GetCryoPlateH(int ip);
	G4double GetCryoPlateZ(int ip);// center Z position in mother volume (world)
	std::vector< std::pair<G4int, G4ThreeVector> >*  GetCryoPlateHoles(int ip);

	//Beams in cold stages. Other cylindrical structures without off-center holes.
	G4int GetNumberOfCryoBeams(){return fCryoBeams.size();};
	G4String  GetCryoBeamName(int ib);
	G4String GetCryoBeamMaterial(int ib);
	G4double GetCryoBeamRI(int ib);
	G4double GetCryoBeamRO(int ib);
	G4double GetCryoBeamL(int ib);// Full length
	G4ThreeVector GetCryoBeamPos(int ib);// center position in mother volume (world).

private:
	// Special volumes. Use structured containers to organize the dimensions.
	// Add to LoadDimensions() accordingly to interface with new GeoXXX classes. 
	// If the geometry does not have special structures, this function is not necessary. For example, GeoShield.
	void LoadCryoWalls();
	void LoadCryoPlate();
	void LoadCryoBeam ();

	//dimensions
	//Polycone for crystat walls. 0->3 outside to inside.
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
		//drill index, x-y position.
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
	std::vector<CryoBeam> fCryoBeams;


	////////////////////////////////////////
	//         Variables in type          //
	////////////////////////////////////////

};


#endif

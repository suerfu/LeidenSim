
/// \file GeometryConstruction.cc
/// \brief Implementation of the GeometryConstruction class

#include "GeometryConstruction.hh"

#include "G4SubtractionSolid.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "GeometryConstructionMessenger.hh"
#include "GeoManager.hh"
#include "GeoShielding.hh"
#include "GeoCryostat.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "Randomize.hh"

#include "G4IStore.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include <sstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


GeometryConstruction::GeometryConstruction() : G4VUserDetectorConstruction(),
{

    fCheckOverlaps = true;
    fDetectorMessenger = new GeometryConstructionMessenger(this);

    // Set default values for world.
    
    world_x = 10.*m;
    world_y = 10.*m;
    world_z = 10.*m;

  //  simple_cube = new SimpleCube( gm );
}



GeometryConstruction::~GeometryConstruction(){
    delete fDetectorMessenger;
}



G4VPhysicalVolume* GeometryConstruction::Construct(){

    G4VPhysicalVolume* world_pv = ConstructWorld();

    /* Other user-defined geometries goes here */
    ConstructUserVolumes();

    return world_pv;
}



G4VPhysicalVolume* GeometryConstruction::ConstructWorld(){

    G4String world_name = "world";
    G4Material* world_material = GeoManagerr::Get()->GetMaterial("G4_Galactic");//fGeometryManager->GetMaterial("G4_Galactic");

    G4Box* world_solid = new G4Box( world_name+"_sld", world_x/2.0, world_y/2.0, world_z/2.0);
    G4LogicalVolume* world_lv = new G4LogicalVolume( world_solid, world_material, world_name+"_lv");
    G4VPhysicalVolume* world_pv = new G4PVPlacement( 0, G4ThreeVector(0,0,0), world_lv, world_name, 0, false, 0,fCheckOverlaps);

    world_lv->SetVisAttributes( G4VisAttributes::Invisible );

	GeoManager::Get()->Add( world_name, world_lv, world_pv );

    return world_pv;
}


void GeometryConstruction::ConstructUserVolumes(){
	//Mark that we are ready to load dimensions!
	GeoManager::Get()->GeometryTypeAndFilesSet();
	G4int geoType = GeoManager::Get()->GetGeometryType();
	switch(geoType){
		case 0: //TESSERACT
			GeoShielding* TESSERACTShield = new GeoShielding();
			GeoCryostat* TESSERACTCryostat = new GeoCryostat();
			//GeoDetectorSPICE* detectorSPICE = new GeoDetectorSPICE());
			TESSERACTShield->Construct();
			TESSERACTCryostat->Construct();
			break;
		case 1: //other
			break;
		defalut:
			G4cerr<<"GeometryConstruction:: Geometry Type"<<geoType<<" not defined!"<<G4endl;
			break;
	}


 //   simple_cube->Construct();
}




/*
G4VIStore* GeometryConstruction::CreateImportanceStore(){
    
    //===============  Importance Sampling to speed up simulation ==============//
    
    G4IStore *istore = G4IStore::GetInstance();

    istore->AddImportanceGeometryCell( 1, *world_pv);
    for( unsigned int i=0; i<list.size(); i++ ){
        istore->AddImportanceGeometryCell( list[i].bias, *list[i].phy);
    }
    
    return istore;
}
*/



/*
    Author:  Burkhant Suerfu
    Date:    November 18, 2021
    Contact: suerfu@berkeley.edu
*/
/// \file GeometryConstruction.cc
/// \brief Implementation of the GeometryConstruction class

#include "GeometryConstruction.hh"

#include "G4SubtractionSolid.hh"

#include "GeometryConstructionMessenger.hh"
//<<<<<<< HEAD
#include "GeoManager.hh"
#include "GeoShielding.hh"
#include "GeoCryostat.hh"
//=======
#include "FarsideDetectorMessenger.hh"
#include "FarsideDetector.hh"
//>>>>>>> master

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

//#include "G4IStore.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include <sstream>



//<<<<<<< HEAD
GeometryConstruction::GeometryConstruction() : G4VUserDetectorConstruction()
{
//=======
//GeometryConstruction::GeometryConstruction( GeometryManager* gm) : G4VUserDetectorConstruction(),
    
//    fGeometryManager( gm ) {
//>>>>>>> master

    fCheckOverlaps = true;
    //fDetectorMessenger = new GeometryConstructionMessenger(this);
    fDetectorMessenger = new GeometryConstructionMessenger(this);

    // Set default values for world.
    
    world_x = 10.*m;
    world_y = 10.*m;
    world_z = 10.*m;

//<<<<<<< HEAD
  //  simple_cube = new SimpleCube( gm );
//=======
    simple_cube = new SimpleCube();// GeoManager::Get() );//gm );

    fFarsideMessenger = new FarsideDetectorMessenger();// GeoManager:Get() );//gm );
//>>>>>>> master
}



GeometryConstruction::~GeometryConstruction(){
    delete fDetectorMessenger;
    delete fFarsideMessenger;
}



G4VPhysicalVolume* GeometryConstruction::Construct(){

    G4cout << "Constructing geometry...\n";

    G4VPhysicalVolume* world_pv = ConstructWorld();

    /* Other user-defined geometries goes here */
    ConstructUserVolumes();

	//set visualization attributes according to material.
	GeoManager::Get()->SetVisAttributes();

    return world_pv;
}



G4VPhysicalVolume* GeometryConstruction::ConstructWorld(){

    G4String world_name = "world";
    G4Material* world_material = GeoManager::Get()->GetMaterial("G4_Galactic");//fGeometryManager->GetMaterial("G4_Galactic");

    G4Box* world_solid = new G4Box( world_name+"_sld", world_x/2.0, world_y/2.0, world_z/2.0);
    G4LogicalVolume* world_lv = new G4LogicalVolume( world_solid, world_material, world_name+"_lv");
    G4VPhysicalVolume* world_pv = new G4PVPlacement( 0, G4ThreeVector(0,0,0), world_lv, world_name, 0, false, 0,fCheckOverlaps);

    world_lv->SetVisAttributes( G4VisAttributes::Invisible );

//<<<<<<< HEAD
	GeoManager::Get()->Add( world_name, world_lv, world_pv );

//=======
//>>>>>>> master
    return world_pv;
}


void GeometryConstruction::ConstructUserVolumes(){
	G4cout<<"Construct user volumes..."<<G4endl;
	// Load dimensions later after GeoManager::SetFilePath() is calledby GeometryConstructionMessenger 
	// Mark that we are ready to load dimensions!
	GeoManager::Get()->GeometryTypeAndFilesSet();
	// Load dimension.
	GeoManager::Get()->LoadDimensions();
	G4int geoType = GeoManager::Get()->GetGeometryType();
	G4cout<<"geometry type is "<<geoType<<G4endl;
	if(geoType==0){ //TESSERACT
	        G4cout<<"TESSERACT"<<G4endl;
			GeoShielding* TESSERACTShield = new GeoShielding();
			GeoCryostat* TESSERACTCryostat = new GeoCryostat();
			//GeoDetectorSPICE* detectorSPICE = new GeoDetectorSPICE());
			TESSERACTShield->Construct();
			TESSERACTCryostat->Construct();
	}
	else if(geoType==1){ //other
		simple_cube->Construct();

		const int Nfs = 6;
		FarsideDetector* fs[Nfs];
		for( int i=0; i<Nfs; i++){
			std::stringstream name;
			name << "fs" << i;
			fs[i] = new FarsideDetector();// fGeometryManager );

			G4double distance = 50 * cm;
			G4double angle = i*CLHEP::twopi/Nfs;
			G4ThreeVector pos( distance*cos(angle), distance*sin(angle),0 );
			fs[i] -> PlaceDetector( name.str(), pos );
		}
	}
	else{ 
		G4cerr<<"GeometryConstruction:: Geometry Type"<<geoType<<" not defined!"<<G4endl;
	}
	G4cout<<"User volumes constructed!!!"<<G4endl;


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



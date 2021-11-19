
// $Id: GeometryConstructionMessenger.cc $
//
/// \file GeometryConstructionMessenger.cc
/// \brief Definition of the GeometryConstructionMessenger class

#include "GeometryConstructionMessenger.hh"
#include "GeometryConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAString.hh"
#include "GeoManager.hh"

GeometryConstructionMessenger::GeometryConstructionMessenger(GeometryConstruction* det) : G4UImessenger(){
	detector = det;
    directory = new G4UIdirectory( "/geometry/" );
    directory->SetGuidance( "Set geometry type and path to dimension files" );

	fGeoTypeCmd = new G4UIcmdWithAnInteger( "/geometry/type", this);
	fGeoTypeCmd->SetGuidance( "Set the geometry type. \n"
							  "0 -> TESSERACT detector with shielding, cryostat, and inner detector.\n"
							  "     Further details are set by the choice of geometry dimension files.\n"
							  "1 -> to be implemented");
	fGeoTypeCmd->SetParameterName("type", true);
	fGeoTypeCmd->SetDefaultValue(0);

	fDimensionFileCmd = new G4UIcmdWithAString( "/geometry/dimensionFile", this);
	fDimensionFileCmd->SetGuidance( "Dimension file path and name. Use this file to include dimension name, value pairs.\n"
				"Consider including groups of dimensions for special geometries in seperate files.");
	fCryostatWallFileCmd = new G4UIcmdWithAString( "/geometry/cryostatWallFile", this);
	fCryostatWallFileCmd->SetGuidance( "TESSERACT cryostat wall profile file path and name" );
	fCryoPlateFileCmd = new G4UIcmdWithAString( "/geometry/cryoPlateFile", this);
	fCryoPlateFileCmd->SetGuidance( "TESSERACT cryostat inner plates with holes, file path and name" );
	fCryoBeamFileCmd = new G4UIcmdWithAString( "/geometry/cryoBeamFile", this);
	fCryoBeamFileCmd->SetGuidance( "TESSERACT cryostat inner beams, file path and name" );
	
/*
    posCmd = new G4UIcmdWith3VectorAndUnit( "/placement/pos", this);
    posCmd->SetGuidance( "Set the position of the farside detector to be placed.\nUnit is in cm by default.");
    posCmd->SetParameterName( "x", "y", "z", false );
    posCmd->AvailableForStates( G4State_Idle );
    posCmd->SetDefaultValue( G4ThreeVector(0,100*CLHEP::cm,0) );
    posCmd->SetDefaultUnit( "cm" );

    angCmd_x = new G4UIcmdWithADoubleAndUnit( "/placement/rotateX", this );
    angCmd_y = new G4UIcmdWithADoubleAndUnit( "/placement/rotateY", this );
    angCmd_z = new G4UIcmdWithADoubleAndUnit( "/placement/rotateZ", this );

    angCmd_x->SetGuidance( "Set the angle of rotation about X-axis of the farside detector to be placed.\nUnit is in degree by default." );
    angCmd_y->SetGuidance( "Set the angle of rotation about Y-axis of the farside detector to be placed.\nUnit is in degree by default." );
    angCmd_z->SetGuidance( "Set the angle of rotation about Z-axis of the farside detector to be placed.\nUnit is in degree by default." );

    angCmd_x->AvailableForStates( G4State_Idle );
    angCmd_y->AvailableForStates( G4State_Idle );
    angCmd_z->AvailableForStates( G4State_Idle );

    angCmd_x->SetParameterName( "Xangle", false );
    angCmd_y->SetParameterName( "Yangle", false );
    angCmd_z->SetParameterName( "Zangle", false );

    angCmd_x->SetDefaultValue( 0. );
    angCmd_y->SetDefaultValue( 0. );
    angCmd_z->SetDefaultValue( 0. );

    angCmd_x->SetDefaultUnit( "deg" );
    angCmd_y->SetDefaultUnit( "deg" );
    angCmd_z->SetDefaultUnit( "deg" );

    place_detector = new G4UIcommand( "/placement/placeDetector", this );
    place_detector->SetGuidance( "Place a far-side detector based on the previously specified positions and angles." );
    place_detector->AvailableForStates( G4State_Idle );
*/
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GeometryConstructionMessenger::~GeometryConstructionMessenger(){
//    delete FSDistanceCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GeometryConstructionMessenger::SetNewValue( G4UIcommand* command, G4String newValue) {
	G4cout<<"GeometryConstructionMessenger::SetNewValue "<<newValue<<G4endl;
	if( command == fGeoTypeCmd){
		GeoManager::Get()->SetGeometryType(fGeoTypeCmd->ConvertToInt(newValue));
		G4cout<<"Detector configuration is " <<GeoManager::Get()->GetGeometryType()<<G4endl;
	}
	else if( command==fDimensionFileCmd ){
		GeoManager::Get()->SetFilePath("dimensionFile", newValue);
	}
	else if( command==fCryostatWallFileCmd ){
		GeoManager::Get()->SetFilePath("cryostatWallFile", newValue);
	}
	else if( command==fCryoPlateFileCmd ){
		GeoManager::Get()->SetFilePath("cryoPlateFile", newValue);
	}
	else if( command==fCryoBeamFileCmd ){
		GeoManager::Get()->SetFilePath("cryoBeamFile", newValue);
	}
/*
    if( command==posCmd ){
        detector->SetFarSidePosition( posCmd->GetNew3VectorValue( newValue ) );
    }
    else if( command==angCmd_x ){
        detector->FarSideRotateX( angCmd_x->GetNewDoubleValue( newValue) );
    }
    else if( command==angCmd_y ){
        detector->FarSideRotateY( angCmd_y->GetNewDoubleValue( newValue) );
    }
    else if( command==angCmd_z ){
        detector->FarSideRotateZ( angCmd_z->GetNewDoubleValue( newValue) );
    }
    else if( command==place_detector ){
        detector->PlaceFarSideDetector();
    }
    return;
*/
}

/*
    Author:  Burkhant Suerfu
    Date:    November 18, 2021
    Contact: suerfu@berkeley.edu
*/
#include "LeidenMessenger.hh"
#include "Leiden.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAString.hh"

LeidenMessenger::LeidenMessenger( Leiden* placement) : G4UImessenger(), detector( placement ){

    name = "cell";
    dirname = G4String("/")+name+"/";

    directory = new G4UIdirectory( dirname.c_str() );
    directory->SetGuidance( "Commands to control the cesium cell geometry." );

    cmdActiveLength = new G4UIcmdWithADoubleAndUnit( (dirname+"activeLen").c_str(), this );
    cmdCellDiameter = new G4UIcmdWithADoubleAndUnit( (dirname+"cellLen").c_str(), this );
    cmdWallThickness = new G4UIcmdWithADoubleAndUnit( (dirname+"wallThickness").c_str(), this );
/*
    angCmd_x->SetGuidance( "Set the angle of rotation about X-axis.\nUnit is degree by default." );
    angCmd_y->SetGuidance( "Set the angle of rotation about Y-axis.\nUnit is degree by default." );
    angCmd_z->SetGuidance( "Set the angle of rotation about Z-axis.\nUnit is degree by default." );

    angCmd_x->SetParameterName( "Xangle", false );
    angCmd_y->SetParameterName( "Yangle", false );
    angCmd_z->SetParameterName( "Zangle", false );
*/
    cmdActiveLength->SetDefaultValue( 1. );
    cmdCellDiameter->SetDefaultValue( 2. );
    cmdWallThickness->SetDefaultValue( 0.1 );

    cmdActiveLength->SetDefaultUnit( "cm" );
    cmdCellDiameter->SetDefaultUnit( "cm" );
    cmdWallThickness->SetDefaultUnit( "cm" );

/*
    cmdActiveLength->AvailableForStates( G4State_Init );
    cmdCellDiameter->AvailableForStates( G4State_Init );
    cmdWallThickness->AvailableForStates( G4State_Init );
    materialCmd = new G4UIcmdWithAString( (dirname+"material").c_str(), this);
    materialCmd->SetGuidance( "Set the target material" );
    materialCmd->SetParameterName( "name", false);

    G4String matList;
    const G4MaterialTable* matTbl = G4Material::GetMaterialTable();
    for(size_t i=0;i<G4Material::GetNumberOfMaterials();i++){
        matList += (*matTbl)[i]->GetName();
        matList += " ";
    }

    materialCmd->SetCandidates(matList);
    materialCmd->AvailableForStates(G4State_Idle);
*/
}



LeidenMessenger::~LeidenMessenger(){}


void LeidenMessenger::SetNewValue( G4UIcommand* command, G4String newValue) {

    if( command==cmdActiveLength){
        detector->SetActiveLength( cmdActiveLength->GetNewDoubleValue( newValue ) );
    }
    else if( command==cmdCellDiameter ){
        detector->SetCellDiameter( cmdCellDiameter->GetNewDoubleValue( newValue) );
    }
    else if( command==cmdWallThickness ){
        detector->SetWallThickness( cmdWallThickness->GetNewDoubleValue( newValue) );
    }
    return;
}

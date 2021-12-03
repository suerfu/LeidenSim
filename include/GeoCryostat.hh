#ifndef GEOCRYOSTAT_H
#define GEOCRYOSTAT_H 1

#include "GeoManager.hh"


#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"

//class GeoCryostatMessenger;

class GeoCryostat{

public:

    GeoCryostat();
    
    ~GeoCryostat();

   // void SetOuterLength( G4double l){ L_out = l;}
   // 
   // void SetInnerLength( G4double l){ L_in = l;}

   // void SetPosition( G4ThreeVector s){ position = s;}

   // void RotateX( G4double a){
   //     rot->rotateX(a);
   // }
   // void RotateY( G4double a){
   //     rot->rotateY(a);
   // }
   // void RotateZ( G4double a){
   //     rot->rotateX(a);
   // }

    void Construct();

private:

   // GeoCryostatMessenger* fGeoCryostatMessenger;

   // G4double L_in, L_out;
   // G4ThreeVector position;
   // G4RotationMatrix* rot;

    G4bool fCheckOverlaps;
	G4LogicalVolume * motherLogic;

	// Just the cryostat walls
	void ConstructTanks();
	// Everything inside
	void ConstructColdParts();

    //GeometryManager* gman;
};


#endif

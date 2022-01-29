/*
    Author:  Burkhant Suerfu
    Date:    November 18, 2021
    Contact: suerfu@berkeley.edu
*/

#ifndef LEIDEN_H
#define LEIDEN_H 1

#include "GeometryManager.hh"

#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"

class LeidenMessenger;

class Leiden{

public:

    Leiden();
    
    ~Leiden();
/*
    void SetMaterial( G4String material );

    void SetPosition( G4ThreeVector s);

    void RotateX( G4double a);
    
    void RotateY( G4double a);
    
    void RotateZ( G4double a);
*/
    void SetActiveLength( G4double a ){ activeLength = a; }
    
    void SetCellDiameter( G4double a ){ cellDiameter = a; }

    void SetCellHeight( G4double a ){ cellHeight = a; }
    
    void SetWallThickness( G4double a ){ wallThickness = a; }

    void SetLHe( G4int i ){ liquidHe = i; }

    void SetLN2( G4int i ){ liquidN2 = i; }

    void Construct();

private:

    G4String thisName;

    LeidenMessenger* fLeidenMessenger;

    G4double activeLength;

    G4double cellDiameter;
    
    G4double cellHeight;

    G4double wallThickness;

    G4int liquidHe;

    G4int liquidN2;

    G4bool fCheckOverlaps;

};


#endif

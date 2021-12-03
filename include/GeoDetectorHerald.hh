#ifndef GEODETECTORHERALD_H
#define GEODETECTORHERALD_H 1

#include "GeometryManager.hh"


#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"


class GeoDetectorHerald{

public:

    GeoDetectorHerald( );
    
    ~GeoDetectorHerald();


    void Construct();

private:
	G4bool fCheckOverlaps;

};


#endif

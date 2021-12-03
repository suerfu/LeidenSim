#ifndef GEODETECTORSPICE_H
#define GEODETECTORSPICE_H 1

#include "GeoManager.hh"


class GeoDetectorSpice{

public:

    GeoDetectorSpice( );
    
    ~GeoDetectorSpice();

    void Construct();

private:


    G4bool fCheckOverlaps;

};


#endif

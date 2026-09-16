///////////////////////////////////////////////////
//              PreLaunch                       //
//////////////////////////////////////////////////
//
// Eliot Walton
// 14 September 2026
// V1 Rocket
// Version 0
// 
// AI Usage: MCopilot365
// - wrote the initial script.          

#ifndef RocketDetectorConstruction_h
#define RocketDetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;

class RocketDetectorConstruction
    : public G4VUserDetectorConstruction
{
public:
    RocketDetectorConstruction();
    virtual ~RocketDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
};

#endif

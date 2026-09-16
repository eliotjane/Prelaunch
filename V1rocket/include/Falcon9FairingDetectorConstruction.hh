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


#ifndef Falcon9FairingDetectorConstruction_h
#define Falcon9FairingDetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;

class Falcon9FairingDetectorConstruction :
    public G4VUserDetectorConstruction
{
public:
    Falcon9FairingDetectorConstruction();
    virtual ~Falcon9FairingDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
};

#endif

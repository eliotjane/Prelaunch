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


#ifndef Falcon9FairingDetectorConstructionWithWeapon_h
#define Falcon9FairingDetectorConstructionWithWeapon_h

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;

class Falcon9FairingDetectorConstructionWithWeapon
    : public G4VUserDetectorConstruction
{
public:
    Falcon9FairingDetectorConstructionWithWeapon();
    virtual ~Falcon9FairingDetectorConstructionWithWeapon();

    virtual G4VPhysicalVolume* Construct();
};


#endif

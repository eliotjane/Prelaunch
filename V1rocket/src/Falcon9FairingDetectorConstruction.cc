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

#include "Falcon9FairingDetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

Falcon9FairingDetectorConstruction::
Falcon9FairingDetectorConstruction()
{
}

Falcon9FairingDetectorConstruction::
~Falcon9FairingDetectorConstruction()
{
}

G4VPhysicalVolume*
Falcon9FairingDetectorConstruction::Construct()
{
    auto nist = G4NistManager::Instance();


    //
    // Rotation
    //
    
    auto fairingRotation = new G4RotationMatrix();
	fairingRotation->rotateY(90.*deg);

    //
    // Materials
    //

    auto air =
        nist->FindOrBuildMaterial("G4_AIR");

    auto aluminum =
        nist->FindOrBuildMaterial("G4_Al");

    //
    // World
    //

    auto worldSolid =
        new G4Box(
            "World",
            10*m,
            10*m,
            10*m);

    auto worldLV =
        new G4LogicalVolume(
            worldSolid,
            air,
            "World");

    auto worldPV =
        new G4PVPlacement(
            nullptr,
            G4ThreeVector(),
            worldLV,
            "World",
            nullptr,
            false,
            0,
            true);

    //
    // Fairing Dimensions
    //

    double fairingRadius = 2.6*m;
    double barrelLength  = 8.0*m;
    double noseLength    = 5.0*m;

    //
    // Cylindrical Barrel
    //

    auto barrelSolid =
        new G4Tubs(
            "Barrel",
            2.55*m,      // inner radius
            2.60*m,      // outer radius
            barrelLength/2,
            0,
            360*deg);

    auto barrelLV =
        new G4LogicalVolume(
            barrelSolid,
            aluminum,
            "Barrel");

    new G4PVPlacement(
	nullptr,
        G4ThreeVector(
            0,
            0,
            0),
        barrelLV,
        "Barrel",
        worldLV,
        false,
        0,
        true);

    //
    // Nose Cone
    //

    auto noseSolid =
        new G4Cons(
            "Nose",
            0,
            fairingRadius,
            0,
            0,
            noseLength/2,
            0,
            360*deg);

    auto noseLV =
        new G4LogicalVolume(
            noseSolid,
            aluminum,
            "Nose");

    new G4PVPlacement(
        nullptr,
        G4ThreeVector(
            0,
            0,
            barrelLength/2 + noseLength/2),
        noseLV,
        "Nose",
        worldLV,
        false,
        0,
        true);

    //
    // Payload Volume
    //

    auto payloadSolid =
        new G4Tubs(
            "Payload",
            0,
            2.30*m,
            3.0*m,
            0,
            360*deg);

    auto payloadLV =
        new G4LogicalVolume(
            payloadSolid,
            air,
            "Payload");

    new G4PVPlacement(
        nullptr,
        G4ThreeVector(
            0,
            0,
            0),
        payloadLV,
        "Payload",
        worldLV,
        false,
        0,
        true);

    //
    // Visual Attributes
    //

    auto worldVis =
        new G4VisAttributes(
            G4Colour(1, 1, 1, 0));
    //::White());

    worldVis->SetForceWireframe(true);
    worldLV->SetVisAttributes(worldVis);

    auto barrelVis =
        new G4VisAttributes(
            G4Colour(0.8,0.8,0.8,0.2));

    barrelVis->SetForceSolid(true);
    //barrelVis->SetForceWireframe(true);
    barrelLV->SetVisAttributes(barrelVis);

    auto noseVis =
        new G4VisAttributes(
            G4Colour(0.3,0.3,1.0));

    noseVis->SetForceSolid(true);
    noseLV->SetVisAttributes(noseVis);

    auto payloadVis =
        new G4VisAttributes(
            G4Colour(0.0,1.0,0.0,0.2));

    payloadVis->SetForceSolid(true);
    payloadLV->SetVisAttributes(payloadVis);

    return worldPV;
}

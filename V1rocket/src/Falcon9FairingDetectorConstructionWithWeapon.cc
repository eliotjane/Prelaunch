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

#include "Falcon9FairingDetectorConstructionWithWeapon.hh"

#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

Falcon9FairingDetectorConstructionWithWeapon::
Falcon9FairingDetectorConstructionWithWeapon()
{
}

Falcon9FairingDetectorConstructionWithWeapon::
~Falcon9FairingDetectorConstructionWithWeapon()
{
}

G4VPhysicalVolume*
Falcon9FairingDetectorConstructionWithWeapon::Construct()
{
    auto nist = G4NistManager::Instance();

    //
    // Materials
    //

    auto air =
        nist->FindOrBuildMaterial("G4_AIR");

    auto aluminum =
        nist->FindOrBuildMaterial("G4_Al");

    auto polyethylene =
        nist->FindOrBuildMaterial("G4_POLYETHYLENE");

    auto plutonium =
        nist->FindOrBuildMaterial("G4_Pu");

    auto boron =
        nist->FindOrBuildElement("B");

    //
    // Borated Polyethylene
    //

    auto boratedPE =
        new G4Material(
            "BoratedPE",
            1.0*g/cm3,
            2);

    boratedPE->AddMaterial(
        polyethylene,
        95.*perCent);

    boratedPE->AddElement(
        boron,
        5.*perCent);

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
    // Falcon 9 Fairing
    //

    double fairingRadius = 2.6*m;
    double barrelLength  = 8.0*m;
    double noseLength    = 5.0*m;

    //
    // Fairing barrel shell
    //

    auto barrelSolid =
        new G4Tubs(
            "Barrel",
            2.55*m,
            2.60*m,
            barrelLength/2.0,
            0,
            360*deg);

    auto barrelLV =
        new G4LogicalVolume(
            barrelSolid,
            aluminum,
            "Barrel");

    //
    // Fairing nose
    //

    auto noseSolid =
        new G4Cons(
            "Nose",
            0,
            0,
            0,
	    fairingRadius,
            noseLength/2.0,
            0,
            360*deg);

    auto noseLV =
        new G4LogicalVolume(
            noseSolid,
            aluminum,
            "Nose");

    //
    // Rotate fairing upright
    //

    auto rot =
        new G4RotationMatrix();

    rot->rotateY(180.*deg);

    //
    // Barrel placement
    //

    new G4PVPlacement(
        nullptr,
        G4ThreeVector(0,0,0),
        barrelLV,
        "Barrel",
        worldLV,
        false,
        0,
        true);

    //
    // Nose placement
    //
    //

   new G4PVPlacement(
        rot,
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


   /*  new G4PVPlacement(
        nullptr,
        G4ThreeVector(
            6.5*m,
            0,
            0),
        noseLV,
        "Nose",
        worldLV,
        false,
        0,
        true);
	*/
    //
    // Shield cube
    //

    auto cubeSolid =
        new G4Box(
            "ShieldCube",
            75*cm,
            75*cm,
            75*cm);

    auto cubeLV =
        new G4LogicalVolume(
            cubeSolid,
            boratedPE,
            "ShieldCube");

    //
    // Hydrocarbon sphere
    //

    auto hydroSolid =
        new G4Sphere(
            "HydroSphere",
            0,
            50*cm,
            0,
            360*deg,
            0,
            180*deg);

    auto hydroLV =
        new G4LogicalVolume(
            hydroSolid,
            polyethylene,
            "HydroSphere");

    //
    // Plutonium sphere
    //

    auto puSolid =
        new G4Sphere(
            "PuSphere",
            0,
            10*cm,
            0,
            360*deg,
            0,
            180*deg);

    auto puLV =
        new G4LogicalVolume(
            puSolid,
            plutonium,
            "PuSphere");

    //
    // Place cube in fairing
    //

    new G4PVPlacement(
        nullptr,
        G4ThreeVector(
            0,
            0,
            0),
        cubeLV,
        "ShieldCube",
        worldLV,
        false,
        0,
        true);

    //
    // Sphere in cube
    //

    new G4PVPlacement(
        nullptr,
        G4ThreeVector(),
        hydroLV,
        "HydroSphere",
        cubeLV,
        false,
        0,
        true);

    //
    // Pu in sphere
    //

    new G4PVPlacement(
        nullptr,
        G4ThreeVector(),
        puLV,
        "PuSphere",
        hydroLV,
        false,
        0,
        true);

    //
    // Visualization
    //

    auto worldVis =
        new G4VisAttributes(
	G4Colour(1,1,1,0));
        //G4Colour::White());

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
            G4Colour(0.2,0.2,1.0,0.80));

    noseVis->SetForceSolid(true);
    //noseVis->SetForceWireframe(true);
    noseLV->SetVisAttributes(noseVis);
    
    auto cubeVis =
        new G4VisAttributes(
            G4Colour(1.0,1.0,0)); //,0.40));

    //cubeVis->SetForceSolid(true);
    cubeVis->SetForceWireframe(true);
    cubeLV->SetVisAttributes(cubeVis);

    auto hydroVis =
        new G4VisAttributes(
            G4Colour(0.0,1.0,0.0,0.2));

    hydroVis->SetForceSolid(true);
    hydroLV->SetVisAttributes(hydroVis);

    auto puVis =
        new G4VisAttributes(
            G4Colour(1.0,0.0,0.0));

    puVis->SetForceSolid(true);
    puLV->SetVisAttributes(puVis);

    return worldPV;
}

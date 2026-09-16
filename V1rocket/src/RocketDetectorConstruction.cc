///////////////////////////////////////////////////
//		PreLaunch			//
//////////////////////////////////////////////////
//
// Eliot Walton
// 14 September 2026
// V1 Rocket
// Version 0
// 
// AI Usage: MCopilot365
// - wrote the initial script.		


// Changes
// - added wireframe world visualisation


#include "G4VUserDetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "RocketDetectorConstruction.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

RocketDetectorConstruction::RocketDetectorConstruction()
{
}

RocketDetectorConstruction::~RocketDetectorConstruction()
{
}

G4VPhysicalVolume* 
RocketDetectorConstruction::Construct()
{
        auto nist = G4NistManager::Instance();

        //
        // Materials
        //

        auto air =
            nist->FindOrBuildMaterial("G4_AIR");

        auto aluminum =
            nist->FindOrBuildMaterial("G4_Al");

        auto steel =
            nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");

        auto water =
            nist->FindOrBuildMaterial("G4_WATER");

        //
        // World
        //

        auto worldSolid =
            new G4Box(
                "World",
                3.0*m,
                3.0*m,
                3.0*m);

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
	// World Visualisation
	//

	auto worldVis =
    		new G4VisAttributes(G4Colour::White());

		worldVis->SetForceWireframe(true);

		worldLV->SetVisAttributes(worldVis);

        //
        // Rocket body
        //

        double rocketRadius = 0.250*m;
        double bodyLength   = 4.0*m;

        auto bodySolid =
            new G4Tubs(
                "Body",
                0,
                rocketRadius,
                bodyLength/2.0,
                0,
                360*deg);

        auto bodyLV =
            new G4LogicalVolume(
                bodySolid,
                aluminum,
                "Body");

        new G4PVPlacement(
            nullptr,
            G4ThreeVector(
                0,
                0,
                0),
            bodyLV,
            "Body",
            worldLV,
            false,
            0,
            true);

        //
        // Nose cone
        //

        double noseLength = 1.0*m;

        auto noseSolid =
            new G4Cons(
                "Nose",
                0,
                rocketRadius,
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
                bodyLength/2 + noseLength/2),
            noseLV,
            "Nose",
            worldLV,
            false,
            0,
            true);

        //
        // Propellant tank
        //

        auto tankSolid =
            new G4Tubs(
                "Tank",
                0,
                0.22*m,
                1.2*m,
                0,
                360*deg);

        auto tankLV =
            new G4LogicalVolume(
                tankSolid,
                water,
                "Tank");

        new G4PVPlacement(
            nullptr,
            G4ThreeVector(
                0,
                0,
                0.5*m),
            tankLV,
            "Tank",
            bodyLV,
            false,
            0,
            true);

        //
        // Engine section
        //

        auto engineSolid =
            new G4Tubs(
                "Engine",
                0,
                0.20*m,
                0.40*m,
                0,
                360*deg);

        auto engineLV =
            new G4LogicalVolume(
                engineSolid,
                steel,
                "Engine");

        new G4PVPlacement(
            nullptr,
            G4ThreeVector(
                0,
                0,
                -1.4*m),
            engineLV,
            "Engine",
            bodyLV,
            false,
            0,
            true);

        //
        // Fins
        //

        auto finSolid =
            new G4Box(
                "Fin",
                0.25*m,
                0.01*m,
                0.50*m);

        auto finLV =
            new G4LogicalVolume(
                finSolid,
                aluminum,
                "Fin");

        double finZ = -1.0*m;

        new G4PVPlacement(
            nullptr,
            G4ThreeVector(
                rocketRadius + 0.01*m,
                0,
                finZ),
            finLV,
            "Fin1",
            worldLV,
            false,
            0,
            true);

        new G4PVPlacement(
            nullptr,
            G4ThreeVector(
                -(rocketRadius + 0.01*m),
                0,
                finZ),
            finLV,
            "Fin2",
            worldLV,
            false,
            1,
            true);

        auto finSolidY =
            new G4Box(
                "FinY",
                0.01*m,
                0.25*m,
                0.50*m);

        auto finLVY =
            new G4LogicalVolume(
                finSolidY,
                aluminum,
                "FinY");

        new G4PVPlacement(
            nullptr,
            G4ThreeVector(
                0,
                rocketRadius + 0.01*m,
                finZ),
            finLVY,
            "Fin3",
            worldLV,
            false,
            2,
            true);

        new G4PVPlacement(
            nullptr,
            G4ThreeVector(
                0,
                -(rocketRadius + 0.01*m),
                finZ),
            finLVY,
            "Fin4",
            worldLV,
            false,
            3,
            true);

        return worldPV;
}

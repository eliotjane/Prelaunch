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

// Changes:
// - added ParticleGeneratorAction
// - disabled multi-threading for visualisation
// - added falcon9fairing

#include "G4RunManagerFactory.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "FTFP_BERT.hh"

//For single threading
#include "G4RunManager.hh"

#include "RocketDetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "Falcon9FairingDetectorConstruction.hh"
#include "Falcon9FairingDetectorConstructionWithWeapon.hh"

int main(int argc, char** argv)
{
    auto runManager = new G4RunManager();

    std::string geometry = "rocket";

if (argc > 1)
{
    geometry = argv[1];
}

if (geometry == "fairing")
{
    G4cout << "Using geometry: Falcon 9 Fairing" << G4endl;

    runManager->SetUserInitialization(
        new Falcon9FairingDetectorConstruction());
}
else if (geometry == "fairingWithWeapon")
{
    G4cout << "Using geometry: Falcon 9 Fairing With Weapon" << G4endl;

    runManager->SetUserInitialization(
        new Falcon9FairingDetectorConstructionWithWeapon());
}
else
{
    G4cout << "Using geometry: Rocket" << G4endl;

    runManager->SetUserInitialization(
        new RocketDetectorConstruction());
}
    
    runManager->SetUserInitialization(
        new FTFP_BERT());

    runManager->SetUserAction(
    	new PrimaryGeneratorAction());

    runManager->Initialize();

    auto visManager = new G4VisExecutive();
    visManager->Initialize();

    auto ui = new G4UIExecutive(argc, argv);
    ui->SessionStart();

    delete ui;
    delete visManager;
    delete runManager;

    return 0;
}

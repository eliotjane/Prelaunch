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

#include "PrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4MuonMinus.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    fParticleGun = new G4ParticleGun(1);

    fParticleGun->SetParticleDefinition(
        G4MuonMinus::Definition());

    fParticleGun->SetParticleEnergy(
        4.0*GeV);

    fParticleGun->SetParticlePosition(
        G4ThreeVector(0,0,8*m));

    fParticleGun->SetParticleMomentumDirection(
        G4ThreeVector(0,0,-1));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(
    G4Event* event)
{
    fParticleGun->GeneratePrimaryVertex(event);
}





#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
#include "G4Gamma.hh"
#include "G4MuonMinus.hh"
#include "G4Proton.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4RandomTools.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction()
{
    fPrimary = new G4ParticleGun();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fPrimary;
}
void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
    fPrimary->SetParticleDefinition(G4MuonMinus::Definition());
    fPrimary->SetParticleEnergy(1.*GeV);
    fPrimary->SetParticlePosition(G4ThreeVector(0.,0.,-60.*cm));
    fPrimary->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fPrimary->GeneratePrimaryVertex(anEvent);
}

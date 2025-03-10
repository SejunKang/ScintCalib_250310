#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Geantino.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4RandomTools.hh"
#include "G4IonTable.hh"
#include "beam.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction()
{
    fPrimary = new G4ParticleGun();
    
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fPrimary;
}

const G4int dist = 140;

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
    
    G4int n = 75 - dist;
    /* G4ParticleTable *particletable = G4ParticleTable::GetParticleTable();
     G4ParticleDefinition *particle = particletable -> FindParticle("geantino");*/

  /* if(particle == G4Geantino::Geantino())
    {
    G4ParticleDefinition* ion =  G4IonTable::GetIonTable()->GetIon(48, 109, 0.); */
    fPrimary->SetParticleDefinition(G4Gamma::Definition());
    fPrimary->SetParticleEnergy(22.*keV);
    fPrimary->SetParticleCharge(0. *eplus);
    fPrimary->SetParticlePosition(G4ThreeVector(0., n *cm, -25 *mm));
    //momentum distribution ===============================
    fPrimary->SetParticleMomentumDirection(G4RandomDirection(sqrt(0.5))); //45 degrees conic distribution
    fPrimary->GeneratePrimaryVertex(anEvent);
//}
}

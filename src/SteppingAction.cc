#include "SteppingAction.hh"
#include "G4String.hh"
#include "G4VPhysicalVolume.hh"
#include "G4TrackStatus.hh"
#include "G4Step.hh"
#include "G4VProcess.hh"
#include "G4RootAnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"

SteppingAction::SteppingAction(EventAction* EA): G4UserSteppingAction(), m_EA(EA)
{
}

SteppingAction::~SteppingAction()
{
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
//Defining particle name
G4String parName = step -> GetTrack() -> GetDefinition() -> GetParticleName();

//Defining process
const G4VProcess* creProc = step -> GetTrack() -> GetCreatorProcess();

//Defining PostPV
G4String namePostPV;
	G4VPhysicalVolume* postPV = step -> GetPostStepPoint() -> GetPhysicalVolume();
	if ( postPV != 0 ) namePostPV = postPV -> GetName();
	else namePostPV = "outside";

//Defining Kinetic Energy
G4double postKinEgy = step -> GetPostStepPoint() -> GetKineticEnergy();

//Counting Optical Photons
//if ( namePostPV == "PMTPhy" && parName == "opticalphoton" && creProc -> GetProcessName() == "Scintillation")

if ( namePostPV == "PMTPhy" && parName == "opticalphoton")

	{
		auto AM = G4RootAnalysisManager::Instance();
		AM -> FillNtupleIColumn(0, G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID());
		AM -> FillNtupleDColumn(1, postKinEgy / eV);
		AM -> AddNtupleRow();

		// Once the photon touches the PMT, it is killed.
		step -> GetTrack() -> SetTrackStatus(fStopAndKill);
	}
}



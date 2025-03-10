#include "SteppingAction.hh"
#include "G4String.hh"
#include "G4VPhysicalVolume.hh"
#include "G4TrackStatus.hh"
#include "G4Step.hh"
#include "G4VProcess.hh"
#include "G4CsvAnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4LogicalSkinSurface.hh"
SteppingAction::SteppingAction(EventAction* EA): G4UserSteppingAction(), m_EA(EA)
{
}

SteppingAction::~SteppingAction()
{
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    G4CsvAnalysisManager* AM = G4CsvAnalysisManager::Instance();

    //Defining particle name
    G4String parName = step -> GetTrack() -> GetDefinition() -> GetParticleName();

    //Defining incident angle
    auto incvec = step -> GetDeltaPosition();
    double dotproduct = incvec.getY();
    double vecmag = incvec.mag();
    double cos = dotproduct / vecmag;

    //Defining process
    const G4VProcess* creProc = step -> GetTrack() -> GetCreatorProcess();

    const G4VProcess* proc = step -> GetPostStepPoint() -> GetProcessDefinedStep();
    G4String procname = proc -> GetProcessName();    

    //Defining PostPV
    G4String namePostPV;
	G4VPhysicalVolume* postPV = step -> GetPostStepPoint() -> GetPhysicalVolume();
	if ( postPV != 0 ) namePostPV = postPV -> GetName();
	else namePostPV = "outside";

    //Defining PrePV
    G4String namePrePV;
	G4VPhysicalVolume* prePV = step -> GetPreStepPoint() -> GetPhysicalVolume();
    namePrePV = prePV -> GetName();

    //Defining Kinetic Energy
    G4double preKinEgy  = step -> GetPreStepPoint()  -> GetKineticEnergy();
    G4double postKinEgy = step -> GetPostStepPoint() -> GetKineticEnergy();
    
    //Other important properties
    G4int ENofStep = G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID();
    G4int num = (step -> GetTrack() -> GetCurrentStepNumber() - 1)*0.5;

    //Counting Optical Photons
    if ( parName == "opticalphoton" && namePostPV == "PMTPhy" && creProc -> GetProcessName() == "Scintillation")
    {   
        step -> GetTrack() -> SetTrackStatus(fStopAndKill);
        // To send to EventAction.cc
        m_EA -> AddOp();
        m_EA -> AddRef(num);

        //To add to ntuples
        AM -> FillNtupleDColumn(0,0, postKinEgy / eV);
        AM -> FillNtupleIColumn(0,1,ENofStep);
        AM -> FillNtupleDColumn(0,2,cos);
        AM -> AddNtupleRow(0);
    
    }
        
    // Accumulate dE
    G4double Delegy = (preKinEgy - postKinEgy) / keV;
    if (parName == "gamma")
    {   
        m_EA -> AddDeltaE(Delegy);
    }

}

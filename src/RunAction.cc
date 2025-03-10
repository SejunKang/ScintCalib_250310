#include <ctime>
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "RunAction.hh"
#include "G4CsvAnalysisManager.hh"
#include "G4RootAnalysisManager.hh"
RunAction::RunAction()
    : G4UserRunAction()
{
/*auto analysisManager = G4AnalysisManager::Instance();
analysisManager->OpenFile("g4_minimal.csv");
analysisManager->CreateNtuple("EDep", "Enaergy Deposition");
analysisManager->CreateNtupleDColumn("EDep");
analysisManager->FinishNtuple();*/
}

RunAction::~RunAction()
{
}

void RunAction::BeginOfRunAction(const G4Run*)
{
    G4CsvAnalysisManager *AM = G4CsvAnalysisManager::Instance();
	AM -> SetVerboseLevel(0);

    AM -> OpenFile("numbers.csv");
    AM -> CreateNtuple("num", "num");
    AM -> CreateNtupleDColumn(0, "num");
    AM -> CreateNtupleIColumn(0,"ENofStep");
    AM -> CreateNtupleDColumn(0, "cos");
    AM -> FinishNtuple(0);
    
    AM -> OpenFile("exclude.csv");
    AM -> CreateNtuple("Eid", "EventID to Delete");
    AM -> CreateNtupleIColumn(1, "ENofEvent");
    AM -> FinishNtuple(1);

    G4RootAnalysisManager *AM_2 = G4RootAnalysisManager::Instance();
	AM_2 -> SetVerboseLevel(0);

    AM_2 -> OpenFile("event.root");
    AM_2 -> CreateNtuple("event", "MC_truth");
    //AM_2 -> CreateNtupleIColumn("EventID"); // Event ID
    //AM_2 -> CreateNtupleSColumn("Particle Name"); // Initial condition: what primary particle is
    //AM_2 -> CreateNtupleDColumn(0, "initial_E" ); // Initial condition: Initial kinetic of the primary
    AM_2 -> CreateNtupleDColumn(0, "dE" ); // Result: Energy deposit in scint
    AM_2 -> CreateNtupleIColumn(0, "n_photons"  ); // Result: Number of optical photons generated
    AM_2 -> CreateNtupleIColumn(0, "n_Ref"); // Result: Number of reflections of the photons that enter the PMT.
    AM_2 -> FinishNtuple(0);  
}


void RunAction::EndOfRunAction(const G4Run*)
{
    G4CsvAnalysisManager *AM = G4CsvAnalysisManager::Instance();
    AM -> Write();
    AM -> CloseFile();

    G4RootAnalysisManager *AM_2 = G4RootAnalysisManager::Instance();
    AM_2 -> Write();
    AM_2 -> CloseFile();

}



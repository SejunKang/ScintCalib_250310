#include <ctime>
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "RunAction.hh"
#include "G4RootAnalysisManager.hh"
RunAction::RunAction()
    : G4UserRunAction()
{
/*auto analysisManager = G4AnalysisManager::Instance();
analysisManager->OpenFile("g4_minimal.csv");
analysisManager->CreateNtuple("EDep", "Enaergy Deposition");
analysisManager->CreateNtupleDColumn("EDep");
analysisManager->FinishNtuple();*/

auto AM = G4RootAnalysisManager::Instance();
	AM -> SetVerboseLevel(0);
	AM -> CreateNtuple("mCP", "mCP");
	AM -> CreateNtupleIColumn("eventID"); // Column ID = 0
	AM -> CreateNtupleDColumn("energy" ); // Column ID = 1
	AM -> FinishNtuple();

}

RunAction::~RunAction()
{
}

void RunAction::BeginOfRunAction(const G4Run*)
{
auto AM = G4RootAnalysisManager::Instance();
AM -> OpenFile("output.root");

}
void RunAction::EndOfRunAction(const G4Run*)
{
/*auto analysisManager = G4AnalysisManager::Instance();
analysisManager->Write();
analysisManager->CloseFile();*/

	auto AM = G4RootAnalysisManager::Instance();
	AM -> Write();
	AM -> CloseFile();
}



#include "G4RunManager.hh"
#include <ctime>
#include "EventAction.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4RootAnalysisManager.hh"
#include "G4CsvAnalysisManager.hh"
#include "G4ParticleDefinition.hh"
#include "beam.hh"
EventAction::EventAction() : G4UserEventAction()
{
// Initialize
	m_NScint = 0;
	m_NCeren = 0;
    m_NOp    = 0;
    m_DeltaE = 0;

   // m_PName  = "";
   // m_KEi    = 0;
   // m_PFound = false;
    m_Rnum = 0;
}

EventAction::~EventAction()
{
}

void EventAction::BeginOfEventAction(const G4Event *)
{
// Initialize
	m_NScint = 0;
	m_NCeren = 0;
    m_NOp    = 0;
    m_DeltaE = 0;

   // m_PName  = "";
   // m_KEi    = 0;
   // m_PFound = false;
    m_Rnum = 0;
}

void EventAction::EndOfEventAction(const G4Event *anEvent)
{
    G4int cut;
    beam(cut);
    
    G4CsvAnalysisManager *AM = G4CsvAnalysisManager::Instance(); 
    G4RootAnalysisManager *AM_2 = G4RootAnalysisManager::Instance();

    // AM_2 -> FillNtupleIColumn(0, 0, anEvent -> GetEventID());
    // AM_2 -> FillNtupleSColumn(0, 1, m_PName);
    // AM_2 -> FillNtupleDColumn(0, 0, m_KEi);
    AM_2 -> FillNtupleDColumn(0, 0, m_DeltaE);
    AM_2 -> FillNtupleIColumn(0, 1, m_NOp);
    AM_2 -> FillNtupleIColumn(0, 2, m_Rnum);
    AM_2 -> AddNtupleRow(0);

     if(m_NOp < cut)
        {
          G4int ENofEvent = anEvent -> GetEventID();
          AM -> FillNtupleIColumn(1,0,ENofEvent);
          AM -> AddNtupleRow(1);
          G4RunManager::GetRunManager() -> AbortEvent();
          return;
        }
}


void EventAction::AddScint()
{
	m_NScint++;
}

void EventAction::AddCeren()
{
	m_NCeren++;
}

/*
void EventAction::SetPrimaryName(G4String pname)
{
	m_PName = pname;
}
*//*
void EventAction::SetPrimaryEnergy(G4double kei)
{
	m_KEi = kei;
}
*//*
void EventAction::SetPrimaryFound()
{
	m_PFound = true;
}
*//*
G4bool EventAction::GetPrimaryFound()
{
    return m_PFound;
}
*/

void EventAction::AddOp()
{
	m_NOp++;
}

void EventAction::AddDeltaE(G4double dE)
{
	m_DeltaE += dE;
}

void EventAction::AddRef(G4int num)
{
    m_Rnum += num;
}





#include <ctime>
#include "EventAction.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4RootAnalysisManager.hh"
EventAction::EventAction()
{
// Initialize
	m_NScint = 0;
	m_NCeren = 0;
}

EventAction::~EventAction()
{
}

void EventAction::BeginOfEventAction(const G4Event *)
{
// Initialize
	m_NScint = 0;
	m_NCeren = 0;
}

void EventAction::EndOfEventAction(const G4Event *anEvent)
{

}


void EventAction::AddScint()
{
	m_NScint++;
}

void EventAction::AddCeren()
{
	m_NCeren++;
}



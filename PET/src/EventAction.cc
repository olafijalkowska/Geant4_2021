
// $Id: EventAction.cc 15.10.2018 A. Fijalkowska $
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//
//
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "G4SystemOfUnits.hh"

EventAction::EventAction()
{
	outputFile.open("spineEnDep.txt");
}
 
EventAction::~EventAction()
{
	outputFile.close();
}


void EventAction::BeginOfEventAction(const G4Event* anEvent)
{
	//std::cout << "Event: " << anEvent->GetEventID ()  << std::endl;
}
 

void EventAction::EndOfEventAction(const G4Event* anEvent)
{
	outputFile << anEvent->GetEventID () << " " 
	           << SteppingAction::spineEnergyDep/keV << std::endl;
	SteppingAction::spineEnergyDep = 0; //zerowanie, żeby w następny zdarzeniu naliczać od nowa
}




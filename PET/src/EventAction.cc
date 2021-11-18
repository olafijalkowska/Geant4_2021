
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
	//outputFile.open("spineEnDep.txt");
	int nrOfDetectors=40;
	for(int i=0; i!=nrOfDetectors; ++i)
	{
		bkgCounter.insert ( std::pair<G4int, G4int>(i,0) );
	}	
}
 
EventAction::~EventAction()
{
	//outputFile.close();
	for (auto it=bkgCounter.begin(); it!=bkgCounter.end(); ++it)
    	std::cout << it->first << " " << it->second << std::endl;
}


void EventAction::BeginOfEventAction(const G4Event* anEvent)
{
	//std::cout << "Event: " << anEvent->GetEventID ()  << std::endl;
}
 

void EventAction::EndOfEventAction(const G4Event* anEvent)
{
	//outputFile << anEvent->GetEventID () << " " 
	//           << SteppingAction::spineEnergyDep/keV << std::endl;
	//SteppingAction::spineEnergyDep = 0; //zerowanie, żeby w następny zdarzeniu naliczać od nowa
	
	for (auto it=SteppingAction::firedDetectors.begin(); it!=SteppingAction::firedDetectors.end(); ++it)
	{
		bkgCounter[*it] +=1;
	}
    SteppingAction::firedDetectors.clear();
	
	
}




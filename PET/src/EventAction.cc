
// $Id: EventAction.cc 15.10.2018 A. Fijalkowska $
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//
//
#include "EventAction.hh"

EventAction::EventAction()
{

}
 
EventAction::~EventAction()
{
}


void EventAction::BeginOfEventAction(const G4Event* anEvent)
{
	std::cout << "Event: " << anEvent->GetEventID ()  << std::endl;
}
 

void EventAction::EndOfEventAction(const G4Event* anEvent)
{
  std::cout << "END of event" << std::endl;
}




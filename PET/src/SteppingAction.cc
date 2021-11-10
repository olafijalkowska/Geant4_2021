//
// $Id: SteppingAction.cc 15.10.2018 A. Fijalkowska $
//
/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class
//
//
#include "SteppingAction.hh"
#include "G4SteppingManager.hh"
#include "G4Step.hh"
#include "G4VPhysicalVolume.hh"

SteppingAction::SteppingAction():G4UserSteppingAction()
{

}

SteppingAction::~SteppingAction() {}


void SteppingAction::UserSteppingAction(const G4Step* theStep)
{
	//find the name of volume, where the step accured
	G4Track* track = theStep->GetTrack();
	G4VPhysicalVolume* physVol = track->GetVolume();
	G4String name = physVol->GetName();
	
	G4double energyDeposit = theStep->GetTotalEnergyDeposit();
	
	if(name == "spinePhys")
		spineEnergyDep+=energyDeposit;
}

double SteppingAction::spineEnergyDep = 0;

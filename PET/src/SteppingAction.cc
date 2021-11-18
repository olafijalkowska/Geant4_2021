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
#include "G4TouchableHistory.hh"
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
	
	//G4double energyDeposit = theStep->GetTotalEnergyDeposit();
	
	if(name == "naIPhys")
	{
		G4StepPoint* preStep = theStep->GetPreStepPoint();
  		G4TouchableHistory* th = (G4TouchableHistory*)(preStep->GetTouchable());
  		G4int indexDepth = 1;
  		G4int replicaNr = th->GetReplicaNumber(indexDepth);
  		firedDetectors.insert(replicaNr);		
	}

}




  
double SteppingAction::spineEnergyDep = 0;
std::set<int> SteppingAction::firedDetectors={};

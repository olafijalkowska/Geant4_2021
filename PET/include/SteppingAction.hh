//
// $Id: SteppingAction.hh 15.10.2018 A. Fijalkowska $
//
/// \file SteppingAction.hh
/// \brief Definition of the SteppingAction class
//
#ifndef SteppingAction_H
#define SteppingACtion_H 1

#include "G4UserSteppingAction.hh"
#include <set>

class SteppingAction : public G4UserSteppingAction
{
  public:
  	static double spineEnergyDep;
  	static std::set<int> firedDetectors;
    SteppingAction();
    virtual ~SteppingAction();
    virtual void UserSteppingAction(const G4Step*); 
  private:
    
};

#endif

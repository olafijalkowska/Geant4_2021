//
// $Id: PrimaryGeneratorAction.hh 15.10.2018 A Fijalkowska $
//
/// \file PrimaryGeneratorAction.hh
/// \brief Definition of the PrimaryGeneratorAction class

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include <vector>

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();

  public:
    virtual void GeneratePrimaries(G4Event*);

  private:
	void SetUpDefault();	
    G4ParticleGun* particleGun;
    G4ParticleTable* particleTable;
    G4ThreeVector GenerateIsotropicDirection();
    void GeneratePositionIncident(G4Event*);
    void GenerateBackgroundIncident(G4Event*);
    G4ThreeVector FindRandomPosition(G4double sizeX, G4double sizeY, G4double sizeZ);
    std::vector<G4double> FindRandomBackgroundEnergy();
};


#endif 


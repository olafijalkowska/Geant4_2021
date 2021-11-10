
// $Id: PrimaryGeneratorAction.cc 15.10.2018 A Fijalkowska $
//
/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction()
{
    particleGun = new G4ParticleGun();
    particleTable = G4ParticleTable::GetParticleTable();
	SetUpDefault();
}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

void PrimaryGeneratorAction::SetUpDefault()
{
	
	G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
	particleGun->SetParticleDefinition(particle);
	particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,0.0*cm));
	particleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
	particleGun->SetParticleEnergy(500.0*keV);

}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{	
//	G4ThreeVector randomVec = GenerateIsotropicDirection();
//	particleGun->SetParticleMomentumDirection(randomVec);
//    particleGun->GeneratePrimaryVertex(anEvent);
	GeneratePositionIncident(anEvent);
}	

G4ThreeVector PrimaryGeneratorAction::GenerateIsotropicDirection()
{	
	G4double cosTheta = 2.*G4UniformRand()-1;
	G4double sinTheta = pow((1-cosTheta*cosTheta),0.5);
	G4double phi = 2*M_PI*G4UniformRand();
	//std::cout << sinTheta*cos(phi) << " " << sinTheta*sin(phi) << " " << cosTheta << std::endl;
	return G4ThreeVector(sinTheta*cos(phi),sinTheta*sin(phi),cosTheta );
}


void PrimaryGeneratorAction::GeneratePositionIncident(G4Event* anEvent)
{
	G4ParticleDefinition* positron = particleTable->FindParticle("e+");
	particleGun->SetParticleDefinition(positron);
	particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,0.0*cm));
	particleGun->SetParticleEnergy(600.0*keV);
	G4ThreeVector randomVec = GenerateIsotropicDirection();
	particleGun->SetParticleMomentumDirection(randomVec);
	particleGun->GeneratePrimaryVertex(anEvent);
}

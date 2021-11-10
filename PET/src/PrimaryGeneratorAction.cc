
// $Id: PrimaryGeneratorAction.cc 15.10.2018 A Fijalkowska $
//
/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "DetectorConstruction.hh"


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
	GenerateBackgroundIncident(anEvent);
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


void PrimaryGeneratorAction::GenerateBackgroundIncident(G4Event* anEvent)
{
	G4ParticleDefinition* gamma = particleTable->FindParticle("gamma");
	particleGun->SetParticleDefinition(gamma);
	G4double worldSize = DetectorConstruction::worldSize;	
	particleGun->SetParticlePosition(FindRandomPosition(worldSize, worldSize, worldSize));
	
	std::vector<G4double> energies = FindRandomBackgroundEnergy();
	for(size_t i=0; i!=energies.size(); ++i)
	{
		particleGun->SetParticleEnergy(energies.at(i));
		particleGun->SetParticleMomentumDirection(GenerateIsotropicDirection());
		particleGun->GeneratePrimaryVertex(anEvent);
	}
}


G4ThreeVector PrimaryGeneratorAction::FindRandomPosition(G4double sizeX, G4double sizeY, G4double sizeZ)
{
	G4double randomX = sizeX*G4UniformRand()-sizeX/2.;
	G4double randomY = sizeY*G4UniformRand()-sizeY/2.;	
	G4double randomZ = sizeZ*G4UniformRand()-sizeZ/2.;
	return G4ThreeVector(randomX,randomY,randomZ);
}

std::vector<G4double> PrimaryGeneratorAction::FindRandomBackgroundEnergy()
{
	std::vector<G4double> energy;
	int randomVal = (int)3*G4UniformRand();
	if(randomVal<2)
	{
		energy.push_back(1461*keV);
	}
	else
	{
		energy.push_back(583*keV);
		energy.push_back(2615*keV);
	}
	return energy;
}

//
// $Id: DetectorConstruction.cc 12.16.2016 A. Fijalkowska $
//
/// \file DetectorConstruction.cc
/// \brief DetectorConstruction class
//
//
#include "DetectorConstruction.hh"
#include "G4PVPlacement.hh" //tworzenie physical volume
#include "G4SystemOfUnits.hh" //jednostki
#include "G4VisAttributes.hh" //sposob wyświetlania, kolory itp

#include "G4Box.hh" //prostopadłościan
#include "G4Tubs.hh" //walec
#include "G4ThreeVector.hh" //trzyelementowy wektor wbudowany w geant
#include "globals.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4PSEnergyDeposit.hh"
#include "HumanPhantom.hh"

DetectorConstruction::DetectorConstruction()
{
    worldLogic = 0L;
    cylinderLogVol=0L;
    man = G4NistManager::Instance();
}



DetectorConstruction::~DetectorConstruction() 
{
    if(worldLogic != 0L)
        delete worldLogic;      
    if(cylinderLogVol != 0L)
        delete cylinderLogVol; 
}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4VPhysicalVolume* worldPhys = ConstructWorld();
    ConstructHumanPhantom();
    ConstructCylinder();
    return worldPhys;
}


G4VPhysicalVolume* DetectorConstruction::ConstructWorld()
{

    G4double worldX = 1.5*m;
    G4double worldY = 1.5*m;
    G4double worldZ = 1.5*m;
    G4Box* worldSolid = new G4Box("worldSolid",worldX,worldY,worldZ);
    
    G4Material* vaccum = new G4Material("GalacticVacuum", 1., 1.01*g/mole,
                           CLHEP::universe_mean_density, 
                           kStateGas, 3.e-18*pascal, 2.73*kelvin);
                           
    worldLogic = new G4LogicalVolume(worldSolid, vaccum,"worldLogic", 0,0,0);
                                             
    //worldLogic->SetVisAttributes(G4VisAttributes::Invisible);
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogic, "world", 0, false, 0);
    return worldPhys;

}


void DetectorConstruction::ConstructHumanPhantom()
{   
    HumanPhantom* phantom = new HumanPhantom(170*cm, 15*cm);
    G4ThreeVector pos(0,0,0);
	phantom->Place(0, pos, "fantom", worldLogic, 0);	
}





void DetectorConstruction::ConstructCylinder()
{
     G4Material* ppy = man->FindOrBuildMaterial("G4_POLYPROPYLENE");
     G4double rMin = 40*cm;
     G4double rMax = 55*cm;
     G4double length = 15*cm;
     G4Tubs* theCylinder = new G4Tubs("theCylinder", rMin, rMax, length/2, 0*deg, 360*deg);
     cylinderLogVol = new G4LogicalVolume(theCylinder, ppy, "cylinderLogVol");

     G4VisAttributes* cylinderAtt = new G4VisAttributes(G4Colour(0.5,0.5,0.5, 0.7));
     cylinderAtt->SetForceAuxEdgeVisible(true);
     cylinderAtt->SetForceSolid(true);
     cylinderLogVol->SetVisAttributes(cylinderAtt);

     G4ThreeVector pos(0,0, 0);
     new G4PVPlacement(0,pos,cylinderLogVol, "cylinderPhy",worldLogic,0,0);
}
//NaI
//wysokość 10 cm
//promień 4 cm
//teflon 1 mm
//odsunięcie od krawędzi: 5 mm

void DetectorConstruction::ConstructSDandField() 
{


}







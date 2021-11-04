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
    detectorLogVol=0L;
    man = G4NistManager::Instance();
    
    NaIHeigh = 10*cm;
	NaIRadius = 4*cm;
	teflonThickness = 1*mm;
	rMin = 40*cm;
    rMax = 55*cm;
    length = 15*cm;
    distanceFromCylinderEdge=5*mm;
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
    ConstructDetector();
    LocateDetectors();
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

void DetectorConstruction::ConstructDetector() 
{
	G4Tubs* naISolid = new G4Tubs("naISolid", 0*cm, NaIRadius, NaIHeigh/2., 0*deg, 360*deg);
	G4Material* naIMaterial = man->FindOrBuildMaterial("G4_SODIUM_IODIDE");
	G4LogicalVolume* naILogVol = new G4LogicalVolume(naISolid, naIMaterial, "NaILogVol");
	
	 G4VisAttributes* naIVisAtt = new G4VisAttributes(G4Colour(0.8,0.3,0.3, 1.));
     naIVisAtt->SetForceAuxEdgeVisible(true);
     naIVisAtt->SetForceSolid(true);
     naILogVol->SetVisAttributes(naIVisAtt);
     
    G4Tubs* teflonSolid = new G4Tubs("naISolid", 0*cm, 
       (NaIRadius+teflonThickness), NaIHeigh/2.+teflonThickness, 0*deg, 360*deg);
	G4Material* teflonMaterial = man->FindOrBuildMaterial("G4_TEFLON");
	detectorLogVol = new G4LogicalVolume(teflonSolid, teflonMaterial, "TeflonLogVol");
	G4VisAttributes* teflonVisAtt = new G4VisAttributes(G4Colour(0.0,0.9,0.3, 0.8));
    teflonVisAtt->SetForceAuxEdgeVisible(true);
    detectorLogVol->SetVisAttributes(teflonVisAtt);
	
	G4ThreeVector pos(0,0, 0);
    new G4PVPlacement(0,pos,naILogVol, "naIPhys",detectorLogVol,0,0);
}

void DetectorConstruction::LocateDetectors()
{
	G4double Rtot=rMin+distanceFromCylinderEdge+NaIHeigh/2.+teflonThickness;
	G4double Htot=rMin+distanceFromCylinderEdge;
	G4double singleDetAngle = 2*atan((NaIRadius+teflonThickness)/Htot);
	G4int nrOfDetectors = (G4int)2.*CLHEP::pi/singleDetAngle;
	std::cout << " Rtot: " << Rtot << " Htot: " << Htot << " nr fo Dets: " << nrOfDetectors << std::endl;
	G4double deltaAngle = 2.*CLHEP::pi/31.;
	
	for(G4int i=0; i!= nrOfDetectors; ++i)
	{
		G4double posX = Rtot*sin(i*deltaAngle);
		G4double posY = Rtot*cos(i*deltaAngle);
		G4RotationMatrix* zRot = new G4RotationMatrix;
		zRot->rotateZ(i*deltaAngle);
		zRot->rotateX(90*deg);
		G4ThreeVector pos(posX,posY, 0);
		new G4PVPlacement(zRot,pos,detectorLogVol, "detectorPhys",cylinderLogVol,0,i, 1);
	}
	
}

void DetectorConstruction::ConstructSDandField() 
{


}







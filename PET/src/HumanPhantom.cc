
#include "HumanPhantom.hh"
#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh" //jednostki
#include "G4PVPlacement.hh" 


HumanPhantom::HumanPhantom(double heigh, double radius)
{
    ConstructPhantom(heigh, radius);
    ConstructSpine(heigh);
}

void HumanPhantom::ConstructPhantom(double heigh, double radius)
{
    G4double radiusMin = 0;
    G4double radiusMax = radius;
    G4double length = heigh;
    G4Tubs* phantomSolid = new G4Tubs("PhantomSolid", radiusMin, radiusMax, length/2., 0*deg, 360*deg);
    G4Material* water = MakeWater();
    phantomLogVol = new G4LogicalVolume(phantomSolid, water, "PhantomLogVol");

     
    G4VisAttributes* phantomVisAtt = new G4VisAttributes( G4Colour(1,0.8,0.8));
	phantomVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
	//PhantomVisAtt->SetForceSolid(true);
	phantomLogVol->SetVisAttributes(phantomVisAtt);

	//G4ThreeVector pos(0,0,0);    
	//new G4PVPlacement(0, pos, PhantomLogVol, "Phantom", worldLogic, 0, 0);

}

G4Material* HumanPhantom::MakeWater()
{
    G4NistManager* man=G4NistManager::Instance();
    G4Element* H = man->FindOrBuildElement("H");
    G4Element* O = man->FindOrBuildElement("O");
    G4Material* water = new G4Material("water", 1.0*g/cm3, 2);
    water->AddElement(H, 2);
    water->AddElement(O, 1);
    return water;

}

void HumanPhantom::ConstructSpine(double heigh)
{
   G4double rMin = 0;
   G4double rMax = 3 *cm;
   G4double halfLength = heigh/4.; 
   G4Tubs* spineSolid = new G4Tubs("spineSolid", rMin, rMax, halfLength, 0*deg, 360*deg);
   
   G4NistManager* man=G4NistManager::Instance();
   G4Material* bone = man->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");

   
   G4LogicalVolume* spineLogVol = new G4LogicalVolume(spineSolid, bone,"spineLogic");
   G4VisAttributes* spineVis = new G4VisAttributes(G4Colour(1,1.,1));
   //aluVis->SetForceSolid(true);
   spineVis->SetForceAuxEdgeVisible(true);
   spineLogVol->SetVisAttributes(spineVis);
   G4ThreeVector pos(0,0*cm,halfLength);
   new G4PVPlacement(0, pos, spineLogVol, "spinePhys", phantomLogVol, 0, 0);
}


void HumanPhantom::Place(G4RotationMatrix *pRot, 
                        G4ThreeVector &tlate, 
                        const G4String &pName, 
                        G4LogicalVolume *pMotherLogical,  
                        G4int pCopyNo)
{
    new G4PVPlacement(pRot, tlate, phantomLogVol, pName,  pMotherLogical, 0,pCopyNo);
}


#ifndef HumanPhantom_H
#define HumanPhantom_H 1
#include "G4Material.hh"
#include "G4LogicalVolume.hh"

class HumanPhantom
{
    public:
    HumanPhantom(double heigh, double radius);
    void Place(G4RotationMatrix *pRot, 
                        G4ThreeVector &tlate, 
                        const G4String &pName, 
                        G4LogicalVolume *pMotherLogical,  
                        G4int pCopyNo);
    
    private:
    void ConstructPhantom(double heigh, double radius);
    void ConstructSpine(double heigh);
    G4Material* MakeWater();
    
    G4LogicalVolume* phantomLogVol;

};

#endif

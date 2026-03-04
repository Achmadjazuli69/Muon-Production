#include "DetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

MyDetectorConstruction::MyDetectorConstruction() {}
MyDetectorConstruction::~MyDetectorConstruction() {}

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
    G4NistManager* nist = G4NistManager::Instance();

    // =============================
    // WORLD
    // =============================
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");

    G4double worldSize = 1.0*m;  // 1 meter full size
    G4Box* solidWorld = new G4Box("solidWorld",
                                  worldSize/2,
                                  worldSize/2,
                                  worldSize/2);

    G4LogicalVolume* logicWorld =
        new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

    G4VPhysicalVolume* physWorld =
        new G4PVPlacement(0,
                          G4ThreeVector(),
                          logicWorld,
                          "physWorld",
                          0,
                          false,
                          0,
                          true);

    // =============================
    // TARGET (TUNGSTEN)
    // =============================
    G4Material* targetMat = nist->FindOrBuildMaterial("G4_W");

    // ---- IMPORTANT ----
    // G4Box uses HALF-LENGTH
    // We want TOTAL thickness = 2.1 cm
    G4double targetHalfZ = 2.1*cm / 2.0;   // = 1.05 cm
    G4double targetHalfXY = 5.0*cm;        // full width 10 cm

    G4Box* solidTarget = new G4Box("solidTarget",
                                   targetHalfXY,
                                   targetHalfXY,
                                   targetHalfZ);

    G4LogicalVolume* logicTarget =
        new G4LogicalVolume(solidTarget,
                            targetMat,
                            "logicTarget");

    // Place target centered at z = +targetHalfZ
    // so front face is at z = 0
    new G4PVPlacement(0,
                      G4ThreeVector(0,0,targetHalfZ),
                      logicTarget,
                      "physTarget",
                      logicWorld,
                      false,
                      0,
                      true);

    return physWorld;
}

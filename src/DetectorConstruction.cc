//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{
  fFilmXY = 1*um;
  fFilmZ  = 1*um;
  fDetectorMessenger = new DetectorMessenger(this);

  G4NistManager* man = G4NistManager::Instance();
  fwater=man->FindOrBuildMaterial("G4_WATER");
  G4double density = 1.1*g/cm3; // 1.38*g/cm3;
  fwater=man->BuildMaterialWithNewDensity("Water_new","G4_WATER",density);
  fFilmMaterial=fwater;
}

DetectorConstruction::~DetectorConstruction()
{ 
  delete fDetectorMessenger;
}
  
G4VPhysicalVolume* DetectorConstruction::Construct()
{ 
  G4bool checkoverlaps = false;
  G4Box* solidworld = new G4Box("world", fFilmXY/2, fFilmXY/2, fFilmZ/2);
  G4LogicalVolume* logicworld = new G4LogicalVolume(solidworld, fFilmMaterial, "world");            
  G4VPhysicalVolume* physiworld =
      new G4PVPlacement(0, G4ThreeVector(), logicworld,        
                        "world", 0, false, 0, checkoverlaps);
  return physiworld;
}

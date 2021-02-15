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

#include "Run.hh"
#include "DetectorConstruction.hh"
#include "HistoManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4PhysicalConstants.hh"
#include "G4RunManager.hh"
#include <vector>

Run::Run() 
: G4Run()
{}

Run::~Run()
{}

void Run::Merge(const G4Run* arun)
{
  G4Run::Merge(arun);
}

void Run::EndOfRun() 
{
  // scale histograms 
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
   
  std::vector<int> hid={0,3,6,9,12}; G4double fac=1./numberOfEvent;
  for (int i=0; i<5; i++){
  analysisManager->ScaleH1(hid[i],fac);
  }
  
  const DetectorConstruction* Detector
        = static_cast<const DetectorConstruction*>
          (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  G4double tracklength=Detector->GetFilmZ();

  hid={1,4,7,10}; fac=1./(numberOfEvent*(tracklength/nm));
  for (int i=0; i<4; i++){
  analysisManager->ScaleH1(hid[i],fac);
  }

  hid={2,5,8,11,14}; fac=1./(eV*numberOfEvent*(tracklength/nm));
  for (int i=0; i<5; i++){
  analysisManager->ScaleH1(hid[i],fac);
  }

}
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

#include "RunAction.hh"
#include "HistoManager.hh"
#include "Run.hh"
#include "SteppingAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "DetectorConstruction.hh"
#include "G4RunManager.hh"

RunAction::RunAction() 
: G4UserRunAction(), fRun(0)
{ 
  // Book predefined histograms
  fHistoManager = new HistoManager();
}

RunAction::~RunAction()
{ 
  delete fHistoManager;
}

G4Run* RunAction::GenerateRun()
{
  fRun = new Run();
  return fRun;
}


void RunAction::BeginOfRunAction(const G4Run*)
{    
  const DetectorConstruction* Detector
        = static_cast<const DetectorConstruction*>
          (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  G4double halfz=0.;
  if (Detector)
  {
    halfz=(Detector->GetFilmZ())/2;
  }
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4double deltad=0.;
  if(analysisManager)
  {
    deltad=analysisManager->GetH1Width(9)*analysisManager->GetH1Unit(9);
    if ( analysisManager->IsActive() ) 
    {
      analysisManager->OpenFile();
    }
  }

  // Note: There is no primary generator action object for "master"
  // run manager for multi-threaded mode.
  const PrimaryGeneratorAction* generatorAction
   = static_cast<const PrimaryGeneratorAction*>
     (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  if (generatorAction)
  {
    const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
    G4double particleEnergy = particleGun->GetParticleEnergy();
    const SteppingAction* stepaction
         = static_cast<const SteppingAction*>
           (G4RunManager::GetRunManager()->GetUserSteppingAction());
    SteppingAction* ncstepaction = const_cast<SteppingAction*>(stepaction);
    ncstepaction->InitRunCond(halfz, deltad, particleEnergy);
  }
}

void RunAction::EndOfRunAction(const G4Run*)
{
  if (isMaster) fRun->EndOfRun();
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();  
   if ( analysisManager->IsActive() ) 
   {
     analysisManager->Write();
     analysisManager->CloseFile();
   } 
}


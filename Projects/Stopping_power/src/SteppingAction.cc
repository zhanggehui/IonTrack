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

#include "SteppingAction.hh"
#include "G4RunManager.hh"
#include "G4Electron.hh"
#include "G4Gamma.hh"
#include "G4Proton.hh"
#include "G4DNAGenericIonsManager.hh"

SteppingAction::SteppingAction()
: G4UserSteppingAction(), fTotalStoppingPower(0.),
fSumOfStepLength(0.), fDepositedEnergy(0.), fNumberOfSteps(0)
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  //由于电荷态会发生变化(以二次电子的形式), 所以要考虑二次粒子, 但是在变换电荷态时可能
  //产生的二次电子先被追踪, 导致时间浪费,故直接kill掉
  //*** WARNING: this line will kill all secondary e- and gammas ***
  if ( (step->GetTrack()->GetDefinition()==G4Electron::ElectronDefinition()
        && step->GetTrack()->GetTrackID() != 1) 
        ||
        step->GetTrack()->GetDefinition()==G4Gamma::GammaDefinition() ) 
    step->GetTrack()->SetTrackStatus(fStopAndKill);

  G4double charge = step->GetTrack()->GetDefinition()->GetPDGCharge();
  if ( 
      // ELECTRONS 
      ( step->GetTrack()->GetTrackID() == 1 &&
        step->GetTrack()->GetParticleDefinition()==G4Electron::ElectronDefinition() )
      ||
      // PROTONS, HYDROGEN, ALPHA PARTICLES AND CHARGED STATES, GenericIons
      ( charge != -1. &&
        step->GetTrack()->GetParticleDefinition()!=G4Gamma::GammaDefinition() )
     )
  {   
    G4DNAGenericIonsManager *instance = G4DNAGenericIonsManager::Instance();
    
    fDepositedEnergy = fDepositedEnergy + step->GetTotalEnergyDeposit();
    fSumOfStepLength = fSumOfStepLength + step->GetStepLength();
    fNumberOfSteps = fNumberOfSteps + 1;
    G4int maxNumberOfSteps = 10000;

    // ELECTRONS
    if ( step->GetTrack()->GetParticleDefinition()==G4Electron::ElectronDefinition() )
      maxNumberOfSteps = 2000;
    // PROTONS, HYDROGEN
    if ( step->GetTrack()->GetParticleDefinition()==G4Proton::ProtonDefinition()
         ||
         step->GetTrack()->GetParticleDefinition()==instance->GetIon("hydrogen") )
      maxNumberOfSteps = 2000;
    // He0, He+, He2+
    if ( step->GetTrack()->GetParticleDefinition()==instance->GetIon("alpha+")
         ||
         step->GetTrack()->GetParticleDefinition()==instance->GetIon("alpha++")
         ||
         step->GetTrack()->GetParticleDefinition()==instance->GetIon("helium") )
      maxNumberOfSteps = 10000;

    // All
    if (fNumberOfSteps > maxNumberOfSteps)
    { 
      fTotalStoppingPower = fDepositedEnergy/fSumOfStepLength;
      G4RunManager::GetRunManager()->AbortEvent();
      fSumOfStepLength = 0.;
      fDepositedEnergy = 0.;
      fNumberOfSteps = 0;
    };
  };
}

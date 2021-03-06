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

#include "StepMax.hh"
#include "PhysicsListMessenger.hh"
#include "G4VPhysicalVolume.hh"
#include "G4TransportationProcessType.hh"

StepMax::StepMax(PhysicsListMessenger* mess)
: G4VEmProcess("UserMaxStep", fGeneral), fMessenger(mess),
  fMaxChargedStep(DBL_MAX), fInitialised(false)
{
  SetProcessSubType(static_cast<G4int>(STEP_LIMITER));  
}

StepMax::~StepMax() 
{}

G4bool StepMax::IsApplicable(const G4ParticleDefinition& part)
{
  return (part.GetPDGCharge() != 0. && !part.IsShortLived());
}

void StepMax::PreparePhysicsTable(const G4ParticleDefinition&)
{
  if(fInitialised) {
    fInitialised = false;
  }
}

void StepMax::BuildPhysicsTable(const G4ParticleDefinition&)
{
  if(!fInitialised) {
    fMaxChargedStep = fMessenger->GetMaxChargedStep();
    fInitialised = true;
    if(fMaxChargedStep < DBL_MAX) {
      G4cout << GetProcessName() << ":  SubType= " << GetProcessSubType()
             << "  Step limit(mm)= " << fMaxChargedStep << G4endl;
    }
  }
}

void StepMax::InitialiseProcess(const G4ParticleDefinition*)
{}

G4double StepMax::PostStepGetPhysicalInteractionLength(const G4Track&,
                                                       G4double,
                                                       G4ForceCondition* condition)
{
  // condition is set to "Not Forced"
  *condition = NotForced;
  return fMaxChargedStep;
}

G4VParticleChange* StepMax::PostStepDoIt(const G4Track& aTrack, const G4Step&)
{
  // do nothing
  aParticleChange.Initialize(aTrack);
  return &aParticleChange;
}

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

#include "PrimaryGeneratorMessenger.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(PrimaryGeneratorAction* Gun)
:G4UImessenger(), fAction(Gun), fIonTrackDir(0), fGunDir(0), fDistanceCmd(0)
{
  fIonTrackDir = new G4UIdirectory("/IonTrack/");
  fIonTrackDir->SetGuidance("UI commands specific to this example");
  fGunDir = new G4UIdirectory("/IonTrack/gun/");
  fGunDir->SetGuidance("gun position control");
  
  fDistanceCmd = new G4UIcmdWithADoubleAndUnit("/IonTrack/gun/distance",this);
  fDistanceCmd->SetGuidance("Distance between two beams");
  fDistanceCmd->SetParameterName("dis",false);
  fDistanceCmd->SetRange("dis>=0.");
  fDistanceCmd->SetUnitCategory("Length"); 
  fDistanceCmd->AvailableForStates(G4State_Idle);   
}

PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
  delete fDistanceCmd;
  delete fGunDir; 
  delete fIonTrackDir; 
}

void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{  
  if (command == fDistanceCmd)
   { fAction->Setdistance(fDistanceCmd->GetNewDoubleValue(newValue));}       
}

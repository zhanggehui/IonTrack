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

#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

DetectorMessenger::DetectorMessenger(DetectorConstruction *Det)
: G4UImessenger(), fDetector(Det)
{
  fIonTrackDir = new G4UIdirectory("/IonTrack/");
  fIonTrackDir->SetGuidance("UI commands specific to simulate IonTrack");

  fDetDir = new G4UIdirectory("/IonTrack/det/");
  fDetDir->SetGuidance("Detector construction commands");

  fFilmXYCmd = new G4UIcmdWithADoubleAndUnit("/IonTrack/det/setFilmXY", this);
  fFilmXYCmd->SetGuidance("Set XY of the Film");
  fFilmXYCmd->SetParameterName("FilmX", false);
  fFilmXYCmd->SetRange("FilmX>0.");
  fFilmXYCmd->SetUnitCategory("Length");
  fFilmXYCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  fFilmXYCmd->SetToBeBroadcasted(false);

  fFilmZCmd = new G4UIcmdWithADoubleAndUnit("/IonTrack/det/setFilmZ", this);
  fFilmZCmd->SetGuidance("Set Z of the Film");
  fFilmZCmd->SetParameterName("FilmZ", false);
  fFilmZCmd->SetRange("FilmZ>0.");
  fFilmZCmd->SetUnitCategory("Length");
  fFilmZCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  fFilmZCmd->SetToBeBroadcasted(false);
}

DetectorMessenger::~DetectorMessenger()
{
  delete fFilmZCmd;
  delete fFilmXYCmd;
  delete fDetDir;
  delete fIonTrackDir;
}

void DetectorMessenger::SetNewValue(G4UIcommand *command, G4String newValue)
{
  if (command == fFilmXYCmd)
  {
    fDetector->SetFilmXY(fFilmXYCmd->GetNewDoubleValue(newValue));
  }
  if (command == fFilmZCmd)
  {
    fDetector->SetFilmZ(fFilmZCmd->GetNewDoubleValue(newValue));
  }
}

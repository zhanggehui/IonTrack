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

#include "TrackingAction.hh"
#include "HistoManager.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4Electron.hh"

TrackingAction::TrackingAction() : G4UserTrackingAction()
{}
 
TrackingAction::~TrackingAction()
{}

void TrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{ 
  // Priamary particle
  if (aTrack->GetParentID()==0)
  {
    G4cout << aTrack->GetDefinition()->GetPDGCharge() << G4endl;
  }
  //secondary electron created only by primary
  else if ( aTrack->GetParentID() == 1 //for there is only primary shooted out in an event
            &&  
            aTrack->GetDefinition() == G4Electron::Electron())
  {
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    G4double energy = aTrack->GetKineticEnergy();
    analysisManager->FillH1(12, energy);
  }
}

void TrackingAction::PostUserTrackingAction(const G4Track*)
{}

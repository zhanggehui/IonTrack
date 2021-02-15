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
#include "HistoManager.hh"

#include "Randomize.hh"
#include "G4Step.hh"
#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4PhysicalConstants.hh"

SteppingAction::SteppingAction()
: G4UserSteppingAction(),fHalfZ(0.),fdeltad(0.),fprimek(0.),
  flastene(0.),fcurrentene(0.),flastdepid(0),fcurrentdepid(0)
{}

SteppingAction::~SteppingAction()
{}


void SteppingAction::InitRunCond
(G4double halfz,G4double deltad,G4double particleEnergy)
{
  fHalfZ=halfz;
  fdeltad=deltad;
  fprimek=particleEnergy;
}

void SteppingAction::InitializeNewPri()
{
  flastene=fprimek; fcurrentene=0.;
  flastdepid=0; fcurrentdepid=0;
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  G4double edep=step->GetTotalEnergyDeposit();
  if (edep<0.) return;
  const G4StepPoint* PrePoint  = step->GetPreStepPoint() ;
  const G4StepPoint* PostPoint = step->GetPostStepPoint();
  G4ThreeVector point=PrePoint->GetPosition() + 
                      G4UniformRand()*(PostPoint->GetPosition()-PrePoint->GetPosition());
  G4double x = point.x(), y = point.y();
  G4double r = std::sqrt(x*x + y*y);

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(14, r, edep);

  // Time Resovled
  G4double fs=0.001*picosecond;
  G4double lasttime    = (PrePoint)  ?  PrePoint->GetGlobalTime(): 0.;
  G4double currenttime = (PostPoint) ? PostPoint->GetGlobalTime(): 0.;

  const G4int tnum=4;
  G4double times[tnum]={1,5,25,75};
  G4int edehitsid[tnum]={2,5,8,11};

  for (G4int i=0; i<tnum ;i++)
  {
    if (currenttime<times[i]*fs)
    {
      for (G4int k=i; k<tnum; k++)
      {
        analysisManager->FillH1(edehitsid[k], r, edep);
      }
    break;
    }
  }

  if (step->GetTrack()->GetDefinition()->GetParticleName() == "e-")
  { 
    G4int timepoint=0;
    for (G4int i=0 ; i<tnum ; i++)
    { 
      if (lasttime<=times[i]*fs && currenttime>=times[i]*fs )
      {
        G4int histid = timepoint ;
        G4double ek = step->GetTrack()->GetKineticEnergy();
        analysisManager->FillH1(histid, ek);
        analysisManager->FillH1(histid+1, r);
        break;
      }
      timepoint=timepoint+3;
    }
  } 
  
  else if (step->GetTrack()->GetParentID()==0)
  {
    /*if (fknown)
    {    
      //point = 0.5*(PostPoint->GetPosition() + PrePoint->GetPosition());
      point = PostPoint->GetPosition();
      G4double depth=fHalfZ-point.z();
      if (depth<0.) depth=0.; 
      fcurrentdepid=floor(depth/fdeltad);
      if (flastdepid!=fcurrentdepid)
      {  
        fcurrentene=step->GetTrack()->GetKineticEnergy();
        if (fcurrentene==0) return; 
        G4double dedx=(flastene-fcurrentene)/fdeltad;
        flastene=fcurrentene;
        flastdepid=fcurrentdepid;
        analysisManager->FillH1(9, depth-fdeltad, dedx);
      }
    }*/
    /*G4double eloss=-step->GetDeltaEnergy();
    point = 0.5*(PostPoint->GetPosition() + PrePoint->GetPosition());
    G4double depth=fHalfZ-point.z();
    if (depth<0.) depth=0.; 
    fcurrentene=step->GetTrack()->GetKineticEnergy();
    if (fcurrentene==0) return; 
    analysisManager->FillH1(9, depth, eloss);*/
  }
}



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

#include "HistoManager.hh"
#include <vector>
#include <string>

HistoManager::HistoManager()
: fFileName("FilmTrack")
{
  Book();
}

HistoManager::~HistoManager()
{
  delete G4AnalysisManager::Instance();
}

void HistoManager::Book()
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetFileName(fFileName);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetActivation(true);  // enable inactivation of histograms

  // Define histograms start values
  const std::vector<std::string> id= { "0","1","2",    //0.1fs
                               "3","4","5",    //1fs 
                               "6","7","8",    //10fs 
                               "9","10","11",  //100fs
                               "12","13","14"};                     
  const std::vector<std::string> title=
                { "Electron Spectrum at 0.1fs","Density of electrons at 0.1fs","Edep Profile at 0.1fs",
                  "Electron Spectrum at 1fs","Density of electrons at 1fs","Edep Profile at 1fs",
                  "Electron Spectrum at 10fs","Density of electrons at 10fs","Edep Profile at 10fs",
                  "Electron Spectrum at 100fs","Density of electrons at 100fs","Edep Profile at 100fs",
                  "Secondary Electron Spectrum","Depth vs Stopping","Edep Profile"
                };
             
  G4int nbins = 100; G4double vmin = 0.; G4double vmax = 100.;
  for (G4int k=0; k<15; k++) {
  G4int ih = analysisManager->CreateH1("h"+id[k],title[k],nbins,vmin,vmax);
  analysisManager->SetH1Activation(ih, false);
  }

}

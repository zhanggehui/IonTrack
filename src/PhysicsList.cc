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

#include "PhysicsList.hh"
#include "PhysicsListMessenger.hh"

#include "G4EmDNAPhysics.hh"
#include "G4EmDNAPhysics_option2.hh"
#include "G4EmDNAPhysics_option4.hh"
#include "G4EmDNAPhysics_option6.hh"

#ifndef CLUSTER_JOB
#include "G4EmDNAPhysics_stationary.hh"
#include "G4EmDNAPhysics_stationary_option2.hh"
#include "G4EmDNAPhysics_stationary_option4.hh"
#include "G4EmDNAPhysics_stationary_option6.hh"
#endif

#include "StepMax.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4UserSpecialCuts.hh"
#include "G4ProcessManager.hh"

// particles
#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"
#include "G4DNAGenericIonsManager.hh"

PhysicsList::PhysicsList() : G4VModularPhysicsList()
{
  fMessenger = new PhysicsListMessenger(this);
  
  // EM physics
  fEmName="dna_opt2";
  fEmPhysicsList = new G4EmDNAPhysics_option2();

  SetDefaultCutValue(1*nm);  
  SetVerboseLevel(1);
}

PhysicsList::~PhysicsList()
{
  delete fMessenger;
  delete fEmPhysicsList;
}

void PhysicsList::ConstructParticle()
{
    G4BosonConstructor  pBosonConstructor;
    pBosonConstructor.ConstructParticle();

    G4LeptonConstructor pLeptonConstructor;
    pLeptonConstructor.ConstructParticle();

    G4MesonConstructor pMesonConstructor;
    pMesonConstructor.ConstructParticle();

    G4BaryonConstructor pBaryonConstructor;
    pBaryonConstructor.ConstructParticle();

    G4IonConstructor pIonConstructor;
    pIonConstructor.ConstructParticle();

    G4ShortLivedConstructor pShortLivedConstructor;
    pShortLivedConstructor.ConstructParticle();

    G4DNAGenericIonsManager* genericIonsManager;
    genericIonsManager=G4DNAGenericIonsManager::Instance();
    genericIonsManager->GetIon("alpha++");
    genericIonsManager->GetIon("alpha+");
    genericIonsManager->GetIon("helium");
    genericIonsManager->GetIon("hydrogen");  
}

void PhysicsList::ConstructProcess()
{
  AddTransportation();
  fEmPhysicsList->ConstructProcess(); 
  AddStepMax();     
}

void PhysicsList::AddStepMax()
{
  // Step limitation seen as a process
  StepMax* stepMaxProcess = new StepMax(fMessenger);

  auto particleIterator=GetParticleIterator();
  particleIterator->reset();
  while ((*particleIterator)()){
    G4ParticleDefinition* particle = particleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();

    if (stepMaxProcess->IsApplicable(*particle))
      {
        pmanager->AddDiscreteProcess(stepMaxProcess);
      }
  }
}

void PhysicsList::AddPhysicsList(const G4String& name)
{
  if (verboseLevel>-1) {
    G4cout << "PhysicsList::AddPhysicsList: <" << name << ">" << G4endl;
  }

  if (name == fEmName) {
    G4cout << "PhysicsList <" << name << "> is already chosen" << G4endl;
    G4cout << "There is no need to rebuild" << G4endl;
    return;
  }
  if (name == "dna") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmDNAPhysics();
  } 
  else if (name == "dna_opt2") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmDNAPhysics_option2();
  }
  else if (name == "dna_opt4") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmDNAPhysics_option4();
  }
  else if (name == "dna_opt6") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmDNAPhysics_option6();
  }
  #ifndef CLUSTER_JOB
  else if (name == "dna_stat") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmDNAPhysics_stationary();
  }
  else if (name == "dna_stat_opt2") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmDNAPhysics_stationary_option2();
  }
  else if (name == "dna_stat_opt4") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmDNAPhysics_stationary_option4();
  }
  else if (name == "dna_stat_opt6") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmDNAPhysics_stationary_option6();
  }
  #endif
  else {
    G4cout << "PhysicsList::AddPhysicsList: <" << name << ">"
           << " is not defined"
           << G4endl;
  }
}

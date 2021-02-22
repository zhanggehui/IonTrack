  G4VisManager* visManager = nullptr; 
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  if (ui) {
    visManager = new G4VisExecutive;
    visManager->Initialize();
    UImanager->ApplyCommand("/control/execute ../vis.mac");
    ui->SessionStart();
    delete ui;
  } 
  else {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }

  delete visManager;
  delete runManager;

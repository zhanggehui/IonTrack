  G4UIExecutive* ui = nullptr;
  if (argc == 1) ui = new G4UIExecutive(argc,argv);

  #ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
  #else
    G4RunManager* runManager = new G4RunManager;
  #endif

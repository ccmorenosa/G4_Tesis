// Geant 4.
#include "G4RunManager.hh"
#include "G4UImanager.hh"
// Visual Interface.
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

// Project Libraries.
#include "H4Detector.hpp"
#include "H4Actions.hpp"
#include "H4TrackingAction.hpp"
#include "H4RunAction.hpp"

int main(int argc, char *argv[]) {

  G4String aaa = "asd";
  G4String bbb = " qwerty";

  // Construct the default run manager.
  G4RunManager *run_manager = new G4RunManager;

  run_manager->SetVerboseLevel(0);

  //** Set mandatory initialization  classes.
  // Detector Geometry.
  run_manager->SetUserInitialization(new H4Detector);

  // Physics List.
  auto physicsList = new QGSP_BERT;
  run_manager->SetUserInitialization(physicsList);

  // Actions Initialization.
  run_manager->SetUserInitialization(new H4Actions);

  // Set actions.

  // Run Actions.
  run_manager->SetUserAction(new H4RunAction);

  // Tracking Actions.
  run_manager->SetUserAction(new H4TrackingAction);

  // Initialize Genat 4 kernel.
  run_manager->Initialize();

  // Get the current pointer to the UI manager and set the verbosities.
  G4UImanager *UI = G4UImanager::GetUIpointer();
  UI->ApplyCommand("/run/verbose 1");
  UI->ApplyCommand("/event/verbose 1");
  UI->ApplyCommand("/tracking/verbose 1");

  // Start a run.
  int number_of_events = 1;
  run_manager->BeamOn(number_of_events);

  // Get the pointer to the User Interface manager.
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if ( argc == 1 ) {
    // Initialize vis manager for vis commands.
    G4VisManager* vis_manager = new G4VisExecutive;
    vis_manager->Initialize();
    // interactive mode : define UI session.
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }
  else {
    // batch mode.
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }

  // Job termination.
  delete run_manager;
  return 0;
}

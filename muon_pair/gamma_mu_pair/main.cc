#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"
#include "RunAction.hh"
#include "TrackingAction.hh"

int main(int argc, char** argv)
{
    // Construct Run Manager
    auto runManager = new G4RunManager();

    // Mandatory initializations
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());

    // Optional explicit actions (if not inside ActionInitialization)
    runManager->SetUserAction(new RunAction());
    runManager->SetUserAction(new TrackingAction());

    runManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    // ===============================
    // BATCH MODE (no GUI)
    // ===============================
    if (argc > 1)
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }
    // ===============================
    // INTERACTIVE MODE (with GUI)
    // ===============================
    else
    {
        auto ui = new G4UIExecutive(argc, argv);

        auto visManager = new G4VisExecutive();
        visManager->Initialize();

        UImanager->ApplyCommand("/control/execute init_vis.mac");

        ui->SessionStart();

        delete visManager;
        delete ui;
    }

    delete runManager;

    return 0;
}

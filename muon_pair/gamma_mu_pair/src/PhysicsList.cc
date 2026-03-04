#include "PhysicsList.hh"

#include "G4EmStandardPhysics_option4.hh"
#include "G4DecayPhysics.hh"

#include "G4GammaConversionToMuons.hh"
#include "G4Gamma.hh"
#include "G4ProcessManager.hh"
#include "G4SystemOfUnits.hh"

MyPhysicsList::MyPhysicsList()
: G4VModularPhysicsList()
{
    G4cout << "=== PhysicsList: Gamma → Mu+Mu- mode ===" << G4endl;

    // EM physics only
    RegisterPhysics(new G4EmStandardPhysics_option4());

    // allow muon decay
    RegisterPhysics(new G4DecayPhysics());
}

MyPhysicsList::~MyPhysicsList()
{}

void MyPhysicsList::ConstructProcess()
{
    G4VModularPhysicsList::ConstructProcess();

    // Add gamma → mu pair conversion explicitly
    auto pManager = G4Gamma::Gamma()->GetProcessManager();

    auto gammaToMuMu = new G4GammaConversionToMuons();

    // MUST be 1.0 for physical results
    gammaToMuMu->SetCrossSecFactor(100000.0);

    pManager->AddDiscreteProcess(gammaToMuMu);

    G4cout << "GammaToMuMu process added." << G4endl;
}

void MyPhysicsList::SetCuts()
{
    //SetDefaultCutValue(0.7*mm);
}


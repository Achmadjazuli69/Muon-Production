#include "RunAction.hh"
#include "G4AnalysisManager.hh"

RunAction::RunAction()
: G4UserRunAction()
{}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run*)
{
    auto analysisManager = G4AnalysisManager::Instance();

    analysisManager->SetDefaultFileType("root");
    analysisManager->OpenFile("muons");

    analysisManager->CreateNtuple("muonTree", "Muon Production");

    analysisManager->CreateNtupleIColumn("eventID");
    analysisManager->CreateNtupleDColumn("energy");
    analysisManager->CreateNtupleDColumn("theta");
    analysisManager->CreateNtupleDColumn("x");
    analysisManager->CreateNtupleDColumn("y");
    analysisManager->CreateNtupleDColumn("z");
    analysisManager->CreateNtupleSColumn("creator");

    analysisManager->FinishNtuple();
}

void RunAction::EndOfRunAction(const G4Run*)
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}


#include "TrackingAction.hh"

#include "G4Track.hh"
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"

TrackingAction::TrackingAction()
: G4UserTrackingAction()
{}

TrackingAction::~TrackingAction()
{}

void TrackingAction::PreUserTrackingAction(const G4Track* track)
{
    auto particle = track->GetDefinition();

    if (particle == G4MuonPlus::MuonPlusDefinition() ||
        particle == G4MuonMinus::MuonMinusDefinition())
    {
        auto analysisManager = G4AnalysisManager::Instance();

        G4int eventID =
        G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

        G4double energy = track->GetKineticEnergy();
        G4double theta = track->GetMomentumDirection().theta();

        auto pos = track->GetVertexPosition();

        G4String creator = "primary";

        if(track->GetCreatorProcess())
            creator = track->GetCreatorProcess()->GetProcessName();

        analysisManager->FillNtupleIColumn(0, eventID);
        analysisManager->FillNtupleDColumn(1, energy);
        analysisManager->FillNtupleDColumn(2, theta);
        analysisManager->FillNtupleDColumn(3, pos.x());
        analysisManager->FillNtupleDColumn(4, pos.y());
        analysisManager->FillNtupleDColumn(5, pos.z());
        analysisManager->FillNtupleSColumn(6, creator);

        analysisManager->AddNtupleRow();
    }
}


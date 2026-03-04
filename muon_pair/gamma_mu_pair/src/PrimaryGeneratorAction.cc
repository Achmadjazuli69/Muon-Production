#include "PrimaryGeneratorAction.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction()
{
    // 1. Tentukan jumlah partikel per satu kali "tembak" (event)
    fParticleGun = new G4ParticleGun(1);

    // 2. Cari definisi partikel dari tabel partikel Geant4
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("e-");
 
    // 3. Set properti default 
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.)); // Arah sumbu Z
    fParticleGun->SetParticleEnergy(10.*GeV);
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -50. *cm)); // Mulai dari titik pusat
}

MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction()
{
    delete fParticleGun;
}

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    fParticleGun->GeneratePrimaryVertex(anEvent);
}

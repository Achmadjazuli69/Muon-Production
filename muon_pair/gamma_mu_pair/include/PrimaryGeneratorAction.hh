#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4Event;

class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    MyPrimaryGeneratorAction();
    ~MyPrimaryGeneratorAction() override;

    // Fungsi ini dipanggil setiap kali sebuah event (tembakan) dimulai
    void GeneratePrimaries(G4Event*) override;

private:
    G4ParticleGun* fParticleGun; // Objek "pistol" partikel
};

#endif

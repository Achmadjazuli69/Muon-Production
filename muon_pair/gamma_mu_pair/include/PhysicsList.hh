#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class MyPhysicsList : public G4VModularPhysicsList
{
public:

    // constructor
    MyPhysicsList();

    // destructor
    virtual ~MyPhysicsList();

    // override ConstructProcess
    virtual void ConstructProcess() override;

    // override SetCuts
    virtual void SetCuts() override;

};

#endif


#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"

MyActionInitialization::MyActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::Build() const
{
    // Daftarkan Primary Generator yang baru saja kita buat
    SetUserAction(new MyPrimaryGeneratorAction());
}

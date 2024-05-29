#ifndef Tracking_HH
#define Tracking_HH

#include "G4UserSteppingAction.hh"

class Tracking : public G4UserSteppingAction
{
public:
    Tracking();
    ~Tracking() override;

    virtual void UserSteppingAction(const G4Step *) override;

private:
};

#endif // EVENTACTION_HH

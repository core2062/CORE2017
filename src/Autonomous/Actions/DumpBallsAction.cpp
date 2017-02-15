#include "DumpBallsAction.h"
#include "Robot.h"

DumpBallsAction::DumpBallsAction(bool reset): m_reset(reset) {


}
void DumpBallsAction::actionInit(){
    //If we're trying to dump, make sure the hopper is down and flap is closed
    if (m_reset == false && Robot::hopperSubsystem->flapIsClosed() && Robot::hopperSubsystem->hopperIsDown()){
        return;
    }

    //Otherwise, if we are resetting, make sure hopper is up and the flap is open
    if (m_reset == true && Robot::hopperSubsystem->flapIsOpen() && Robot::hopperSubsystem->hopperIsUp()){
        return;
    }
    //TODO: Abort action
    cout << "Dump Balls action should be aborted: This code needs to be written";
}

COREAutonAction::actionStatus DumpBallsAction::action(){
    //If we're dumping, if hopper is up and flap is open, return end
    if (m_reset == false && Robot::hopperSubsystem->flapIsOpen() && Robot::hopperSubsystem->hopperIsUp()){
        return COREAutonAction::END;
    }

    //If we're resetting, if hopper is down and flap is closed, return end
    if (m_reset == true && Robot::hopperSubsystem->flapIsClosed() && Robot::hopperSubsystem->hopperIsDown()){
        return COREAutonAction::END;
    }
    //Otherwise continue
    return COREAutonAction::CONTINUE;
}

void DumpBallsAction::actionEnd() {
    COREAutonAction::actionEnd();
}
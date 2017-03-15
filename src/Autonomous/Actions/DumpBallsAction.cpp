#include "DumpBallsAction.h"
#include "Robot.h"

DumpBallsAction::DumpBallsAction(double dumpFlapTime) {

}

void DumpBallsAction::actionInit() {

}

COREAutonAction::actionStatus DumpBallsAction::action() {
	Robot->hopperSubsystem.openFlap();
	Robot->gearSubsystem.closeFlap();
	Robot->hopperSubsystem.setRequestedState(HopperSubsystem::DUMP);
	if(!Robot->hopperSubsystem.hopperIsUp()) {
		return COREAutonAction::CONTINUE;
	} else {
		return COREAutonAction::END;
	}
}

void DumpBallsAction::actionEnd() {
    COREAutonAction::actionEnd();
}

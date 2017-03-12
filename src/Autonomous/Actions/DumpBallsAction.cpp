#include "DumpBallsAction.h"
#include "Robot.h"

DumpBallsAction::DumpBallsAction(double dumpFlapTime) : m_dumpFlapTime(dumpFlapTime) {

}

void DumpBallsAction::actionInit() {
	m_timer.Reset();
	m_timer.Start();
}

COREAutonAction::actionStatus DumpBallsAction::action() {
	Robot->hopperSubsystem.openFlap();
	Robot->gearSubsystem.closeFlap();
	if(m_timer.Get() < m_dumpFlapTime) {
		return COREAutonAction::CONTINUE;
	}
	Robot->hopperSubsystem.setLiftTop();
	if(!Robot->hopperSubsystem.hopperIsUp()) {
		return COREAutonAction::CONTINUE;
	} else {
		return COREAutonAction::END;
	}
}

void DumpBallsAction::actionEnd() {
    COREAutonAction::actionEnd();
}

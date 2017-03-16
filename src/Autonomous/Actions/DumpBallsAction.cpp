#include "DumpBallsAction.h"
#include "Robot.h"

DumpBallsAction::DumpBallsAction(double waitTime) {
	m_waitTime = waitTime;
}

void DumpBallsAction::actionInit() {
	m_waitTimer.Reset();
	m_waitTimer.Stop();

}

COREAutonAction::actionStatus DumpBallsAction::action() {
	Robot->hopperSubsystem.openFlap();
	Robot->gearSubsystem.closeFlap();
	Robot->hopperSubsystem.setRequestedState(HopperSubsystem::DUMP);
	if(Robot->hopperSubsystem.hopperIsUp()) {
		if(m_waitTimer.Get() == 0.0){
			m_waitTimer.Start();
			std::cout << "Lift Is up, waiting: " << m_waitTime << " seconds" << std::endl;
		}
		if(m_waitTimer.Get() > m_waitTime){
			return COREAutonAction::END;
		}
	}

	return COREAutonAction::CONTINUE;
}

void DumpBallsAction::actionEnd() {
	m_waitTimer.Reset();
	m_waitTimer.Stop();
    COREAutonAction::actionEnd();
}

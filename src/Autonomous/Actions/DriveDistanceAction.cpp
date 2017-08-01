#include "DriveDistanceAction.h"
#include "Robot.h"
#include "CORERobotLib.h"

DriveDistanceAction::DriveDistanceAction(double speedInFraction, double distanceInInches) {
	m_speedInFraction = speedInFraction;
	m_distanceInInches = distanceInInches;
}
    void DriveDistanceAction::actionInit() {
        //driveMotorFR.CANTalonController->SetEncPosition(0);
        Robot->driveSubsystem.resetEncoders(DriveSide::BOTH);
        m_initTime.Reset();
        m_initTime.Start();

        Robot->driveSubsystem.teleopInit();

    }
    COREAutonAction::actionStatus DriveDistanceAction::action() {
    	//How far have we gone since the reset?
    	std::pair<double, double> dists = {2.0,3.0}/*Robot->driveSubsystem.getEncoderInches()*/;
    	double averDist = (fabs(dists.first) + fabs(dists.second)) * .5;
    	//Is this less than how far we were supposed to go?
    	if (averDist < m_distanceInInches || m_initTime.Get() < .1) {
    		//If yes, set motors to appropriate speed, return CONTINUE.
    		Robot->driveSubsystem.m_swerveDrive.tank(-1, -1);
    		return COREAutonAction::CONTINUE;

    	}else{
        	//If no, set motors to zero, return END.
    		Robot->driveSubsystem.m_swerveDrive.tank(0, 0);
    		//Robot->driveSubsystem.setMotorSpeed(0, DriveSide::BOTH);
    		return COREAutonAction::END;

    	}

    	// PLACEHOLDER
    	return COREAutonAction::END;
    }

    void DriveDistanceAction::actionEnd() {
    	Robot->driveSubsystem.m_swerveDrive.tank(0, 0);
    }


//        if(abs(driveMotorFR.m_CANTalonController->GetEncPosition()) < 10000) {
//        	Robot::CORERobot::CORESubsystem
//            return actionStatus::CONTINUE;
//        } else {
//        	//driveMotorFR.Set(0);
//        	//driveMotorFL.Set(0);
//        	//driveMotorBR.Set(0);
//        	//driveMotorBL.Set(0);
//            return actionStatus::END;
//        }
//    }

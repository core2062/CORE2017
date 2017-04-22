#include "DriveHybridController.h"
#include "Robot.h"

DriveHybridController::DriveHybridController() : COREController(){
}

void DriveHybridController::robotInitTask() {
	 Robot->driverJoystick.registerButton(COREJoystick::LEFT_BUTTON);
	 Robot->driverJoystick.registerAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
	 Robot->driverJoystick.registerAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_X);
	 Robot->driverJoystick.registerButton(CORE::COREJoystick::START_BUTTON);
	 Robot->driverJoystick.registerButton(CORE::COREJoystick::BACK_BUTTON);
}

void DriveHybridController::enabledLoop() {
	SmartDashboard::PutNumber("Gyro Yaw", Robot->driveSubsystem.getGyroAngle().getDegrees());
	std::pair<double, double> vels = Robot->driveSubsystem.getEncoderSpeed();
	SmartDashboard::PutNumber("Left Speed", vels.first);
	SmartDashboard::PutNumber("Right Speed", vels.second);

	if(Robot->driverJoystick.getRisingEdge(COREJoystick::START_BUTTON)){
		Robot->driveSubsystem.hardResetYaw();
	}

	if(Robot->driverJoystick.getRisingEdge(COREJoystick::BACK_BUTTON)){
		if(m_hybrid){
			if(m_pursuit){
				delete m_pursuit;
			}
			if(m_frame){
				delete m_frame;
			}
			m_frame = nullptr;
			m_pursuit = nullptr;
			m_hybrid = false;
			Robot->visionSubsystem.visionTable->PutBoolean("disablePegVision", true);
			Robot->visionSubsystem.visionTable->PutBoolean("disableVision", true);
		} else {
			Robot->visionSubsystem.visionTable->PutBoolean("disablePegVision", false);
			Robot->visionSubsystem.visionTable->PutBoolean("disableVision", false);
			m_hybrid = true;
			m_frame = nullptr;
			m_pursuit = nullptr;
			m_visionTimer.Reset();
			m_visionTimer.Start();
			Robot->driveSubsystem.setLowGear();
		}
	}

	if(!m_hybrid){
		if(Robot->driverJoystick.getRisingEdge(COREJoystick::LEFT_BUTTON)){
			if(Robot->driveSubsystem.getHighGear()){
				Robot->driveSubsystem.setLowGear();
			} else {
				Robot->driveSubsystem.setHighGear();
			}
		}

		double mag = -Robot->driverJoystick.getAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
		double rot = Robot->driverJoystick.getAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_X);

		if(Robot->driverJoystick.getButton(CORE::COREJoystick::RIGHT_BUTTON)){
			mag *=.5;
			rot *=.5;
		}

		VelocityPair speeds = COREEtherDrive::calculate(mag, rot, .1);
		Robot->driveSubsystem.setMotorSpeed(speeds.left, speeds.right);
	} else {
		if(m_visionTimer.Get() > .25){
			if(!m_pursuit){
				Robot->visionSubsystem.calculatePath();
				m_pursuit = new AdaptivePursuit(24, 150, .025, *Robot->visionSubsystem.getPath(), true, .25, true);
				m_frame = Robot->visionSubsystem.getFrame();
			}
			if(m_pursuit){
				Position2d pos;
				pos = m_frame->getLatest();

				Position2d::Delta command = m_pursuit->update(pos, Timer::GetFPGATimestamp());
				VelocityPair setpoint = TankKinematics::inverseKinematics(command);
				double maxVel = 0.0;
				maxVel = max(maxVel, setpoint.left);
				maxVel = max(maxVel, setpoint.right);
				if (maxVel > 100){
					double scaling = 100 / maxVel;
					setpoint = VelocityPair(setpoint.left * scaling, setpoint.right * scaling);
				}
				Robot->driveSubsystem.setMotorSpeed(setpoint.left * .01, setpoint.right * .01);

				if(m_pursuit->isDone()){
					Robot->driveSubsystem.setMotorSpeed(0,0);
					Robot->gearSubsystem.placeGear();
					if(m_pursuit){
						delete m_pursuit;
					}
					if(m_frame){
						delete m_frame;
					}
					m_frame = nullptr;
					m_pursuit = nullptr;
					m_hybrid = false;
					Robot->visionSubsystem.visionTable->PutBoolean("disablePegVision", true);
					Robot->visionSubsystem.visionTable->PutBoolean("disableVision", true);
				}
			}
		}
	}
}


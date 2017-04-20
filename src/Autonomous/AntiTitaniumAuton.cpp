#include "AntiTitaniumAuton.h"
#include "Robot.h"
#include "Actions.h"
#include "AutonPaths.h"

AntiTitaniumAuton::AntiTitaniumAuton() :
	COREAuton("Def Legal Auton", 0.0){
}

void AntiTitaniumAuton::addNodes() {
	if(SmartDashboard::GetNumber("TurnTest", -500) == -500){
		SmartDashboard::PutNumber("TurnTest", 0);
	}
//	m_setHighGearPosition = new Node(10, new VisionAlignGearAction(100,true,false));
	m_setHighGearPosition = new Node(10, new DriveShiftAction(GearPosition::HIGH_GEAR));
	m_goToTheOppositeSideOfTheField = new Node(10, new TurnAngleAction(Rotation2d::fromDegrees(SmartDashboard::GetNumber("TurnTest", 0)), 10));
//	m_goToTheOppositeSideOfTheField = new Node(10, new DriveWaypointAction(	PathLoader::loadPath("def_legal.csv", 1.0,
//			(CORERobot::getAlliance() == CORERobot::RED)), true, .25, 99999));
	//TODO Add actual values to the DriveDistanceAction
	addFirstNode(m_setHighGearPosition);
	m_setHighGearPosition->addNext(m_goToTheOppositeSideOfTheField);


}

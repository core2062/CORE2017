#include "AntiTitaniumAuton.h"
#include "Robot.h"
#include "Actions.h"
#include "AutonPaths.h"

AntiTitaniumAuton::AntiTitaniumAuton() :
	COREAuton("High Goal Hopper Auton", 0.0){

}

void AntiTitaniumAuton::addNodes() {
	m_setHighGearPosition = new Node(10, new DriveShiftAction(GearPosition::HIGH_GEAR));
	m_goToTheOppositeSideOfTheField = new Node(10, new DriveDistanceAction(1.0, 30.0, true));
	//TODO Add actual values to the DriveDistanceAction
	addFirstNode(m_setHighGearPosition);
	m_setHighGearPosition->addNext(m_goToTheOppositeSideOfTheField);


}

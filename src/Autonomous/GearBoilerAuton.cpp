//#include "GearBoilerAuton.h"
//#include "Actions.h"
//#include "Robot.h"
//
//GearBoilerAuton::GearBoilerAuton() :
//		COREAuton("Gear and Boiler Auton", &m_driveToPeg, true),
//		m_driveToPeg(new DriveWaypointAction(getPathForPeg(Robot->getStartingPosition()))),
//		m_loadGearOnPeg(new LoadGearOntoPegAction()),
//		m_backupFromPeg(new DriveWaypointAction(backupFromPeg())),
//		m_driveToBoiler(new DriveWaypointAction(getPathForBoiler())),
//		m_dumpBallsInBoiler(new DumpBallsAction(false)),
//		m_shimmyHopper(new ShimmyAction(0.0, 0.0)),
//		m_resetHopper(new DumpBallsAction(true)){
//
//
//}
//
//void GearBoilerAuton::addNodes() {
//	m_driveToPeg.addNext(&m_loadGearOnPeg);
//	m_loadGearOnPeg.addNext(&m_backupFromPeg);
//	m_backupFromPeg.addNext(&m_driveToBoiler);
//	m_driveToBoiler.addNext(&m_dumpBallsInBoiler);
//	m_dumpBallsInBoiler.addNext(&m_shimmyHopper);
//	m_shimmyHopper.addNext(&m_resetHopper);
//}
//
//Path* GearBoilerAuton::getPathForPeg(StartingPosition startingPosition) {
//	return new Path({{{0,0},0}, {{1,1},1}});
//		//TODO: Replace with code that reads the path from the csv file
//}
//
//Path* GearBoilerAuton::backupFromPeg() {
//	return new Path({{{0,0},0}, {{1,1},1}});
//}
//
//Path* GearBoilerAuton::getPathForBoiler(StartingPosition startingPosition) {
//}

#include "DumpBallsAuton.h"
#include "Actions/DumpBalls.h"
#include "Robot.h"

DumpBallsAuton::DumpBallsAuton(bool reset) : COREAuton("Dump Balls", new Node(&m_dumpBalls), true), m_dumpBalls(reset) {

}

void DumpBallsAuton::addNodes() {

}

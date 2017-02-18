#pragma once

#include "CORERobotLib.h"

using namespace CORE;

class LoadGearOntoPegAuton : public COREAutonAction {
public:
    LoadGearOntoPegAuton();
    void actionInit() override;
	COREAutonAction::actionStatus action() override;
	void actionEnd() override;
private:
	bool m_punchIsOut;

};

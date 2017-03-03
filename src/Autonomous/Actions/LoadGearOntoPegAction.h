#pragma once

#include "CORERobotLib.h"

using namespace CORE;

class LoadGearOntoPegAction : public COREAutonAction {
public:
    LoadGearOntoPegAction();
    void actionInit() override;
	COREAutonAction::actionStatus action() override;
	void actionEnd() override;
private:
	bool m_punchIsOut;

};

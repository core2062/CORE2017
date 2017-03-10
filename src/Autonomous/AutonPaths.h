#pragma once

class AutonPaths{
public:
	static Path * getForwardPegPath();
	static Path * getForwardBoilerPath();
	static Path * getForwardHopperPath();
	static Path * getReversePegPath();
	static Path * getReverseBoilerPath();
	static Path * getReverseHopperPath();
};

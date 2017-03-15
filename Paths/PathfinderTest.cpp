// PathfinderTest.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "pathfinder.h"


int main()
{
	/*
	Waypoint points[]{
		//{-30,105,d2r(180)},
		{-125,205,d2r(-120)},
		{-39, 283.5,d2r(-135)}

		Waypoint points[]{
		//{-30,105,d2r(180)},
		{ -100,162,d2r(180) },
		{ -41, 286.5,d2r(-135) }
		};
	};
	*/

	Waypoint points[]{
		{-30,326,d2r(180)},
		{ -123,205,d2r(-120) }
		//{ -41, 286.5,d2r(-135) }
	};

	int num = 0;
	for (auto i : points) {
		num++;
	}
	num = 2;

	TrajectoryCandidate candidate;
	pathfinder_prepare(points, num, FIT_HERMITE_CUBIC, PATHFINDER_SAMPLES_HIGH, .25, 100, 50, 100, &candidate);
	
	int length = candidate.length;

	std::vector<Segment> trajectory;
	trajectory.resize(length);

	pathfinder_generate(&candidate, &trajectory[0]);

	std::cout << "There are " << trajectory.size() << " points" << std::endl;

	std::string folder = "C:/Users/Joshua/Documents/FRC2017 Code/Paths/";
	std::string name = "gearAuton_forward_boiler.csv";

	std::ofstream outFile(folder+name);
	if (outFile.is_open()) {
		for (unsigned int i = 0; i < length-1; ++i) {
			outFile << trajectory[i].x << "," << trajectory[i].y << "," << 100 << "\r\n";
		}
		std::cout << "Done" << std::endl;
	}
	else {
		std::cout << "Fail to Open" << std::endl;
	}
	outFile.close();


	while (true);
	return 0;
}


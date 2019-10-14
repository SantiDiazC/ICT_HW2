#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <cmath>

#include "fuzzy.hpp"
#include "control.hpp"

int main()
{

	double timeStep=0.05;
	Control control(4, timeStep);
	std::vector<double> a = {1.0, -2.856 , 2.717, -0.861};
	std::vector<double> b = {0.0, 0.0, 2.3136e-4, 9.28e-7};

	//////////////////////////////////////////////////////
	// Use plausibility measure xi=0.75, belief measure xi=0.25, respectively. 
	Fuzzy::xi = 0.8;
	Fuzzy::preference = {1,10,5};
//	Fuzzy::preference = {5,1,10};
//	Fuzzy::preference = {10,5,1};
	//////////////////////////////////////////////////////
	
	control.setA(a);
	control.setB(b);

	std::fstream fileout("flc.txt", std::ios::out);

	//////////////////////////////////////////////////////
	// Use the parameters you used in HW#1.
	//double Ke = 1.886226, Kce = 1.8875, Ku = 1.051013;
    double Ke = 1.529, Kce = 1.587, Ku = 3.202;
	/////////////////////////////////////////////////////

	double yout = 0.0;
	double target = 1.0;
	control.setTarget(target);

	int maxTimeStep = 500;
	for (int t=0; t<maxTimeStep; t++) {

		control.FLC(Ke, Kce, Ku);
		yout = control.motor();
		control.delay(yout);

		std::cout << yout << std::endl;
		fileout << yout << std::endl;
	}

	fileout.close();
	return 0;
}

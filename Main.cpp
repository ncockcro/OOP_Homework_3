/**
\class Main

\brief Main entry point of the application

This class holds the main entry point into the application for the
Coyote vs. Roadrunner simulation. In main, it simple creates an instance
of the Simulation class and called the "MainGame" method to start the
simiulation.

*/

#include "Simulation.h"

int main() {

	Simulation sim;

	sim.MainGame();
	return 0;
}
/**
\class Simulation

\brief Main running of the Roadrunner vs. Coyote simulator

This class defines how the simulation will run by prompting the user
for how big the board should be, and how many roadrunners and coyotes
will initially spawn in. Once those parameters are set, the simulator
will be set up and cycle through the total numbers of agents and
pick a play for them to either move, breed, or die depending on
what is going on with each individual agent.

*/

#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "Agent.h"
#include "Coyote.h"
#include "Roadrunner.h"

using namespace std;

class Simulation
{
public:
	Simulation();
	~Simulation();
	void MainGame();

private:
	
	void GetStartingInfo();
	void PrintBoard();
	void TrimStartingAgents();
	void CreateStartingAgents();
	void PlotAgentsToBoard();
	void RemoveAgent(Coordinates a_coord);
	void DeleteAgents();
	void SaveBreed(Agent* a_agent);
	void Breed();
	bool GameIsOver();
	bool AllRoadrunners();
	bool EmptyBoard();
	void SaveAgentCounts();
	bool IsDigits(string &a_input);

	int m_length;
	int m_width;
	int m_coyotes;
	int m_roadrunners;
	int m_cycles;
	vector< vector<char>> m_board;
	vector<Agent*> m_agents;
	vector<Agent> m_coordinatesForBreeding;
	vector<int> m_needDeleting;

	vector<int> m_coyoteCounts;
	vector<int>m_roadrunnerCounts;
	bool m_allRoadrunnerEnd;
	bool m_emptyBoardEnd;
	
};

#endif
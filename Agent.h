/**
\class Coyote

\brief Specifications for a Coyote agent

This class inherits from the "Agent" class and provides further specification and
functionality for how a Coyote works. It specifices its movement, if it can
breed, and if it is dead.

*/

#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

struct Coordinates {
	int m_width;
	int m_length;
};
class Agent
{
public:
	Agent();

	char GetAgentLetter();
	virtual void Move(vector< vector<char> > &a_board);
	void SetPosition(int a_width, int a_length);
	Coordinates GetPosition();
	Coordinates GetCoordinateToMoveTo();
	virtual bool CanBreed();
	vector<Coordinates> GetSurroundingPositions(int a_widthSize, int a_lengthSize);
	vector<Coordinates> GetEmptySpots(const vector< vector<char> > &a_board, vector<Coordinates> a_validSpots);
	virtual bool IsDead();

protected:
	vector<Coordinates> GetSurroundingPositions(int a_widthSize, int a_lengthSize, Coordinates a_coordinates);
	vector<Coordinates> GetOtherAgentSpots(const vector< vector<char> > &a_board, vector<Coordinates> a_validSpots, char a_oppositeAgent);
	Coordinates PickRandomSpot(vector<Coordinates> a_spots);
	vector<Coordinates> GetCommonSpots(vector<Coordinates> a_agent1, vector<Coordinates> a_agent2);

	char m_agentLetter;
	Coordinates m_coordinates;
	Coordinates m_coordinateToMoveTo;
	int breedCounter;
	int dieCounter;
};

#endif
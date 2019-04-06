#include "Agent.h"

/**

	This function is the default constructor for the
	Agent class. It initializes any variables for
	the Agent class.

	@return none
	*/
Agent::Agent()
{
	srand((unsigned int)time(0));

	breedCounter = 0;
	dieCounter = 0;
}

/**

	This function returns the letter that represents
	a Coyote or a Roadrunner, either a 'c' or 'r'.

	@return char
	*/
char Agent::GetAgentLetter() {
	return m_agentLetter;
}

/**

	This function is a virtual function for the Move operation that
	each of the agents have. The actual functionality for this function
	is defined in the classes that derive from the Agent class.

	@param a_board, the current board with all of the characters on it
	@return void
	*/
void Agent::Move(vector< vector<char> > &a_board) {

}

/**

	This function accepts two parameters which are the width
	and length for a position and sets it to an Agent's
	current position.

	@param a_width, the width position
	@param a_length, the length position
	@return void
	*/
void Agent::SetPosition(int a_width, int a_length) {

	m_coordinates.m_width = a_width;
	m_coordinates.m_length = a_length;
}

/**

	This function returns the current position an Agent is at.

	@return Coordinates
	*/
Coordinates Agent::GetPosition() {
	return m_coordinates;
}

/**

	This function returns all of the surrounding, valid points
	around a particular agent. It first gathers all of the 8 potential
	points around an agent, and then uses the board's width and length
	to see which one of the points are actually on the board. Then the function
	will return a vector of those valid points.

	@param a_widthSize, width size of the board
	@param a_lengthSize, length size of the board
	@return vector<Coordinates>
	*/
vector<Coordinates> Agent::GetSurroundingPositions(int a_widthSize, int a_lengthSize) {

	vector<Coordinates> surroundingPoints;
	Coordinates tempCoordinates;
	vector<Coordinates> validPoints;

	// Point above
	tempCoordinates.m_width = m_coordinates.m_width - 1;
	tempCoordinates.m_length = m_coordinates.m_length;
	surroundingPoints.push_back(tempCoordinates);

	// Point below
	tempCoordinates.m_width = m_coordinates.m_width + 1;
	tempCoordinates.m_length = m_coordinates.m_length;
	surroundingPoints.push_back(tempCoordinates);

	// Point to the left 
	tempCoordinates.m_width = m_coordinates.m_width;
	tempCoordinates.m_length = m_coordinates.m_length - 1;
	surroundingPoints.push_back(tempCoordinates);

	// Point to the right
	tempCoordinates.m_width = m_coordinates.m_width;
	tempCoordinates.m_length = m_coordinates.m_length + 1;
	surroundingPoints.push_back(tempCoordinates);

	// Point to the upper left diagnol
	tempCoordinates.m_width = m_coordinates.m_width - 1;
	tempCoordinates.m_length = m_coordinates.m_length - 1;
	surroundingPoints.push_back(tempCoordinates);

	// Point to the lower right diagnol
	tempCoordinates.m_width = m_coordinates.m_width + 1;
	tempCoordinates.m_length = m_coordinates.m_length + 1;
	surroundingPoints.push_back(tempCoordinates);

	// Point to lower left diagnol
	tempCoordinates.m_width = m_coordinates.m_width + 1;
	tempCoordinates.m_length = m_coordinates.m_length - 1;
	surroundingPoints.push_back(tempCoordinates);

	// Point to upper right diagnol
	tempCoordinates.m_width = m_coordinates.m_width - 1;
	tempCoordinates.m_length = m_coordinates.m_length + 1;
	surroundingPoints.push_back(tempCoordinates);

	for (size_t i = 0; i < surroundingPoints.size(); i++) {
		if (surroundingPoints[i].m_width < a_widthSize && surroundingPoints[i].m_width >= 0 && surroundingPoints[i].m_length < a_lengthSize && surroundingPoints[i].m_length >= 0) {
			validPoints.push_back(surroundingPoints[i]);
		}
	}

	return validPoints;
}

/**

	This function is overloaded and has similar functionality to the
	other function but this takes an additional parameter which is
	a pair of coordinates. This function differs as it will find all
	of the surrounding points around the coordinates passed in where
	as the other function looked for all of the surrounding positions
	based on if they were valid from the board.

	@param a_widthSize, the width size of the board
	@param a_lengthSize, the length size of the board
	@param a_coordinates, a pair of coordinates to get the surrounding points from
	@return vector<Coordinates>
	*/
vector<Coordinates> Agent::GetSurroundingPositions(int a_widthSize, int a_lengthSize, Coordinates a_coordinates) {

	vector<Coordinates> surroundingPoints;
	Coordinates tempCoordinates;
	vector<Coordinates> validPoints;

	// Point above
	tempCoordinates.m_width = a_coordinates.m_width - 1;
	tempCoordinates.m_length = a_coordinates.m_length;
	surroundingPoints.push_back(tempCoordinates);

	// Point below
	tempCoordinates.m_width = a_coordinates.m_width + 1;
	tempCoordinates.m_length = a_coordinates.m_length;
	surroundingPoints.push_back(tempCoordinates);

	// Point to the left 
	tempCoordinates.m_width = a_coordinates.m_width;
	tempCoordinates.m_length = a_coordinates.m_length - 1;
	surroundingPoints.push_back(tempCoordinates);

	// Point to the right
	tempCoordinates.m_width = a_coordinates.m_width;
	tempCoordinates.m_length = a_coordinates.m_length + 1;
	surroundingPoints.push_back(tempCoordinates);

	// Point to the upper left diagnol
	tempCoordinates.m_width = a_coordinates.m_width - 1;
	tempCoordinates.m_length = a_coordinates.m_length - 1;
	surroundingPoints.push_back(tempCoordinates);

	// Point to the lower right diagnol
	tempCoordinates.m_width = a_coordinates.m_width + 1;
	tempCoordinates.m_length = a_coordinates.m_length + 1;
	surroundingPoints.push_back(tempCoordinates);

	// Point to lower left diagnol
	tempCoordinates.m_width = a_coordinates.m_width + 1;
	tempCoordinates.m_length = a_coordinates.m_length - 1;
	surroundingPoints.push_back(tempCoordinates);

	// Point to upper right diagnol
	tempCoordinates.m_width = a_coordinates.m_width - 1;
	tempCoordinates.m_length = a_coordinates.m_length + 1;
	surroundingPoints.push_back(tempCoordinates);

	for (size_t i = 0; i < surroundingPoints.size(); i++) {
		if (surroundingPoints[i].m_width < a_widthSize && surroundingPoints[i].m_width >= 0 && surroundingPoints[i].m_length < a_lengthSize && surroundingPoints[i].m_length >= 0) {
			validPoints.push_back(surroundingPoints[i]);
		}
	}


	return validPoints;
}

/**

	This function will cycle through the vector of valid spots and return all
	of those spots that contain the agent letter that was passed in.

	@param a_board, the current board with all of the characters on it
	@param a_validSpots, valid positions an agent can travel to
	@param, a_oppositeAgent, the character of the opposite agent's letter
	@return vector<Coordinates>
	*/
vector<Coordinates> Agent::GetOtherAgentSpots(const vector< vector<char> > &a_board, vector<Coordinates> a_validSpots, char a_oppositeAgent) {

	vector<Coordinates> otherAgentSpots;
	for (size_t i = 0; i < a_validSpots.size(); i++) {
		if (a_board[a_validSpots[i].m_width][a_validSpots[i].m_length] == a_oppositeAgent) {
			otherAgentSpots.push_back(a_validSpots[i]);
		}
	}

	return otherAgentSpots;
}

/**

	This function returns the coordinates that an agent is going
	to move to.

	@return Coordinates
	*/
Coordinates Agent::GetCoordinateToMoveTo() {
	return m_coordinateToMoveTo;
}

/**

	This function will randomly select a coordinate position
	from a vector of coordinates.

	@param a_spots, a vector of coordinates to pick from
	@return Coordinates
	*/
Coordinates Agent::PickRandomSpot(vector<Coordinates> a_spots) {
	int randomNum = rand() % a_spots.size();

	return a_spots[randomNum];
}

/**

	This function gets all of the empty spots from a list of valid
	spots an agent can travel to. It cycles through the valid spots
	vector and if the spot has a '0' on the board, it adds it to a new
	vector that will be returned with coordinates of the empty spots.

	@param a_board, the current board with all of the characters on it
	@param a_validSpots, spots an agent can travel to
	@return vector<Coordinates> 
	*/
vector<Coordinates> Agent::GetEmptySpots(const vector< vector<char> > &a_board, vector<Coordinates> a_validSpots) {

	vector<Coordinates> emptySpots;
	for (size_t i = 0; i < a_validSpots.size(); i++) {
		if (a_board[a_validSpots[i].m_width][a_validSpots[i].m_length] == '0') {
			emptySpots.push_back(a_validSpots[i]);
		}
	}

	return emptySpots;
}

/**

	This function takes in two agents with a vector of coordinates
	with all of the valid locations on the board they can travel to.
	Then, it cycles through both of the vectors and finds any spots
	that they have in common and adds them to a new vector to be 
	returned.

	@param a_agent1, the first agent's valid spots comparing with
	@param a_agent2, the second agent's valid spots comparing with
	@return vector<Coordinates>
	*/
vector<Coordinates> Agent::GetCommonSpots(vector<Coordinates> a_agent1, vector<Coordinates> a_agent2) {

	vector<Coordinates> commonSpots;

	for (size_t i = 0; i < a_agent1.size(); i++) {
		for (size_t j = 0; j < a_agent2.size(); j++) {
			if (a_agent1[i].m_width == a_agent2[j].m_width && a_agent1[i].m_length == a_agent2[j].m_length) {
				commonSpots.push_back(a_agent1[i]);
			}
		}
	}

	return commonSpots;
}

/**

	This function is virtual and determines if an agent can breed or
	not. It is further defined in the derived classes.

	@return bool
	*/
bool Agent::CanBreed() {
	return false;
}

/**

	This function is virtual and determines if an agent is dead or
	not. It is further defined in the derived class.

	@return bool
	*/
bool Agent::IsDead() {
	return false;
}
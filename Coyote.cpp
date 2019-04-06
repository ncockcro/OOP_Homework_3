#include "Coyote.h"

/**

	This function is the default constructor for the Coyote class.
	It initializes any of the variables used in the class.

	@param a_entry entry to be added to a set
	@return none
	*/
Coyote::Coyote()
{
	dieCounter = 0;
	m_agentLetter = 'c';
	breedCounter = 0;
}

/**

	This function contains the functionality for how a Coyote moves in
	the simulation. Similar to the Roadrunner, it first gets all of the
	valid locations the Coyote can move to. Then, it checks to see if any
	Roadrunners are close by for the Coyote to eat. If there are, go to
	a Roadrunner's location and eat them, otherwise, go to a random
	location. If there are no available locations, the Coyote will stay where
	it is at.

	@param a_board, the current board with all of the characters on it
	@return void
	*/
void Coyote::Move(vector< vector<char> > &a_board) {

	vector<Coordinates> validSpots = GetSurroundingPositions(a_board.size(), a_board[0].size());
	vector<Coordinates> emptySpots;
	vector<Coordinates> roadrunnerSpots;
	vector<Coordinates> validSpotsByRoadrunner;
	vector<Coordinates> emptySpotsByRoadrunner;
	vector<Coordinates> foodSpots;
	bool isFood = false;
	bool captureSpot = false;

	// Gets the spots around the roadrunner that has a coyote in it
	roadrunnerSpots = GetOtherAgentSpots(a_board, validSpots, 'r');

	// If there are any spots with a roadrunner nearby, the coyote will go and eat the roadrunner
	for (size_t i = 0; i < roadrunnerSpots.size(); i++) {
		m_coordinateToMoveTo = roadrunnerSpots[i];
		breedCounter++;
		return;
	}

	// Gets the locations that coyotes can travel to
	for (size_t i = 0; i < roadrunnerSpots.size(); i++) {
		validSpotsByRoadrunner = GetSurroundingPositions(a_board.size(), a_board[0].size(), roadrunnerSpots[i]);
	}

	// Getting the empty spots surrounding the roadrunner that are valid
	emptySpots = GetEmptySpots(a_board, validSpots);

	emptySpotsByRoadrunner = GetEmptySpots(a_board, validSpotsByRoadrunner);

	// Cycling through the empty spots between the roadrunner and nearby coyotes and get a list of the spots where
	// if the roadrunner moved to it, it would get eaten!
	foodSpots = GetCommonSpots(emptySpots, emptySpotsByRoadrunner);

	// Cylce through the empty spots and the 
	for (size_t i = 0; i < emptySpots.size(); i++) {
		for (size_t j = 0; j < foodSpots.size(); j++) {
			if (emptySpots[i].m_width == foodSpots[j].m_width && emptySpots[i].m_length == foodSpots[j].m_length) {
				isFood = true;
			}
		}

		if (isFood) {
			m_coordinateToMoveTo = emptySpots[i];
			captureSpot = true;
			break;
		}
	}

	// Pick a random spot if they can't capture
	if (!captureSpot && emptySpots.size() != 0) {
		m_coordinateToMoveTo = PickRandomSpot(emptySpots);
	}
	// If they can't capture and there are no empty spots, stay in the same position
	else if (!captureSpot && emptySpots.size() == 0) {
		m_coordinateToMoveTo = m_coordinates;
	}

	breedCounter++;
	dieCounter++;

}

/**

	This function checks if a Coyote can breed or not.
	Once the breed counter reaches 8, the function will
	return true and reset the counter to 0. Otherwise,
	the function will return false.

	@return bool
	*/
bool Coyote::CanBreed() {

	if (breedCounter == 8) {
		breedCounter = 0;
		return true;
	}
	else {
		return false;
	}
}

/**

	This function checks if a coyote dies or not. If the
	dieCounter is greater than 4, return true because the
	Coyote went 4 moves without eating a Roadrunner. Otherwise,
	the function will return false because it isn't dead.

	@return bool
	*/
bool Coyote::IsDead() {
	if (dieCounter >= 4) {
		return true;
	}
	else {
		return false;
	}
}
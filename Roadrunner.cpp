#include "Roadrunner.h"

/**

	This function is the default constructor for the Roadrunner class. It
	simply initializes any variables used in the class to default values.

	@return none
	*/
Roadrunner::Roadrunner()
{
	m_agentLetter = 'r';
	breedCounter = 0;
}

/**

	This function handles how a Roadrunner should move on a board. It first,
	gets the spots all around the Roadrunner's current position that the 
	Roadrunner could move to, spots with a '0' in it. Then it checks out of
	those valid spots, which ones have a coyote in it. If there is a Coyote
	in a nearby spot, the Roadrunner will try and move away from it, if there
	are no coyotes, it will pick a random spot around it, and if there are no
	spots to move, the roadrunner will stay in the same spot.

	@param a_board, the current board with all of the characters on it
	@return void
	*/
void Roadrunner::Move(vector< vector<char> > &a_board) {

	vector<Coordinates> validSpots = GetSurroundingPositions(a_board.size(), a_board[0].size());
	vector<Coordinates> emptySpots;
	vector<Coordinates> coyoteSpots;
	vector<Coordinates> validSpotsByCoyote;
	vector<Coordinates> emptySpotsByCoyote;
	vector<Coordinates> dangerSpots;
	bool isDanger = false;
	bool safeSpot = false;

	// Gets the spots around the roadrunner that has a coyote in it
	coyoteSpots = GetOtherAgentSpots(a_board, validSpots, 'c');

	// Gets the locations that coyotes can travel to
	for (size_t i = 0; i < coyoteSpots.size(); i++) {
		validSpotsByCoyote = GetSurroundingPositions(a_board.size(), a_board[0].size(), coyoteSpots[i]);
	}

	// Getting the empty spots surrounding the roadrunner that are valid
	emptySpots = GetEmptySpots(a_board, validSpots);

	emptySpotsByCoyote = GetEmptySpots(a_board, validSpotsByCoyote);

	// Cycling through the empty spots between the roadrunner and nearby coyotes and get a list of the spots where
	// if the roadrunner moved to it, it would get eaten!
	dangerSpots = GetCommonSpots(emptySpots, emptySpotsByCoyote); 
	
	// Cylce through the empty spots and the 
	for (size_t i = 0; i < emptySpots.size(); i++) {
		for (size_t j = 0; j < dangerSpots.size(); j++) {
			if (emptySpots[i].m_width == dangerSpots[j].m_width && emptySpots[i].m_length == dangerSpots[j].m_length) {
				isDanger = true;
			}
		}

		if (isDanger) {
			isDanger = false;
		}
		else {
			m_coordinateToMoveTo = emptySpots[i];
			safeSpot = true;
			break;
		}
	}

	// If the roadrunner has coyotes all around it but there are empty spots, just pick a random one
	if (!safeSpot && emptySpots.size() != 0) {
		m_coordinateToMoveTo = PickRandomSpot(emptySpots);
	}
	// If there are no safe spots nor empty spots, just stay where the roadrunner is already
	else if(!safeSpot && emptySpots.size() == 0) {
		m_coordinateToMoveTo = m_coordinates;
	}

	breedCounter++;

}

/**

	This function checks to see if a Roadrunner is able to breed or not.
	For Roadrunners, once they have moved 3 times, they can bread. If this
	functions returns true, it will reset the Roadrunner's breed counter
	back to zero so they can start the breeding process again. Otherwise,
	the function will just return false.

	@return bool
	*/
bool Roadrunner::CanBreed() {

	if (breedCounter == 3) {
		breedCounter = 0;
		return true;
	}
	else {
		return false;
	}
}

/**

	This function is virtual from the parent class and is primarily used for Coyotes
	that have the chance to die if they do not eat any Roadrunners. In the Roadrunner
	class, this function simply returns false.

	@return bool
	*/
bool Roadrunner::IsDead() {
	return false;
}
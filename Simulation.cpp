#include "Simulation.h"

/**

	This function serves as the default constructor for the Simulation
	class. It initializes any values used in the Simulation class.

	@return none
	*/
Simulation::Simulation()
{
	m_length = 0;
	m_width = 0;
	m_coyotes = 0;
	m_roadrunners = 0;
	m_allRoadrunnerEnd = false;
	m_emptyBoardEnd = false;

	srand((unsigned int)time(0));
}

/**

	This function is the default destructor for the Simulation class.
	It frees up the memory that was allocated to the heap from the
	Simulation class.

	@return none
	*/
Simulation::~Simulation() {

	for (size_t i = 0; i < m_agents.size(); i++) {
		delete m_agents[i];
	}
}

/**

	This function serves as the main running of the simulation. It
	first counts to the number of cycles specified in the config file.
	Then, it will cycle through all of the agents in a random order, 
	allowing each one to make a move before the same agent gets
	repeated. Once all of them cycle through, the vector of agents gets
	randomized again so different agents get to go before others. During
	the simulation, some agents die and these are immediatley taken off
	the board but remain in the agents vector until AFTER the loop for
	cycling through the agents has finished to avoid any issues with 
	deleting from the vector. For breeding, when it happens for a
	particular agent, the location of the agent is saved and the new
	baby agent is spawned in AFTER the agents vector is finished
	cycling through to avoid adding in new agents while iterating through
	the vector.

	@return void
	*/
void Simulation::MainGame() {

	bool skipAgent = false;
	int count = 0;
	GetStartingInfo();
	PlotAgentsToBoard();
	cout << "Starting board:" << endl;
	PrintBoard();
	SaveAgentCounts();
	cout << "------------------------------------" << endl;

	while (count < m_cycles && !GameIsOver()) {

		for (size_t i = 0; i < m_agents.size(); i++) {

			if (m_agents[i]->IsDead()) {
				m_board[m_agents[i]->GetPosition().m_width][m_agents[i]->GetPosition().m_length] = '0';
				m_needDeleting.push_back(i);
				continue;
			}
			// Cycle through the list of road runners that need to be deleted and skip them since
			// they are technically dead and shouldn't be playing
			for (size_t j = 0; j < m_needDeleting.size(); j++) {
				if (m_needDeleting[j] == i) {
					skipAgent = true;
				}
			}

			if (skipAgent) {
				skipAgent = false;
				continue;
			}

			// Agents makes a move somewhere on the board, Coyote or Roadrunner
			m_agents[i]->Move(m_board);

			// If the new position the agent is moving to has an 'r', and the agent isn't already a roadrunner,
			// then that means a coyote is eating a roadrunner and it should be added to the vector of needing
			// to be removed agents
			if (m_board[m_agents[i]->GetCoordinateToMoveTo().m_width][m_agents[i]->GetCoordinateToMoveTo().m_length] == 'r' && m_agents[i]->GetAgentLetter() != 'r') {
				RemoveAgent(m_agents[i]->GetCoordinateToMoveTo());
			}

			if (i < m_agents.size()) {

				m_board[m_agents[i]->GetPosition().m_width][m_agents[i]->GetPosition().m_length] = '0';
				m_agents[i]->SetPosition(m_agents[i]->GetCoordinateToMoveTo().m_width, m_agents[i]->GetCoordinateToMoveTo().m_length);
				m_board[m_agents[i]->GetPosition().m_width][m_agents[i]->GetPosition().m_length] = m_agents[i]->GetAgentLetter();

				if (m_agents[i]->CanBreed()) {
					SaveBreed(m_agents[i]);
				}
			}

		}

		cout << "Board on iteration: " << count + 1 << endl;
		PrintBoard();
		SaveAgentCounts();
		cout << "------------------------------------" << endl;

		// Removing and breeding agents after cycling through the vector of agents
		DeleteAgents();
		Breed();

		count++;
	}

	cout << "Board on iteration: " << count + 1 << endl;
	PrintBoard();
	SaveAgentCounts();
	cout << "------------------------------------" << endl;

	if (m_allRoadrunnerEnd) {
		cout << endl << "Simulation ended early due to the board being full of roadrunners!" << endl;
	}

	if (m_emptyBoardEnd) {
		cout << endl << "Simulation ended early due to the board being empty!" << endl;
	}

	system("pause");
}

/**

	This function opens the config file and reads in the file for the
	values needed to run the simulation. It also will create the config
	file if it doesn't exist. This will also initialize some information
	like the board and the agents.

	@return void
	*/
void Simulation::GetStartingInfo() {

	fstream outputConfigFile("config.txt");
	string input;

	// If there is no leaderboard file, this will initialize it
	if (!outputConfigFile) {
		outputConfigFile.open("config.txt", fstream::out);

		outputConfigFile << "Length: 9" << endl;
		outputConfigFile << "Width: 9" << endl;
		outputConfigFile << "Coyote: 9" << endl;
		outputConfigFile << "Roadrunner: 9" << endl;
		outputConfigFile << "Cycles: 9" << endl;
	}

	// After the leaderboard file was  initialized or if it already existed, this will output
	// the contents of the file
	ifstream inputConfigFile;
	inputConfigFile.open("config.txt");
	while (inputConfigFile >> input) {
		
		if (input == "Length:") {
			inputConfigFile >> input;
			m_length = stoi(input);
		}

		if (input == "Width:") {
			inputConfigFile >> input;
			m_width = stoi(input);
		}

		if (input == "Coyote:") {
			inputConfigFile >> input;
			m_coyotes = stoi(input);
		}

		if (input == "Roadrunner:") {
			inputConfigFile >> input;
			m_roadrunners = stoi(input);
		}

		if (input == "Cycles:") {
			inputConfigFile >> input;
			m_cycles = stoi(input);
		}


	}
	inputConfigFile.close();

	outputConfigFile.close();

	m_agents.reserve(m_width * m_length * 5);

	vector<char> tempRow;
	for (int i = 0; i < m_length; i++) {
		tempRow.push_back('0');
	}

	for (int i = 0; i < m_width; i++) {
		m_board.push_back(tempRow);
	}

	if ((m_length * m_width) < (m_coyotes + m_roadrunners)) {
		TrimStartingAgents();
	}

	CreateStartingAgents();

}

/**

	This function prints the board to the console.

	@return void
	*/
void Simulation::PrintBoard() {
	for (size_t i = 0; i < m_board.size(); i++) {
		for (size_t j = 0; j < m_board[i].size(); j++) {
			cout << m_board[i][j] << " ";
		}
		cout << endl;
	}
}

/**

	This function will trim the number of starting agents based on the board
	size. If the board is too small for how many agents were listed in the
	config file, this will reduce the number so they fill the board.

	@return void
	*/
void Simulation::TrimStartingAgents() {

	int numberOfSpaces = m_length * m_width;
	int numberOfAgents = m_coyotes + m_roadrunners;

	if (numberOfSpaces < numberOfAgents) {
		m_coyotes = numberOfSpaces / 2;
		m_roadrunners = numberOfSpaces / 2;
		m_roadrunners += numberOfSpaces % 2;
	}

}

/**

	This function will allocate the memory and initialize the agents
	to how many there were after being trimmed.

	@return void
	*/
void Simulation::CreateStartingAgents() {


	for (int i = 0; i < m_coyotes; i++) {
		Agent* temp = new Coyote();
		m_agents.push_back(temp);
	}

	for (int i = 0; i < m_roadrunners; i++) {
		Agent* temp = new Roadrunner();
		m_agents.push_back(temp);
	}

}

/**

	This function cycle through the vector of agents and randomly
	plot them to the board so long as it is an empty position.

	@return void
	*/
void Simulation::PlotAgentsToBoard() {

	int randomNum1 = rand() % m_width;
	int randomNum2 = rand() % m_length;

	for (size_t i = 0; i < m_agents.size(); i++) {

		// If it is an empty 
		if (m_board[randomNum1][randomNum2] == '0') {
			m_board[randomNum1][randomNum2] = m_agents[i]->GetAgentLetter();
			m_agents[i]->SetPosition(randomNum1, randomNum2);
		}
		else {
			i--;
		}

		randomNum1 = rand() % m_width;
		randomNum2 = rand() % m_length;
	}

}

/**

	This function takes in the coordinates of an agent and add them to a
	vector of coordinates which will be saved for later to be deleted
	from the vector of agents once they are done being cycled through.

	@param a_coord, coordinates of the agent to be deleted
	@return void
	*/
void Simulation::RemoveAgent(Coordinates a_coord) {

	for (size_t i = 0; i < m_agents.size(); i++) {
		if (m_agents[i]->GetPosition().m_width == a_coord.m_width && m_agents[i]->GetPosition().m_length == a_coord.m_length) {
			m_needDeleting.push_back(i);
		}
	}
}

/**

	This function cycles through the vector of agents
	that need to be deleted and removes them from the vector
	of agents.

	@return void
	*/
void Simulation::DeleteAgents() {

	sort(m_needDeleting.begin(), m_needDeleting.end(), greater<int>());

	for (size_t i = 0; i < m_needDeleting.size(); i++) {
		m_agents.erase(m_agents.begin() + m_needDeleting[i]);
	}

	m_needDeleting.clear();
}

/**

	This function saves the coordinates of an agent to a vector to be
	used later for adding new agents pointers to the vector of agents.

	@param a_agent, the agent that holds the coordinates for where to breed
	@return void
	*/
void Simulation::SaveBreed(Agent* a_agent) {

	m_coordinatesForBreeding.push_back(*a_agent);
}

/**

	This function cycles through the vector of coordinates that need to be
	breed by and spawns a new Coyote or Roadrunner randomly by those
	coordinates if there is an open spot. If there is no empty spot,
	the new agent will not be breed.

	@return void
	*/
void Simulation::Breed() {

	vector<Coordinates> surroundingPoints;
	vector<Coordinates> emptySpots;
	int randomNum;

	// Cycling through the list of coordinates for where breeding is going to happen...
	for (size_t i = 0; i < m_coordinatesForBreeding.size(); i++) {

		surroundingPoints = m_coordinatesForBreeding[i].GetSurroundingPositions(m_board.size(), m_board[0].size());
		emptySpots = m_coordinatesForBreeding[i].GetEmptySpots(m_board, surroundingPoints);

		if (emptySpots.size() > 0) {
			randomNum = rand() % emptySpots.size();

			if (m_coordinatesForBreeding[i].GetAgentLetter() == 'r') {
				Agent* temp = new Roadrunner();
				m_agents.push_back(temp);
			}
			else if (m_coordinatesForBreeding[i].GetAgentLetter() == 'c') {
				Agent* temp = new Coyote();
				m_agents.push_back(temp);
			}

			m_agents.back()->SetPosition(emptySpots[randomNum].m_width, emptySpots[randomNum].m_length);
			m_board[m_agents.back()->GetPosition().m_width][m_agents.back()->GetPosition().m_length] = m_agents.back()->GetAgentLetter();
		}

	}

	m_coordinatesForBreeding.clear();
}

/**

	This function checks to see if the game is over by validating two
	states the game may be in. The first is checking to see if the board is
	full of roadrunners. If all of the coyotes die out, it is possible that
	the board is full of roadrunners and nothing new will happen. The other way
	the game may end prematurely is if the board is completly empty. This could
	happen if the coyotes eat all of the roadrunners since after 8 moves of
	inactivity, a coyote dies out

	@return bool
	*/
bool Simulation::GameIsOver() {

	if (AllRoadrunners()) {
		m_allRoadrunnerEnd = true;
		return true;
	}
	else if (EmptyBoard()) {
		m_emptyBoardEnd = true;
		return true;
	}
	else {
		return false;
	}
}

/**

	This function checks to see if the board is full of roadrunners.
	It cycles through and if it sees a location with a 'c' or a '0'
	in it, it will return false, otherwise, it will return true.

	@return bool
	*/
bool Simulation::AllRoadrunners() {

	for (size_t i = 0; i < m_board.size(); i++) {
		for (size_t j = 0; j < m_board[i].size(); j++) {
			
			if (m_board[i][j] == 'c' || m_board[i][j] == '0') {
				return false;
			}
		}
	}

	return true;
}

/**

	This function checks to see if every location on the board is empty.
	It cycles through the board and if it sees a location with a 'c' or 'r',
	it will return false, otherwise, it will return true.

	@return bool
	*/
bool Simulation::EmptyBoard() {

	for (size_t i = 0; i < m_board.size(); i++) {
		for (size_t j = 0; j < m_board[i].size(); j++) {

			if (m_board[i][j] == 'c' || m_board[i][j] == 'r') {
				return false;
			}
		}
	}

	return true;
}

/**

	This function will cycle through the board and count all of
	the coyotes and roadrunners that are on there. Then, it will
	save it to two member vectors, one which holds all of the counts
	for coyotes, and the other which holds all of the counts for
	roadrunners.

	@return void
	*/
void Simulation::SaveAgentCounts() {

	int coyoteCount = 0;
	int roadrunnerCount = 0;

	for (size_t i = 0; i < m_board.size(); i++) {
		for (size_t j = 0; j < m_board[i].size(); j++) {

			if (m_board[i][j] == 'c') {
				coyoteCount++;
			}

			if (m_board[i][j] == 'r') {
				roadrunnerCount++;
			}
		}
	}

	cout << "Coyote: " << coyoteCount << endl;
	cout << "Roadrunner: " << roadrunnerCount << endl;

	m_coyoteCounts.push_back(coyoteCount);
	m_roadrunnerCounts.push_back(roadrunnerCount);
}
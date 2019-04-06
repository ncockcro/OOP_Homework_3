/**
\class Roadrunner

\brief Specifications for a Roadrunner agent

This class inherits from the "Agent" class and provides further specification and
functionality for how a Roadrunner works. It specifices its movement, if it can
breed, and if it is dead.

*/
#ifndef ROADRUNNER_H
#define ROADRUNNER_H

#include <iostream>
#include <vector>
#include "Agent.h"
class Roadrunner : public Agent
{
public:
	Roadrunner();
	void Move(vector< vector<char> > &a_board);
	bool CanBreed();
	bool IsDead();

private:
};

#endif
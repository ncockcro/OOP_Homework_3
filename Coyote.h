/**
\class Coyote

\brief Specifications for a Coyote agent

This class inherits from the "Agent" class and provides further specification and
functionality for how a Coyote works. It specifices its movement, if it can
breed, and if it is dead.

*/

#ifndef COYOTE_H
#define COYOTE_H

#include <iostream>
#include <vector>
#include "Agent.h"
class Coyote : public Agent
{
public:
	Coyote();
	void Move(vector< vector<char> > &a_board);
	bool CanBreed();
	bool IsDead();

};

#endif
//////////////////////////////////////////////////////////////////////////
//
//  Name:   State.cpp
//
//  Desc:   Abstract class that represent a game's state
//
//  Author: Bertoa Nicolas - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#include <cassert>

#include "State.h"

namespace Game 
{
	State::State(GameManager * const gameManager)
		: mGameManager(gameManager)
	{
		assert(gameManager && "State: NULL pointer");
	}
	
	State::~State() { }
}

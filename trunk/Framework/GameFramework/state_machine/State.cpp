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
	State::State(GameManager& gameManager)
		: mGameManager(gameManager)
	{
	}
	
	State::~State() { }
}

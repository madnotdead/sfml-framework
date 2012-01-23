//////////////////////////////////////////////////////////////////////////
//
// File: StateMachine.cpp
//
// Desc: StateMachine class manages the game states. The user can change 
//       the current state.
//
// Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#include "../utilities/Types.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "State.h"
#include "StateMachine.h"

#include "../managers/GameManager.h"

namespace Game
{
	StateMachine::StateMachine(GameManager * const gameManager) 
		: mRenderWindow(gameManager->GetRenderWindow())
		, mCurrentState(0)
		, mMainMenuState(gameManager)
		, mControlsState(gameManager)
		, mCreditsState(gameManager)
		, mGameExplanationState(gameManager)
		, mLoadingState(gameManager)
		, mLevel01State(gameManager)
	{
		assert(mRenderWindow && "StateMachine:NULL pointer");
		assert(gameManager && "StateMachine: NULL pointer");
	}

	// Change the current state.
	void StateMachine::ChangeState(State * const newState)
	{
		assert(newState && "ChangeState: NULL pointer");

		// Call the exit method of the existing state
		if(mCurrentState)
			mCurrentState->Clear();

		// Change state to the new state
		mCurrentState = newState;

		//call the entry method of the new state
		mCurrentState->Init();
	}	
}

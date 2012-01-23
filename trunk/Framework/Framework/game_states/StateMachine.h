//////////////////////////////////////////////////////////////////////////
//
// File: StateMachine.h
//
// Desc: StateMachine class manages the game states. The user can change 
//       and update the current state
//
// Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include <cassert>

#include "ControlsState.h"
#include "CreditsState.h"
#include "GameExplanationState.h"
#include "Level01State.h"
#include "LoadingState.h"
#include "MainMenuState.h"

class GameManager;

namespace sf
{
	class Event;
}

namespace Game
{
	class State;

	class StateMachine
	{
	public:
		StateMachine(GameManager * const gameManager);

	public:
		void ChangeState(State * const newState);
		inline void Update();
		inline void ManageEvents(const sf::Event& ev);

		inline State* GetMainMenuState();
		inline State* GetControlsState();
		inline State* GetCreditsState();
		inline State* GetGameExplanationState();
		inline State* GetLoadingState();
		inline State* GetLevel01State();

	private:
		StateMachine(const StateMachine& stateMachine);
		StateMachine& operator=(const StateMachine& stateMachine);

		sf::RenderWindow * const mRenderWindow;
		State *mCurrentState;

		MainMenuState mMainMenuState;
		ControlsState mControlsState;
		CreditsState mCreditsState;
		GameExplanationState mGameExplanationState;
		LoadingState mLoadingState;
		Level01State mLevel01State;
	};

	// Update the current state.
	void StateMachine::Update()
	{
		assert(mCurrentState && "Update(): NULL pointer");

		mCurrentState->Execute();
	}

	void StateMachine::ManageEvents(const sf::Event& ev)
	{
		assert(mCurrentState && "ManageEvents: NULL pointer");

		mCurrentState->ManageEvents(ev);
	}

	State* StateMachine::GetMainMenuState() 
	{
		return &mMainMenuState;
	}

	State* StateMachine::GetControlsState() 
	{
		return &mControlsState;
	}


	State* StateMachine::GetCreditsState() 
	{
		return &mCreditsState;
	}

	State* StateMachine::GetGameExplanationState() 
	{
		return &mGameExplanationState;
	}

	State* StateMachine::GetLoadingState()
	{
		return &mLoadingState;
	}

	State* StateMachine::GetLevel01State()
	{
		return &mLevel01State;
	}
}

#endif // GAME_STATE_MACHINE_H

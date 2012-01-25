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

#include "State.h"

namespace sf
{
	class Event;
}

namespace Game
{
	class StateMachine
	{
	public:
		StateMachine();

	public:
		void ChangeState(State * const newState);
		inline void Update();
		inline void ManageEvents(const sf::Event& ev);



	private:
		StateMachine(const StateMachine& stateMachine);
		StateMachine& operator=(const StateMachine& stateMachine);

		State *mCurrentState;
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
}

#endif // GAME_STATE_MACHINE_H

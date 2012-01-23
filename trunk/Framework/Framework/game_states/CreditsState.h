//////////////////////////////////////////////////////////////////////////
//
//  File:   CreditsState.h
//
//  Desc:   State that shows the credits of the game (programmers, artists)
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_CREDITS_STATE_H
#define GAME_CREDITS_STATE_H

#include "InformationState.h"

namespace Game
{
	class GameManager;

	class CreditsState : public InformationState
	{
	public:
		CreditsState(GameManager * const gameManager);

	protected:
		void DrawContent();
	};
}

#endif // GAME_CREDITS_STATE_H

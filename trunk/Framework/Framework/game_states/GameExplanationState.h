//////////////////////////////////////////////////////////////////////////
//
//  File:   GameExplanationState.h
//
//  Desc:   Game state that explains how to play and the game objective
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_GAMEEXPLANATION_STATE_H
#define GAME_GAMEEXPLANATION_STATE_H

#include "InformationState.h"

namespace Game
{
	class GameManager;

	class GameExplanationState : public InformationState
	{
	public:
		GameExplanationState(GameManager * const gameManager);

	protected:
		void DrawContent();
	};
}

#endif // GAME_GAMEEXPLANATION_STATE_H

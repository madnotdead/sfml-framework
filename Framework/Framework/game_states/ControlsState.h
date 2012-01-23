//////////////////////////////////////////////////////////////////////////
//
//  File:   ControlsState.h
//
//  Desc:   Game state that shows the player's controls.
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


#ifndef GAME_CONTROLS_STATE_H
#define GAME_CONTROLS_STATE_H

#include "InformationState.h"

namespace Game
{
	class GameManager;

	class ControlsState : public InformationState
	{
	public:
		ControlsState(GameManager * const gameManager);
		
	protected:
		void DrawContent();
	};
}

#endif // GAME_CONTROLS_STATE_H

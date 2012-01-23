//////////////////////////////////////////////////////////////////////////
//
//  File:   LoadingState.h
//
//  Desc:   Game state that shows a loading message before the level.
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_LOADING_STATE_H
#define GAME_LOADING_STATE_H

#include "State.h"

namespace sf
{
	class Event;
	class Sprite;
}

namespace Game
{
	class GameManager;

	class LoadingState : public State
	{
	public:
		LoadingState(GameManager * const gameManager);
		
	public:
		void Init();
		void Execute();
		void ManageEvents(const sf::Event& ev);
		virtual void Clear();

	private:
		void LoadResources();
		void DestroyResources();

		sf::Sprite *mBackgroundSprite;

		float mDelayForNextState; // Time to wait to change the current state
	};
}

#endif // GAME_LOADING_STATE_H

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

#include <GameFramework/state_machine/State.h>

namespace sf
{
	class Event;
	class Sprite;
}

namespace Game
{
	class GameManager;

	class CreditsState : public State
	{
	public:
		CreditsState(GameManager& gameManager);

	public:
		void Init();

		void Execute();

		void ManageEvents(const sf::Event& ev);

		virtual void Clear();

	protected:

		void Draw();
		
		sf::Sprite *mBackgroundSprite;
	};
}

#endif // GAME_CREDITS_STATE_H

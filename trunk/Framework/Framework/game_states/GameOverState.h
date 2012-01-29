#ifndef GAME_GAMEOVER_STATE_H
#define GAME_GAMEOVER_STATE_H

#include <GameFramework/state_machine/State.h>

namespace sf
{
	class Event;
	class Sound;
	class Sprite;
}

namespace Game
{
	class GameManager;

	class GameOverState : public State
	{
	public:
		GameOverState(GameManager& gameManager);

	public:
		void Init();
		void Execute();
		void ManageEvents(const sf::Event& ev);
		virtual void Clear();

	private:
		void LoadResources();
		void DestroyResources();

		sf::Sprite *mBackgroundSprite;
		sf::Sound *mMusic;

		float mDelayForNextState; // Time to wait to change the current state
	};
}

#endif // GAME_GAMEOVER_STATE_H

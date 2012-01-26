//////////////////////////////////////////////////////////////////////////
//
//  Name:   State.h
//
//  Desc:   Abstract class that represent a game's state
//
//  Author: Bertoa Nicolas - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_STATE_H
#define GAME_STATE_H

namespace sf
{
	class Event;
	class RenderWindow;
}

namespace Game
{
	class GameManager;

	class State
	{
	public:
		State(GameManager& gameManager);
		virtual ~State();

	public:
		virtual void Init() = 0;
		virtual void Execute() = 0;
		virtual void ManageEvents(const sf::Event& ev) = 0;
		virtual void Clear() = 0;

	protected:
		GameManager& mGameManager;

	private:
		State(const State& state);
		State& operator=(const State& state);
	};
}

#endif // GAME_STATE_H

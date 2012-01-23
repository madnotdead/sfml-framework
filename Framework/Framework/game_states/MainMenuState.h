//////////////////////////////////////////////////////////////////////////
//
//  File: MainMenuState.h
//
//  Desc: State that represents the main menu of the game.
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_MAIN_MENU_STATE_H
#define GAME_MAIN_MENU_STATE_H

#include <SFML/Graphics/Color.hpp>

#include <SFML/Window/Keyboard.hpp>

#include "InformationState.h"

namespace sf
{
	class Event;
}

namespace Game
{
	class MainMenuState : public InformationState
	{
	public:
		MainMenuState(GameManager * const gameManager);
		
	public:
		void Init();

		void ManageEvents(const sf::Event& ev);

	private:

		enum MenuOption
		{
			MenuOption_NewGame,
			MenuOption_Controls,
			MenuOption_GameExplanation,
			MenuOption_Credits,
			MenuOption_Exit
		};

		void DrawContent();

		inline sf::Color GetOptionColor(const MenuOption option) const;
		
		sf::Keyboard::Key mLastKeyOptionChange;        // Last key pressed that made an option change.
		
		MenuOption mCurrentOption;				    // Current option that will be highlighted
		
		bool mEnableChangeOption;                  // Enable or disable an option change
	};

	sf::Color MainMenuState::GetOptionColor(const MenuOption option) const
	{
		return (mCurrentOption == option) ? sf::Color::Black : sf::Color::White;
	}
}




#endif // GAME_MAIN_MENU_STATE_H
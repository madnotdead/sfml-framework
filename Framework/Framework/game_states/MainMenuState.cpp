//////////////////////////////////////////////////////////////////////////
//
//  File: MainMenuState.cpp
//
//  Desc: State that represents the main menu of the game.
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#include <cassert>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include <SFML/Window/Event.hpp>

#include "ControlsState.h"
#include "CreditsState.h"
#include "GameExplanationState.h"
#include "LoadingState.h"
#include "MainMenuState.h"
#include <GameFramework/state_machine/StateMachine.h>

#include "../managers/GameManager.h"

namespace Game
{
	MainMenuState::MainMenuState(GameManager& gameManager) 
		: InformationState(gameManager)
		, mLastKeyOptionChange(sf::Keyboard::Key(sf::Keyboard::Up)) 
		, mCurrentOption(MenuOption_NewGame)
		, mEnableChangeOption(true)
	{
	}
	
	void MainMenuState::Init()
	{
		InformationState::Init();

		mCurrentOption = MenuOption_NewGame;

		mEnableChangeOption = true;

		assert(mText && "Init: NULL pointer");
		mText->SetStyle(sf::Text::Bold);
		
		sf::Music& music = mGameManager.GetMusic();
		if (music.GetStatus() != sf::Music::Playing)
		{
			music.OpenFromFile("resources/sounds/intro.wav");
			music.SetLoop(true);
			music.Play();
		}
	}
	
	void MainMenuState::ManageEvents(const sf::Event& ev) 
	{
		StateMachine& stateMachine = mGameManager.GetStateMachine();
		sf::RenderWindow& renderWindow = mGameManager.GetRenderWindow();

		// Check if we must do an option change
		if(ev.Type == sf::Event::KeyPressed && mEnableChangeOption)
		{
			if(ev.Key.Code == sf::Keyboard::Up)
			{
				switch(mCurrentOption)
				{
				case(MenuOption_NewGame):
					mCurrentOption = MenuOption_Exit;
					break;				

				case(MenuOption_Credits):
					mCurrentOption = MenuOption_NewGame;
					break;

				case(MenuOption_Exit):
					mCurrentOption = MenuOption_Credits;
					break;

				default:
					break;
				}

				mEnableChangeOption = false;
				mLastKeyOptionChange = sf::Keyboard::Up;
			}

			else if(ev.Key.Code == sf::Keyboard::Down)
			{
				switch(mCurrentOption)
				{
				case(MenuOption_NewGame):
					mCurrentOption = MenuOption_Credits;
					break;				

				case(MenuOption_Credits):
					mCurrentOption = MenuOption_Exit;
					break;

				case(MenuOption_Exit):
					mCurrentOption = MenuOption_NewGame;
					break;

				default:
					break;
				}

				mEnableChangeOption = false;
				mLastKeyOptionChange = sf::Keyboard::Down;
			}

			else if(ev.Key.Code == sf::Keyboard::Return)
			{
				switch(mCurrentOption)
				{
				case(MenuOption_NewGame):
					stateMachine.ChangeState(mGameManager.GetLoadingState());
					break;				

				case(MenuOption_Credits):
					stateMachine.ChangeState(mGameManager.GetCreditsState());
					break;

				case(MenuOption_Exit):
					exit(0);
					renderWindow.Close();
					break;

				default:
					break;
				}

				mEnableChangeOption = false;
				mLastKeyOptionChange = sf::Keyboard::Return;
			}
		}

		// Check if we must enable the option change or not
		else if(ev.Type == sf::Event::KeyReleased && ev.Key.Code == mLastKeyOptionChange)
			mEnableChangeOption = true;
	}

	void MainMenuState::DrawContent()
	{
		assert(mText && "DrawContent: NULL pointer");
		
		sf::RenderWindow& renderWindow = mGameManager.GetRenderWindow();

		const float xPos = 350.0f;
		const float yPos = 470.0f;
		const float initialPos = 50.0f;
		const float displacement = 75.0f;
		
		DisplayText("New Game", xPos, yPos + initialPos, GetOptionColor(MenuOption_NewGame));
		DisplayText("Credits", xPos, yPos + initialPos + displacement, GetOptionColor(MenuOption_Credits));
		DisplayText("Exit", xPos, yPos + initialPos + 2.0f * displacement, GetOptionColor(MenuOption_Exit));
	}
}

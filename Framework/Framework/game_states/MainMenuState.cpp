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
#include "StateMachine.h"

#include "../managers/GameManager.h"

namespace Game
{
	MainMenuState::MainMenuState(GameManager * const gameManager) 
		: InformationState(gameManager)
		, mLastKeyOptionChange(sf::Keyboard::Key(sf::Keyboard::Up)) 
		, mCurrentOption(MenuOption_NewGame)
		, mEnableChangeOption(true)
	{
		assert(gameManager && "MainMenuState: NULL pointer");
	}
	
	void MainMenuState::Init()
	{
		InformationState::Init();

		mCurrentOption = MenuOption_NewGame;

		mEnableChangeOption = true;

		assert(mText && "Init: NULL pointer");
		mText->SetStyle(sf::Text::Bold);
	}
	
	void MainMenuState::ManageEvents(const sf::Event& ev) 
	{
		assert(mGameManager && "ManageEvents: NULL pointer");
		StateMachine * const stateMachine = mGameManager->GetStateMachine();
		assert(stateMachine && "ManageEvents: NULL pointer");

		sf::RenderWindow * const renderWindow = mGameManager->GetRenderWindow();
		assert(renderWindow && "ManageEvents: NULL pointer");

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

				case(MenuOption_Controls):
					mCurrentOption = MenuOption_NewGame;
					break;

				case(MenuOption_GameExplanation):
					mCurrentOption = MenuOption_Controls;
					break;

				case(MenuOption_Credits):
					mCurrentOption = MenuOption_GameExplanation;
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
					mCurrentOption = MenuOption_Controls;
					break;

				case(MenuOption_Controls):
					mCurrentOption = MenuOption_GameExplanation;
					break;

				case(MenuOption_GameExplanation):
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
					stateMachine->ChangeState(stateMachine->GetLoadingState());
					break;

				case(MenuOption_Controls):
					stateMachine->ChangeState(stateMachine->GetControlsState());
					break;

				case(MenuOption_GameExplanation):
					stateMachine->ChangeState(stateMachine->GetGameExplanationState());
					break;

				case(MenuOption_Credits):
					stateMachine->ChangeState(stateMachine->GetCreditsState());
					break;

				case(MenuOption_Exit):
					renderWindow->Close();
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

		assert(mGameManager && "DrawContent: NULL pointer");
		sf::RenderWindow * const renderWindow = mGameManager->GetRenderWindow();
		assert(renderWindow && "DrawContent: NULL pointer");

		const float xPos = static_cast<float>(renderWindow->GetWidth()) * 0.6f;
		const float yPos = static_cast<float>(renderWindow->GetHeight()) * 0.4f;
		const float initialPos = 50.0f;
		const float displacement = 50.0f;
		
		DisplayText("New Game", xPos, yPos + initialPos, GetOptionColor(MenuOption_NewGame));
		DisplayText("Controls", xPos, yPos + initialPos + displacement, GetOptionColor(MenuOption_Controls));
		DisplayText("Game Explanation", xPos, yPos + initialPos + 2.0f * displacement, GetOptionColor(MenuOption_GameExplanation));
		DisplayText("Credits", xPos, yPos + initialPos + 3.0f * displacement, GetOptionColor(MenuOption_Credits));
		DisplayText("Exit", xPos, yPos + initialPos + 4.0f * displacement, GetOptionColor(MenuOption_Exit));
	}
}

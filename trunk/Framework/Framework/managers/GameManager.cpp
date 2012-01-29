//////////////////////////////////////////////////////////////////////////
//
//  Name:   GameManager.cpp
//
//  Desc:   GameManager class is responsible to coordinate the different
//          componentes of the game. It only has a function to run the game.
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <sstream>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/ContextSettings.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

#include "GameManager.h"

#include "../game_states/MainMenuState.h"

namespace Game
{
	GameManager::GameManager() 
		: mRenderWindow(sf::VideoMode::VideoMode(1024, 768), "Cosmic Ring", sf::Style::Close)
		, mMainMenuState(*this)
		, mCongratulationsState(*this)
		, mControlsState(*this)
		, mCreditsState(*this)
		, mGameOverState(*this)
		, mGameExplanationState(*this)
		, mLoadingState(*this)
		, mLevel01State(*this)
#ifdef _DEBUG
		, mFpsText(0)
#endif
		, mFont(new sf::Font)
	{
		mStateMachine.ChangeState(mMainMenuState);
		
		bool correctLoading = mFont->LoadFromFile("resources/fonts/calibri.ttf");
		assert(correctLoading && "GameManager: Incorrect font loading");

#ifdef _DEBUG
		InitText();
#endif 
		mRenderWindow.SetFramerateLimit(30);
		mRenderWindow.ShowMouseCursor(false);
	}
	
	GameManager::~GameManager()
	{
		mImageManager.releaseAllResources();

#ifdef _DEBUG
		delete mFpsText;
#endif

		delete mFont;
	}
	
	void GameManager::Run()
	{
		// Start game loop
		while (mRenderWindow.IsOpen())
		{
			// Process events
			sf::Event event;
			while (mRenderWindow.PollEvent(event))
			{
				// Close window : exit
				if (event.Type == sf::Event::Closed)
					mRenderWindow.Close();
				else
					mStateMachine.ManageEvents(event);
			}

			// Clear the screen (fill it with black color)
			mRenderWindow.Clear();

			mStateMachine.Update();

			mTimerManager.tik();

#ifdef _DEBUG
			DrawFPS();
#endif

			// Display window contents on screen
			mRenderWindow.Display();

#ifdef _DEBUG
			mFpsManager.Update();
#endif
		}
	}

#ifdef _DEBUG
	void GameManager::InitText()
	{
		assert(mFont && "InitText(): NULL pointer");

		mFpsText = new sf::Text("", *mFont);
		mFpsText->SetCharacterSize(30);
		const float xCoord = 10.0f;
		const float yCoord = 10.0f;
		mFpsText->SetPosition(xCoord, yCoord);
		mFpsText->SetStyle(sf::Text::Regular);
		mFpsText->SetColor(sf::Color::White);
	}
#endif


#ifdef _DEBUG
	void GameManager::DrawFPS()
	{
		assert(mFpsText && "DrawFPS: NULL pointer");
		
		std::ostringstream oss; 
		oss << "FPS" << " " << mFpsManager.GetFPS();
		mFpsText->SetString(oss.str());
		mRenderWindow.Draw(*mFpsText);		
	}
#endif
}

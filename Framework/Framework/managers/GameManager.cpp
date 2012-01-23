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
		: mRenderWindow(sf::VideoMode::VideoMode(1024, 768), "Game", sf::Style::Close)
		, mMemoryPool(sMemoryBlocks, sMemoryBlockSize)
		, mImageManager(&mMemoryPool)
		, mSpriteManager(&mMemoryPool)
		, mStateMachine(this)
#ifdef _DEBUG
		, mFpsText(0)
#endif
		, mFont(new (mMemoryPool.Alloc(sizeof(sf::Font))) sf::Font)
	{
		mStateMachine.ChangeState(mStateMachine.GetMainMenuState());
		
		bool correctLoading = mFont->LoadFromFile("resources/fonts/calibri.ttf");
		assert(correctLoading && "GameManager: Incorrect font loading");

#ifdef _DEBUG
		InitText();
#endif 

		mRenderWindow.EnableVerticalSync(true);
	}
	
	GameManager::~GameManager()
	{
		mImageManager.releaseAllResources();
		mSpriteManager.releaseAllResources();

#ifdef _DEBUG
		mMemoryPool.Free(mFpsText);
#endif

		mMemoryPool.Free(mFont);
	}
	
	void GameManager::Run()
	{
		// Start game loop
		while (mRenderWindow.IsOpened())
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

		void *memory = mMemoryPool.Alloc(sizeof(sf::Text));
		mFpsText = new (memory) sf::Text("", *mFont);
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

///////////////////////////////////////////////////////////////////////////
//
//  Name:   GameManager.h
//
//  Desc:   GameManager class is responsible to coordinate the different
//          componentes of the game. It only has a function to run the game.
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_GAMEMANAGER_H
#define GAME_GAMEMANAGER_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "../game_states/StateMachine.h"

#ifdef _DEBUG
#include "../utilities/FPSCalculator.h"
#endif

#include "../utilities/MemoryPool.h"

#include "../utilities/Types.h"

#include "ImageManager.h"
#include "SpriteManager.h"

namespace sf
{
	class Font;
	class Text;
}

namespace Game
{
	class State;

	class GameManager
	{
	public:
		GameManager(); 
		~GameManager(); 

	public:
		void Run();
		inline sf::RenderWindow* GetRenderWindow();
		inline ImageManager* GetImageManager();
		inline SpriteManager* GetSpriteManager();
		inline StateMachine* GetStateMachine();
		inline Utils::MemoryPool* GetMemoryPool();

	private:
#ifdef _DEBUG
		void InitText();
		void DrawFPS();
#endif
		
		static const uint32_t sMemoryBlocks = 20;
		static const uint32_t sMemoryBlockSize = 512;

		sf::RenderWindow mRenderWindow;

		Utils::MemoryPool mMemoryPool;
		
		ImageManager mImageManager;

		SpriteManager mSpriteManager;

		StateMachine mStateMachine;
		
#ifdef _DEBUG
		Utils::FPSCalculator mFpsManager;
		sf::Text *mFpsText;
#endif
		sf::Font *mFont;
	};

	sf::RenderWindow* GameManager::GetRenderWindow()
	{
		return &mRenderWindow;
	}

	ImageManager* GameManager::GetImageManager()
	{
		return &mImageManager;
	}

	SpriteManager* GameManager::GetSpriteManager()
	{
		return &mSpriteManager;
	}

	StateMachine* GameManager::GetStateMachine()
	{
		return &mStateMachine;
	}

	Utils::MemoryPool * GameManager::GetMemoryPool()
	{
		return &mMemoryPool;
	}
}

#endif // GAME_GAMEMANAGER_H

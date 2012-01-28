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

#include <GameFramework/state_machine/StateMachine.h>

#ifdef _DEBUG
#include <GameFramework/utilities/FPSCalculator.h>
#endif

#include <GameFramework/utilities/Types.h>
#include <GameFramework/utilities/TimerManager.h>

#include <GameFramework/managers/ImageManager.h>
#include <GameFramework/managers/SoundManager.h>

#include "../game_states/ControlsState.h"
#include "../game_states/CreditsState.h"
#include "../game_states/GameExplanationState.h"
#include "../game_states/Level01State.h"
#include "../game_states/LoadingState.h"
#include "../game_states/MainMenuState.h"

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
		inline sf::RenderWindow& GetRenderWindow();
		inline ImageManager& GetImageManager();
		inline SoundManager& GetSoundManager();
		inline StateMachine& GetStateMachine();
		inline Utils::TimerManager& GetTimerManager();


		inline State& GetMainMenuState();
		inline State& GetControlsState();
		inline State& GetCreditsState();
		inline State& GetGameExplanationState();
		inline State& GetLoadingState();
		inline State& GetLevel01State();

	private:
#ifdef _DEBUG
		void InitText();
		void DrawFPS();
#endif
		
		static const uint32_t sMemoryBlocks = 20;
		static const uint32_t sMemoryBlockSize = 512;

		sf::RenderWindow mRenderWindow;
				
		ImageManager mImageManager;

		SoundManager mSoundManager;

		StateMachine mStateMachine;

		Utils::TimerManager mTimerManager;

		MainMenuState mMainMenuState;
		ControlsState mControlsState;
		CreditsState mCreditsState;
		GameExplanationState mGameExplanationState;
		LoadingState mLoadingState;
		Level01State mLevel01State;
		
#ifdef _DEBUG
		Utils::FPSCalculator mFpsManager;
		sf::Text *mFpsText;
#endif
		sf::Font *mFont;
	};

	sf::RenderWindow& GameManager::GetRenderWindow()
	{
		return mRenderWindow;
	}

	ImageManager& GameManager::GetImageManager()
	{
		return mImageManager;
	}

	SoundManager& GameManager::GetSoundManager()
	{
		return mSoundManager;
	}

	StateMachine& GameManager::GetStateMachine()
	{
		return mStateMachine;
	}

    Utils::TimerManager& GameManager::GetTimerManager() 
	{
		return mTimerManager;
	}

	State& GameManager::GetMainMenuState() 
	{
		return mMainMenuState;
	}

	State& GameManager::GetControlsState() 
	{
		return mControlsState;
	}

	State& GameManager::GetCreditsState() 
	{
		return mCreditsState;
	}

	State& GameManager::GetGameExplanationState() 
	{
		return mGameExplanationState;
	}

	State& GameManager::GetLoadingState()
	{
		return mLoadingState;
	}

	State& GameManager::GetLevel01State()
	{
		return mLevel01State;
	}
}

#endif // GAME_GAMEMANAGER_H

//////////////////////////////////////////////////////////////////////////
//
//  File:   LoadingState.cpp
//
//  Desc:   Game state that shows a loading message before the level.
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#include <cassert>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>

#include "Level01State.h"
#include "LoadingState.h"
#include "StateMachine.h"

#include "../managers/GameManager.h"
#include "../managers/ImageManager.h"
#include "../managers/SpriteManager.h"

namespace Game
{
	LoadingState::LoadingState(GameManager * const gameManager) 
		: State(gameManager)
		, mBackgroundSprite(0) 
		, mDelayForNextState(0.0f)
	{
		assert(gameManager && "LoadingState: NULL pointer");
	}

	void LoadingState::Init()
	{
		LoadResources();

		mDelayForNextState = 2.5f;
	}

	void LoadingState::Execute()
	{
		assert(mGameManager && "Execute: NULL pointer");
		sf::RenderWindow * const renderWindow = mGameManager->GetRenderWindow();
		assert(renderWindow && "Execute: NULL pointer");
		StateMachine * const stateMachine = mGameManager->GetStateMachine();
		assert(stateMachine && "Execute: NULL pointer");

		// Check if we must show the thanks message or change the state.
		if(mDelayForNextState > 0.0f)
		{
			mDelayForNextState -= renderWindow->GetFrameTime() / 1000.0f;
			renderWindow->Draw(*mBackgroundSprite);
		}

		else
			stateMachine->ChangeState(stateMachine->GetLevel01State());
	}

	void LoadingState::ManageEvents(const sf::Event& ev) 
	{
		ev;
	}

	void LoadingState::Clear()
	{
		DestroyResources();
	}

	void LoadingState::LoadResources()
	{
		assert(mGameManager && "LoadResources: NULL pointer");
		sf::RenderWindow * const renderWindow = mGameManager->GetRenderWindow();
		assert(renderWindow && "LoadResources: NULL pointer");

		ImageManager * const imageManager = mGameManager->GetImageManager();
		assert(imageManager && "LoadResources: NULL pointer");

		sf::Texture * const backgroundImage = imageManager->getResource("resources/images/background/loading.png");
		assert(backgroundImage && "LoadResources: NULL pointer");

		SpriteManager * const spriteManager = mGameManager->GetSpriteManager();
		assert(spriteManager && "LoadResources: NULL pointer");

		mBackgroundSprite = spriteManager->getResource("MainMenuBackground");
		assert(mBackgroundSprite && "LoadResources: NULL pointer");
		
		mBackgroundSprite->SetTexture(*backgroundImage);
		mBackgroundSprite->SetPosition(0.0f, 0.0f);
	}
	
	void LoadingState::DestroyResources()
	{
		assert(mGameManager && "DestroyResources: NULL pointer");
		
		ImageManager * const imageManager = mGameManager->GetImageManager();
		assert(imageManager && "DestroyResources: NULL pointer");
		imageManager->releaseResource("resources/images/background/loading.png");
	
		SpriteManager * const spriteManager = mGameManager->GetSpriteManager();
		assert(spriteManager && "DestroyResources: NULL pointer");
		spriteManager->releaseResource("MainMenuBackground");
	}
}

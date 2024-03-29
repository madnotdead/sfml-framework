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
#include <GameFramework/state_machine/StateMachine.h>

#include "../managers/GameManager.h"
#include <GameFramework/managers/ImageManager.h>

namespace Game
{
	LoadingState::LoadingState(GameManager& gameManager) 
		: State(gameManager)
		, mBackgroundSprite(0) 
		, mDelayForNextState(0.0f)
	{
	}

	void LoadingState::Init()
	{
		LoadResources();
	}

	void LoadingState::Execute()
	{
		sf::RenderWindow& renderWindow = mGameManager.GetRenderWindow();
		StateMachine& stateMachine = mGameManager.GetStateMachine();

		// Check if we must show the thanks message or change the state.
		if(mDelayForNextState > 0.0f)
		{
			mDelayForNextState -= 17;
			renderWindow.Draw(*mBackgroundSprite);
		} 

		else
			stateMachine.ChangeState(mGameManager.GetLevel01State());
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
		sf::RenderWindow& renderWindow = mGameManager.GetRenderWindow();
		ImageManager& imageManager = mGameManager.GetImageManager();

		sf::Texture * const backgroundImage = imageManager.getResource("resources/background/loading.jpg");
		assert(backgroundImage && "LoadResources: NULL pointer");
		
		mBackgroundSprite = new sf::Sprite;
		mBackgroundSprite->SetTexture(*backgroundImage);
		mBackgroundSprite->SetPosition(0.0f, 0.0f);

		mDelayForNextState = 6000.0f;
	}
	
	void LoadingState::DestroyResources()
	{		
		ImageManager& imageManager = mGameManager.GetImageManager();
		imageManager.releaseResource("resources/background/loading.jpg");
	
		delete mBackgroundSprite;
	}
}

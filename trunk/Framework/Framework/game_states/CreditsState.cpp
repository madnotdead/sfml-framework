//////////////////////////////////////////////////////////////////////////
//
//  File:   CreditsState.cpp
//
//  Desc:   State that shows the credits of the game (programmers, artists)
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#include <cassert>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "CreditsState.h"
#include "MainMenuState.h"

#include "../managers/GameManager.h"

namespace Game
{
	CreditsState::CreditsState(GameManager& gameManager) 
		: State(gameManager)
		, mBackgroundSprite(0)
	{
	} 

	void CreditsState::Init()
	{
		ImageManager& imageManager = mGameManager.GetImageManager();		
		sf::Texture * const backgroundImage = imageManager.getResource("resources/background/credits.jpg");
		assert(backgroundImage && "LoadResources: NULL pointer");

		mBackgroundSprite = new sf::Sprite;
		mBackgroundSprite->SetTexture(*backgroundImage);
		mBackgroundSprite->SetPosition(0.0f, 0.0f);
	}

	void CreditsState::Execute()
	{
		mGameManager.GetRenderWindow().Draw(*mBackgroundSprite);		
	}

	void CreditsState::ManageEvents(const sf::Event& ev) 
	{
		StateMachine& stateMachine = mGameManager.GetStateMachine();

		if(ev.Type == sf::Event::KeyPressed && ev.Key.Code == sf::Keyboard::Escape)
			stateMachine.ChangeState(mGameManager.GetMainMenuState());
	}

	void CreditsState::Clear()
	{
		mGameManager.GetImageManager().releaseResource("resources/background/credits.jpg");
		delete mBackgroundSprite;
	}	
}

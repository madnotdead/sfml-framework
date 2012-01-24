//////////////////////////////////////////////////////////////////////////
//
// File: InformationState.cpp
//
// Desc: Abstract state that provides functionality to states that
//       will need to show information on the screen like main menu, 
//       controls, game explanation, etc.
//
// Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#include <cassert>
#include "../utilities/Types.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <SFML/Window/Event.hpp>

#include "InformationState.h"
#include "MainMenuState.h"
#include "StateMachine.h"

#include "../managers/GameManager.h"
#include "../managers/ImageManager.h"
#include "../managers/SpriteManager.h"

namespace Game
{
	InformationState::InformationState(GameManager * const gameManager) 
		: State(gameManager)
		, mBackgroundSprite(0)
		, mFont(0)
		, mText(0) 
	{
		assert(gameManager && "InformationState: NULL pointer");
	} 

	void InformationState::Init()
	{
		LoadResources();

		InitFont();
		InitText();
	}

	void InformationState::Execute()
	{
		Draw();
		DrawContent();
	}

	void InformationState::ManageEvents(const sf::Event& ev) 
	{
		assert(mGameManager && "ManageEvents: NULL pointer");
		StateMachine * const stateMachine = mGameManager->GetStateMachine();
		assert(stateMachine && "ManageEvents: NULL pointer");
		
		if(ev.Type == sf::Event::KeyPressed && ev.Key.Code == sf::Keyboard::Escape)
			stateMachine->ChangeState(stateMachine->GetMainMenuState());
	}

	void InformationState::Clear()
	{
		DestroyResources();
	}

	void InformationState::LoadResources()
	{
		assert(mGameManager && "LoadResources: NULL pointer");
		
		ImageManager * const imageManager = mGameManager->GetImageManager();
		assert(imageManager && "LoadResources: NULL pointer");
		
		sf::Texture * const backgroundImage = imageManager->getResource("resources/background/main_screen.png");
		assert(backgroundImage && "LoadResources: NULL pointer");

		sf::RenderWindow * const renderWindow = mGameManager->GetRenderWindow();
		assert(renderWindow && "LoadResources: NULL pointer");

		SpriteManager * const spriteManager = mGameManager->GetSpriteManager();
		assert(spriteManager && "LoadResources: NULL pointer");

		mBackgroundSprite = spriteManager->getResource("MainMenuBackground");

		mBackgroundSprite->SetTexture(*backgroundImage);
		mBackgroundSprite->SetPosition(0.0f, 0.0f);
	}

	void InformationState::DestroyResources()
	{
		Utils::MemoryPool * const memoryPool = mGameManager->GetMemoryPool();
		memoryPool->Free(mFont);
		memoryPool->Free(mText);
	}

	void InformationState::InitFont()
	{
		void *memory = mGameManager->GetMemoryPool()->Alloc(sizeof(sf::Font));
		mFont = new (memory) sf::Font();
		bool correctLoading = mFont->LoadFromFile("resources/fonts/calibri.ttf");
		assert(correctLoading && "InitFont: Font was not correctly loeaded");
	}

	void InformationState::InitText()
	{
		void *memory = mGameManager->GetMemoryPool()->Alloc(sizeof(sf::Text));
		mText = new (memory) sf::Text("", *mFont);
		mText->SetCharacterSize(50);
		mText->SetStyle(sf::Text::Bold);
		mText->SetColor(sf::Color::White);
	}

	void InformationState::Draw()
	{
		assert(mBackgroundSprite && "Draw(): NULL pointer");

		assert(mGameManager && "Draw: NULL pointer");
		sf::RenderWindow * const renderWindow = mGameManager->GetRenderWindow();
		assert(renderWindow && "Draw: NULL pointer");

		renderWindow->Draw(*mBackgroundSprite);
	}

	void InformationState::DisplayText(const std::string& body, const float xPos, const float yPos, const sf::Color& color)
	{
		assert(mText && "DisplayText: NULL pointer");

		assert(mGameManager && "DisplayText: NULL pointer");
		sf::RenderWindow * const renderWindow = mGameManager->GetRenderWindow();
		assert(renderWindow && "DisplayText: NULL pointer");

		mText->SetString(body.c_str());
		mText->SetPosition(xPos, yPos);
		mText->SetColor(color);
		renderWindow->Draw(*mText);
	}
}

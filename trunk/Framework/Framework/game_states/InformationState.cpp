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
#include <GameFramework/utilities/Types.h>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <SFML/Window/Event.hpp>

#include "InformationState.h"
#include "MainMenuState.h"
#include <GameFramework/state_machine/StateMachine.h>

#include "../managers/GameManager.h"
#include <GameFramework/managers/ImageManager.h>
#include <GameFramework/managers/SpriteManager.h>

namespace Game
{
	InformationState::InformationState(GameManager& gameManager) 
		: State(gameManager)
		, mBackgroundSprite(0)
		, mFont(0)
		, mText(0) 
	{
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
		StateMachine& stateMachine = mGameManager.GetStateMachine();
		
		if(ev.Type == sf::Event::KeyPressed && ev.Key.Code == sf::Keyboard::Escape)
			stateMachine.ChangeState(mGameManager.GetMainMenuState());
	}

	void InformationState::Clear()
	{
		DestroyResources();
	}

	void InformationState::LoadResources()
	{		
		ImageManager& imageManager = mGameManager.GetImageManager();		
		sf::Texture * const backgroundImage = imageManager.getResource("resources/background/main_screen.png");
		assert(backgroundImage && "LoadResources: NULL pointer");

		SpriteManager& spriteManager = mGameManager.GetSpriteManager();

		mBackgroundSprite = spriteManager.getResource("MainMenuBackground");

		mBackgroundSprite->SetTexture(*backgroundImage);
		mBackgroundSprite->SetPosition(0.0f, 0.0f);
	}

	void InformationState::DestroyResources()
	{
		Utils::MemoryPool& memoryPool = mGameManager.GetMemoryPool();
		memoryPool.Free(mFont);
		memoryPool.Free(mText);
	}

	void InformationState::InitFont()
	{
		void *memory = mGameManager.GetMemoryPool().Alloc(sizeof(sf::Font));
		mFont = new (memory) sf::Font();
		bool correctLoading = mFont->LoadFromFile("resources/fonts/calibri.ttf");
		assert(correctLoading && "InitFont: Font was not correctly loeaded");
	}

	void InformationState::InitText()
	{
		void *memory = mGameManager.GetMemoryPool().Alloc(sizeof(sf::Text));
		mText = new (memory) sf::Text("", *mFont);
		mText->SetCharacterSize(50);
		mText->SetStyle(sf::Text::Bold);
		mText->SetColor(sf::Color::White);
	}

	void InformationState::Draw()
	{
		assert(mBackgroundSprite && "Draw(): NULL pointer");

		sf::RenderWindow& renderWindow = mGameManager.GetRenderWindow();
		renderWindow.Draw(*mBackgroundSprite);
	}

	void InformationState::DisplayText(const std::string& body, const float xPos, const float yPos, const sf::Color& color)
	{
		assert(mText && "DisplayText: NULL pointer");
				
		mText->SetString(body.c_str());
		mText->SetPosition(xPos, yPos);
		mText->SetColor(color);

		sf::RenderWindow& renderWindow = mGameManager.GetRenderWindow();
		renderWindow.Draw(*mText);
	}
}

//////////////////////////////////////////////////////////////////////////
//
//  File:   GameExplanationState.cpp
//
//  Desc:   Game state that explains how to play and the game objective
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#include <cassert>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "GameExplanationState.h"
#include "MainMenuState.h"

#include "../managers/GameManager.h"

namespace Game
{
	GameExplanationState::GameExplanationState(GameManager& gameManager) 
		: InformationState(gameManager) 
	{
	} 

	void GameExplanationState::DrawContent()
	{
		assert(mText && "DrawContent: NULL pointer.");

		sf::RenderWindow& renderWindow = mGameManager.GetRenderWindow();

		const float xPos = static_cast<float>(renderWindow.GetWidth()) * 0.25f;
		const float yPos = static_cast<float>(renderWindow.GetHeight()) * 0.4f;
		const float initialPos = 0.0f;
		const float displacement = 60.0f;

		mText->SetCharacterSize(30);

		const char *explanation = "1) Collect the sequence of gems from left  \n"
								  "    to right. \n"  
								  "2) If you collect an invalid gem, the sequence \n"
								  "    will be reseted. \n" 
								  "3) Kill the friendly enemies wandering the space \n \n"
								  "Press ESC to go to main menu";
		DisplayText(explanation, xPos, yPos + initialPos, sf::Color::Black);
	}
}

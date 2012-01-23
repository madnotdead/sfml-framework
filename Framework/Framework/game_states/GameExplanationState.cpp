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
	GameExplanationState::GameExplanationState(GameManager * const gameManager) 
		: InformationState(gameManager) 
	{
		assert(gameManager && "GameExplanationState: NULL pointer");
	} 

	void GameExplanationState::DrawContent()
	{
		assert(mText && "DrawContent: NULL pointer.");

		assert(mGameManager && "DrawContent: NULL pointer");
		sf::RenderWindow * const renderWindow = mGameManager->GetRenderWindow();
		assert(renderWindow && "DrawContent: NULL pointer");

		const float xPos = static_cast<float>(renderWindow->GetWidth()) * 0.25f;
		const float yPos = static_cast<float>(renderWindow->GetHeight()) * 0.4f;
		const float initialPos = 0.0f;
		const float displacement = 60.0f;

		mText->SetCharacterSize(30);

		const char *explanation = "1) Extinguish all the fire in the road as you can \n"
								  "2) Each time you extinguish a fire, you increase your timer \n"
								  "3) If your timer reaches zero, you lose \n \n"
								  "Press ESC to go to main menu";
		DisplayText(explanation, xPos, yPos + initialPos, sf::Color::Black);
	}
}

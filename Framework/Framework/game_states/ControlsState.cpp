//////////////////////////////////////////////////////////////////////////
//
//  File:   ControlsState.h
//
//  Desc:   Game state that shows the player's controls.
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#include <cassert>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "ControlsState.h"
#include "MainMenuState.h"

#include "../managers/GameManager.h"

namespace Game
{
	ControlsState::ControlsState(GameManager& gameManager)
		: InformationState(gameManager)
	{
	}
	
	void ControlsState::DrawContent()
	{
		assert(mText && "DrawContent: NULL pointer");

		sf::RenderWindow& renderWindow = mGameManager.GetRenderWindow();
		const float xPos = static_cast<float>(renderWindow.GetWidth()) * 0.5f;
		const float yPos = static_cast<float>(renderWindow.GetHeight()) * 0.4f;
		const float initialPos = 40.0f;
		const float displacement = 40.0f;

		mText->SetCharacterSize(30);
		const char* controls = "Use the arrows to move the ship \n"
							   "Press A to shot \n"
							   "Esc: Main Menu \n \n"
							   "Press ESC to go to main menu \n";
		DisplayText(controls, xPos, yPos + initialPos, sf::Color::Black);
	}
}

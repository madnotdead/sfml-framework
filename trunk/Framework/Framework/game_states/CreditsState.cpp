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

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "CreditsState.h"
#include "MainMenuState.h"

#include "../managers/GameManager.h"

namespace Game
{
	CreditsState::CreditsState(GameManager& gameManager)
		: InformationState(gameManager)
	{
	}

	void CreditsState::DrawContent()
	{
		assert(mText && "Init: NULL pointer");

		sf::RenderWindow& renderWindow = mGameManager.GetRenderWindow();

		const float xPos = static_cast<float>(renderWindow.GetWidth()) * 0.3f;
		const float yPos = static_cast<float>(renderWindow.GetHeight()) * 0.4f;
		const float initialPos = 0.0f;
		const float displacement = 40.0f;

		mText->SetCharacterSize(30);

		const char *credits = "Programmers: \n"
							  "Ramiro Del Corro - ramiro.del.corro@gmail.com \n"
							  "Bertoa Nicolas - nicobertoa@gmail.com";
		DisplayText(credits, xPos, yPos + initialPos, sf::Color::White);
	}
}

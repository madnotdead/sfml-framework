//////////////////////////////////////////////////////////////////////////
//
// File: Updaters.cpp
//
// Desc: Update different things like position, collisions, etc
//
// Author: Bertoa Nicolas - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cfloat>

#include <SFML/Window/Keyboard.hpp>

#include "Updaters.h"

namespace Game
{
	// Update a position according to keyboard inputs.
	void UpdatePlayerPositionFromInput(sf::Vector2f& position, const float speed)
	{
		if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Right))
			position.x += speed;
		
		else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Left))
			position.x -= speed;
		
		if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Down))
			position.y += speed;
		
		else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Up))
			position.y -= speed;
	}

	// If the sprite is outside screen, then we reposition it inside the screen.
	void FitInsideScreen(sf::Vector2f& spritePosition, const uint32_t spriteWidth, const uint32_t spriteHeight,
		const uint32_t windowWidth, const uint32_t windowHeight)
	{
		if(spritePosition.x < 0.0f)
			spritePosition.x = 0.0f;
		if(spritePosition.y < 0.0f)
			spritePosition.y = 0.0f;

		const float rightLimit = static_cast<float>(windowWidth - spriteWidth); 
		if(rightLimit < spritePosition.x)
			spritePosition.x = rightLimit;
		
		const float upLimit = static_cast<float>(windowHeight - spriteHeight);
		if(upLimit < spritePosition.y)
			spritePosition.y = upLimit;
	}

	void UpdatePlayerBulletsPositions(const uint8_t numberOfBullets, sf::Vector2f * const bulletsPositions, const bool * const bulletsState, const float bulletSpeed)
	{
		assert(bulletsPositions && "UpdatePlayerBulletsPositions: NULL pointer");
		assert(bulletsState && "UpdatePlayerBulletsPositions: NULL pointer");

		for(uint8_t i = 0; i < numberOfBullets; ++i)
		{
			if(bulletsState[i])
				bulletsPositions[i].y -= bulletSpeed;
		}
	}

	void UpdatePlayerBulletsState(const uint8_t numberOfBullets, sf::Vector2f * const bulletsPositions, bool * const bulletsState, const uint32_t bulletHeight)
	{
		assert(bulletsPositions && "UpdatePlayerBulletsState: NULL pointer");
		assert(bulletsState && "UpdatePlayerBulletsState: NULL pointer");

		const float outOfScreenYPosition = 0.0f - bulletHeight;
		for(uint32_t i = 0; i < numberOfBullets; ++i)
		{
			// Deactivate the bullet if necessary.
			if(bulletsPositions[i].y <= outOfScreenYPosition)
			{
				bulletsState[i] = false;
			}
		}
	}

	bool UpdateBulletsFromInput(const uint8_t numberOfBullets, sf::Vector2f * const bulletsPositions, bool * const bulletsState, const sf::Vector2f& playerPosition, 
		const uint32_t playerSpriteWidth, const uint32_t bulletSpriteWidth)
	{
		assert(bulletsPositions && "UpdateBulletsFromInput: NULL pointer");
		assert(bulletsState && "UpdateBulletsFromInput: NULL pointer");

		// The player pressed fire button
		if (sf::Keyboard::IsKeyPressed(sf::Keyboard::A))
		{
			// Shot a bullet if possible.
			for(uint8_t i = 0; i < numberOfBullets; ++i)
			{
				if(!bulletsState[i])
				{
					bulletsPositions[i].y = playerPosition.y;
					const float halfPlayerXPosition = playerPosition.x + playerSpriteWidth / 2.0f;
					bulletsPositions[i].x = halfPlayerXPosition - bulletSpriteWidth / 2.0f;
					bulletsState[i] = true;

					return true;
				}
			}
		}

		return false;
	}
}
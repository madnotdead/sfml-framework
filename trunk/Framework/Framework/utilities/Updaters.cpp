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
	void UpdatePlayerPositionFromInput(sf::Vector2f * const position, const float frameTime, const float speed)
	{
		assert(position && "UpdatePositionFromInput: NULL pointer");

		const float finalSpeed = frameTime * speed;
		if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Right))
			position->x += finalSpeed;
		
		else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Left))
			position->x -= finalSpeed;
		
		if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Down))
			position->y += finalSpeed;
		
		else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Up))
			position->y -= finalSpeed;
	}

	// If the sprite is outside screen, then we reposition it inside the screen.
	void FitInsideScreen(sf::Vector2f * const spritePosition, const uint32_t spriteWidth, const uint32_t spriteHeight,
		const uint32_t windowWidth, const uint32_t windowHeight)
	{
		assert(spritePosition && "FitInsideScreen: NULL pointer");

		if(spritePosition->x < 0.0f)
			spritePosition->x = 0.0f;
		if(spritePosition->y < 0.0f)
			spritePosition->y = 0.0f;

		const float rightLimit = static_cast<float>(windowWidth - spriteWidth); 
		if(rightLimit < spritePosition->x)
			spritePosition->x = rightLimit;
		
		const float upLimit = static_cast<float>(windowHeight - spriteHeight);
		if(upLimit < spritePosition->y)
			spritePosition->y = upLimit;
	}

	void UpdatePlayerBulletsPositions(const uint8_t numberOfBullets, sf::Vector2f * const bulletsPositions, const float bulletSpeed,
		const float frameTime)
	{
		assert(bulletsPositions && "UpdatePlayerBulletsPositions: NULL pointer");
		const float finalSpeed = bulletSpeed * frameTime;

		for(uint8_t i = 0; i < numberOfBullets; ++i)
		{
			if(bulletsPositions[i].y != FLT_MAX)
				bulletsPositions[i].y -= finalSpeed;
		}
	}

	void UpdatePlayerBulletsState(const uint8_t numberOfBullets, sf::Vector2f * const bulletsPositions, const uint32_t bulletHeight)
	{
		assert(bulletsPositions && "UpdatePlayerBulletsState: NULL pointer");

		const float outOfScreenYPosition = 0.0f - bulletHeight;
		for(uint32_t i = 0; i < numberOfBullets; ++i)
		{
			// Deactivate the bullet if necessary.
			if(bulletsPositions[i].y <= outOfScreenYPosition)
				bulletsPositions[i].y = FLT_MAX;
		}
	}

	bool UpdateBulletsFromInput(const uint8_t numberOfBullets, sf::Vector2f * const bulletsPositions, const sf::Vector2f& playerPosition, 
		const uint32_t playerSpriteWidth, const uint32_t bulletSpriteWidth)
	{
		assert(bulletsPositions && "UpdateBulletsFromInput: NULL pointer");

		// The player pressed fire button
		if (sf::Keyboard::IsKeyPressed(sf::Keyboard::A))
		{
			// Shot a bullet if possible.
			for(uint8_t i = 0; i < numberOfBullets; ++i)
			{
				if(bulletsPositions[i].y == FLT_MAX)
				{
					bulletsPositions[i].y = playerPosition.y;
					const float halfPlayerXPosition = playerPosition.x + playerSpriteWidth / 2.0f;
					bulletsPositions[i].x = halfPlayerXPosition - bulletSpriteWidth / 2.0f;

					return true;
				}
			}
		}

		return false;
	}
}
//////////////////////////////////////////////////////////////////////////
//
// File: Updaters.h
//
// Desc: Update different things like position, collisions, etc
//
// Author: Bertoa Nicolas - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#include <GameFramework/utilities/Types.h>

#include <SFML/System/Vector2.hpp>

namespace sf
{
	class Input;
}

namespace Game
{
	// Update a position according to keyboard inputs.
	void UpdatePlayerPositionFromInput(sf::Vector2f * const position, const float frameTime, const float speed);

	// If the sprite is outside screen, then we reposition it inside the screen.
	void FitInsideScreen(sf::Vector2f * const spritePosition, const uint32_t spriteWidth, const uint32_t spriteHeight,
		const uint32_t windowWidth, const uint32_t windowHeight); 
	
	// Update the position of the bullets according to its speed.
	void UpdatePlayerBulletsPositions(const uint8_t numberOfBullets, sf::Vector2f * const bulletsPositions, const float bulletSpeed,
		const float frameTime);

	// If the bullets get out from the top of the screen, then we need to deactivate them.
	void UpdatePlayerBulletsState(const uint8_t numberOfBullets, sf::Vector2f * const bulletsPositions, const uint32_t bulletHeight);

	// Check if the player want to shot a bullet and activate one of them if are available.
	bool UpdateBulletsFromInput(const uint8_t numberOfBullets, sf::Vector2f * const bulletsPositions, const sf::Vector2f& playerPosition, 
		const uint32_t playerSpriteWidth, const uint32_t bulletSpriteWidth);
}
#ifndef GAME_COLLISION_HELPER_H
#define GAME_COLLISION_HELPER_H

#include <vector>

#include <GameFramework/utilities/Types.h>

#include "../entities/Enemy.h"

#include <SFML/System/Vector2.hpp>

namespace Game
{
	class CollisionHelper
	{
	public:

		void PlayerBulletsAndEnemiesCollisions(std::vector<Enemy*>& enemies, const sf::Vector2f * const playerBullets, 
			const uint8_t numberOfBullets, bool * const bulletsState, const uint32_t bulletWidth, const uint32_t bulletHeight);
	};
}

#endif // GAME_COLLISION_HELPER_H

#include "CollisionHelper.h"

#include <cassert>

#include <GameFramework/utilities/CollisionDetection.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace Game
{
	void CollisionHelper::PlayerBulletsAndEnemiesCollisions(std::vector<Enemy*>& enemies, const sf::Vector2f * const playerBullets, 
		const uint8_t numberOfBullets, bool * const bulletsState, const uint32_t bulletWidth, const uint32_t bulletHeight)
	{
		assert(playerBullets && "CollisionHelper::PlayerBulletsAndEnemiesCollisions: NULL pointer");
		assert(bulletsState && "CollisionHelper::PlayerBulletsAndEnemiesCollisions: NULL pointer");

		for (size_t i = 0; i < enemies.size(); ++i)
		{
			if (enemies[i]->isActive())
			{
				sf::Sprite * enemy = enemies[i]->getSprite();
				assert(enemy && "CollisionHelper::PlayerBulletsAndEnemiesCollisions: NULL pointer");

				for (uint8_t j = 0; j < numberOfBullets; ++j)
				{
					if (bulletsState[j])
					{
						const sf::Vector2f &currentBullet = playerBullets[j];   
						const sf::Vector2f &currentEnemy = enemy->GetPosition();
						const sf::Texture * texture = enemy->GetTexture();
						assert(texture && "CollisionHelper::PlayerBulletsAndEnemiesCollisions: NULL pointer"); 
						if (CheckRectanglesCollision(Rectangle(currentBullet, bulletWidth, bulletHeight), 
							Rectangle(currentEnemy, enemy->GetTexture()->GetWidth() * static_cast<uint32_t> (enemy->GetScale().x), 
									enemy->GetTexture()->GetHeight() * static_cast<uint32_t> (enemy->GetScale().y))))
						{
							enemies[i]->disable();
							bulletsState[j] = false;
						}
					}
				}
			}
		}
	}
}
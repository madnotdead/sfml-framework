#include "EnemyColider.h"
#include "..\entities\Enemy.h"

bool Game::EnemyColider::Colide( std::vector<Enemy*>& enemies, const sf::Sprite* ship )
{
	for(size_t i = 0; i < enemies.size(); ++i) {
		if (enemies[i]->isActive())
		{
			sf::Sprite* enemy = enemies[i]->getSprite();
			const sf::Vector2f &currentEnemy = enemy->GetPosition();
			const sf::Vector2f &shipPos = ship->GetPosition();
			const sf::Texture * texture = enemy->GetTexture(); 
			const sf::Texture * shipTexture = ship->GetTexture(); 
			if (CheckRectanglesCollision(
				Rectangle(shipPos, shipTexture->GetWidth() * static_cast<uint32_t> (ship->GetScale().x), 
				shipTexture->GetHeight() * static_cast<uint32_t> (ship->GetScale().y)), 
				Rectangle(currentEnemy, texture->GetWidth() * static_cast<uint32_t> (enemy->GetScale().x), 
				texture->GetHeight() * static_cast<uint32_t> (enemy->GetScale().y))))
			{
				return true;
			}
		}
	}
	return false;
}

Game::EnemyColider::EnemyColider( GameManager& gameManager ) : mGameManager(gameManager)
{}


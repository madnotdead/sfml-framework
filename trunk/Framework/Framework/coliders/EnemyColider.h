#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <GameFramework/utilities/CollisionDetection.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace Game {
class GameManager;
class Enemy;

	class EnemyColider {
	public:
		EnemyColider(GameManager& gameManager);

		bool Colide(std::vector<Enemy*>& enemies, const sf::Sprite* ship);

	private:
		GameManager& mGameManager;
	};
}
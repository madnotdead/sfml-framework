#pragma once
#include <SFML/System/Vector2.hpp>

namespace Game {
	class GameManager;
	class Algorithm {
	public:
		virtual void move(sf::Vector2f& position, float speed) = 0;
		virtual ~Algorithm() {}
		Algorithm(GameManager& gameManager) : mGameManager(gameManager) {}
		protected:
		GameManager& mGameManager;
	};
}
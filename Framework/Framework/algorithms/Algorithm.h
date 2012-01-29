#pragma once
#include <SFML/System/Vector2.hpp>
#include "../entities_generators/MoveType.h"

namespace Game {
	class GameManager;
	class Algorithm {
	public:
		virtual void move(sf::Vector2f& position, float speed) = 0;
		virtual ~Algorithm() {}
		Algorithm(GameManager& gameManager) : mGameManager(gameManager) {}
		virtual MOVE_TYPE getType() = 0;
		protected:
		GameManager& mGameManager;
	};
}
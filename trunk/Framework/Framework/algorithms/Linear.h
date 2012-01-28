#pragma once
#include "Algorithm.h"

namespace Game {
	class Linear  : public Algorithm{
	public:
		Linear(GameManager& gameManager) : Algorithm(gameManager) {}
		void move(sf::Vector2f& position, float speed);
	};
}
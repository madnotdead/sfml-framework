#pragma once
#include "Algorithm.h"

namespace Game {
	class Diagonal  : public Algorithm{
	public:
		Diagonal(GameManager& gameManager) : Algorithm(gameManager) {}
		void move(sf::Vector2f& position, float speed);
	};
}
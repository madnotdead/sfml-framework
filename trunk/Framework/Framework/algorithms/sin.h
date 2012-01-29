#pragma once
#include "Algorithm.h"

namespace Game {
	class Sin  : public Algorithm{
	public:
		Sin(GameManager& gameManager) : Algorithm(gameManager), mCount(0.f) {}
		void move(sf::Vector2f& position, float speed);
		MOVE_TYPE getType() { return SIN;}

	private: 
		float mCount;
	};
}
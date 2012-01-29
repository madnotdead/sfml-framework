#pragma once
#include "Algorithm.h"

namespace Game {
	class Z  : public Algorithm{
	public:
		Z(GameManager& gameManager) : Algorithm(gameManager), movement(RIGHT) {}
		void move(sf::Vector2f& position, float speed);
		MOVE_TYPE getType() { return MOVE_Z;}

	private:
		enum MOVEMENT { LEFT, RIGHT } movement;
	};
}
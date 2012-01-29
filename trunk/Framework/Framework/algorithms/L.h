#pragma once
#include "Algorithm.h"

namespace Game {
	class L  : public Algorithm{
	public:
		L(GameManager& gameManager);
		void move(sf::Vector2f& position, float speed);
		MOVE_TYPE getType() { return MOVE_L;}

	private:
		enum MOVEMENT { DOWN, RIGHT } movement;
		float mCutOff;
	};
}
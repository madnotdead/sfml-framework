#pragma once
#include "Algorithm.h"

namespace Game {
	class Bounce  : public Algorithm{
	public:
		Bounce(GameManager& gameManager) : Algorithm(gameManager), xmove(XPLUS), ymove(YPLUS)  {}
		void move(sf::Vector2f& position, float speed);
	    MOVE_TYPE getType() { return BOUNCE;}

	private:
		enum MOVEMENT { XPLUS, XMINUS, YPLUS, YMINUS };
		MOVEMENT xmove;
		MOVEMENT ymove;
	};
}
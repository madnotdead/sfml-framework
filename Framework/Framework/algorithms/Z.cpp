#include "Z.h"
#include "..\managers\GameManager.h"


void Game::Z::move( sf::Vector2f& position,  float speed)
{
	float width = mGameManager.GetRenderWindow().GetWidth();
	if(position.x + speed >= width) {
		movement = LEFT;
	} else if(position.x - speed <= 0.f) {
		movement = RIGHT;
	}

	if(movement == LEFT) {
		position.x -= speed;
		position.y += speed;
	} else {
		position.x += speed;
		position.y += speed;
	}	
}

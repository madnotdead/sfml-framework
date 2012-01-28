#include "L.h"
#include <cstdlib>

void Game::L::move( sf::Vector2f& position,  float speed)
{
	if(position.y + speed >= mCutOff) {
		movement = RIGHT;
	} 

	if(movement == RIGHT) {
		position.x += speed;
	} else {
		position.y += speed;
	}	
}

Game::L::L( GameManager& gameManager ) : Algorithm(gameManager), movement(DOWN), mCutOff(0.f)
{
	mCutOff = (rand()%768) + 50;
}

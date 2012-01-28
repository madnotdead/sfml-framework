#include "Sin.h"
#include "..\managers\GameManager.h"
#include <math.h>

void Game::Sin::move( sf::Vector2f& position,  float speed)
{
	float width = mGameManager.GetRenderWindow().GetWidth();
	position.y += speed;	
	position.x += sin(position.x) * 10; 
}

#include "Sin.h"
#include "..\managers\GameManager.h"
#include <math.h>

void Game::Sin::move( sf::Vector2f& position,  float speed)
{
	const float width = static_cast<float> (mGameManager.GetRenderWindow().GetWidth());
	position.y += speed;	
	position.x += sin(position.x) * 10; 
}

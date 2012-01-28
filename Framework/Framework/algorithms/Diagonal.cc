#include "Diagonal.h"
#include "..\managers\GameManager.h"

void Game::Diagonal::move( sf::Vector2f& position,  float speed)
{
	position.x += speed / 2;
	position.y += speed;
}

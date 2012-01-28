#include "Bounce.h"
#include "..\managers\GameManager.h"

void Game::Bounce::move( sf::Vector2f& position,  float speed)
{
	const float width = static_cast<float> (mGameManager.GetRenderWindow().GetWidth());
	const float height = static_cast<float> (mGameManager.GetRenderWindow().GetHeight());
	if(position.x > width) {
		xmove = xmove == XPLUS ? XMINUS : XPLUS;
	} else if(position.x < 0.f) {
		xmove = xmove == XPLUS ? XMINUS : XPLUS;
	} else if(position.y >= height) {
		ymove = ymove == YPLUS ? YMINUS : YPLUS;
	} else if(position.y < 0.f) {
		ymove = ymove == YPLUS ? YMINUS : YPLUS;
	}

	position.x = xmove == XPLUS ? position.x += speed :  position.x -= speed;
	position.y = ymove == YPLUS ? position.y += speed :  position.y -= speed;
}

#include "GemColider.h"
#include "..\managers\GameManager.h"
#include <GameFramework\utilities\CollisionDetection.h>

Game::GemColider::GemColider( GameManager& gameManager, Hud& hud ) : mGameManager(gameManager), mHud(hud)
{
}

void Game::GemColider::update(const sf::Sprite& ship, std::vector<JewelsGenerator::Item>& jewels )
{
	Game::Rectangle shipRect(ship.GetPosition(), ship.GetTexture()->GetWidth(), ship.GetTexture()->GetHeight());
	for(size_t i = 0; i < jewels.size(); ++i) {
		if(jewels[i].isActive) {
			Game::Rectangle jewelRect(jewels[i].mSprite->GetPosition(),jewels[i].mSprite->GetTexture()->GetWidth(), 
				jewels[i].mSprite->GetTexture()->GetHeight());
			bool colide = CheckRectanglesCollision(shipRect, jewelRect); 
			if(colide) {
				jewels[i].isActive = false;
				
			}
		}
	}
}

#include "GemColider.h"

#include <GameFramework\utilities\CollisionDetection.h>

#include <SFML/Audio/Sound.hpp>

#include "../hud/Hud.h"
#include "..\hud\HudPopulator.h"

#include "..\managers\GameManager.h"

Game::GemColider::GemColider( GameManager& gameManager, Hud& hud, HudPopulator& hudPopulator, sf::Sound& rightSelection, sf::Sound& wrongSelection) 
	: mGameManager(gameManager)
	, mHud(hud)
	, mHudPopulator(hudPopulator)
	, mCurrentIndex(0)
	, mRightSelection(rightSelection)
	, mWrongSelection(wrongSelection)
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
				if(i == mHudPopulator.getHudIndices()[mCurrentIndex]) {
					mHud.turnOn();
					mRightSelection.Play();
					// Alto hardcodeo
					if (mCurrentIndex < 9)
					{
						++mCurrentIndex;
					}
				} else {
					mWrongSelection.Play();
					mHud.clear();
					mCurrentIndex = 0;
				}
			}
		}
	}
}

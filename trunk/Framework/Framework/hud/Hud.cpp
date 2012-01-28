#include "Hud.h"
#include "..\managers\GameManager.h"

namespace Game {

const float HUD_SIZE = 30.f;
const float HUD_OFFSET = 20.f;
const sf::Vector2f CIRCLE_POSITION(30.f, 600.f);

Hud::Hud (GameManager& gameManager, size_t textureCount) : mGameManager(gameManager), mCurrentIndex(0)
{ 
	mHudInfo.reserve(textureCount);
	mNextPosition.x = HUD_SIZE * 2;
	mNextPosition.y = HUD_SIZE;
}

void Hud::addItem(const sf::Texture* offTexture, const sf::Texture* onTexture)
{
	HudInfo info;
	info.offTexture = offTexture;
	info.onTexture = onTexture;
	info.position = mNextPosition;
	mHudInfo.push_back(info);
	updateNextPosition();
}

void Hud::draw() 
{
	sf::Sprite sprite;
	for(size_t i = 0; i < mHudInfo.size(); ++i) {
		sprite.SetPosition(mHudInfo[i].position);
		const sf::Texture* texture = mHudInfo[i].state == HudInfo::OFF ?  mHudInfo[i].offTexture : mHudInfo[i].onTexture;
		sprite.SetTexture(*texture);
		mGameManager.GetRenderWindow().Draw(sprite);
	}
	
	// Draw circle
	sprite.SetPosition(CIRCLE_POSITION);
	sprite.SetTexture(*mCircle);
	mGameManager.GetRenderWindow().Draw(sprite);

	// Draw part
	sprite.SetPosition(CIRCLE_POSITION);
	sprite.SetTexture(*mPart);
	sprite.SetOrigin(105.f, 105.f);
	sprite.Rotate(mPartRotation);
	mGameManager.GetRenderWindow().Draw(sprite);
}

void Hud::updateNextPosition() 
{
	mNextPosition.x += (HUD_SIZE + HUD_OFFSET);
}

void Hud::turnOn()
{
	mHudInfo[mCurrentIndex].state = HudInfo::ON;
	mCurrentIndex++;
}

void Hud::turnOff()
{
	mCurrentIndex--;
	mHudInfo[mCurrentIndex].state = HudInfo::OFF;
}	

void Hud::clear() 
{
	for(size_t i = 0; i < mHudInfo.size(); ++i) {
		mHudInfo[i].state = HudInfo::OFF;
		mCurrentIndex = 0;
	}
}

void Hud::addCircle( const sf::Texture* circle )
{
	mCircle = circle;
}

void Hud::addMovingPart( const sf::Texture* part )
{
	mPart = part;
}

void Hud::setPartRotation( float mapPosition )
{
	mPartRotation = (365.f / 100) * mapPosition; 
}

}
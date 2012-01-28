#include "Hud.h"
#include "..\managers\GameManager.h"

namespace Game {

const float HUD_SIZE = 30.f;
const float HUD_OFFSET = 40.f;
const sf::Vector2f CIRCLE_POSITION(30.f, 500.f);

Hud::Hud (GameManager& gameManager, size_t textureCount) : mGameManager(gameManager), mCurrentIndex(0), mMapPosition(0), mLife(0)
{ 
	mHudInfo.reserve(textureCount);
	mNextPosition.x = HUD_SIZE;
	mNextPosition.y = HUD_SIZE;
}

void Hud::addItem(const sf::Texture* offTexture, const sf::Texture* onTexture)
{
	BallInfo info;
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
		const sf::Texture* texture = mHudInfo[i].state == BallInfo::OFF ?  mHudInfo[i].offTexture : mHudInfo[i].onTexture;
		sprite.SetTexture(*texture);
		mGameManager.GetRenderWindow().Draw(sprite);
	}

	// Draw map position
	sprite.SetPosition(CIRCLE_POSITION);
	sprite.SetTexture(*(mMapInfo[mMapPosition]), true); 
	mGameManager.GetRenderWindow().Draw(sprite);

	// Draw life
	sprite.SetPosition(CIRCLE_POSITION);
	sprite.SetTexture(*(mLifeInfo[mLife]), true);
	mGameManager.GetRenderWindow().Draw(sprite);
}

void Hud::updateNextPosition() 
{
	mNextPosition.x += (HUD_SIZE + HUD_OFFSET);
}

void Hud::turnOn()
{
	mHudInfo[mCurrentIndex].state = BallInfo::ON;
	mCurrentIndex++;
}

void Hud::turnOff()
{
	mCurrentIndex--;
	mHudInfo[mCurrentIndex].state = BallInfo::OFF;
}	

void Hud::clear() 
{
	for(size_t i = 0; i < mHudInfo.size(); ++i) {
		mHudInfo[i].state = BallInfo::OFF;
		mCurrentIndex = 0;
	}
}

void Hud::addLifeTexture( const sf::Texture* texture )
{
	mLifeInfo.push_back(texture);
}

void Hud::addMapPositionTexture( const sf::Texture* texture )
{
	mMapInfo.push_back(texture);
}

void Hud::setLife( size_t life )
{
	mLife = life;
}

void Hud::setMapPosition( size_t mapPos )
{
	mMapPosition = mapPos;
}



}
#include "Hud.h"
#include "..\managers\GameManager.h"

namespace Game {

const float HUD_SIZE = 30.f;
const float HUD_OFFSET = 20.f;
const sf::Vector2f mNextPosition;

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
	for(size_t i = 0; i < mHudInfo.size(); ++i) {
		mSprite.SetPosition(mHudInfo[i].position);
		const sf::Texture* texture = mHudInfo[i].state == HudInfo::OFF ?  mHudInfo[i].offTexture : mHudInfo[i].onTexture;
		mSprite.SetTexture(*texture);
		mGameManager.GetRenderWindow().Draw(mSprite);
	}
	mGameManager.GetRenderWindow().Draw(mCircle);
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

}
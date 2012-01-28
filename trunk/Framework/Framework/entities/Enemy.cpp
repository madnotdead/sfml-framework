#include "Enemy.h"
#include "..\managers\GameManager.h"

namespace Game {

Enemy::Enemy( GameManager& gameManager ) 
	: mGameManager(gameManager)
	, mActive(false)
	, mRotationEnable(false)
	, mAlgorithm(NULL)
	, mEnemyImage(0)
{
}

void Enemy::draw()
{
	if(mActive) {
		sf::Vector2f position = mSprite.GetPosition();
		mAlgorithm->move(position, mSpeed);
		if(position.y > mGameManager.GetRenderWindow().GetHeight() || (position.x > mGameManager.GetRenderWindow().GetWidth() + 100.f)) {
			mActive = false;
			return;
		}
		mSprite.SetPosition(position);
		if(mRotationEnable) {
			mSprite.SetRotation(mSprite.GetRotation() + 1.f);
		}
		mGameManager.GetRenderWindow().Draw(mSprite);
	}
}

Enemy::~Enemy()
{
	delete mAlgorithm;
}

void Enemy::setTexture( const sf::Texture* texture )
{
	mEnemyImage = texture;
	mSprite.SetTexture(*texture);
}

sf::Sprite* Enemy::getSprite()
{
	return &mSprite;
}

void Enemy::restart()
{
	mSpeed = static_cast<float> ((rand() % 10) + 1); 
	mSprite.SetPosition((static_cast<float> (rand() % (1024 - 80))) , - static_cast<float> (mSprite.GetTexture()->GetHeight()));
	mActive = true;
}

}
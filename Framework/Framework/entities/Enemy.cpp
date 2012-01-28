#include "Enemy.h"
#include "..\managers\GameManager.h"

namespace Game {

Enemy::Enemy( GameManager& gameManager ) : mGameManager(gameManager), mActive(false), mRotationEnable(false), mAlgorithm(NULL)
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
		mSprite.SetTexture(*mEnemyImage);
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
}

sf::Sprite* Enemy::getSprite()
{
	return &mSprite;
}

void Enemy::restart()
{
	mSpeed = (rand()%30)+1; 
	mSprite.SetPosition((rand()%1024), 0);
	mActive = true;
}

}
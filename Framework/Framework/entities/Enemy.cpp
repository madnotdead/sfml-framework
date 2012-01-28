#include "Enemy.h"

#include "..\algorithms\Linear.h"
#include "..\algorithms\Z.h"
#include "..\algorithms\L.h"
#include "..\algorithms\sin.h"
#include "..\algorithms\Bounce.h"
#include "..\algorithms\Diagonal.h"
#include "..\managers\GameManager.h"

namespace Game {

Algorithm* Game::Enemy::getAlgorithm()
{
	int algorithmId = (rand()%6);
	switch(algorithmId) {
		case 0:
			return new Bounce(mGameManager);
		case 1:
			return new Linear(mGameManager);
		case 2:
			return new Z(mGameManager);
		case 3:
			return new L(mGameManager);
		default:
		case 4:
			return new Sin(mGameManager);
	}	
}

Enemy::Enemy( GameManager& gameManager ) : mGameManager(gameManager), mActive(true)
{
	mSpeed = (rand()%30)+1; 
	mAlgorithm = getAlgorithm();
	mSprite.SetPosition((rand()%1024), 0);
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
		mSprite.SetRotation(mSprite.GetRotation() + 1.f);
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
	delete mAlgorithm;
	mSpeed = (rand()%30)+1; 
	mAlgorithm = getAlgorithm();
	mSprite.SetPosition((rand()%1024), 0);
	mActive = true;
}

}
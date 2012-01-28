#include "EnemysGenerator.h"
#include "../managers/GameManager.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "..\algorithms\Linear.h"
#include "..\algorithms\Z.h"
#include "..\algorithms\L.h"
#include "..\algorithms\sin.h"
#include "..\algorithms\Bounce.h"
#include "..\algorithms\Diagonal.h"

namespace Game
{
	EnemysGenerator::EnemysGenerator(GameManager& gameManager)
		: mGamemanager(gameManager)
		, mTimer(Utils::Timer(timerGenerateItem, this))
	{
	}

	EnemysGenerator::~EnemysGenerator()
	{
		mGamemanager.GetTimerManager().unregisterTimer(mTimer);
		for (size_t i = 0; i < mEnemyPool.size(); ++i)
		{
			delete mEnemyPool[i];
		}
	}

	Algorithm* EnemysGenerator::getAlgorithm(MOVE_TYPE type)
	{
		switch(type) {
		case EnemysGenerator::BOUNCE:
			return new Bounce(mGamemanager);
		case EnemysGenerator::LINEAR:
			return new Linear(mGamemanager);
		case EnemysGenerator::Z:
			return new Game::Z(mGamemanager);
		case EnemysGenerator::L:
			return new Game::L(mGamemanager);
		default:
		case EnemysGenerator::SIN:
			return new Sin(mGamemanager);
		}	
	}

	void EnemysGenerator::startGeneration(const size_t milliseconds)
	{
		mGamemanager.GetTimerManager().registerTimer(mTimer);
		mTimer.start(milliseconds);
	}

	void EnemysGenerator::draw()
	{
		for (size_t i = 0; i < mEnemyPool.size(); ++i)
		{
			if (mEnemyPool[i]->isActive())
			{
				mEnemyPool[i]->draw();
			}
		}
	}

	void EnemysGenerator::timerGenerateItem(void *thisClass)
	{
		EnemysGenerator* enemysGenerator = reinterpret_cast<EnemysGenerator*> (thisClass);
		enemysGenerator->generateItem();		
	}

	void EnemysGenerator::generateItem()
	{
		while(true) {
			int index = (rand()%mEnemyPool.size()); 
			if(mEnemyPool[index]->isActive() == false) {
				mEnemyPool[index]->restart();
				break;
			}
		}
	}

	void EnemysGenerator::addEnemy( sf::Texture& image, bool enableRotation, MOVE_TYPE type )
	{
		for(size_t i = 0; i < 3; ++i) {
			Enemy* enemy = new Enemy(mGamemanager);
			enemy->setTexture(&image);
			enemy->setAlgorithm(getAlgorithm(type));
			if(enableRotation) {
				enemy->enableRotation();
			}
			mEnemyPool.push_back(enemy);
		}
	}
}

#pragma once
#include <vector>
#include <GameFramework/utilities/Timer.h>
#include "..\entities\Enemy.h"
#include "MoveType.h"

namespace sf
{
	class Sprite;
	class Texture;
}

namespace Game
{	
	class GameManager;
	class EnemysGenerator
	{
	public:
		EnemysGenerator(GameManager& gameManager);
		~EnemysGenerator();

		void addEnemy(sf::Texture& image, bool enableRotation, MOVE_TYPE type, const float scaleFactor=1);
		void startGeneration(const size_t milliseconds);
		void draw();

		static void timerGenerateItem(void *thisClass);
		void generateItem();

		inline std::vector<Enemy*> &getEnemies(); 

	private:
		std::vector<Enemy*> mEnemyPool;
		GameManager& mGamemanager;
		Utils::Timer mTimer;
		Algorithm* getAlgorithm(MOVE_TYPE type);
	};

	std::vector<Enemy*> &EnemysGenerator::getEnemies()
	{
		return mEnemyPool;
	}
}

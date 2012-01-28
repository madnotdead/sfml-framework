#pragma once
#include <vector>
#include <GameFramework/utilities/Timer.h>
#include "..\entities\Enemy.h"

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
		enum MOVE_TYPE {BOUNCE, DIAGONAL, L, LINEAR, SIN, Z};
		EnemysGenerator(GameManager& gameManager);
		~EnemysGenerator();

		void addEnemy(sf::Texture& image, bool enableRotation, MOVE_TYPE type);
		void startGeneration(const size_t milliseconds);
		void draw();

		static void timerGenerateItem(void *thisClass);
		void generateItem();

	private:
		std::vector<Enemy*> mEnemyPool;
		GameManager& mGamemanager;
		Utils::Timer mTimer;
		Algorithm* getAlgorithm(MOVE_TYPE type);
	};
}

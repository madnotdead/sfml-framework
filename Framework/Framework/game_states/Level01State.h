//////////////////////////////////////////////////////////////////////////
//
// File: Level01State.h
//
// Desc: Game level 01
//
// Author: Bertoa Nicolas - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_LEVEL01_STATE_H
#define GAME_LEVEL01_STATE_H

#include "../entities/KamikazeEnemy.h"

#include "../utilities/Types.h"

#include "State.h"

namespace sf
{
	class Event;
	class Sprite; 
}

namespace Game
{
	class GameManager;

	class Level01State : public State
	{
	public:
		static const uint8_t sPlayerBullets = 5;

	public:
		Level01State(GameManager * const gameManager);

	public:
		void Init();
		void Execute();
		void ManageEvents(const sf::Event& ev);
		void Clear();

	private: 
		void CheckEnemyToBulletsCollisions();

		KamikazeEnemy mEnemy;
		sf::Vector2f mPlayerPosition;
		sf::Vector2f mPlayerBulletsPositions[sPlayerBullets];
		sf::Sprite *mPlayerSprite;
		sf::Sprite *mPlayerBulletSprite;
		sf::Sprite *mEnemySprite;
		sf::Sprite *mBackground;
		const float mPlayerSpeed;
		const float mPlayerBulletSpeed;
		const int mPlayerBulletPower;
		const float mTimeToWaitToShot;
		const float mTimeIncrement;
		float mElapsedTimeFromLastShot;
		uint32_t mPlayerMaxHealth;
		uint32_t mPlayerCurrentHealth;
	};
}

#endif // GAME_LEVEL01_STATE_H

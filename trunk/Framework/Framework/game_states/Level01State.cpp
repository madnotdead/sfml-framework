//////////////////////////////////////////////////////////////////////////
//
// File: Level01State.h
//
// Desc: Game level 01
//
// Author: Bertoa Nicolas - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cfloat>

#include <SFML/Window/Event.hpp>

#include "Level01State.h"
#include "StateMachine.h"

#include "../managers/GameManager.h"
#include "../managers/ImageManager.h"
#include "../managers/SpriteManager.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../utilities/CollisionDetection.h"
#include "../utilities/Updaters.h"

namespace
{
	void InitBulletsPosition(const uint8_t numberOfBullets, sf::Vector2f * const bulletsPosition)
	{
		assert(bulletsPosition && "InitBulletsPosition: NULL pointer");

		// Init bullets position.
		// Initially they are deactivated, that is, its
		// coordinates are FLT_MAX.
		const sf::Vector2f bulletInitialPosition(FLT_MAX, FLT_MAX);
		for(uint8_t i = 0; i < numberOfBullets; ++i)
		{
			bulletsPosition[i] = bulletInitialPosition;
		}
	}
}

namespace Game
{
	Level01State::Level01State(GameManager * const gameManager)
		: State(gameManager)
		, mEnemy(sf::Vector2f(FLT_MAX, FLT_MAX), 2000.0f, 10000)
		, mPlayerPosition(sf::Vector2f(FLT_MAX, FLT_MAX))
		, mPlayerSprite(0)
		, mPlayerBulletSprite(0)
		, mEnemySprite(0)
		, mBackground(0)
		, mPlayerSpeed(300.0f)
		, mPlayerBulletSpeed(700.0f)
		, mPlayerBulletPower(500)
		, mTimeToWaitToShot(0.5f)
		, mTimeIncrement(3.0f)
		, mElapsedTimeFromLastShot(0.0f)
		, mPlayerMaxHealth(2000)
		, mPlayerCurrentHealth(mPlayerMaxHealth)
	{
		assert(gameManager && "Level01State: NULL pointer");

		InitBulletsPosition(sPlayerBullets, mPlayerBulletsPositions);
	}

	void Level01State::Init()
	{
		// The player can shot from the beginning.
		mElapsedTimeFromLastShot = mTimeToWaitToShot;
		
		ImageManager * const imageManager = mGameManager->GetImageManager();
		assert(imageManager && "Init: NULL pointer");

		// Init player sprite.
		const sf::Texture *image = imageManager->getResource("resources/ships/PlayerShip.png");
		assert(image && "Init: NULL pointer");
		SpriteManager * const spriteManager = mGameManager->GetSpriteManager();
		assert(spriteManager && "Init: NULL pointer");
		mPlayerSprite = spriteManager->getResource("PlayerShipSprite");
		assert(mPlayerSprite && "Init: NULL pointer");
		mPlayerSprite->SetTexture(*image);
		mPlayerPosition.x = 0.0f;
		mPlayerPosition.y = 0.0f;
				
		// Init player bullets.
		image = imageManager->getResource("resources/bullets/bullet.png");
		assert(image && "Init: NULL pointer");
		mPlayerBulletSprite = spriteManager->getResource("PlayerBulletSprite");
		assert(mPlayerBulletSprite && "Init: NULL pointer");
		mPlayerBulletSprite->SetTexture(*image);
		InitBulletsPosition(sPlayerBullets, mPlayerBulletsPositions);

		// Init enemy sprite.
		image = imageManager->getResource("resources/ships/boss.PNG");
		assert(image && "Init: NULL pointer");
		mEnemySprite = spriteManager->getResource("EnemyShipSprite");
		assert(mEnemySprite && "Init: NULL pointer");
		mEnemySprite->SetTexture(*image);
		mEnemy.mPosition.x = 0.0f;
		mEnemy.mPosition.y = 0.0f;

		// Init background
		image = imageManager->getResource("resources/background/level1.png");
		assert(image && "Init: NULL pointer");
		mBackground = spriteManager->getResource("LevelBackground");
		assert(mBackground && "Init: NULL pointer");
		mBackground->SetTexture(*image);

		sf::RenderWindow * const renderWindow = mGameManager->GetRenderWindow();
		assert(renderWindow && "Init: NULL pointer");
		//mBackground->Resize(static_cast<float>(renderWindow->GetWidth()), static_cast<float>(renderWindow->GetHeight()));
		mBackground->SetPosition(0.0f, 0.0f);
	}

	void Level01State::Execute()
	{
		sf::RenderWindow * const renderWindow = mGameManager->GetRenderWindow();
		assert(renderWindow && "Execute: NULL pointer");

		// Update player position
		const float frameTime = static_cast<float>(renderWindow->GetFrameTime()) / 1000.0f;
		UpdatePlayerPositionFromInput(&mPlayerPosition, frameTime, mPlayerSpeed);
				
		// Fit player sprite onto the screen
		const sf::Texture * const playerImage = mPlayerSprite->GetTexture();
		assert(playerImage && "Execute: NULL pointer");
		FitInsideScreen(&mPlayerPosition, playerImage->GetWidth(), playerImage->GetHeight(), renderWindow->GetWidth(), 
			renderWindow->GetHeight());
		mPlayerSprite->SetPosition(mPlayerPosition);

		// Update player bullet positions
		UpdatePlayerBulletsPositions(sPlayerBullets, mPlayerBulletsPositions, mPlayerBulletSpeed, frameTime);
		UpdatePlayerBulletsState(sPlayerBullets, mPlayerBulletsPositions, mPlayerBulletSprite->GetTexture()->GetHeight());

		// Check if the player shoot.
		mElapsedTimeFromLastShot += mTimeIncrement * frameTime;
		if(mTimeToWaitToShot <= mElapsedTimeFromLastShot)
		{
			const sf::Texture * const bulletImage = mPlayerBulletSprite->GetTexture();
			assert(bulletImage && "Execute: NULL pointer");

			if(UpdateBulletsFromInput(sPlayerBullets, mPlayerBulletsPositions, mPlayerPosition, playerImage->GetWidth(), bulletImage->GetWidth()))
				mElapsedTimeFromLastShot = 0.0f;
		}

		// Update enemy
		const sf::Texture * const enemyImage = mEnemySprite->GetTexture();
		mEnemy.Update(frameTime, enemyImage->GetWidth(), enemyImage->GetHeight(), renderWindow->GetWidth(), renderWindow->GetHeight());
		mEnemySprite->SetPosition(mEnemy.mPosition);

		// Calculate collisions between player bullets and enemy.
		CheckEnemyToBulletsCollisions();

		// Check collisions between player and enemy ships
		if(CheckRectanglesCollision(Rectangle(mPlayerPosition, playerImage->GetWidth(), playerImage->GetHeight()),
			Rectangle(mEnemy.mPosition, enemyImage->GetWidth(), enemyImage->GetHeight())))
		{
			mPlayerPosition.x = 0.0f;
			mPlayerPosition.y = 0.0f;
		}

		renderWindow->Draw(*mBackground);

		// Draw player ship and bullets
		for(uint8_t i = 0; i < sPlayerBullets; ++i)
		{
			if(mPlayerBulletsPositions[i].y != FLT_MAX)
			{
				mPlayerBulletSprite->SetPosition(mPlayerBulletsPositions[i]);
				renderWindow->Draw(*mPlayerBulletSprite);
			}
		}

		renderWindow->Draw(*mEnemySprite);
		renderWindow->Draw(*mPlayerSprite);
	}

	void Level01State::ManageEvents(const sf::Event& ev)
	{
		// Check if we must return to main menu.
		if(ev.Type == sf::Event::KeyPressed)
		{
			if(ev.Key.Code == sf::Keyboard::Escape)
			{
				assert(mGameManager && "ManageEvents: NULL pointer");
				
				ImageManager * const imageManager = mGameManager->GetImageManager();
				assert(imageManager && "ManageEvents: NULL pointer");
				imageManager->releaseResource("resources/images/PlayerShip.png");

				SpriteManager * const spriteManager = mGameManager->GetSpriteManager();
				assert(spriteManager && "ManageEvents: NULL pointer");
				spriteManager->releaseResource("PlayerShip");
				
				StateMachine * const stateMachine = mGameManager->GetStateMachine();
				assert(stateMachine && "ManageEvents: NULL pointer");
				stateMachine->ChangeState(stateMachine->GetMainMenuState());
			}	
		}
	}
	
	void Level01State::Clear()
	{
		ImageManager * const imageManager = mGameManager->GetImageManager();
		assert(imageManager && "Clear: NULL pointer");	
		imageManager->releaseResource("resources/ships/boss.png");
		imageManager->releaseResource("resources/background/level1.jpg");

		imageManager->releaseResource("resources/images/PlayerShip.png");

		SpriteManager * const spriteManager = mGameManager->GetSpriteManager();
		assert(spriteManager && "Clear: NULL pointer");
		spriteManager->releaseResource("PlayerShipSprite");
		spriteManager->releaseResource("PlayerBulletSprite");
		spriteManager->releaseResource("EnemyShipSprite");
		spriteManager->releaseResource("LevelBackground");
	}

	void Level01State::CheckEnemyToBulletsCollisions()
	{
		Rectangle enemyRectangle(mEnemy.mPosition, mEnemySprite->GetTexture()->GetWidth(), mEnemySprite->GetTexture()->GetHeight());
		Rectangle bulletRectangle(sf::Vector2f(0.0f, 0.0f), mPlayerBulletSprite->GetTexture()->GetWidth(), mPlayerBulletSprite->GetTexture()->GetHeight());

		for(uint32_t i = 0; i < sPlayerBullets; ++i)
		{ 
			// Update the rectangle position
			bulletRectangle.mPosition = mPlayerBulletsPositions[i];
			if(CheckRectanglesCollision(enemyRectangle, bulletRectangle))
			{
				// Decrement enemy health
				mEnemy.mHealth -= mPlayerBulletPower;

				// Reposition the bullet rectangle.
				mPlayerBulletsPositions[i].x = FLT_MAX;
				mPlayerBulletsPositions[i].y = FLT_MAX;
			}
		}
	}
}

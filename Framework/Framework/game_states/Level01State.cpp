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
#include <SFML/Graphics/Shader.hpp>

#include "Level01State.h"
#include <GameFramework/state_machine/StateMachine.h>

#include "../managers/GameManager.h"

#include "../scrolling_map/BackgroundItemsGenerator.h"
#include "../scrolling_map/ScrollingMap.h"

#include "../utilities/Updaters.h"

#include <GameFramework/managers/ImageManager.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <GameFramework/utilities/CollisionDetection.h>

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
	Level01State::Level01State(GameManager& gameManager)
		: State(gameManager)
		, mMap(0)
		, mBackgroundItemsGenerator(0)
		, mEnemy(sf::Vector2f(FLT_MAX, FLT_MAX), 2000.0f, 10000)
		, mPlayerPosition(sf::Vector2f(FLT_MAX, FLT_MAX))
		, mPlayerSprite(0)
		, mPlayerBulletSprite(0)
		, mEnemySprite(0)
		, mPlayerSpeed(300.0f)
		, mPlayerBulletSpeed(700.0f)
		, mPlayerBulletPower(500)
		, mTimeToWaitToShot(0.5f)
		, mTimeIncrement(3.0f)
		, mElapsedTimeFromLastShot(0.0f)
		, mPlayerMaxHealth(2000)
		, mPlayerCurrentHealth(mPlayerMaxHealth)
		, mHud(gameManager, 10)
	{
		InitBulletsPosition(sPlayerBullets, mPlayerBulletsPositions);
	}

	void Level01State::Init()
	{
		// The player can shot from the beginning.
		mElapsedTimeFromLastShot = mTimeToWaitToShot;
		
		ImageManager& imageManager = mGameManager.GetImageManager();

		// Init player sprite.
		sf::Texture *image = imageManager.getResource("resources/ships/PlayerShip.png");
		assert(image && "Init: NULL pointer");
		mPlayerSprite = new  sf::Sprite;
		mPlayerSprite->SetTexture(*image);
		mPlayerPosition.x = 0.0f;
		mPlayerPosition.y = 0.0f;
				
		// Init player bullets.
		image = imageManager.getResource("resources/bullets/bullet.png");
		assert(image && "Init: NULL pointer");
		mPlayerBulletSprite = new sf::Sprite;
		mPlayerBulletSprite->SetTexture(*image);
		InitBulletsPosition(sPlayerBullets, mPlayerBulletsPositions);

		// Init enemy sprite.
		image = imageManager.getResource("resources/ships/boss.PNG");
		assert(image && "Init: NULL pointer");
		mEnemySprite = new sf::Sprite;
		mEnemySprite->SetTexture(*image);
		mEnemy.mPosition.x = 0.0f;
		mEnemy.mPosition.y = 0.0f;

		// Init Map
		mMap = new ScrollingMap(mGameManager);
		image = imageManager.getResource("resources/background/background1.jpg");
		assert(image && "Init: NULL pointer");
		mMap->initMap(*image);
		mMap->setScrollingSpeed(2.0f);

		// Init background items generator.
		mBackgroundItemsGenerator = new BackgroundItemsGenerator(mGameManager);
		image = imageManager.getResource("resources/background/items/circle.png");
		assert(image && "Init: NULL pointer");
		mBackgroundItemsGenerator->addImage(*image);
		image = imageManager.getResource("resources/background/items/nebulosa1big.psd.png");
		assert(image && "Init: NULL pointer");
		mBackgroundItemsGenerator->addImage(*image);
		image = imageManager.getResource("resources/background/items/nebulosa2big.psd.png");
		assert(image && "Init: NULL pointer");
		mBackgroundItemsGenerator->addImage(*image);
		image = imageManager.getResource("resources/background/items/nebulosa3big.psd.png");
		assert(image && "Init: NULL pointer");
		mBackgroundItemsGenerator->addImage(*image);
		image = imageManager.getResource("resources/background/items/nebulosa4big.psd.png");
		assert(image && "Init: NULL pointer");
		mBackgroundItemsGenerator->addImage(*image);
		image = imageManager.getResource("resources/background/items/otroplaneta.png");
		assert(image && "Init: NULL pointer");
		mBackgroundItemsGenerator->addImage(*image);
		image = imageManager.getResource("resources/background/items/planeta1.psd.png");
		assert(image && "Init: NULL pointer");
		mBackgroundItemsGenerator->addImage(*image);
		image = imageManager.getResource("resources/background/items/planeta2.png");
		assert(image && "Init: NULL pointer");
		mBackgroundItemsGenerator->addImage(*image);
		image = imageManager.getResource("resources/background/items/planetalool.psd.png");
		assert(image && "Init: NULL pointer");
		mBackgroundItemsGenerator->addImage(*image);
		mBackgroundItemsGenerator->startGeneration(1000);		
	}

	void Level01State::Execute()
	{
		sf::RenderWindow& renderWindow = mGameManager.GetRenderWindow();

		// Update player position
		const float frameTime = static_cast<float>(renderWindow.GetFrameTime()) / 1000.0f;
		UpdatePlayerPositionFromInput(&mPlayerPosition, frameTime, mPlayerSpeed);
				
		// Fit player sprite onto the screen
		const sf::Texture * const playerImage = mPlayerSprite->GetTexture();
		assert(playerImage && "Execute: NULL pointer");
		FitInsideScreen(&mPlayerPosition, playerImage->GetWidth(), playerImage->GetHeight(), renderWindow.GetWidth(), 
			renderWindow.GetHeight());
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
		mEnemy.Update(frameTime, enemyImage->GetWidth(), enemyImage->GetHeight(), renderWindow.GetWidth(), renderWindow.GetHeight());
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

		mMap->update();
		mMap->draw();

		mBackgroundItemsGenerator->update();
		mBackgroundItemsGenerator->draw();

		// Draw player ship and bullets
		for(uint8_t i = 0; i < sPlayerBullets; ++i)
		{
			if(mPlayerBulletsPositions[i].y != FLT_MAX)
			{
				mPlayerBulletSprite->SetPosition(mPlayerBulletsPositions[i]);
				renderWindow.Draw(*mPlayerBulletSprite);
			}
		}

		renderWindow.Draw(*mEnemySprite);
		renderWindow.Draw(*mPlayerSprite);	
		//mHud.draw();
	}

	void Level01State::ManageEvents(const sf::Event& ev)
	{
		// Check if we must return to main menu.
		if(ev.Type == sf::Event::KeyPressed)
		{
			if(ev.Key.Code == sf::Keyboard::Escape)
			{				
				StateMachine& stateMachine = mGameManager.GetStateMachine();
				stateMachine.ChangeState(mGameManager.GetMainMenuState());
			}	
		}
	}
	
	void Level01State::Clear()
	{
		ImageManager& imageManager = mGameManager.GetImageManager();
		imageManager.releaseAllResources();
		
		delete mPlayerBulletSprite;
		delete mPlayerSprite;
		delete mEnemySprite;		
		delete mBackgroundItemsGenerator;
		delete mMap;
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

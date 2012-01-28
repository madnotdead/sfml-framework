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

#include "../animators/PlayerAnimator.h"

#include "../entities_generators/EnemysGenerator.h"
#include "../entities_generators/JewelsGenerator.h"

#include "../hud/Hud.h"

#include "../managers/GameManager.h"

#include "../scrolling_map/BackgroundItemsGenerator.h"
#include "../scrolling_map/ScrollingMap.h"

#include "../utilities/Updaters.h"

#include <GameFramework/managers/ImageManager.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <GameFramework/utilities/CollisionDetection.h>

#include "..\hud\HudPopulator.h"

#include <sstream>

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
		, mJewelsGenerator(0)
		, mPlayerAnimator(0)
		, mPlayerPosition(sf::Vector2f(FLT_MAX, FLT_MAX))
		, mPlayerSprite(0)
		, mPlayerBulletSprite(0)
		, mPlayerSpeed(5.0f)
		, mPlayerBulletSpeed(10.0f)
		, mPlayerBulletPower(500)
		, mTimeToWaitToShot(0.5f)
		, mTimeIncrement(0.05f)
		, mElapsedTimeFromLastShot(0.0f)
		, mPlayerMaxHealth(2000)
		, mPlayerCurrentHealth(mPlayerMaxHealth)
		, mHud(0)
		, mEnemyGenerator(0)
		, mHudPopulator(0)
	{
		InitBulletsPosition(sPlayerBullets, mPlayerBulletsPositions);
	}

	void Level01State::Init()
	{
		// Init hud
		mHud = new Hud(mGameManager, 10);

		// The player can shot from the beginning.
		mElapsedTimeFromLastShot = mTimeToWaitToShot;
		
		ImageManager& imageManager = mGameManager.GetImageManager();

		// Init player sprite.
		mPlayerSprite = new  sf::Sprite;
		sf::Texture *image = imageManager.getResource("resources/ships/player/player1.png");
		assert(image && "Init: NULL pointer");
		mPlayerPosition.x = static_cast<float> ((mGameManager.GetRenderWindow().GetWidth() / 2)) - static_cast<float> ((image->GetWidth() / 2));
		mPlayerPosition.y = static_cast<float> ((mGameManager.GetRenderWindow().GetHeight())) - static_cast<float> ((image->GetHeight()));
		mPlayerSprite->SetTexture(*image);
		mPlayerAnimator = new Animator::PlayerAnimator(mGameManager, *mPlayerSprite);
		mPlayerAnimator->addImage(*image); 
		image = imageManager.getResource("resources/ships/player/player2.png"); 
		assert(image && "Init: NULL pointer");
		mPlayerAnimator->addImage(*image);
		image = imageManager.getResource("resources/ships/player/player3.png"); 
		assert(image && "Init: NULL pointer");
		mPlayerAnimator->addImage(*image);
		image = imageManager.getResource("resources/ships/player/player4.png"); 
		assert(image && "Init: NULL pointer");
		mPlayerAnimator->addImage(*image);
		image = imageManager.getResource("resources/ships/player/player5.png"); 
		assert(image && "Init: NULL pointer");
		mPlayerAnimator->addImage(*image);
		mPlayerAnimator->startImageChangingTimer(17 * 10); 
					
		// Init player bullets.
		image = imageManager.getResource("resources/bullets/bullet.png");
		assert(image && "Init: NULL pointer");
		mPlayerBulletSprite = new sf::Sprite;
		mPlayerBulletSprite->SetTexture(*image); 
		InitBulletsPosition(sPlayerBullets, mPlayerBulletsPositions);

		// All the bullets are deactivated.
		for (size_t i = 0; i < sPlayerBullets; ++i)
			mPlayerBulletsState[i] = false;

		// Init Map
		mMap = new ScrollingMap(mGameManager);
		image = imageManager.getResource("resources/background/level1a.jpg");
		assert(image && "Init: NULL pointer");		
		sf::Texture *image2 = imageManager.getResource("resources/background/level1b.jpg");
		assert(image2 && "Init: NULL pointer");
		mMap->initMap(*image, *image2);
		mMap->setScrollingSpeed(2.0f);

		// Init background items generator.
		mBackgroundItemsGenerator = new BackgroundItemsGenerator(mGameManager);
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
		mBackgroundItemsGenerator->startGeneration(10000);		

		// Init jewels generator.
		mJewelsGenerator = new JewelsGenerator(mGameManager, *mHud);
		mHudPopulator = new HudPopulator(*mHud, *mJewelsGenerator);
		image = imageManager.getResource("resources/jewels/small/darkGreen.png");
		sf::Texture* imageb = imageManager.getResource("resources/jewels/small/darkGreenb.png");
		mHudPopulator->addTextures(imageb, image);
		assert(image && "Init: NULL pointer");
		mJewelsGenerator->addJewel(*image, JewelsGenerator::JewelColor_DarkGreen);
		image = imageManager.getResource("resources/jewels/small/blue.png");
		imageb = imageManager.getResource("resources/jewels/small/blueb.png");
		mHudPopulator->addTextures(imageb, image);
		assert(image && "Init: NULL pointer");
		mJewelsGenerator->addJewel(*image, JewelsGenerator::JewelColor_Blue);
		image = imageManager.getResource("resources/jewels/small/darkYellow.png");
		imageb = imageManager.getResource("resources/jewels/small/darkYellowb.png");
		mHudPopulator->addTextures(imageb, image);
		assert(image && "Init: NULL pointer");
		mJewelsGenerator->addJewel(*image, JewelsGenerator::JewelColor_DarkYellow);
		image = imageManager.getResource("resources/jewels/small/lightGreen.png");
		imageb = imageManager.getResource("resources/jewels/small/lightGreenb.png");
		mHudPopulator->addTextures(imageb, image);
		assert(image && "Init: NULL pointer");
		mJewelsGenerator->addJewel(*image, JewelsGenerator::JewelColor_LightGreen);
		image = imageManager.getResource("resources/jewels/small/lightYellow.png");
		imageb = imageManager.getResource("resources/jewels/small/lightYellowb.png");
		mHudPopulator->addTextures(imageb, image);
		assert(image && "Init: NULL pointer");
		mJewelsGenerator->addJewel(*image, JewelsGenerator::JewelColor_LightYellow);
		image = imageManager.getResource("resources/jewels/small/violet.png");
		imageb = imageManager.getResource("resources/jewels/small/violetb.png");
		mHudPopulator->addTextures(imageb, image);
		assert(image && "Init: NULL pointer");
		mJewelsGenerator->addJewel(*image, JewelsGenerator::JewelColor_Violet);
		image = imageManager.getResource("resources/jewels/small/orange.png");
		imageb = imageManager.getResource("resources/jewels/small/orangeb.png");
		mHudPopulator->addTextures(imageb, image);
		assert(image && "Init: NULL pointer");
		mJewelsGenerator->addJewel(*image, JewelsGenerator::JewelColor_Orange);
		image = imageManager.getResource("resources/jewels/small/pink.png");
		imageb = imageManager.getResource("resources/jewels/small/pinkb.png");
		mHudPopulator->addTextures(imageb, image);
		assert(image && "Init: NULL pointer");
		mJewelsGenerator->addJewel(*image, JewelsGenerator::JewelColor_Pink);
		image = imageManager.getResource("resources/jewels/small/red.png");
		imageb = imageManager.getResource("resources/jewels/small/redb.png");
		mHudPopulator->addTextures(imageb, image);
		assert(image && "Init: NULL pointer");
		mJewelsGenerator->addJewel(*image, JewelsGenerator::JewelColor_Red);
		image = imageManager.getResource("resources/jewels/small/turquesa.png");
		imageb = imageManager.getResource("resources/jewels/small/turquesab.png");
		mHudPopulator->addTextures(imageb, image);
		assert(image && "Init: NULL pointer");
		mJewelsGenerator->addJewel(*image, JewelsGenerator::JewelColor_Turquesa);
		mJewelsGenerator->startGeneration(static_cast<size_t> (static_cast<float> (mMap->getMapHeight() * 17) / (10.0f * mMap->getScrollingSpeed())));	
		mHudPopulator->pouplateHud();

		mGemColider = new GemColider(mGameManager, *mHud, *mHudPopulator);

		// add map textures
		for(size_t i = 0; i < 12; ++i) 
		{
			std::stringstream ss;
			ss << i+1;
			image = imageManager.getResource("resources/hud/map/" + ss.str() + ".png");
			mHud->addMapPositionTexture(image);
		}

		// add life textures
		for(size_t i = 0; i < 11; ++i) 
		{
			std::stringstream ss;
			ss << i+1;
			image = imageManager.getResource("resources/hud/health/" + ss.str() + ".png");
			mHud->addLifeTexture(image);
		}

		mHud->setLife(5);

		// Init enemy generator.
		mEnemyGenerator = new EnemysGenerator(mGameManager);
		image = imageManager.getResource("resources/enemies/iceCream.png");
		assert(image && "Init: NULL pointer");
		mEnemyGenerator->addEnemy(*image, false, EnemysGenerator::LINEAR);
		image = imageManager.getResource("resources/enemies/egg.png");
		assert(image && "Init: NULL pointer");
		mEnemyGenerator->addEnemy(*image, false, EnemysGenerator::LINEAR, 2.0f);
		image = imageManager.getResource("resources/enemies/chupetin.png");
		assert(image && "Init: NULL pointer");
		mEnemyGenerator->addEnemy(*image, false, EnemysGenerator::LINEAR, 2.0f);
		mEnemyGenerator->startGeneration(2000);
	}

	void Level01State::Execute()
	{
		sf::RenderWindow& renderWindow = mGameManager.GetRenderWindow();

		// Update player position
		UpdatePlayerPositionFromInput(mPlayerPosition, mPlayerSpeed);
				
		// Fit player sprite onto the screen
		const sf::Texture * const playerImage = mPlayerSprite->GetTexture();
		assert(playerImage && "Execute: NULL pointer");
		FitInsideScreen(mPlayerPosition, playerImage->GetWidth(), playerImage->GetHeight(), renderWindow.GetWidth(), renderWindow.GetHeight());
		mPlayerSprite->SetPosition(mPlayerPosition);

		mCollisionHelper.PlayerBulletsAndEnemiesCollisions(mEnemyGenerator->getEnemies(), mPlayerBulletsPositions, sPlayerBullets, mPlayerBulletsState, 
			mPlayerBulletSprite->GetTexture()->GetWidth(), mPlayerBulletSprite->GetTexture()->GetHeight());

		// Update player bullet positions
		UpdatePlayerBulletsPositions(sPlayerBullets, mPlayerBulletsPositions, mPlayerBulletsState, mPlayerBulletSpeed);
		UpdatePlayerBulletsState(sPlayerBullets, mPlayerBulletsPositions, mPlayerBulletsState, mPlayerBulletSprite->GetTexture()->GetHeight());

		// Check if the player shoot.
		mElapsedTimeFromLastShot += mTimeIncrement;
		if(mTimeToWaitToShot <= mElapsedTimeFromLastShot)
		{
			const sf::Texture * const bulletImage = mPlayerBulletSprite->GetTexture();
			assert(bulletImage && "Execute: NULL pointer");

			if(UpdateBulletsFromInput(sPlayerBullets, mPlayerBulletsPositions, mPlayerBulletsState, mPlayerPosition, playerImage->GetWidth(), bulletImage->GetWidth()))
				mElapsedTimeFromLastShot = 0.0f;
		}

		mMap->update();
		mMap->draw();

		mBackgroundItemsGenerator->update();
		mBackgroundItemsGenerator->draw();

		mJewelsGenerator->update();
		mJewelsGenerator->draw();

		// Draw enemies.
		mEnemyGenerator->draw();

		// Draw player ship and bullets
		for(uint8_t i = 0; i < sPlayerBullets; ++i)
		{
			if(mPlayerBulletsState[i])
			{
				mPlayerBulletSprite->SetPosition(mPlayerBulletsPositions[i]);
				renderWindow.Draw(*mPlayerBulletSprite);
			}
		}
		
		renderWindow.Draw(*mPlayerSprite);	
		mHud->draw();

		mGemColider->update(*mPlayerSprite, mJewelsGenerator->getItemPool());
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
		delete mBackgroundItemsGenerator;
		delete mJewelsGenerator;
		delete mPlayerAnimator;
		delete mEnemyGenerator;
		delete mMap;
		delete mHud;
	}	
}

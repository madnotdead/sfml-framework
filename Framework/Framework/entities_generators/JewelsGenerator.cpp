#include "JewelsGenerator.h"

#include <time.h>

#include "../managers/GameManager.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace Game
{
	JewelsGenerator::JewelsGenerator(GameManager& gameManager, Hud& hud)
		: mGamemanager(gameManager)
		, mTimer(timerGenerateItem, this)
		, mCurrentItem(0)
		, mHud(hud)
	{
		srand(static_cast<uint32_t> (time(0)));
	}

	JewelsGenerator::~JewelsGenerator()
	{
		for (size_t i = 0; i < mItemsPools.size(); ++i)
		{
			delete mItemsPools[i].mSprite;
		}

		mGamemanager.GetTimerManager().unregisterTimer(mTimer);
	}

	void JewelsGenerator::addJewel(sf::Texture& image, const JewelColor color)
	{
		sf::Vector2f randomPosition;
		randomPosition.y = - static_cast<float> (image.GetHeight());
		randomPosition.x = static_cast<float> (rand() % (mGamemanager.GetRenderWindow().GetWidth() - image.GetWidth()));

		const float randomSpeed = static_cast<float> ((rand() % 3) + 1);

		Item item;
		item.mSprite = new sf::Sprite;
		item.mSprite->SetTexture(image);
		item.mSprite->SetPosition(randomPosition);
		item.mSpeed = randomSpeed;
		item.mColor = color;
		item.isActive = false;
		mItemsPools.push_back(item);
		mBackupPositions.push_back(randomPosition);
	}

	void JewelsGenerator::startGeneration(const size_t milliseconds)
	{
		mGamemanager.GetTimerManager().registerTimer(mTimer);
		mTimer.start(milliseconds);
	}

	void JewelsGenerator::update()
	{
		for (size_t i = 0; i < mItemsPools.size(); ++i)
		{
			// Update the items that must be drawn.
			if (mItemsPools[i].isActive)
			{
				// Check if the item must be deactivated.
				const sf::Vector2f itemPosition = mItemsPools[i].mSprite->GetPosition();
				if (itemPosition.y > mGamemanager.GetRenderWindow().GetHeight())
				{
					mItemsPools[i].isActive = false;
				}

				else
				{
					mItemsPools[i].mSprite->Move(0.0f, mItemsPools[i].mSpeed);
				}
			}
		}
	}

	void JewelsGenerator::draw()
	{
		for (size_t i = 0; i < mItemsPools.size(); ++i)
		{
			if (mItemsPools[i].isActive)
			{
				mGamemanager.GetRenderWindow().Draw(*(mItemsPools[i].mSprite));
			}
		}
	}

	void JewelsGenerator::timerGenerateItem(void *thisClass)
	{
		JewelsGenerator* jewelsGenerator = reinterpret_cast<JewelsGenerator*> (thisClass);
		jewelsGenerator->generateItem();		
	}

	void JewelsGenerator::generateItem()
	{
		if (mCurrentItem + 1 < mItemsPools.size())
		{
			// Load the backup.
			mItemsPools[mCurrentItem].mSprite->SetPosition(mBackupPositions[mCurrentItem]);
			mItemsPools[mCurrentItem].isActive = true;
			++mCurrentItem;
		}

		else
		{
			mItemsPools[mCurrentItem].mSprite->SetPosition(mBackupPositions[mCurrentItem]);
			mItemsPools[mCurrentItem].isActive = true;
			mCurrentItem = 0;
		}
		static size_t pos = 0;
		if(pos == 12) {
			pos = 0;
		}
		mHud.setMapPosition(pos++);
	}
}

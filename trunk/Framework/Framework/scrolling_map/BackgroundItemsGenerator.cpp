#include "BackgroundItemsGenerator.h"

#include <time.h>

#include "../managers/GameManager.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace Game
{
	BackgroundItemsGenerator::BackgroundItemsGenerator(GameManager& gameManager)
		: mGamemanager(gameManager)
		, mTimer(Utils::Timer(timerGenerateItem, this))
	{
		srand(static_cast<uint32_t> (time(0)));
	}

	BackgroundItemsGenerator::~BackgroundItemsGenerator()
	{
		for (size_t i = 0; i < mItemsPools.size(); ++i)
		{
			delete mItemsPools[i].mSprite;
		}

		mGamemanager.GetTimerManager().unregisterTimer(mTimer);
	}

	void BackgroundItemsGenerator::addImage(sf::Texture& image)
	{
		mTextures.push_back(&image);
	}

	void BackgroundItemsGenerator::startGeneration(const size_t milliseconds)
	{
		mGamemanager.GetTimerManager().registerTimer(mTimer);
		mTimer.start(milliseconds);
	}

	void BackgroundItemsGenerator::update()
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

	void BackgroundItemsGenerator::draw()
	{
		for (size_t i = 0; i < mItemsPools.size(); ++i)
		{
			if (mItemsPools[i].isActive)
			{
				mGamemanager.GetRenderWindow().Draw(*(mItemsPools[i].mSprite));
			}
		}
	}

	void BackgroundItemsGenerator::timerGenerateItem(void *thisClass)
	{
		BackgroundItemsGenerator* backgroundItemsGenerator = reinterpret_cast<BackgroundItemsGenerator*> (thisClass);
		backgroundItemsGenerator->generateItem();		
	}

	void BackgroundItemsGenerator::generateItem()
	{
		// Define random data.
		const size_t numberOfTextures = mTextures.size();
		const size_t randomTextureIndex = rand() % numberOfTextures;
		sf::Texture *randomTexture = mTextures[randomTextureIndex];

		sf::Vector2f randomPosition;
		randomPosition.y = - static_cast<float> (randomTexture->GetHeight());
		randomPosition.x = static_cast<float> (rand() % (mGamemanager.GetRenderWindow().GetWidth() - randomTexture->GetWidth()));

		const float randomSpeed = static_cast<float> (rand() % 10);

		// Search an unused sprite in the memory pool. 
		bool inactiveWasFound = false;
		for (size_t i = 0; i < mItemsPools.size(); ++i)
		{
			if (!mItemsPools[i].isActive)
			{
				mItemsPools[i].mSprite->SetTexture(*randomTexture, true);
				mItemsPools[i].mSprite->SetPosition(randomPosition);
				mItemsPools[i].mSpeed = randomSpeed;
				mItemsPools[i].isActive = true;		
				inactiveWasFound = true;
			}
		}

		// Create a new sprite and add it into the items pool.
		if (!inactiveWasFound)
		{
			Item item;
			item.mSprite = new sf::Sprite;
			item.mSprite->SetTexture(*randomTexture);
			item.mSprite->SetPosition(randomPosition);
			item.mSpeed = randomSpeed;
			item.isActive = true;
			mItemsPools.push_back(item);
		}
	}
}

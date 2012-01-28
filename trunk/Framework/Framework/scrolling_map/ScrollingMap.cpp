#include "ScrollingMap.h"

#include <cassert>

#include <GameFramework/utilities/Types.h>

#include <SFML/Graphics/Texture.hpp>

#include "../managers/GameManager.h"

namespace Game
{
	ScrollingMap::ScrollingMap(GameManager& gameManager)
		: mGameManager(gameManager)
		, mMapTile1(new (mGameManager.GetMemoryPool().Alloc(sizeof(sf::Sprite))) sf::Sprite)
		, mMapTile2(new (mGameManager.GetMemoryPool().Alloc(sizeof(sf::Sprite))) sf::Sprite)
		, mScrollingSpeed(0.0f)
	{

	}

	ScrollingMap::~ScrollingMap()
	{
		mGameManager.GetMemoryPool().Free(mMapTile1);
		mGameManager.GetMemoryPool().Free(mMapTile2);
	}

	void ScrollingMap::initMap(const sf::Texture& image)
	{		
		mMapTile1->SetTexture(image);
		const uint32_t windowHeight = mGameManager.GetRenderWindow().GetHeight();
		const uint32_t imageHeight = mMapTile1->GetTexture()->GetHeight();
		int beginOffset = windowHeight - imageHeight;
		mMapTile1->SetPosition(0.0f, beginOffset);

		mMapTile2->SetTexture(image);
		beginOffset = mMapTile1->GetPosition().y - imageHeight;
		mMapTile2->SetPosition(0.0f, beginOffset);
	}

	void ScrollingMap::update() 
	{
		const sf::Vector2f& tile1Position = mMapTile1->GetPosition();
		const sf::Vector2f& tile2Position = mMapTile2->GetPosition();
		const uint32_t windowHeight = mGameManager.GetRenderWindow().GetHeight();
		if (tile1Position.y >= windowHeight) 
		{
			const uint32_t imageHeight = mMapTile1->GetTexture()->GetHeight();
			mMapTile1->Move(0.0f, -imageHeight);
		}

		else if (tile2Position.y >= windowHeight) 
		{
			const uint32_t imageHeight = mMapTile1->GetTexture()->GetHeight();
			mMapTile2->Move(0.0f, -imageHeight);
		}

		else
		{
			// Update the current map position.
			mMapTile1->Move(0.0f, mScrollingSpeed);
			mMapTile2->Move(0.0f, mScrollingSpeed);
		}
	}

	void ScrollingMap::draw()
	{
		assert(mMapTile1 && "ScrollingMap::draw: NULL pointer");
		assert(mMapTile2 && "ScrollingMap::draw: NULL pointer");

		mGameManager.GetRenderWindow().Draw(*mMapTile1);
		mGameManager.GetRenderWindow().Draw(*mMapTile2);
	}
}
#include "ScrollingMap.h"

#include <cassert>

#include <SFML/Graphics/RenderWindow.hpp>

#include "../managers/GameManager.h"

namespace Game
{
	ScrollingMap::ScrollingMap(GameManager& gameManager)
		: mGameManager(gameManager)
		, mMapTile1(new sf::Sprite)
		, mMapTile2(new sf::Sprite)
		, mScrollingSpeed(0.0f)
	{

	}

	ScrollingMap::~ScrollingMap()
	{
		delete mMapTile1;
		delete mMapTile2;
	}

	void ScrollingMap::initMap(const sf::Texture& image)
	{		
		mMapTile1->SetTexture(image);
		const uint32_t windowHeight = mGameManager.GetRenderWindow().GetHeight();
		const uint32_t imageHeight = mMapTile1->GetTexture()->GetHeight();
		int beginOffset = windowHeight - imageHeight;
		mMapTile1->SetPosition(0.0f, static_cast<float> (beginOffset));

		mMapTile2->SetTexture(image);
		beginOffset = static_cast<int> (mMapTile1->GetPosition().y) - imageHeight;
		mMapTile2->SetPosition(0.0f, static_cast<float> (beginOffset));
	}

	void ScrollingMap::update() 
	{
		const sf::Vector2f& tile1Position = mMapTile1->GetPosition();
		const sf::Vector2f& tile2Position = mMapTile2->GetPosition();
		const uint32_t windowHeight = mGameManager.GetRenderWindow().GetHeight();
		if (tile1Position.y >= windowHeight) 
		{
			const uint32_t imageHeight = mMapTile1->GetTexture()->GetHeight();
			int beginOffset = static_cast<int> (mMapTile2->GetPosition().y) - imageHeight;
			mMapTile1->SetPosition(0.0f, static_cast<float> (beginOffset));
		}

		if (tile2Position.y >= windowHeight) 
		{
			const uint32_t imageHeight = mMapTile2->GetTexture()->GetHeight();
			int beginOffset = static_cast<int> (mMapTile1->GetPosition().y) - imageHeight;
			mMapTile2->SetPosition(0.0f, static_cast<float> (beginOffset));
		}

		// Update the current map position.
		mMapTile1->Move(0.0f, mScrollingSpeed);
		mMapTile2->Move(0.0f, mScrollingSpeed);		
	}

	void ScrollingMap::draw()
	{
		assert(mMapTile1 && "ScrollingMap::draw: NULL pointer");
		assert(mMapTile2 && "ScrollingMap::draw: NULL pointer");

		mGameManager.GetRenderWindow().Draw(*mMapTile1);
		mGameManager.GetRenderWindow().Draw(*mMapTile2);
	}

	float ScrollingMap::getMapYPosition() const
	{	
		const float toPositiveRange = mMapTile1->GetPosition().y + mMapTile1->GetTexture()->GetHeight() * 2 - mGameManager.GetRenderWindow().GetHeight();
		return toPositiveRange * (100.0f / mMapTile1->GetTexture()->GetHeight());
	}
}
#include "ScrollingMap.h"

#include <cassert>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../managers/GameManager.h"

namespace Game
{
	ScrollingMap::ScrollingMap(GameManager& gameManager)
		: mGameManager(gameManager)
		, mMap(new (mGameManager.GetMemoryPool().Alloc(sizeof(sf::Sprite))) sf::Sprite)
	{

	}

	ScrollingMap::~ScrollingMap()
	{
		mGameManager.GetMemoryPool().Free(mMap);
	}

	void ScrollingMap::initMap(const sf::Texture& image)
	{		
		mMap->SetTexture(image);
		mMap->SetPosition(0.0f, 0.0f);
	}

	void ScrollingMap::update() 
	{

	}

	void ScrollingMap::draw()
	{
		assert(mMap && "ScrollingMap::draw: NULL pointer");

		mGameManager.GetRenderWindow().Draw(*mMap);
	}
}
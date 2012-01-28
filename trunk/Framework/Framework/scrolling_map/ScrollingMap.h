#ifndef GAME_SCROLLING_MAP_H
#define GAME_SCROLLING_MAP_H

#include <string>

#include <GameFramework/utilities/Types.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace Game
{
	class GameManager;

	class ScrollingMap
	{
	public:
		ScrollingMap(GameManager& gameManager);
		~ScrollingMap();
		
		void initMap(const sf::Texture& image1, const sf::Texture& image2);

		inline void setScrollingSpeed(const float scrollingSpeed);
		inline float getScrollingSpeed() const;
		inline uint32_t getMapHeight() const;
		void update();
		void draw();

		float getMapYPosition() const;

	private:
		GameManager& mGameManager;
		sf::Sprite *mMapTile1;
		sf::Sprite *mMapTile2;
		float mScrollingSpeed;
	};

	void ScrollingMap::setScrollingSpeed(const float scrollingSpeed) 
	{ 
		mScrollingSpeed = scrollingSpeed; 
	}

	inline float ScrollingMap::getScrollingSpeed() const
	{
		return mScrollingSpeed;
	}

	inline uint32_t ScrollingMap::getMapHeight() const
	{
		return mMapTile1->GetTexture()->GetHeight() + mMapTile2->GetTexture()->GetHeight();
	}
}

#endif // GAME_SCROLLING_MAP_H

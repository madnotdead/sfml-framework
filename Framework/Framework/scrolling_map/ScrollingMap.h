#ifndef GAME_SCROLLING_MAP_H
#define GAME_SCROLLING_MAP_H

#include <string>

namespace sf
{
	class Sprite;
	class Texture;
}

namespace Game
{
	class GameManager;

	class ScrollingMap
	{
	public:
		ScrollingMap(GameManager& gameManager);
		~ScrollingMap();
		
		void initMap(const sf::Texture& image);

		inline void setScrollingSpeed(const float scrollingSpeed);
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
}

#endif // GAME_SCROLLING_MAP_H

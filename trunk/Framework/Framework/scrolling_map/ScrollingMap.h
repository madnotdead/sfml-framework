#ifndef GAME_SCROLLING_MAP_H
#define GAME_SCROLLING_MAP_H

#include <string>

#include <SFML/Graphics/Sprite.hpp>

namespace sf
{
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
		inline float getMapYPosition() const;
		void update();
		void draw();

	private:
		//std::vector<sf::Sprite*> mMapElements;
		GameManager& mGameManager;
		sf::Sprite *mMapTile1;
		sf::Sprite *mMapTile2;
		float mScrollingSpeed;
	};

	void ScrollingMap::setScrollingSpeed(const float scrollingSpeed) 
	{ 
		mScrollingSpeed = scrollingSpeed; 
	}

	float ScrollingMap::getMapYPosition() const
	{
		return mMapTile1->GetPosition().y;
	}
}

#endif // GAME_SCROLLING_MAP_H

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
		//void addElement(const sf::Texture& image);

		void update();
		void draw();

	private:
		//std::vector<sf::Sprite*> mMapElements;
		GameManager& mGameManager;
		sf::Sprite *mMap;
	};
}

#endif // GAME_SCROLLING_MAP_H

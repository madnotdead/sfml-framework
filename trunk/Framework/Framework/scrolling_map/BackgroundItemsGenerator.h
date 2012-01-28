#ifndef GAME_GAME_ITEMS_GENERATOR_H_H
#define GAME_GAME_ITEMS_GENERATOR_H_H

#include <vector>

#include <GameFramework/utilities/Timer.h>

namespace sf
{
	class Sprite;
	class Texture;
}

namespace Game
{
	class GameManager;

	class BackgroundItemsGenerator
	{
	public:
		BackgroundItemsGenerator(GameManager& gameManager);
		~BackgroundItemsGenerator();

		void addImage(sf::Texture& image);
		
		void startGeneration(const size_t milliseconds);

		void update();

		void draw();

		// This function is used by the timer to decorate background.
		static void timerGenerateItem(void *thisClass);

		void generateItem();

	private:
		struct Item
		{
			Item() 
				: mSprite(0)
				, mSpeed(0.0f)
				, isActive(false)
			{

			}
			
			sf::Sprite *mSprite;
			float mSpeed;
			bool isActive;
		};

		std::vector<Item> mItemsPools;
		std::vector<sf::Texture*> mTextures;
		GameManager& mGamemanager;
		Utils::Timer mTimer;
	};
}

#endif // GAME_BACKGROUND_DECORATOR_H

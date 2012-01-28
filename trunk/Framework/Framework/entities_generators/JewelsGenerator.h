#ifndef GAME_GAME_JEWELS_GENERATOR_H_H
#define GAME_GAME_JEWELS_GENERATOR_H_H

#include <vector>

#include <GameFramework/utilities/Timer.h>

#include <SFML/System/Vector2.hpp>

namespace sf
{
	class Sprite;
	class Texture;
}

namespace Game
{
	class GameManager;

	class JewelsGenerator
	{
	public:
		enum JewelColor
		{
			JewelColor_Red = 0,
			JewelColor_Blue,
			JewelColor_LightYellow,
			JewelColor_DarkYellow,
			JewelColor_Pink,
			JewelColor_Orange,
			JewelColor_LightGreen,
			JewelColor_DarkGreen,
			JewelColor_Violet,
			JewelColor_Turquesa,
			JewelColor_Invalid,
		};

		JewelsGenerator(GameManager& gameManager);
		~JewelsGenerator();

		void addJewel(sf::Texture& image, const JewelColor color);

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
				, mColor(JewelColor_Invalid)
				, isActive(false)
			{

			}

			sf::Sprite *mSprite;
			float mSpeed;
			JewelColor mColor;
			bool isActive;
		};

		std::vector<Item> mItemsPools;
		std::vector<sf::Vector2f> mBackupPositions;
		GameManager& mGamemanager;
		Utils::Timer mTimer;
		size_t mCurrentItem;
	};
}

#endif // GAME_JEWELS_GENERATOR_H

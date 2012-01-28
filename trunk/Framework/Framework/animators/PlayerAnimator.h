#ifndef ANIMATORS_PLAYER_ANIMATOR_H
#define ANIMATORS_PLAYER_ANIMATOR_H

#include <vector>

#include <GameFramework/utilities/Timer.h>

namespace Game
{
	class GameManager;
}

namespace sf
{
	class Sprite;
	class Texture;
}

namespace Animator
{
	class PlayerAnimator
	{
	public:
		PlayerAnimator(Game::GameManager &gameManager, sf::Sprite& player);
		~PlayerAnimator();

		void startImageChangingTimer(const size_t milliseconds);
		void addImage(sf::Texture& image);

		static void timerCallback(void *thisClass);

		// Used only for timerCallback
		void updateSprite();

	private:
		std::vector<sf::Texture*> mTextures;
		sf::Sprite &mSprite;
		Game::GameManager &mGameManager;
		Utils::Timer mTimer;
		size_t mCurrentTexture;
	};
}

#endif // ANIMATORS_PLAYER_ANIMATOR_H

#include "PlayerAnimator.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../managers/GameManager.h"

namespace Animator
{
	PlayerAnimator::PlayerAnimator(Game::GameManager &gameManager, sf::Sprite& player)
		: mSprite(player)
		, mGameManager(gameManager)
		, mTimer(timerCallback, this)
		, mCurrentTexture(0)
	{

	}

	PlayerAnimator::~PlayerAnimator()
	{
		mGameManager.GetTimerManager().unregisterTimer(mTimer);
	}

	void PlayerAnimator::startImageChangingTimer(const size_t milliseconds)
	{
		mGameManager.GetTimerManager().registerTimer(mTimer);
		mTimer.start(milliseconds);
	}

	void PlayerAnimator::addImage(sf::Texture& image)
	{
		mTextures.push_back(&image);
	}

	void PlayerAnimator::timerCallback(void *thisClass)
	{
		PlayerAnimator *playerAnimator = reinterpret_cast<PlayerAnimator *> (thisClass);
		playerAnimator->updateSprite();
	}

	void PlayerAnimator::updateSprite()
	{
		if (mCurrentTexture + 1 < mTextures.size())
		{
			mSprite.SetTexture(*(mTextures[mCurrentTexture]));
			++mCurrentTexture;
		}

		else
		{
			mSprite.SetTexture(*(mTextures[mCurrentTexture]));
			mCurrentTexture = 0;
		}
	}
}


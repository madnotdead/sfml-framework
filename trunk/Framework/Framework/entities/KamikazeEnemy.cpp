//////////////////////////////////////////////////////////////////////////
//
// File: KamikazeEnemy.cpp
//
// Desc: Enemy who go directly to the player without bullets.
//
// Author: Bertoa Nicolas - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#include <cassert>
#include "../utilities/Types.h"

#include "KamikazeEnemy.h"

namespace Game
{
	KamikazeEnemy::KamikazeEnemy(const sf::Vector2f& position, const float speed, const uint32_t health)
		: mPosition(position)
		, mSpeed(speed)
		, mHealth(health)
		, mDirection(MovementDirection_Left)

	{

	}

	void KamikazeEnemy::Update(const float frameTime, const uint32_t enemyWidth, const uint32_t enemyHeight, const uint32_t windowWidth,
		const uint32_t windowHeight)
	{
		const float finalSpeed = mSpeed * frameTime;
		if(mDirection == MovementDirection_Left)
		{
			mPosition.x -= finalSpeed;

			if(mPosition.x <= 0.0f)
			{
				mPosition.x = 0.0f;
				mDirection = MovementDirection_Down;
			}
		}

		if(mDirection == MovementDirection_Down)
		{
			mPosition.y += finalSpeed;

			const float downScreenLimit = static_cast<float>(windowHeight - enemyHeight);
			if(downScreenLimit <= mPosition.y)
			{
				mPosition.y = downScreenLimit;
				mDirection = MovementDirection_Right;
			}
		}

		if(mDirection == MovementDirection_Right)
		{
			mPosition.x += finalSpeed;

			const float rightLimit = static_cast<float>(windowWidth - enemyWidth);
			if(rightLimit <= mPosition.x)
			{
				mPosition.x = rightLimit;
				mDirection = MovementDirection_Up;
			}
		}

		if(mDirection == MovementDirection_Up)
		{
			mPosition.y -= finalSpeed;

			if(mPosition.y <= 0.0f)
			{
				mPosition.y = 0.0f;
				mDirection = MovementDirection_Left;
			}
		}
	}
}

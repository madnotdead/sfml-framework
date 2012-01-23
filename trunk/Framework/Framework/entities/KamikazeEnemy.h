//////////////////////////////////////////////////////////////////////////
//
// File: KamikazeEnemy.h
//
// Desc: Enemy who go directly to the player without bullets.
//
// Author: Bertoa Nicolas - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#ifndef KAMIKAZE_ENEMY_H
#define KAMIKAZE_ENEMY_H

#include "../utilities/Types.h"

#include <SFML/System/Vector2.hpp>

namespace Game
{
	class KamikazeEnemy
	{
	public:
		KamikazeEnemy(const sf::Vector2f& position, const float speed, const uint32_t health);

	public:
		void Update(const float frameTime, const uint32_t width, const uint32_t height, const uint32_t windowWidth,
			const uint32_t windowHeight);

	public:
		sf::Vector2f mPosition;
		float mSpeed;
		uint32_t mHealth;
	
	private:
		enum MovementDirection
		{
			MovementDirection_Up,
			MovementDirection_Down,
			MovementDirection_Left,
			MovementDirection_Right
		};

		MovementDirection mDirection;
	};
}

#endif // KAMIKAZE_ENEMY_H

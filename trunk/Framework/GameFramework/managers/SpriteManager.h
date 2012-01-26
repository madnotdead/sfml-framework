#ifndef GAME_SPRITE_MANAGER_H
#define GAME_SPRITE_MANAGER_H

#include <string>

#include <SFML/Graphics/Sprite.hpp>

#include "ResourceManager.h"

namespace Utils
{
	class MemoryPool;
}

namespace Game
{
	class SpriteManager : public ResourceManager<sf::Sprite> 
	{
	public:
		SpriteManager(Utils::MemoryPool& memoryPool);

	protected:
		sf::Sprite* load(const std::string& strId);
	};
}

#endif // GAME_SPRITE_MANAGER_H

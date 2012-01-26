#include <cassert>
#include "../utilities/Types.h"

#include "SpriteManager.h"

#include "../utilities/MemoryPool.h"

namespace Game
{
	SpriteManager::SpriteManager(Utils::MemoryPool& memoryPool)
		: ResourceManager(memoryPool)
	{
	}

	sf::Sprite* SpriteManager::load(const std::string& strId) 
	{
		strId; // Not used

		sf::Sprite *sprite = reinterpret_cast<sf::Sprite *>(mMemoryPool.Alloc(sizeof(sf::Sprite)));
		
		return new (sprite) sf::Sprite;
	}
}

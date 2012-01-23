#include <cassert>
#include "../utilities/Types.h"

#include "SpriteManager.h"

#include "../utilities/MemoryPool.h"

namespace Game
{
	SpriteManager::SpriteManager(::Utils::MemoryPool * const memoryPool)
		: ResourceManager(memoryPool)
	{
		assert(mMemoryPool && "SpriteManager: NULL pointer");
	}

	sf::Sprite* SpriteManager::load(const std::string& strId) 
	{
		strId; // Not used

		assert(mMemoryPool && "load: NULL pointer");
		sf::Sprite *sprite = reinterpret_cast<sf::Sprite *>(mMemoryPool->Alloc(sizeof(sf::Sprite)));
		
		return new (sprite) sf::Sprite;
	}
}

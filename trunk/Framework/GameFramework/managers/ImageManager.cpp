#include <cassert>
#include "../utilities/Types.h"

#include "ImageManager.h"

namespace Game
{
	ImageManager::ImageManager(Utils::MemoryPool& memoryPool)
		: ResourceManager(memoryPool)
	{
	}

	sf::Texture* ImageManager::load(const std::string& strId) 
	{
		sf::Texture *image = reinterpret_cast<sf::Texture *>(mMemoryPool.Alloc(sizeof(sf::Texture)));
		new (image) sf::Texture;
		if(!image->LoadFromFile(strId)) 
		{
			mMemoryPool.Free(image);
			image = 0;
		}

		return image;
	}
}
#ifndef GAME_IMAGE_MANAGER_H
#define GAME_IMAGE_MANAGER_H

#include <string>

#include <SFML/Graphics/Texture.hpp>

#include "ResourceManager.h"

namespace Utils
{
	class MemoryPool;
}

namespace Game
{
	class ImageManager : public ResourceManager<sf::Texture> 
	{
	public:
		ImageManager(Utils::MemoryPool& memoryPool);

	protected:
		sf::Texture* load(const std::string& strId);
	};
}

#endif // GAME_IMAGE_MANAGER_H

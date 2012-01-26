#include "SoundManager.h"

#include <cassert>

#include "../utilities/MemoryPool.h"
#include "../utilities/Types.h"

namespace Game
{
	SoundManager::SoundManager(Utils::MemoryPool& memoryPool)
		: ResourceManager(memoryPool)
	{
	}

	sf::SoundBuffer* SoundManager::load(const std::string& strId) 
	{
		sf::SoundBuffer *soundBuffer = reinterpret_cast<sf::SoundBuffer *> (mMemoryPool.Alloc(sizeof(sf::SoundBuffer)));
		new (soundBuffer) sf::SoundBuffer;
		if(!soundBuffer->LoadFromFile(strId)) 
		{
			mMemoryPool.Free(soundBuffer);
			soundBuffer = 0;
		}

		return soundBuffer;
	}
}

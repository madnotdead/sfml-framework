#include "HudPopulator.h"
#include "..\entities_generators\JewelsGenerator.h"
#include <cstdlib>
#include <algorithm>
#include "..\hud\Hud.h"

void Game::HudPopulator::pouplateHud()
{
	std::vector<JewelsGenerator::Item>& itemPool = mJewelsGenerator.getItemPool();
	int maxIndex = itemPool.size();
	while(mIndices.size() != maxIndex) {
		int rnd = (rand()%maxIndex); 
		std::vector<size_t>::iterator it;
		it = std::find(mIndices.begin(), mIndices.end(), rnd);
		if(it == mIndices.end()) {
			mIndices.push_back(rnd);
		}
	}
	for(size_t i = 0; i < mIndices.size(); ++i) {
		mHud.addItem(mTextures[mIndices[i]].first, mTextures[mIndices[i]].second);
	}
}

Game::HudPopulator::HudPopulator( Hud& hud, JewelsGenerator& jewelsGenerator ) : mHud(hud), mJewelsGenerator(jewelsGenerator)
{
	
}

void Game::HudPopulator::addTextures( const sf::Texture* offTexture, const sf::Texture* onTexture )
{	
	mTextures.push_back(std::make_pair(offTexture, onTexture));
}

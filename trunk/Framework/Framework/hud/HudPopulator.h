#pragma once
#include <vector>
#include <utility>
#include <SFML/Graphics/Texture.hpp>


namespace Game {
	class Hud;
	class JewelsGenerator;

class HudPopulator {
public:
	HudPopulator(Hud& hud, JewelsGenerator& jewelsGenerator);
	void pouplateHud();
	void addTextures(const sf::Texture* offTexture, const sf::Texture* onTexture);

private:
	Hud& mHud;
	JewelsGenerator& mJewelsGenerator;
	std::vector<size_t> mIndices;
	std::vector<std::pair<const sf::Texture*, const sf::Texture*> > mTextures;
};
}
#pragma once
#include <vector>
#include "..\entities_generators\JewelsGenerator.h"
#include <SFML\Graphics\Sprite.hpp>

namespace Game {
class GameManager;
class Hud;
class HudPopulator;

class GemColider {
public:
	GemColider(GameManager& gameManager, Hud& hud, HudPopulator& hudPopulator);
	void update(const sf::Sprite& ship, std::vector<JewelsGenerator::Item>& jewels);

private:
	GameManager& mGameManager;
	Hud& mHud;
	HudPopulator& mHudPopulator;
	size_t mCurrentIndex;
};
}
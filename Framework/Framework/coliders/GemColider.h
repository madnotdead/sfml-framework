#pragma once
#include <vector>
#include "..\entities_generators\JewelsGenerator.h"
#include <SFML\Graphics\Sprite.hpp>

namespace sf
{
	class Sound;
}

namespace Game {
class GameManager;
class Hud;
class HudPopulator;

class GemColider {
public:
	GemColider(GameManager& gameManager, Hud& hud, HudPopulator& hudPopulator, sf::Sound& rightSelection, sf::Sound& wrongSelection);
	void update(const sf::Sprite& ship, std::vector<JewelsGenerator::Item>& jewels);

private:
	GameManager& mGameManager;
	Hud& mHud;
	HudPopulator& mHudPopulator;
	size_t mCurrentIndex;
	sf::Sound &mRightSelection;
	sf::Sound &mWrongSelection;
};
}
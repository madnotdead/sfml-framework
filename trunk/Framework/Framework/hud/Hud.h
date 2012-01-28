#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

namespace Game {

class GameManager;

struct HudInfo {
	enum STATE {OFF, ON};
	STATE state;
	const sf::Texture* offTexture;
	const sf::Texture* onTexture;
	sf::Vector2f position;
	HudInfo() : state(OFF), offTexture(NULL), onTexture(NULL) {}
};

class Hud {
public:
	Hud (GameManager& gameManager, size_t textureCount);
	void addItem(const sf::Texture* offTexture, const sf::Texture* onTexture);
	void draw();
	void turnOn();	
	void turnOff();	
	void clear();

	// circle
	void addCircle(const sf::Texture* circle);
	void addMovingPart(const sf::Texture* part);
	void setPartRotation(float mapPosition); // 0 to 100

private:

void updateNextPosition();
std::vector<HudInfo> mHudInfo;
GameManager& mGameManager;
sf::Vector2f mNextPosition;
size_t mCurrentIndex;

const sf::Texture* mCircle;
const sf::Texture* mPart;
float mPartRotation;





};

}
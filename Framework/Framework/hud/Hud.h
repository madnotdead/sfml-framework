#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

namespace Game {

class GameManager;

struct BallInfo {
	enum STATE {OFF, ON};
	STATE state;
	const sf::Texture* offTexture;
	const sf::Texture* onTexture;
	sf::Vector2f position;
	BallInfo() : state(OFF), offTexture(NULL), onTexture(NULL) {}
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
	void addLifeTexture(const sf::Texture* texture);
	void addMapPositionTexture(const sf::Texture* texture);
	void setLife(size_t life);
	void setMapPosition(size_t mapPos);


private:

void updateNextPosition();
std::vector<BallInfo> mHudInfo;
GameManager& mGameManager;
sf::Vector2f mNextPosition;
size_t mCurrentIndex;

std::vector<const sf::Texture*> mLifeInfo;
std::vector<const sf::Texture*> mMapInfo;
size_t mMapPosition;
size_t mLife;





};

}
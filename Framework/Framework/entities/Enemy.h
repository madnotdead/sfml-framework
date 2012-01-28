#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cstdlib>
#include "..\algorithms\Algorithm.h"

namespace Game {
	class GameManager;

	class Enemy {
	public:
		Enemy(GameManager& gameManager);
		sf::Sprite* getSprite();
		void draw();
		~Enemy();
		void setTexture (const sf::Texture* texture);
		bool isActive () {return mActive;}
		void restart();
		void disable() { mActive = false;}

	private:
		Algorithm* getAlgorithm();
		
		sf::Sprite mSprite;
		float mSpeed;
		GameManager& mGameManager;
		Algorithm* mAlgorithm;
		
		const sf::Texture* mEnemyImage;
		bool mActive;


	};
}
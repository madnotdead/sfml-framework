//////////////////////////////////////////////////////////////////////////
//
// File: InformationState.h
//
// Desc: Abstract state that provides functionality to states that
//       will need to show information on the screen like main menu, 
//       controls, game explanation, credits, etc.
//
// Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_INFORMATION_STATE_H
#define GAME_INFORMATION_STATE_H

#include <string>

#include <SFML/Graphics/Color.hpp>

#include <GameFramework/state_machine/State.h>

namespace sf
{
	class Font;
	class Sprite;
	class Text;
}

namespace Game
{
	class GameManager;
	class ImageManager;
	
	class InformationState : public State
	{
	public:
		InformationState(GameManager * const gameManager);

	public:
		void Init();

		void Execute();

		void ManageEvents(const sf::Event& ev);

		virtual void Clear();

	protected:

		virtual void LoadResources();
		virtual void DestroyResources();

		void InitFont();
		void InitText();

		void Draw();
		virtual void DrawContent() = 0;

		void DisplayText(const std::string& body, const float xPos, const float yPos, const sf::Color& color);

		sf::Sprite *mBackgroundSprite;
		
		sf::Font *mFont;
		sf::Text *mText;
	};
}

#endif // GAME_INFORMATION_STATE_H
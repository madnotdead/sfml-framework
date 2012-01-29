#include "CongratulationsState.h"

#include <cassert>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>

#include "MainMenuState.h"

#include <GameFramework/state_machine/StateMachine.h>

#include "../managers/GameManager.h"
#include <GameFramework/managers/ImageManager.h>

namespace Game
{
	CongratulationsState::CongratulationsState(GameManager& gameManager) 
		: State(gameManager)
		, mBackgroundSprite(0) 
		, mDelayForNextState(0.0f)
		, mMusic(0)
	{
	}

	void CongratulationsState::Init()
	{
		LoadResources();
	}

	void CongratulationsState::Execute()
	{
		sf::RenderWindow& renderWindow = mGameManager.GetRenderWindow();
		StateMachine& stateMachine = mGameManager.GetStateMachine();

		// Check if we must show the thanks message or change the state.
		if(mDelayForNextState > 0.0f)
		{
			mDelayForNextState -= 17;
			renderWindow.Draw(*mBackgroundSprite);
		} 

		else
			stateMachine.ChangeState(mGameManager.GetMainMenuState());
	}

	void CongratulationsState::ManageEvents(const sf::Event& ev) 
	{
		ev;
	} 

	void CongratulationsState::Clear()
	{
		DestroyResources();
	}

	void CongratulationsState::LoadResources()
	{
		sf::RenderWindow& renderWindow = mGameManager.GetRenderWindow();
		ImageManager& imageManager = mGameManager.GetImageManager();

		sf::Texture * const backgroundImage = imageManager.getResource("resources/background/final.jpg");
		assert(backgroundImage && "LoadResources: NULL pointer");

		mBackgroundSprite = new sf::Sprite;
		mBackgroundSprite->SetTexture(*backgroundImage);
		mBackgroundSprite->SetPosition(0.0f, 0.0f);

		mDelayForNextState = 6000.0f;

		sf::SoundBuffer *soundBuffer = mGameManager.GetSoundManager().getResource("resources/sounds/congratulations.wav");
		assert(soundBuffer && "CongratulationsState::LoadResources: NULL pointer");
		mMusic = new sf::Sound(*soundBuffer);
		mMusic->SetLoop(false);
		mMusic->Play();
	}

	void CongratulationsState::DestroyResources()
	{		
		ImageManager& imageManager = mGameManager.GetImageManager();
		imageManager.releaseResource("resources/background/final.jpg");

		mGameManager.GetSoundManager().releaseAllResources();

		delete mBackgroundSprite;
		delete mMusic;
	}
}

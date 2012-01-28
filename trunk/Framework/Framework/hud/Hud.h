#pragma once
#include <GameFramework/utilities/Timer.h>
#include "..\managers\GameManager.h"

namespace Game {

class Hud {
	static void timeout(void* data) {
		int i = 0;
		i++;
	}

public:
	Hud (GameManager& gameManager) : mDecrementTimer(timeout, this)
	{ 
		mDecrementTimer.start(5000);
		gameManager.GetTimerManager().registerTimer(mDecrementTimer);
	}


private:
	Utils::Timer mDecrementTimer;
	

};

}
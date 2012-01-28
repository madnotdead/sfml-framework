#pragma once
#include <vector>
#include "Timer.h"

namespace Utils
{

class TimerManager {
public:
	void registerTimer(Timer& timer) {
		mTimers.push_back(&timer);
	}

	void tik() {
		for(size_t i = 0; i < mTimers.size(); ++i ) {
			mTimers[i]->tik();
		}
	}

private:
	std::vector<Timer*> mTimers;

};

}
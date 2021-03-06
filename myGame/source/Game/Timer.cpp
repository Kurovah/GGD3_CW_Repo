#include "Timer.h"
#include "GameTime.h"
namespace Rendering {
	Timer::Timer() {
		active = false;
		secs = 0;
		mins = 0;
		currentTime = 0;
		offset = 0;
	}
	Timer::~Timer() {
		mGame = nullptr;
	}

	void Timer::Update(const GameTime& gameTime) {
		if (active) {
			currentTime += 0.0025f;
			mins = currentTime / 60;
			secs = currentTime - (mins*60);
		}
	}
	void Timer::StartTimer(const GameTime& gameTime) {
		active = true;
		offset = gameTime.ElapsedGameTime();
	}

	void Timer::Reset() {
		active = false;
		secs = 0;
		mins = 0;
		currentTime = 0;
		offset = 0;
	}
}

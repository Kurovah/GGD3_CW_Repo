#pragma once
#include "GameObject.h"
namespace Rendering {
	class Timer
	{
	public:
		bool active;
		int offset;
		float currentTime;
		int secs;
		int mins;
		Timer();
		~Timer();
		void Update(const GameTime& gameTime);
		void StartTimer(const GameTime& gameTime);
		void Reset();
		Game* mGame;
	};
}

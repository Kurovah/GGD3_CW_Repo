#pragma once
#include <string>
namespace Rendering {
	static class SaveSystem
	{
	public:
		SaveSystem();
		static void SaveBestTime(int time, int track);
		
		static int GetBestTime(int Track);
		static void SaveCurrentCar(int car);
		static std::string GetCurrentCar();
		static std::string GetCurrentTexture();
		static float GetCurrentScale();
		static void InitialiseSaves();
		static void ResetSaves();
	};
}


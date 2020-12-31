#pragma once
namespace Rendering {
	static class SaveSystem
	{
	public:
		SaveSystem();
		static void SaveBestTime(int time, int track);
		static int GetBestTime(int Track);
		static void InitialiseSaves();
		static void ResetSaves();
	};
}


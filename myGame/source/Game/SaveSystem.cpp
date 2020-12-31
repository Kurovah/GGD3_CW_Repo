#include "SaveSystem.h"
#include <iostream>
#include <fstream>
#include<sstream>
#include <string>
#include <filesystem>

namespace Rendering {
	SaveSystem::SaveSystem() {

	}
	void SaveSystem::SaveBestTime(int time, int track) {
		std::ofstream file;

		file.open("./Content/Saves/Save"+std::to_string(track)+".txt");
		file << time<< std::endl;
		file.close();
		
	}
	int SaveSystem::GetBestTime(int track) {
		
		std::string time;
		std::string line;
		std::ifstream file("./Content/Saves/Save" + std::to_string(track) + ".txt");
		time.assign((std::istreambuf_iterator<char>(file)),(std::istreambuf_iterator<char>()));

		int toReturn = stoi(time);
		return  toReturn;
	}

	void SaveSystem::InitialiseSaves() {
		for (int i = 0; i < 2; i++) {
			//if a file doesn't exist then create a new one with a default value
			std::ifstream check("./Content/Saves/Save" + std::to_string(i) + ".txt");
			if (!check) {
				std::ofstream file;

				file.open("./Content/Saves/Save" + std::to_string(i) + ".txt");
				file << 999 << std::endl;
				file.close();
			}
		}
	}

	void SaveSystem::ResetSaves() {
		for (int i = 0; i < 2; i++) {
			std::ofstream file;
			file.open("./Content/Saves/Save" + std::to_string(i) + ".txt");
			file << 9999 << std::endl;
			file.close();
		}
	}
}

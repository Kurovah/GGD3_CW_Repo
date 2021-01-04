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

		//for the car
		std::ifstream check2("./Content/Saves/CurrentCar.txt");
		if (!check2) {
			std::ofstream file2;

			file2.open("./Content/Saves/CurrentCar.txt");
			file2 << 0 << std::endl;
			file2.close();
		}
	}

	void SaveSystem::ResetSaves() {
		for (int i = 0; i < 1; i++) {
			std::ofstream file;
			file.open("./Content/Saves/Save" + std::to_string(i) + ".txt");
			file << 9999 << std::endl;
			file.close();
		}

		std::ofstream file2;

		file2.open("./Content/Saves/CurrentCar.txt");
		file2 << 0 << std::endl;
		file2.close();
	}

	void SaveSystem::SaveCurrentCar(int car) {
		std::ofstream file2;
		file2.open("./Content/Saves/CurrentCar.txt");
		file2 << car << std::endl;
		file2.close();
	}

	std::string SaveSystem::GetCurrentCar() {
		std::string car;
		std::string line;
		std::ifstream file("./Content/Saves/CurrentCar.txt");
		car.assign((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));

		int toReturn = stoi(car);

		switch (toReturn) {
			case 0:
				return  "Content\\Models\\player_ship.obj";
				break;

			case 1:
				return "Content\\Models\\ShipFinal.obj";
				break;
			default:
				return  "Content\\Models\\player_ship.obj";
				break;
		}
		
	}
	std::string SaveSystem::GetCurrentTexture() {
		std::string car;
		std::string line;
		std::ifstream file("./Content/Saves/CurrentCar.txt");
		car.assign((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));

		int toReturn = stoi(car);

		switch (toReturn) {
		case 0:
			return  "Content\\Textures\\shipUVs.png";
			break;

		case 1:
			return "Content\\Textures\\ShipColourUV.jpg";
			break;
		default:
			return  "Content\\Textures\\shipUVs.png";
			break;
		}
	}


	float SaveSystem::GetCurrentScale() {
		std::string car;
		std::string line;
		std::ifstream file("./Content/Saves/CurrentCar.txt");
		car.assign((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));

		int toReturn = stoi(car);

		switch (toReturn) {
		case 0:
			return  1;
			break;

		case 1:
			return 0.5f;
			break;
		default:
			return  1;
			break;
		}
	}
	
}

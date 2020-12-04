#pragma once
#include "Common.h"
#include "GameObject.h"
namespace Rendering{
	class Scene
	{
	public:
		std::vector<GameObject> objects;

		Scene();
		~Scene();

		void Load();
		void UnLoad();
	};
}


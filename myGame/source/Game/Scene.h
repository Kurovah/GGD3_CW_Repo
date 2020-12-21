#pragma once
#include "Common.h"
#include "GameObject.h"
#include "Game.h"
namespace Rendering{
	class GameObject;
	class PlayerObject;

	class Scene
	{
	public:
		std::vector<GameObject*> objects;

		Scene(Game& game, Camera& camera);
		~Scene();

		virtual void Load(Game &game);
		void UnLoad();

		PlayerObject* player;
		GameObject* testObj;
	};
}


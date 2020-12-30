#pragma once
#include "Common.h"
#include "GameObject.h"
#include "Game.h"
#include "CollisionLine.h"

namespace Rendering{
	class GameObject;
	class PlayerObject;
	class CollisionLine;

	class Scene
	{
	public:
		std::vector<GameObject*> objects;

		Scene(Game& game, Camera& camera, int type);
		~Scene();

		virtual void Load(Game &game);
		void UnLoad();

		PlayerObject* player;
		PlayerObject* skyboxV2;
		GameObject* testObj;
		GameObject* testFloor;
		GameObject* skybox;
		std::vector<CollisionLine*> collisionPoints;
	};
}


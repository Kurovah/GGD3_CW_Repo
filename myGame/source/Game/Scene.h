#pragma once
#include "Common.h"
#include "GameObject.h"
#include "Game.h"
#include "CollisionLine.h"

namespace Rendering{
	class GameObject;
	class PlayerObject;
	class CollisionLine;
	class Canvas;

	class Scene
	{
	public:
		std::vector<GameObject*> objects;

		Scene(Game& game, Camera& camera, int type);
		~Scene();

		virtual void Load(Game &game);
		void UnLoad();

		PlayerObject* player;
		GameObject* testObj;
		GameObject* testFloor;
		Canvas* canvas;
		std::vector<CollisionLine*> collisionPoints;
	};
}


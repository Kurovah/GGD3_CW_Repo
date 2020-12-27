#include "Scene.h"
#include "PlayerObject.h"
#include "GameObject.h"
#include "CollisionLine.h"
#include "RenderingGame.h"

namespace Rendering{
	Scene::Scene(Game& game, Camera& camera, int type):testObj(nullptr),testFloor(nullptr) {
		
		collisionPoints.push_back(new CollisionLine(XMFLOAT3(5, 0, 5), XMFLOAT3(-5, 0, 5)));
		collisionPoints.push_back(new CollisionLine(XMFLOAT3(-5, 0, 5), XMFLOAT3(-5, 0, -5)));
		collisionPoints.push_back(new CollisionLine(XMFLOAT3(-5, 0, -5), XMFLOAT3(5, 0, -5)));
		collisionPoints.push_back(new CollisionLine(XMFLOAT3(5, 0, -5), XMFLOAT3(5, 0, 5)));

		player = new PlayerObject(game, camera, XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), 0.01f, "Content\\Models\\bench.3ds", "Content\\Textures\\bench.jpg", collisionPoints);
		objects.push_back(player);


		switch (type) {
		case 0:
			testObj = new GameObject(game, camera, XMFLOAT3(5, 0, 0), XMFLOAT3(0, 0, 0), 0.01f, "Content\\Models\\bench.3ds", "Content\\Textures\\bench.jpg");
			objects.push_back(testObj);
			break;

		case 1:
			testObj = new GameObject(game, camera, XMFLOAT3(0, 0, 5), XMFLOAT3(0, 0, 0), 0.01f, "Content\\Models\\bench.3ds", "Content\\Textures\\bench.jpg");
			objects.push_back(testObj);
			break;
		}
		
		testFloor = new GameObject(game, camera, XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), 1.0f, "Content\\Models\\tutFloor.obj", "Content\\Textures\\grass.jpg");
		objects.push_back(testFloor);


		
	}

	void Scene::Load(Game& game) {
		for (GameObject* obj : objects){
			game.AddObject(obj);
		}

	}
}

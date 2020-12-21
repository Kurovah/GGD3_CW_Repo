#include "Scene.h"
#include "PlayerObject.h"
#include "GameObject.h"

namespace Rendering{
	Scene::Scene(Game& game, Camera& camera) {
		player = new PlayerObject(game, camera, XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), 0.01f);
		objects.push_back(player);

		testObj = new GameObject(game, camera, XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), 0.01f);
		objects.push_back(testObj);
	}

	void Scene::Load(Game& game) {
		for (GameObject* obj : objects){
			game.AddObject(obj);
		}
	}
}

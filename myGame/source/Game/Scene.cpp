#include "Scene.h"
#include "PlayerObject.h"
#include "GameObject.h"
#include "CollisionLine.h"
#include "Canvas.h"
#include "RenderingGame.h"
#include "Interactable.h"
#include "Sprite.h"
#include "Button.h"
#include "BoostBarSprite.h"
#include "FinishLine.h"

namespace Rendering{
	Scene::Scene(Game& game, Camera& camera, int type):testObj(nullptr),testFloor(nullptr) {
		




		

		switch (type) {
		case 0://main menu

			
			sceneSprites.push_back(new Button(game, camera, XMFLOAT2(458, 496), XMFLOAT2(1, 1), "Content\\Textures\\ButtonBack.png", "Start",0));
			break;

		case 1://track selection
			sceneSprites.push_back(new Button(game, camera, XMFLOAT2(100, 100), XMFLOAT2(1, 1), "Content\\Textures\\ButtonBack.png", "To Track 1", 1));
			sceneSprites.push_back(new Button(game, camera, XMFLOAT2(100, 200), XMFLOAT2(1, 1), "Content\\Textures\\ButtonBack.png", "To Track 2", 2));
			break;
		case 2://track 1
			//add collision like this
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(5, 0, 5), XMFLOAT3(-5, 0, 5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(-5, 0, 5), XMFLOAT3(-5, 0, -5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(-5, 0, -5), XMFLOAT3(5, 0, -5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(5, 0, -5), XMFLOAT3(5, 0, 5)));

			player = new PlayerObject(game, camera, XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), 0.75f, "Content\\Models\\player_ship.obj", "Content\\Textures\\shipUVs.png", collisionPoints);
			objects.push_back(player);
			objects.push_back(new FinishLine(game, camera, XMFLOAT3(5, 0, 5), XMFLOAT2(4, 4)));

			objects.push_back(new Interactable(game, camera, XMFLOAT3(0, 0, 4), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			testFloor = new GameObject(game, camera, XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), 1.0f, "Content\\Models\\tutFloor.obj", "Content\\Textures\\grass.jpg");
			objects.push_back(testFloor);

			sceneSprites.push_back(new BoostBarSprite(game, camera, XMFLOAT2(18, 16), XMFLOAT2(1, 1), "Content\\Textures\\BoostBarBack.png"));
			sceneSprites.push_back(new Sprite(game, camera, XMFLOAT2(0, 0), XMFLOAT2(1, 1), "Content\\Textures\\BoostBar.png"));
			break;
		case 3://track 2
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(5, 0, 5), XMFLOAT3(-5, 0, 5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(-5, 0, 5), XMFLOAT3(-5, 0, -5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(-5, 0, -5), XMFLOAT3(5, 0, -5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(5, 0, -5), XMFLOAT3(5, 0, 5)));

			player = new PlayerObject(game, camera, XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), 0.01f, "Content\\Models\\bench.3ds", "Content\\Textures\\bench.jpg", collisionPoints);
			objects.push_back(player);
			objects.push_back(new FinishLine(game, camera, XMFLOAT3(5, 0, 5), XMFLOAT2(4, 4)));

			objects.push_back(new Interactable(game, camera, XMFLOAT3(0, 0, 4), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			testFloor = new GameObject(game, camera, XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), 1.0f, "Content\\Models\\tutFloor.obj", "Content\\Textures\\grass.jpg");
			objects.push_back(testFloor);
			sceneSprites.push_back(new BoostBarSprite(game, camera, XMFLOAT2(18, 16), XMFLOAT2(1, 1), "Content\\Textures\\BoostBarBack.png"));
			sceneSprites.push_back(new Sprite(game, camera, XMFLOAT2(0, 0), XMFLOAT2(1, 1), "Content\\Textures\\BoostBar.png"));

			break;
		}	
		
		
	}

	Scene::~Scene() {
		for (GameObject* _g : objects) {
			DeleteObject(_g);
		}
	}

	void Scene::Load(Game& game) {
		for (GameObject* obj : objects){
			game.AddObject(obj);
		}

	}
}

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
#include "TimerSprite.h"
#include "FinishLine.h"

namespace Rendering{
	Scene::Scene(Game& game, Camera& camera, int type):testObj(nullptr),testFloor(nullptr) {
		




		

		switch (type) {
		case 0://main menu

			
			sceneSprites.push_back(new Button(game, camera, XMFLOAT2(458, 420), XMFLOAT2(1, 1), "Content\\Textures\\ButtonBack.png", "Start",0));
			sceneSprites.push_back(new Button(game, camera, XMFLOAT2(458, 560), XMFLOAT2(1, 1), "Content\\Textures\\ButtonBack.png", "ResetSaves",4));
			break;

		case 1://track selection
			sceneSprites.push_back(new Button(game, camera, XMFLOAT2(100, 100), XMFLOAT2(1, 1), "Content\\Textures\\ButtonBack.png", "To Track 1", 1));
			sceneSprites.push_back(new Button(game, camera, XMFLOAT2(100, 240), XMFLOAT2(1, 1), "Content\\Textures\\ButtonBack.png", "To Track 2", 2));
			break;
		case 2://track 1
			//add collision like this
			/*collisionPoints.push_back(new CollisionLine(XMFLOAT3(6, 0, 6), XMFLOAT3(-6, 0, 6)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(-6, 0, 6), XMFLOAT3(-6, 0, -6)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(-6, 0, -6), XMFLOAT3(6, 0, -6)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(6, 0, -6), XMFLOAT3(6, 0, 6)));*/
	
			//Skybox
			objects.push_back(new GameObject(game, camera, XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), 5.0f, "Content\\Models\\testSkyBox.obj", "Content\\Textures\\skyBoxUV.png"));

			//Track Pieces
			objects.push_back(new GameObject(game, camera, XMFLOAT3(0, 0, 0), XMFLOAT3(0, 1.5708, 0), 1.0f, "Content\\Models\\Straight_Track.obj", "Content\\Textures\\Straight_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(0, 0, 22.5), XMFLOAT3(0, 4.71239, 0), 1.0f, "Content\\Models\\Corner_Track.obj", "Content\\Textures\\Corner_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(42.70, 0, 42.75), XMFLOAT3(0, 3.14159, 0), 1.0f, "Content\\Models\\Straight_Track.obj", "Content\\Textures\\Straight_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(65.20, 0, 42.75), XMFLOAT3(0, 3.14159, 0), 1.0f, "Content\\Models\\Straight_Track.obj", "Content\\Textures\\Straight_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(87.70, 0, 42.75), XMFLOAT3(0, 3.14159, 0), 1.0f, "Content\\Models\\Straight_Track.obj", "Content\\Textures\\Straight_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(110.20, 0, 42.75), XMFLOAT3(0, 0, 0), 1.0f, "Content\\Models\\Corner_Track.obj", "Content\\Textures\\Corner_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(130.45, 0, 0), XMFLOAT3(0, 4.71239, 0), 1.0f, "Content\\Models\\Straight_Track.obj", "Content\\Textures\\Straight_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(130.45, 0, -22.5), XMFLOAT3(0, 4.71239, 0), 1.0f, "Content\\Models\\Straight_Track.obj", "Content\\Textures\\Straight_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(130.45, 0, -45), XMFLOAT3(0, 4.71239, 0), 1.0f, "Content\\Models\\Straight_Track.obj", "Content\\Textures\\Straight_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(130.45, 0, -67.5), XMFLOAT3(0, 4.71239, 0), 1.0f, "Content\\Models\\Straight_Track.obj", "Content\\Textures\\Straight_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(130.45, 0, -90), XMFLOAT3(0, 1.5708, 0), 1.0f, "Content\\Models\\Corner_Track.obj", "Content\\Textures\\Corner_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(87.70, 0, -110.25), XMFLOAT3(0, 0, 0), 1.0f, "Content\\Models\\Straight_Track.obj", "Content\\Textures\\Straight_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(65.20, 0, -110.25), XMFLOAT3(0, 0, 0), 1.0f, "Content\\Models\\Straight_Track.obj", "Content\\Textures\\Straight_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(42.70, 0, -110.25), XMFLOAT3(0, 0, 0), 1.0f, "Content\\Models\\Straight_Track.obj", "Content\\Textures\\Straight_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(20.25, 0, -110.25), XMFLOAT3(0, 3.14159, 0), 1.0f, "Content\\Models\\Corner_Track.obj", "Content\\Textures\\Corner_Track.png"));			
			objects.push_back(new GameObject(game, camera, XMFLOAT3(0, 0, -67.5), XMFLOAT3(0, 1.5708, 0), 1.0f, "Content\\Models\\Straight_Track.obj", "Content\\Textures\\Straight_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(0, 0, -45.0), XMFLOAT3(0, 1.5708, 0), 1.0f, "Content\\Models\\Straight_Track.obj", "Content\\Textures\\Straight_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(0, 0, -22.5), XMFLOAT3(0, 1.5708, 0), 1.0f, "Content\\Models\\Finishline_Track.obj", "Content\\Textures\\Finishline_Track.png"));
			//objects.push_back(new FinishLine(game, camera, XMFLOAT3(0, 0, 0), XMFLOAT2(4, 4)));

			//Player
			player = new PlayerObject(game, camera, XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), 0.75f, "Content\\Models\\ShipV2.obj", "Content\\Textures\\ShipColourUV.jpg", collisionPoints);
			objects.push_back(player);
			

			objects.push_back(new Interactable(game, camera, XMFLOAT3(0, 0, 4), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			//testFloor = new GameObject(game, camera, XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), 1.0f, "Content\\Models\\tutFloor.obj", "Content\\Textures\\grass.jpg");
			//objects.push_back(testFloor);
			

			sceneSprites.push_back(new BoostBarSprite(game, camera, XMFLOAT2(18, 16), XMFLOAT2(1, 1), "Content\\Textures\\BoostBarBack.png"));
			sceneSprites.push_back(new Sprite(game, camera, XMFLOAT2(0, 0), XMFLOAT2(1, 1), "Content\\Textures\\BoostBar.png"));
			sceneSprites.push_back(new TimerSprite(game, camera, XMFLOAT2(916, 0), XMFLOAT2(1, 1), "Content\\Textures\\ButtonBack.png"));
			break;
		case 3://track 2
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(5, 0, 5), XMFLOAT3(-5, 0, 5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(-5, 0, 5), XMFLOAT3(-5, 0, -5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(-5, 0, -5), XMFLOAT3(5, 0, -5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(5, 0, -5), XMFLOAT3(5, 0, 5)));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), 5.0f, "Content\\Models\\testSkyBox.obj", "Content\\Textures\\skyBoxUV.png"));
			player = new PlayerObject(game, camera, XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), 1.0f, "Content\\Models\\player_ship.obj", "Content\\Textures\\shipUVs.png", collisionPoints);
			objects.push_back(player);
			objects.push_back(new FinishLine(game, camera, XMFLOAT3(5, 0, 5), XMFLOAT2(4, 4)));

			objects.push_back(new Interactable(game, camera, XMFLOAT3(0, 0, 4), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			testFloor = new GameObject(game, camera, XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), 1.0f, "Content\\Models\\tutFloor.obj", "Content\\Textures\\grass.jpg");
			objects.push_back(testFloor);
			

			sceneSprites.push_back(new BoostBarSprite(game, camera, XMFLOAT2(18, 16), XMFLOAT2(1, 1), "Content\\Textures\\BoostBarBack.png"));
			sceneSprites.push_back(new Sprite(game, camera, XMFLOAT2(0, 0), XMFLOAT2(1, 1), "Content\\Textures\\BoostBar.png"));
			sceneSprites.push_back(new TimerSprite(game, camera, XMFLOAT2(916, 0), XMFLOAT2(1, 1), "Content\\Textures\\ButtonBack.png"));
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

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

namespace Rendering {
	Scene::Scene(Game& game, Camera& camera, int type) :testObj(nullptr), testFloor(nullptr) {

		switch (type) {
		case 0://main menu

			sceneSprites.push_back(new Button(game, camera, XMFLOAT2(458, 420), XMFLOAT2(1, 1), "Content\\Textures\\ButtonBack.png", "Start", 0));
			sceneSprites.push_back(new Button(game, camera, XMFLOAT2(458, 560), XMFLOAT2(1, 1), "Content\\Textures\\ButtonBack.png", "ResetSaves", 4));
			break;

		case 1://track selection
			sceneSprites.push_back(new Button(game, camera, XMFLOAT2(100, 100), XMFLOAT2(1, 1), "Content\\Textures\\ButtonBack.png", "To Track 1", 1));
			sceneSprites.push_back(new Button(game, camera, XMFLOAT2(100, 200), XMFLOAT2(1, 1), "Content\\Textures\\ButtonBack.png", "To Track 2", 2));
			break;

		case 2://track 1

			//Collisions
#pragma region Collisions			
			//Collisions - Outer ring
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(-8, 0, 6), XMFLOAT3(-8, 1, -110)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(110.20, 0, 50.75), XMFLOAT3(0, 1, 50.75)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(138.45, 0, -110), XMFLOAT3(138.45, 1, 50.75)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(-8, 0, -118.5), XMFLOAT3(138.45, 1, -118.5)));

			//Collisions - Inner ring
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(7, 0, -34), XMFLOAT3(7, 1, 36)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(66, 0, 34.5), XMFLOAT3(124.5, 1, 34.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(123.5, 0, -33.5), XMFLOAT3(123.5, 1, -103.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(66, 0, -102.25), XMFLOAT3(7, 1, -102.5)));

			//Collisions - Corners
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(-7.5, 0, 27.5), XMFLOAT3(-8, 1, 22.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(-7, 0, 32.5), XMFLOAT3(-7.5, 1, 27.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(-6, 0, 37.5), XMFLOAT3(-7, 1, 32.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(-4, 0, 42.5), XMFLOAT3(-6, 1, 37.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(0, 0, 47.5), XMFLOAT3(-4, 1, 42.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(5, 0, 49.5), XMFLOAT3(0, 1, 47.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(20, 0, 50.5), XMFLOAT3(10, 1, 49.5)));

			collisionPoints.push_back(new CollisionLine(XMFLOAT3(128.45, 0, 49.5), XMFLOAT3(118, 1, 50.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(130.45, 0, 47.5), XMFLOAT3(128.45, 1, 49.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(132.45, 0, 45.5), XMFLOAT3(130.45, 1, 47.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(134.45, 0, 43.5), XMFLOAT3(132.45, 1, 45.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(136.45, 0, 41.5), XMFLOAT3(134.45, 1, 43.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(138.45, 0, 39.5), XMFLOAT3(136.45, 1, 41.5)));

			collisionPoints.push_back(new CollisionLine(XMFLOAT3(136.45, 0, -107.5), XMFLOAT3(138.45, 1, -105.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(134.45, 0, -109.5), XMFLOAT3(136.45, 1, -107.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(132.45, 0, -111.5), XMFLOAT3(134.45, 1, -109.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(130.45, 0, -113.5), XMFLOAT3(132.45, 1, -111.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(128.45, 0, -115.5), XMFLOAT3(130.45, 1, -113.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(118.45, 0, -117.5), XMFLOAT3(128.45, 1, -115.5)));

			collisionPoints.push_back(new CollisionLine(XMFLOAT3(0, 0, -115.5), XMFLOAT3(2, 1, -117.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(-2, 0, -113.5), XMFLOAT3(0, 1, -115.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(-4, 0, -111.5), XMFLOAT3(-2, 1, -113.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(-6, 0, -109.5), XMFLOAT3(-4, 1, -111.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(-7, 0, -107.5), XMFLOAT3(-6, 1, -109.5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(-8, 0, -105.5), XMFLOAT3(-7, 1, -107.5)));

			//Collsions - Prevent player from going to finishline from start
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(-8, 0, -8), XMFLOAT3(8, 1, -8)));
#pragma endregion

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
			//objects.push_back(new FinishLine(game, camera, XMFLOAT3(0, 0, 1), XMFLOAT2(4, 4)));

			//Player
			player = new PlayerObject(game, camera, XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), 0.50f, "Content\\Models\\ShipV2.3ds", "Content\\Textures\\ShipColourUV.jpg", collisionPoints);
			objects.push_back(player);

			//Boost Boxes
			objects.push_back(new Interactable(game, camera, XMFLOAT3(0, 1, 20), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(0, 1, -80), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(0, 1, -60), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(0, 1, -40), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));

			objects.push_back(new Interactable(game, camera, XMFLOAT3(25, 1, 40), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(50, 1, 47), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(75, 1, 44), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(100, 1, 41), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));

			objects.push_back(new Interactable(game, camera, XMFLOAT3(128, 1, 20), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(134, 1, 0), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(131, 1, -20), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(126, 1, -40), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(131, 1, -60), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(129, 1, -80), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));

			objects.push_back(new Interactable(game, camera, XMFLOAT3(100, 1, -113), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(75, 1, -110), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(50, 1, -107), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(25, 1, -113), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));


			//UI
			sceneSprites.push_back(new BoostBarSprite(game, camera, XMFLOAT2(18, 16), XMFLOAT2(1, 1), "Content\\Textures\\BoostBarBack.png"));
			sceneSprites.push_back(new Sprite(game, camera, XMFLOAT2(0, 0), XMFLOAT2(1, 1), "Content\\Textures\\BoostBar.png"));
			sceneSprites.push_back(new TimerSprite(game, camera, XMFLOAT2(916, 0), XMFLOAT2(1, 1), "Content\\Textures\\ButtonBack.png"));
			break;

		case 3://track 2
			/*collisionPoints.push_back(new CollisionLine(XMFLOAT3(5, 0, 5), XMFLOAT3(-5, 0, 5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(-5, 0, 5), XMFLOAT3(-5, 0, -5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(-5, 0, -5), XMFLOAT3(5, 0, -5)));
			collisionPoints.push_back(new CollisionLine(XMFLOAT3(5, 0, -5), XMFLOAT3(5, 0, 5)));*/

			objects.push_back(new GameObject(game, camera, XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), 5.0f, "Content\\Models\\testSkyBox.obj", "Content\\Textures\\skyBoxUV.png"));

			//Track Pieces
			objects.push_back(new GameObject(game, camera, XMFLOAT3(0, 0, 0.04), XMFLOAT3(0, 1.5708, 0), 1.0f, "Content\\Models\\Straight_Track.obj", "Content\\Textures\\Straight_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(-20.25, 0, 42.75), XMFLOAT3(0, 0, 0), 1.0f, "Content\\Models\\Corner_Track.obj", "Content\\Textures\\Corner_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(-42.75, 0, 42.75), XMFLOAT3(0, 3.14159, 0), 1.0f, "Content\\Models\\Corner_Track.obj", "Content\\Textures\\Corner_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(-63, 0, 85.46), XMFLOAT3(0, 4.71239, 0), 1.0f, "Content\\Models\\Corner_Track.obj", "Content\\Textures\\Corner_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(-20.25, 0, 105.725), XMFLOAT3(0, 3.14159, 0), 1.0f, "Content\\Models\\Straight_Track.obj", "Content\\Textures\\Straight_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(2.25, 0, 105.725), XMFLOAT3(0, 3.14159, 0), 1.0f, "Content\\Models\\Straight_Track.obj", "Content\\Textures\\Straight_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(24.5, 0, 105.725), XMFLOAT3(0, 3.14159, 0), 1.0f, "Content\\Models\\Straight_Track.obj", "Content\\Textures\\Straight_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(47.0, 0, 105.725), XMFLOAT3(0, 0, 0), 1.0f, "Content\\Models\\Corner_Track.obj", "Content\\Textures\\Corner_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(67.25, 0, 63), XMFLOAT3(0, 4.71239, 0), 1.0f, "Content\\Models\\Straight_Track.obj", "Content\\Textures\\Straight_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(67.25, 0, 40.75), XMFLOAT3(0, 4.71239, 0), 1.0f, "Content\\Models\\Straight_Track.obj", "Content\\Textures\\Straight_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(67.25, 0, 18.5), XMFLOAT3(0, 4.71239, 0), 1.0f, "Content\\Models\\Straight_Track.obj", "Content\\Textures\\Straight_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(67.25, 0, -3.75), XMFLOAT3(0, 4.71239, 0), 1.0f, "Content\\Models\\Straight_Track.obj", "Content\\Textures\\Straight_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(67.25, 0, -26), XMFLOAT3(0, 4.71239, 0), 1.0f, "Content\\Models\\Straight_Track.obj", "Content\\Textures\\Straight_Track.png"));
			objects.push_back(new GameObject(game, camera, XMFLOAT3(67.25, 0, -48.25), XMFLOAT3(0, 4.71239, 0), 1.0f, "Content\\Models\\Finishline_Track.obj", "Content\\Textures\\Finishline_Track.png"));
			//objects.push_back(new FinishLine(game, camera, XMFLOAT3(0, 1, 0), XMFLOAT2(4, 4)));

			player = new PlayerObject(game, camera, XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), 0.50f, "Content\\Models\\ShipV2.3ds", "Content\\Textures\\ShipColourUV.jpg", collisionPoints);
			objects.push_back(player);

			//Boost Boxes
			objects.push_back(new Interactable(game, camera, XMFLOAT3(0, 1, 15), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(-20, 1, 42.75), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(-40, 1, 42.75), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(-63, 1, 85), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(-63, 1, 65), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(-40, 1, 105.725), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(-20, 1, 110.725), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(0, 1, 100.725), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(20, 1, 105.725), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(40, 1, 110.725), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(55, 1, 105.725), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(62.25, 1, 85.725), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(64.25, 1, 65.725), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(66.25, 1, 45.725), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(68.25, 1, 25.725), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(65.25, 1, 5.725), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(65.25, 1, -15.725), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));
			objects.push_back(new Interactable(game, camera, XMFLOAT3(65.25, 1, -35.725), XMFLOAT3(0, 0, 0), 0.5f, "Content\\Models\\boostBox.obj", "Content\\Textures\\BoostBoxTexture.png"));

			//UI
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
		for (GameObject* obj : objects) {
			game.AddObject(obj);
		}

	}
}

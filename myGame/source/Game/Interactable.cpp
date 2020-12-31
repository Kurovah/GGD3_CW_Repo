#include "Interactable.h"
#include "GameObject.h"
#include "PlayerObject.h"
#include "RenderingGame.h"
#include <math.h> 
#include <iostream>
namespace Rendering {
	Interactable::Interactable(Game& _game, Camera& _camera, XMFLOAT3 translate, XMFLOAT3 rotation, float scale, std::string _modelPath, std::string _texturePath)
		:GameObject(_game, _camera, translate, rotation, scale, _modelPath, _texturePath)
	{
		range = 1.0f;
	}

	void Interactable::Initialize() {
		RenderingGame* _g = (RenderingGame*)mGame;
		mPlayer = _g->playerObj;
		GameObject::Initialize();
	}

	void Interactable::Update(const GameTime& gameTime)
	{
		rotation.y += 0.001f;
		XMFLOAT3 playerPos = mPlayer->position;
		float a = playerPos.x - position.x;
		float b = playerPos.z - position.z;
		

		float distance = sqrtf(powf(a, 2) + powf(b, 2));
		if (distance < range) {
			ActivateTrigger();
		}


		GameObject::Update(gameTime);
	}

	Interactable::~Interactable() {
		mPlayer = nullptr;
	}

	void Interactable::ActivateTrigger() {
		mPlayer->SetBoost(mPlayer->boostPow+5);
		Disable();
	}
}

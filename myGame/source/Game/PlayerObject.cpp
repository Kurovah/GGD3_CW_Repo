#include "PlayerObject.h"
#include "GameException.h"
#include "Game.h"
#include "GameTime.h"
#include "Keyboard.h"
#include "Camera.h"
#include "VectorHelper.h"
#include <iostream>

namespace Rendering {
	PlayerObject::PlayerObject(Game& _game, Camera& _camera, XMFLOAT3 translate, XMFLOAT3 rotation, float scale):GameObject(_game, _camera, translate, rotation, scale),
		velocity(),keyboard(nullptr),forwardVec()
	{
	}
	PlayerObject::~PlayerObject()
	{

	}

	void PlayerObject::Initialize() 
	{
		keyboard = (Keyboard*)mGame->Services().GetService(Keyboard::TypeIdClass());
		forwardVec = Vector3Helper::Backward;
		GameObject::Initialize();
	}

	void PlayerObject::Update(const GameTime& gameTime)
	{
		float Speed = 0;
		XMFLOAT3 _fv;
		XMFLOAT3 _turnVel = Vector3Helper::Zero;
		XMVECTOR _pos = XMLoadFloat3(&position);
		float elapsedTime = (float)gameTime.ElapsedGameTime();
		if (keyboard->IsKeyDown(DIK_W)) {
			Speed = 1;
		}

		if (keyboard->IsKeyDown(DIK_S)) {
			Speed = -1;
		}


		if (keyboard->IsKeyDown(DIK_A)) {
			_turnVel.y = 0.5f ;
		}
		
		if (keyboard->IsKeyDown(DIK_D)) {
			_turnVel.y = -0.5f;
		}

		rotation.y += _turnVel.y * elapsedTime;
		_fv = XMFLOAT3(sin(rotation.y), 0, cos(rotation.y));
		XMVECTOR fVec = XMLoadFloat3(&_fv);
		XMStoreFloat3(&forwardVec,  fVec);
		_pos += fVec*Speed*elapsedTime;
		XMStoreFloat3(&position, _pos);

		//for cam offset
		XMFLOAT3 hOffset = XMFLOAT3(0, 1, 0);
		XMVECTOR yOffset = XMLoadFloat3(&hOffset);
		_pos = _pos - fVec+yOffset;
		mCamera->SetPosition(_pos);
		mCamera->mDirection = _fv;
		//position = position + velocity;
		GameObject::Update(gameTime);
	}
	void PlayerObject::Draw(const GameTime& gameTime)
	{

		GameObject::Draw(gameTime);
	}
}

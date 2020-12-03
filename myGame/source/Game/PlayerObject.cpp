#include "PlayerObject.h"
#include "GameException.h"
#include "Game.h"
#include "GameTime.h"
#include "Keyboard.h"
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
		XMFLOAT2 _turnVel2D = Vector2Helper::Zero;
		XMVECTOR _pos = XMLoadFloat3(&position);
		XMVECTOR _rot = XMLoadFloat3(&rotation);
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

		/*XMVECTOR axisMovement = XMLoadFloat3(&_turnVel)*elapsedTime;
		_rot += axisMovement;
		XMStoreFloat3(&rotation, _rot);*/

		rotation.y += _turnVel.y * elapsedTime;
		_fv = XMFLOAT3(sin(rotation.y), 0, cos(rotation.y));

		XMVECTOR fVec = XMLoadFloat3(&_fv);
		//XMMATRIX pitchMatrix = XMMatrixRotationAxis(fVec, rotation.y);
		//fVec = XMVector3TransformNormal(fVec, pitchMatrix);
		
		
		
		XMStoreFloat3(&forwardVec,  fVec);
		_pos += fVec*Speed*elapsedTime;
		XMStoreFloat3(&position, _pos);
		
		//position = position + velocity;
		GameObject::Update(gameTime);
	}
	void PlayerObject::Draw(const GameTime& gameTime)
	{

		GameObject::Draw(gameTime);
	}
}

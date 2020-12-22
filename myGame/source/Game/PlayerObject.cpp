#include "PlayerObject.h"
#include "GameException.h"
#include "Game.h"
#include "GameTime.h"
#include "Keyboard.h"
#include "Camera.h"
#include "VectorHelper.h"
#include <iostream>
#include <cmath>

namespace Rendering {
	PlayerObject::PlayerObject(Game& _game, Camera& _camera, XMFLOAT3 translate, XMFLOAT3 rotation, float scale, std::string _modelPath, std::string _texturePath)
		:GameObject(_game, _camera, translate, rotation, scale, _modelPath, _texturePath),
		velocity(),keyboard(nullptr),forwardVec(),CamOffset()
	{
	}
	PlayerObject::~PlayerObject()
	{

	}

	void PlayerObject::Initialize() 
	{
		keyboard = (Keyboard*)mGame->Services().GetService(Keyboard::TypeIdClass());
		mCamera = (Camera*)mGame->Services().GetService(Camera::TypeIdClass());
		forwardVec = Vector3Helper::Backward;
		CamOffset = XMFLOAT2(4,2.5f);
		velocity = 0;
		angVelocity = 0;
		GameObject::Initialize();
	}

	void PlayerObject::Update(const GameTime& gameTime)
	{
		float Speed = 0;
		float _turnVel = 0;
		float elapsedTime = (float)gameTime.ElapsedGameTime();
		XMFLOAT3 _fv;
		XMVECTOR _pos = XMLoadFloat3(&position);
		
		//set movespeed
		if (keyboard->IsKeyDown(DIK_W)) {
			Speed = 4;
		}

		if (keyboard->IsKeyDown(DIK_S)) {
			Speed = -4;
		}

		//set turn velocity
		if (keyboard->IsKeyDown(DIK_A)) {
			_turnVel = 0.5f ;
		}
		
		if (keyboard->IsKeyDown(DIK_D)) {
			_turnVel = -0.5f;
		}

		velocity = lerp(velocity,Speed,0.01f);
		angVelocity = lerp(angVelocity, _turnVel,0.01f);
		//rotate and then move forwards in direction if need be
		rotation.y += angVelocity * elapsedTime;
		_fv = XMFLOAT3(sin(rotation.y), 0, cos(rotation.y));
		XMVECTOR fVec = XMLoadFloat3(&_fv);
		XMStoreFloat3(&forwardVec,  fVec);
		_pos += fVec* velocity *elapsedTime;
		XMStoreFloat3(&position, _pos);

		//for cam offset
		XMFLOAT3 hOffset = XMFLOAT3(0, CamOffset.y, 0);
		XMVECTOR yOffset = XMLoadFloat3(&hOffset);
		_pos = _pos - (fVec* CamOffset.x)+yOffset;

		//make the cam face the model
		XMFLOAT3 camF = XMFLOAT3(_fv.x, -CamOffset.y/8, _fv.z);
		mCamera->SetPosition(_pos);
		mCamera->mDirection = camF;
		mCamera->mUp = Vector3Helper::Up;
		//position = position + velocity;
		GameObject::Update(gameTime);
	}
	void PlayerObject::Draw(const GameTime& gameTime)
	{

		GameObject::Draw(gameTime);
	}

	float PlayerObject::lerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}
}

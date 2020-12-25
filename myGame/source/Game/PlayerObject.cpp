#include "PlayerObject.h"
#include "GameException.h"
#include "Game.h"
#include "GameTime.h"
#include "Keyboard.h"
#include "Camera.h"
#include "VectorHelper.h"
#include "CollisionLine.h"
#include <iostream>
#include <cmath>

namespace Rendering {
	PlayerObject::PlayerObject(Game& _game, Camera& _camera, XMFLOAT3 translate, XMFLOAT3 rotation, float scale, std::string _modelPath, std::string _texturePath, std::vector<CollisionLine*> _colliders)
		:GameObject(_game, _camera, translate, rotation, scale, _modelPath, _texturePath),
		velocity(),keyboard(nullptr),forwardVec(),CamOffset()
	{
		colRadius = 1;
		colliders = _colliders;
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
		
		for (CollisionLine* _col : colliders)
		{
			if (checkTouching(*_col)) {
				XMFLOAT3 ori = XMFLOAT3(0, 0, 0);
				_pos = XMLoadFloat3(&ori);
				/*ResolveCollision(*_col, _pos);*/
			}
		}
		

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

	bool PlayerObject::checkTouching(CollisionLine& _line) {
		float a = Distance(position,_line.point1);
		float b = Distance(position,_line.point2);
		float c = Distance(_line.point1,_line.point2);
		float x = (a + b + c) / 2;
		float h = (2 * std::sqrt(x*(x-a)*(x-b)*(x-c)))/c;

		
		return h < colRadius;
	}

	void PlayerObject::ResolveCollision(CollisionLine& _line, XMVECTOR& _newPos) {
		XMFLOAT3 AVector = XMFLOAT3(position.x - _line.point1.x, 0, position.z - _line.point1.z);
		XMFLOAT3 BVector = XMFLOAT3(position.x - _line.point1.x, 0, position.z - _line.point1.z);
		XMFLOAT3 resVector = XMFLOAT3(AVector.x + BVector.x, 0, AVector.z + BVector.z);
		XMVECTOR pos = XMLoadFloat3(&position);
		XMVECTOR res = XMLoadFloat3(&resVector);
		res = XMVector3Normalize(res) * 0.5f;
		_newPos += res;
	}

	float PlayerObject::GetOffset(CollisionLine& _line) {
		float a = Distance(position, _line.point1);
		float b = Distance(position, _line.point2);
		float c = Distance(_line.point1, _line.point2);
		float x = (a + b + c) / 2;
		float h = (2 * std::sqrt(x * (x - a) * (x - b) * (x - c))) / c;


		return h - colRadius;
	}

	float PlayerObject::Distance(XMFLOAT3 _a, XMFLOAT3 _b) {
		return std::sqrt((_a.x - _b.x) * (_a.x - _b.x) +
			(_a.y - _b.y) * (_a.y - _b.y) +
			(_a.z - _b.z) * (_a.z - _b.z));
	}
}

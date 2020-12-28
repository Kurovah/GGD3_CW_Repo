#pragma once
#include "GameObject.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace Library {
	class Keyboard;
	class Mouse;
}

namespace Rendering
{
	class CollisionLine;
	class PlayerObject :
		public GameObject
	{
	public:
		float velocity;
		float angVelocity;
		float colRadius;
		XMFLOAT3 forwardVec;
		XMFLOAT2 CamOffset;
		float boostPow;
		float boostMod;
		bool boosting;
		float accel;
		Keyboard* keyboard;
		std::vector<CollisionLine*> colliders;
		PlayerObject(Game& _game, Camera& _camera, XMFLOAT3 translate, XMFLOAT3 rotation, float scale, std::string _modelPath, std::string _texturePath, std::vector<CollisionLine*> _colliders);
		~PlayerObject();
		virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime) override;
		virtual void Draw(const GameTime& gameTime) override;
		float lerp(float a, float b, float f);
		bool checkTouching(CollisionLine& _line);
		float GetOffset(CollisionLine& _line);
		float DotProduct(XMFLOAT3 _a, XMFLOAT3 _b);
		void ResolveCollision(CollisionLine& _line);
		float Distance(XMFLOAT3 _a, XMFLOAT3 _b);
		XMFLOAT3 GetPos();
	};
}

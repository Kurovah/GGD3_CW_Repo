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
	class PlayerObject :
		public GameObject
	{
	public:
		float velocity;
		float angVelocity;
		XMFLOAT3 forwardVec;
		XMFLOAT2 CamOffset;
		Keyboard* keyboard;
		PlayerObject(Game& _game, Camera& _camera, XMFLOAT3 translate, XMFLOAT3 rotation, float scale, std::string _modelPath, std::string _texturePath);
		~PlayerObject();
		virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime) override;
		virtual void Draw(const GameTime& gameTime) override;
		float lerp(float a, float b, float f);
	};
}

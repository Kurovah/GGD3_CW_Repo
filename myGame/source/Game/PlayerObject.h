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
		XMFLOAT3 velocity;
		XMFLOAT3 forwardVec;
		XMFLOAT3 CamOffset;
		Keyboard* keyboard;
		PlayerObject(Game& _game, Camera& _camera, XMFLOAT3 translate, XMFLOAT3 rotation, float scale);
		~PlayerObject();
		virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime) override;
		virtual void Draw(const GameTime& gameTime) override;

		
	};
}

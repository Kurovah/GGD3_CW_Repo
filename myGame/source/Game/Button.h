#pragma once
#include "Sprite.h"
#include "Mouse.h"

namespace DirectX {
	class SpriteFont;
}

namespace Library {
	class Mouse;
}
namespace Rendering {
	class Button :
		public Sprite
	{
	public:
		Button(Game& _game, Camera& _camera, XMFLOAT2 _pos, XMFLOAT2 _scale, std::string _texturePath, std::string _text);
		virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime) override;
		virtual void Draw(const GameTime& gameTime, SpriteBatch* spriteBatch) override;
		virtual void ActivateButton();
		Mouse* mMouse;
		SpriteFont* mSpriteFont;
		std::string buttonText;
		float Offsetx;
		float Offsety;

		bool IsInBounds(float _x, float _y);
	};
}


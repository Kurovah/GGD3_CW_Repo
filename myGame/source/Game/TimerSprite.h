#pragma once
#include "Sprite.h"
namespace DirectX {
	class SpriteFont;
}
namespace Rendering {
	class TimerSprite :
		public Sprite
	{
		public:
		TimerSprite(Game& _game, Camera& _camera, XMFLOAT2 _pos, XMFLOAT2 _scale, std::string _texturePath);
		virtual void Initialize() override;
		//virtual void Update(const GameTime& gameTime) override;
		virtual void Draw(const GameTime& gameTime, SpriteBatch* spriteBatch) override;
		std::string displayedTime;
		SpriteFont* mSpriteFont;
	};
}


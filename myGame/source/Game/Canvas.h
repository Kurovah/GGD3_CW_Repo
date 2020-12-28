#pragma once
#include "GameObject.h"
#include <CommonStates.h>

namespace DirectX
{
	class SpriteBatch;
	class SpriteFont;
}

namespace Rendering{
	class Sprite;
	class BoostBarSprite;
	class PlayerObject;
	class Canvas :
		public GameObject
	{
	public:
		Canvas(Game& _game, Camera& _camera);
		virtual void Initialize() override;
		void Update(const GameTime& gameTime, PlayerObject& player);
		virtual void Draw(const GameTime& gameTime) override;
		std::vector<Sprite*> sprites;
		SpriteBatch* mSpriteBatch;
		ID3D11BlendState* blendState;
		DirectX::CommonStates* mStates;
	};
}


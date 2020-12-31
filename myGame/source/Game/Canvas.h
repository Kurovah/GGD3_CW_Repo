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
	class RenderingGame;
	class Scene;
	class Canvas :
		public GameObject
	{
	public:
		Canvas(Game& _game, Camera& _camera);
		void Initialize(Scene* scene);
		void Update(const GameTime& gameTime);
		virtual void Draw(const GameTime& gameTime) override;
		std::vector<Sprite*> sprites;
		RenderingGame* rGame;
		SpriteBatch* mSpriteBatch;
		ID3D11BlendState* blendState;
		DirectX::CommonStates* mStates;
	};
}


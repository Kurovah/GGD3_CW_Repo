#pragma once
#include "GameObject.h"
#include "DrawableGameComponent.h"

namespace DirectX
{
	class SpriteBatch;
	class SpriteFont;
	class ID2D1Bitmap1;
}

namespace Rendering {
	class Direct2D;
	class PlayerObject;
	class Sprite :
		public GameObject
	{
	public:
		Sprite(Game& _game, Camera& _camera, XMFLOAT2 _pos, XMFLOAT2 _scale, std::string _texturePath);
		XMFLOAT2 position;
		XMFLOAT2 scale;
		XMFLOAT2 origin;
		RECT spriteRect;
		virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime, PlayerObject& player);
		void Draw(const GameTime& gameTime, SpriteBatch* spriteBatch);

		

		HRESULT status;
		std::string texturePath;
		ID3D11ShaderResourceView* mTextureView;
		//ID3D11Resource* mTexture;
		float x, y;
	};
}


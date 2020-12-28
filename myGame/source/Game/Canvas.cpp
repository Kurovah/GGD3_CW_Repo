#include "Canvas.h"
#include "Game.h"
#include "Camera.h"
#include "Sprite.h"
#include "BoostBarSprite.h"
#include "PlayerObject.h"
#include <SpriteBatch.h>

namespace Rendering {
	Canvas::Canvas(Game& _game, Camera& _camera) :GameObject(_game, _camera),mSpriteBatch(nullptr), mStates(nullptr)
	{
		sprites.push_back(new BoostBarSprite(_game, _camera, XMFLOAT2(18, 16), XMFLOAT2(1, 1), "Content\\Textures\\BoostBarBack.png"));
		sprites.push_back(new Sprite(_game, _camera, XMFLOAT2(0, 0), XMFLOAT2(1, 1), "Content\\Textures\\BoostBar.png"));
	}


	void Canvas::Initialize() {
		mStates = new CommonStates(mGame->Direct3DDevice());
		mSpriteBatch = new SpriteBatch(mGame->Direct3DDeviceContext());
		for (Sprite* _spr : sprites) {
			_spr->Initialize();
		}
	}
	void Canvas::Update(const GameTime& gameTime, PlayerObject& player) {
		for (Sprite* _spr : sprites) {
			_spr->Update(gameTime,player);
		}
	}

	void Canvas::Draw(const GameTime& gameTime) {
		mSpriteBatch->Begin(SpriteSortMode_Deferred, mStates->NonPremultiplied());
		for (Sprite* _spr : sprites) {
			_spr->Draw(gameTime,mSpriteBatch);
		}
		mSpriteBatch->End();
	}
}

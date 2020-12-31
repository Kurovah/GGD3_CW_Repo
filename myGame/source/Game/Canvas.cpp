#include "Canvas.h"
#include "Game.h"
#include "Camera.h"
#include "Sprite.h"
#include "BoostBarSprite.h"
#include "Button.h"
#include "PlayerObject.h"
#include "RenderingGame.h"
#include <SpriteBatch.h>
#include "Scene.h"

namespace Rendering {
	Canvas::Canvas(Game& _game, Camera& _camera) :GameObject(_game, _camera),mSpriteBatch(nullptr), mStates(nullptr)
	{
		
	}


	void Canvas::Initialize(Scene* scene) {
		//GameObject::Initialize();
		mStates = new CommonStates(mGame->Direct3DDevice());
		mSpriteBatch = new SpriteBatch(mGame->Direct3DDeviceContext());

		//get all the sprites from the current scene
		for (Sprite* _s: scene->sceneSprites) {
			sprites.push_back(_s);
		}

		for (Sprite* _spr : sprites) {
			_spr->Initialize();
		}
	}
	void Canvas::Update(const GameTime& gameTime) {
		for (Sprite* _spr : sprites) {
			_spr->Update(gameTime);
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

#include "Sprite.h"
#include <SpriteBatch.h>
#include "Game.h"
#include "Utility.h"
#include "PlayerObject.h"
#include "RenderingGame.h"
#include <WICTextureLoader.h>
#include <GameException.h>
#include <codecvt>

namespace Rendering {
	Sprite::Sprite(Game& _game, Camera& _camera, XMFLOAT2 _pos, XMFLOAT2 _scale, std::string _texturePath):GameObject(_game, _camera),
		mTextureView(nullptr)
	{
		spritePosition = _pos;
		texturePath = _texturePath;
		scale = _scale;
		origin = XMFLOAT2(0,0);
	}

	void Sprite::Initialize() {
		SetCurrentDirectory(Utility::ExecutableDirectory().c_str());
		RenderingGame* _g = (RenderingGame*)mGame;
		if (_g->playerObj != nullptr) {
			player = _g->playerObj;
		}
		
		HRESULT hr;
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring textureName = converter.from_bytes(texturePath);
		if (FAILED(hr = CreateWICTextureFromFile(mGame->Direct3DDevice(), mGame->Direct3DDeviceContext(), textureName.c_str(), nullptr, &mTextureView))) {
			throw GameException("CreateWICTextureFromFile() failed.", hr);
		}

	}
	void Sprite::Update(const GameTime& gameTime) {

	}
	void Sprite::Draw(const GameTime& gameTime, SpriteBatch* spriteBatch) {
		spriteBatch->Draw(mTextureView, spritePosition,nullptr,Colors::White,0.0f, origin ,scale);
	}
}

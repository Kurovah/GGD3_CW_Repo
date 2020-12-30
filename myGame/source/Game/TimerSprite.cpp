#include "TimerSprite.h"
#include "Utility.h"
#include "Game.h"
#include "RenderingGame.h"
#include "Timer.h"
#include <SpriteFont.h>
#include <codecvt>
#include <iostream>
#include <string>

namespace Rendering {
	TimerSprite::TimerSprite(Game& _game, Camera& _camera, XMFLOAT2 _pos, XMFLOAT2 _scale, std::string _texturePath)
		:Sprite(_game, _camera, _pos, _scale, _texturePath)
	{

	}

	void TimerSprite::Initialize()
	{
		SetCurrentDirectory(Utility::ExecutableDirectory().c_str());
		mSpriteFont = new SpriteFont(mGame->Direct3DDevice(), L"Content\\Fonts\\Arial_14_Regular.spritefont");;
		Sprite::Initialize();
	}

	void TimerSprite::Draw(const GameTime& gameTime, SpriteBatch* spriteBatch) {
		Sprite::Draw(gameTime, spriteBatch);

		RenderingGame* _g = (RenderingGame*)mGame;
		displayedTime = std::to_string(_g->mTimer->mins) +":"+ std::to_string(_g->mTimer->secs);


		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		const std::wstring btext = converter.from_bytes(displayedTime);
		mSpriteFont->DrawString(spriteBatch, btext.c_str(), XMFLOAT2(spritePosition.x + 30, spritePosition.y + 15), Colors::White, 0.0f, XMFLOAT2(0, 0), XMFLOAT2(2, 2));
	}
}

#include "Button.h"
#include "RenderingGame.h"
#include "Utility.h"
#include <SpriteFont.h>
#include <SpriteBatch.h>
#include <codecvt>
#include <sstream>
#include <iomanip>

namespace Rendering {
	Button::Button(Game& _game, Camera& _camera, XMFLOAT2 _pos, XMFLOAT2 _scale, std::string _texturePath, std::string _text)
		:Sprite(_game,  _camera,  _pos, _scale,  _texturePath) 
	{
		buttonText = _text;
		Offsetx = Game::screenX;
		Offsety = Game::screenY;
	}

	void Button::Initialize() {
		SetCurrentDirectory(Utility::ExecutableDirectory().c_str());
		
		mMouse = (Mouse*)mGame->Services().GetService(Mouse::TypeIdClass());
		mSpriteFont = new SpriteFont(mGame->Direct3DDevice(), L"Content\\Fonts\\Arial_14_Regular.spritefont");;
		Sprite::Initialize();
	}

	void Button::Update(const GameTime& gameTime) {

		if ((mMouse != nullptr) && (mMouse->IsButtonDown(MouseButtonsLeft)))
		{
			LPDIMOUSESTATE mouseState = mMouse->CurrentState();
			if (IsInBounds(mMouse->X() , mMouse->Y())) {
				ActivateButton();
			}
		}
		Sprite::Update(gameTime);
	}

	void Button::Draw(const GameTime& gameTime, SpriteBatch* spriteBatch) {
		Sprite::Draw(gameTime,spriteBatch);
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		const std::wstring btext = converter.from_bytes(buttonText);
		mSpriteFont->DrawString(spriteBatch, btext.c_str(), XMFLOAT2(spritePosition.x + 10, spritePosition.y +10),Colors::White,0.0f,XMFLOAT2(0,0), XMFLOAT2(5, 5));
	}

	void Button::ActivateButton() {
		RenderingGame* _g = (RenderingGame*)mGame;
		_g->queuedScene = 1;
		_g->ChangeRequest = true;
	}

	bool Button::IsInBounds(float _x, float _y) {
		return _x < spritePosition.x + 200  && _y <spritePosition.y + 100 && _x > spritePosition.x && _y > spritePosition.y;
	}
}

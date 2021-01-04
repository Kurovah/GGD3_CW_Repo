#include "Button.h"
#include "RenderingGame.h"
#include "Utility.h"
#include <SpriteFont.h>
#include <SpriteBatch.h>
#include "SaveSystem.h"
#include <codecvt>
#include <sstream>
#include <iomanip>

namespace Rendering {
	Button::Button(Game& _game, Camera& _camera, XMFLOAT2 _pos, XMFLOAT2 _scale, std::string _texturePath, std::string _text, int type)
		:Sprite(_game,  _camera,  _pos, _scale,  _texturePath) 
	{
		buttonType = type;
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
			if (IsInBounds()) {
				ActivateButton();
			}
		}
		Sprite::Update(gameTime);
	}

	void Button::Draw(const GameTime& gameTime, SpriteBatch* spriteBatch) {
		Sprite::Draw(gameTime, spriteBatch);

		if (buttonType == 5 || buttonType == 6 || buttonType == 3) {
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			const std::wstring btext = converter.from_bytes(buttonText);
			mSpriteFont->DrawString(spriteBatch, btext.c_str(), XMFLOAT2(spritePosition.x + 40, spritePosition.y + 30), Colors::White, 0.0f, XMFLOAT2(0, 0), XMFLOAT2(2, 2));
		}
	}

	void Button::ActivateButton() {
		RenderingGame* _g = (RenderingGame*)mGame;

		switch (buttonType) {
			case 0://start menu
				_g->queuedScene = 1;
				_g->ChangeRequest = true;
				break;
			case 1://to track 1
				_g->queuedScene = 2;
				_g->ChangeRequest = true;
				break;
			case 2://to track 2
				_g->queuedScene = 3;
				_g->ChangeRequest = true;
				break;
			case 3://back to main menu
				_g->queuedScene = 0;
				_g->ChangeRequest = true;
				break;
			case 4://reset saves
				SaveSystem::ResetSaves();
				break;
			case 5://change to ship 1
				SaveSystem::SaveCurrentCar(0);
				break;
			case 6://change to ship 2
				SaveSystem::SaveCurrentCar(1);
				break;
		}
		
	}

	bool Button::IsInBounds() {
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(mGame->WindowHandle(), &p);
		return p.x < spritePosition.x + 364  && p.y <spritePosition.y + 112 && p.x > spritePosition.x && p.y > spritePosition.y;
	}
}

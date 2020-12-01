#pragma once


#include "Game.h"
#include "Keyboard.h"
#include "Mouse.h"

using namespace Library;

namespace Library
{
    class FirstPersonCamera;
	class RenderStateHelper;
	class Keyboard;
	class Mouse;
	class FpsComponent;
}

namespace DirectX
{
	class SpriteBatch;
	class SpriteFont;
}


namespace Rendering
{
    class TriangleDemo;
	class ModelFromFile;
	class ObjectDiffuseLight;
	class Scene;

    class RenderingGame : public Game
    {
    public:
        RenderingGame(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand);
        ~RenderingGame();

        virtual void Initialize() override;		
        virtual void Update(const GameTime& gameTime) override;
        virtual void Draw(const GameTime& gameTime) override;
		void ChangeScene(Scene _newScene);

    protected:
        virtual void Shutdown() override;

    private:
		static const XMFLOAT4 BackgroundColor;
		Scene* currentScene;
        FirstPersonCamera * mCamera;
        TriangleDemo* mDemo;
		LPDIRECTINPUT8 mDirectInput;
		Keyboard* mKeyboard;
		Mouse* mMouse;
		ModelFromFile* mModel;
		ModelFromFile* floorModel;
		ModelFromFile* gearModel;
		FpsComponent* mFpsComponent;
		RenderStateHelper* mRenderStateHelper;
		ObjectDiffuseLight* mObjectDiffuseLight;
		int mScore;
		SpriteBatch* mSpriteBatch;
		SpriteFont* mSpriteFont;
	
		void Pick(int sx, int sy, ModelFromFile*);
    };
}
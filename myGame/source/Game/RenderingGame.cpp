#include "RenderingGame.h"
#include "GameException.h"
#include "FirstPersonCamera.h"
#include "TriangleDemo.h"
#include "ModelFromFile.h"
#include "FpsComponent.h"
#include "RenderStateHelper.h"
#include "ObjectDiffuseLight.h"
#include "SamplerStates.h"
#include "RasterizerStates.h"
#include "Scene.h"
#include "GameObject.h"
#include "Canvas.h"
#include "PlayerObject.h"
//display score
#include <SpriteFont.h>
#include <sstream>


namespace Rendering
{;

	const XMFLOAT4 RenderingGame::BackgroundColor = { 0.5f, 0.5f, 0.5f, 1.0f };

    RenderingGame::RenderingGame(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand)
        :  Game(instance, windowClass, windowTitle, showCommand),
        mDemo(nullptr),mMouse(nullptr),mKeyboard(nullptr),mDirectInput(nullptr),mModel(nullptr),gearModel(nullptr),floorModel(nullptr),
		mFpsComponent(nullptr), mRenderStateHelper(nullptr), mObjectDiffuseLight(nullptr),mSpriteFont(nullptr), mSpriteBatch(nullptr),
		playerObj(nullptr),currentScene(nullptr),nextScene(nullptr),mCanvas(nullptr)
    {
		ChangeRequest = false;
        mDepthStencilBufferEnabled = true;
        mMultiSamplingEnabled = true;
    }

    RenderingGame::~RenderingGame()
    {
    }

    void RenderingGame::Initialize()
    {
		//do common elements first
		
		AddCommonElements();
		mServices.AddService(Camera::TypeIdClass(), mCamera);


		RasterizerStates::Initialize(mDirect3DDevice);
		SamplerStates::Initialize(mDirect3DDevice);

		mCanvas = new Canvas(*this, *mCamera);
		mCanvas->Initialize();

		mFpsComponent = new FpsComponent(*this);
		mFpsComponent->Initialize();
		mRenderStateHelper = new RenderStateHelper(*this);

		

		mSpriteBatch = new SpriteBatch(mDirect3DDeviceContext);
		mSpriteFont = new SpriteFont(mDirect3DDevice, L"Content\\Fonts\\Arial_14_Regular.spritefont");

		currentScene = new Scene(*this, *mCamera, 0);
		nextScene = new Scene(*this, *mCamera, 1);

		//add the scene based objects here (use the scene class)
		currentScene->Load(*this);
		playerObj = currentScene->player;

		//mModel = new ModelFromFile(*this, *mCamera, "Content\\Models\\bench.3ds", "Content\\Textures\\bench.jpg");
		//mModel->SetPosition(-1.57f, -0.0f, -0.0f, 0.005f, 5.0f, 0.6f, -5.0f);
		//AddObject(mModel);
		////mComponents.push_back(mModel);

		//gearModel = new ModelFromFile(*this, *mCamera, "Content\\Models\\bench.3ds", "Content\\Textures\\bench.jpg",L"Descriptor goes here", 10);
		//gearModel->SetPosition(-1.57f, -0.0f, -0.0f, 0.005f, 0.0f, 0.6f, -5.0f);
		//mComponents.push_back(gearModel);

		//floorModel = new ModelFromFile(*this, *mCamera, "Content\\Models\\tutFloor.obj", "Content\\Textures\\grass.jpg");
		////floorModel->SetPosition(0.0f, -0.0f, -0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		//mComponents.push_back(floorModel);


		/*XMFLOAT3 testTrans = XMFLOAT3(0, 0, 0);
		XMFLOAT3 testRot = XMFLOAT3(0, 0, 0);
		testObj = new PlayerObject(*this, *mCamera, testTrans, testRot, 0.01f);
		mComponents.push_back(testObj);*/

        Game::Initialize();

		mCamera->SetPosition(0.0f, 1.0f, 5.0f);
    }

	void RenderingGame::AddCommonElements() {
		mCamera = new FirstPersonCamera(*this);
		mComponents.push_back(mCamera);
		
		if (FAILED(DirectInput8Create(mInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&mDirectInput, nullptr)))
		{
			throw GameException("DirectInput8Create() failed");
		}
		mKeyboard = new Keyboard(*this, mDirectInput);
		mComponents.push_back(mKeyboard);
		
		mMouse = new Mouse(*this, mDirectInput);
		mComponents.push_back(mMouse);

		mServices.AddService(Keyboard::TypeIdClass(), mKeyboard);
		mServices.AddService(Mouse::TypeIdClass(), mMouse);

	}

    void RenderingGame::Shutdown()
    {
		DeleteObject(mDemo);
        DeleteObject(mCamera);
		DeleteObject(mKeyboard);
		DeleteObject(mMouse);
		DeleteObject(mModel);
		DeleteObject(floorModel);
		DeleteObject(gearModel);
		ReleaseObject(mDirectInput);
		DeleteObject(mFpsComponent);
		DeleteObject(mRenderStateHelper);
		DeleteObject(mObjectDiffuseLight);
		DeleteObject(mSpriteFont);
		DeleteObject(mSpriteBatch);
		DeleteObject(playerObj);
		DeleteObject(mCanvas);

        Game::Shutdown();
    }

    void RenderingGame::Update(const GameTime &gameTime)
    {
		
		mCanvas->Update(gameTime, *playerObj);
		if (mKeyboard->WasKeyPressedThisFrame(DIK_ESCAPE))
		{
			Exit();
		}

		if (mKeyboard->WasKeyPressedThisFrame(DIK_J))
		{
			ChangeRequest = true;
		}
		mFpsComponent->Update(gameTime);
		ReleaseObject(mDirectInput);
        Game::Update(gameTime);

		if (ChangeRequest) {
			ChangeScene(nextScene);
			ChangeRequest = false;
		}
		if (Game::toPick)
		{

			if (gearModel->Visible())
				Pick(Game::screenX, Game::screenY, gearModel);



			Game::toPick = false;
		}
    }

	void RenderingGame::ChangeScene(Scene* newScene) {
		//clear out components+services and add new ones
		mServices.RemoveService(Keyboard::TypeIdClass());
		//mServices.RemoveService(Camera::TypeIdClass());
		mServices.RemoveService(Mouse::TypeIdClass());

		Camera* tempCam = (Camera*)mComponents[0];

		mComponents.clear();
		mComponents.push_back(tempCam);

		currentScene = newScene;

		AddCommonElements();
		currentScene->Load(*this);
		Game::Initialize();
	}

	void RenderingGame::Pick(int sx, int sy, ModelFromFile* model)
	{
		//XMMATRIX P = mCam.Proj(); 
		XMFLOAT4X4 P;
		XMStoreFloat4x4(&P, mCamera->ProjectionMatrix());
		//Compute picking ray in view space.
		float vx = (+2.0f * sx / Game::DefaultScreenWidth - 1.0f) / P(0, 0);
		float vy = (-2.0f * sy / Game::DefaultScreenHeight + 1.0f) / P(1, 1);
		// Ray definition in view space.
		XMVECTOR rayOrigin = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
		XMVECTOR rayDir = XMVectorSet(vx, vy, -1.0f, 0.0f);
		// Tranform ray to local space of Mesh via the inverse of both of view and world transform
		XMMATRIX V = mCamera->ViewMatrix();
		XMMATRIX invView = XMMatrixInverse(&XMMatrixDeterminant(V), V);
		XMMATRIX W = XMLoadFloat4x4(model->WorldMatrix());
		XMMATRIX invWorld = XMMatrixInverse(&XMMatrixDeterminant(W), W);
		XMMATRIX toLocal = XMMatrixMultiply(invView, invWorld);
		rayOrigin = XMVector3TransformCoord(rayOrigin, toLocal);
		rayDir = XMVector3TransformNormal(rayDir, toLocal);

		// Make the ray direction unit length for the intersection tests.
		rayDir = XMVector3Normalize(rayDir);
		float tmin = 0.0;
		if (model->mBoundingBox.Intersects(rayOrigin, rayDir, tmin))
		{
			std::wostringstream pickupString;
			pickupString << L"Do you want to pick up: " << (model->GetModelDes()).c_str() << '\n' << '\t' << '+' << model->ModelValue() << L" points";
			int result = MessageBox(0, pickupString.str().c_str(), L"Object Found", MB_ICONASTERISK | MB_YESNO);

			//To make the object invisible after being picked, in the Pick function, add the following code:
			if (result == IDYES)
			{ //hide the object
				model->SetVisible(false);
				//update the score
				mScore += model->ModelValue();
			}
		}
	}

    void RenderingGame::Draw(const GameTime &gameTime)
    {
        mDirect3DDeviceContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&BackgroundColor));
        mDirect3DDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		mRenderStateHelper->SaveAll();
		mFpsComponent->Draw(gameTime);
		mCanvas->Draw(gameTime);
		mSpriteBatch->Begin();
		//draw the score
		std::wostringstream scoreLabel;
		scoreLabel << L"Your current score: " << mScore << "\n";
		mSpriteFont->DrawString(mSpriteBatch, scoreLabel.str().c_str(), XMFLOAT2(0.0f, 120.0f), Colors::Red);
		mSpriteBatch->End();

		mRenderStateHelper->RestoreAll();

        Game::Draw(gameTime);
       
        HRESULT hr = mSwapChain->Present(0, 0);
        if (FAILED(hr))
        {
            throw GameException("IDXGISwapChain::Present() failed.", hr);
        }
    }
}
#include "GameObject.h"
#include "ModelFromFile.h"
#include "MatrixHelper.h"

namespace Rendering{
	GameObject::GameObject(Game& _game, Camera& _camera):DrawableGameComponent(_game,_camera),model(nullptr),worldMatrix(MatrixHelper::Identity){
		model = new ModelFromFile(_game, _camera, "Content\\Models\\bench.3ds", "Content\\Textures\\bench.jpg");
		//model->SetPosition(worldMatrix);
	}

	GameObject::~GameObject() {
		if (model != nullptr) {
			DeleteObject(model);
		}
	}

	void GameObject::Update(const GameTime& gameTime)
	{

		if (model != nullptr) {
			model->SetPosition(worldMatrix);
			model->Update(gameTime);
		}
	}

	void GameObject::SetPos(const float rotateX, const float rotateY, const float rotateZ,
		const float scaleFactor,
		const float translateX, const float translateY, const float translateZ) 
	{
		XMMATRIX _worldMatrix = XMLoadFloat4x4(&worldMatrix);
		XMMATRIX RotationZ = XMMatrixRotationZ(rotateZ);
		XMMATRIX RotationX = XMMatrixRotationX(rotateX);
		XMMATRIX RotationY = XMMatrixRotationY(rotateY);
		XMMATRIX Scale = XMMatrixScaling(scaleFactor, scaleFactor, scaleFactor);
		XMMATRIX Translation = XMMatrixTranslation(translateX, translateY, translateZ);
		_worldMatrix = RotationZ * RotationX * RotationY * Scale * Translation;

		XMStoreFloat4x4(&worldMatrix, _worldMatrix);
	}


	void GameObject::Initialize() {
		model->Initialize();
	}

	void GameObject::Draw(const GameTime& gameTime) {

		if (model != nullptr) {
			model->Draw(gameTime);
		}
	}
}


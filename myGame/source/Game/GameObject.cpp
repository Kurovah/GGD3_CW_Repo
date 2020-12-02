#include "GameObject.h"
#include "ModelFromFile.h"
#include "MatrixHelper.h"

namespace Rendering{
	GameObject::GameObject(Game& _game, Camera& _camera, XMFLOAT3 translate, XMFLOAT3 rotation, float scale):DrawableGameComponent(_game,_camera),model(nullptr),worldMatrix(MatrixHelper::Identity){
		//make initial matrix
		XMMATRIX tempMatrix = XMLoadFloat4x4(&worldMatrix);
		XMMATRIX trans = XMMatrixTranslation(translate.x, translate.y, translate.z);
		XMMATRIX rotZ = XMMatrixRotationZ(rotation.z);
		XMMATRIX rotY = XMMatrixRotationY(rotation.y);
		XMMATRIX rotX = XMMatrixRotationX(rotation.x);
		XMMATRIX Scale = XMMatrixScaling(scale, scale, scale);

		tempMatrix = rotZ * rotX * rotY * Scale * trans;
		XMStoreFloat4x4(&worldMatrix, tempMatrix);
		//add model component
		model = new ModelFromFile(_game, _camera, "Content\\Models\\bench.3ds", "Content\\Textures\\bench.jpg");
		model->SetPosition(worldMatrix);
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


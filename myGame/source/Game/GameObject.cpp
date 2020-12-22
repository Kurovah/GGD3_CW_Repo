#include "GameObject.h"
#include "ModelFromFile.h"
#include "MatrixHelper.h"

namespace Rendering{
	GameObject::GameObject(Game& _game, Camera& _camera, XMFLOAT3 _translate, XMFLOAT3 _rotation, float scale, std::string _modelPath, std::string _texturePath):DrawableGameComponent(_game,_camera)
		,model(nullptr),worldMatrix(MatrixHelper::Identity),staticObject(false){
		//init values
		position = _translate;
		rotation = _rotation;
		//make initial matrix
		XMMATRIX tempMatrix = XMLoadFloat4x4(&worldMatrix);
		XMMATRIX trans = XMMatrixTranslation(position.x, position.y, position.z);
		XMMATRIX rotZ = XMMatrixRotationZ(rotation.z);
		XMMATRIX rotY = XMMatrixRotationY(rotation.y);
		XMMATRIX rotX = XMMatrixRotationX(rotation.x);
		XMMATRIX Scale = XMMatrixScaling(scale, scale, scale);

		tempMatrix = rotZ * rotX * rotY * Scale * trans;
		XMStoreFloat4x4(&worldMatrix, tempMatrix);
		//add model component
		//"Content\\Models\\bench.3ds" "Content\\Textures\\bench.jpg"
		model = new ModelFromFile(_game, _camera, _modelPath, _texturePath);
		model->SetPosition(worldMatrix);
	}

	GameObject::~GameObject() {
		if (model != nullptr) {
			DeleteObject(model);
		}
	}

	void GameObject::Update(const GameTime& gameTime)
	{
		//update the object
		SetPos(position, 0.01f, rotation);
		//update the model
		if (model != nullptr) {
			model->SetPosition(worldMatrix);
			model->Update(gameTime);
		}
	}

	void GameObject::SetPos(XMFLOAT3 _pos, const float scaleFactor, XMFLOAT3 _rot)
	{
		XMMATRIX _worldMatrix = XMLoadFloat4x4(&worldMatrix);
		XMMATRIX RotationZ = XMMatrixRotationZ(_rot.z);
		XMMATRIX RotationX = XMMatrixRotationX(_rot.x);
		XMMATRIX RotationY = XMMatrixRotationY(_rot.y);
		XMMATRIX Scale = XMMatrixScaling(scaleFactor, scaleFactor, scaleFactor);
		XMMATRIX Translation = XMMatrixTranslation(_pos.x, _pos.y, _pos.z);
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


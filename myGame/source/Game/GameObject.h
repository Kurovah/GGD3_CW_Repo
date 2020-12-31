#pragma once

#include "DrawableGameComponent.h"
#include "Common.h"
#include <DirectXCollision.h>

using namespace Library;
namespace Rendering {
	class ModelFromFile;
	class GameObject :public DrawableGameComponent
	{
		//RTTI_DECLARATIONS(GameObject, DrawableGameComponent);
	public:
		GameObject( Game &_game, Camera& _camera, XMFLOAT3 translate, XMFLOAT3 rotation, float scale, std::string _modelPath, std::string _texturePath);
		GameObject( Game &_game, Camera& _camera);
		GameObject(Game& _game, Camera& _camera, XMFLOAT3 translate);
		~GameObject();
		virtual void Initialize() override;
		void Disable();
		XMFLOAT4X4 worldMatrix;
		XMFLOAT3 position;
	protected:
		ModelFromFile* model;
		
		XMFLOAT3 rotation;
		float modelScale;
		bool Paused;
		virtual void Update(const GameTime& gameTime) override;
		virtual void Draw(const GameTime& gameTime) override;

	private:
		void SetPos(XMFLOAT3 _pos, const float scaleFactor, XMFLOAT3 _rot);
		
	};
}

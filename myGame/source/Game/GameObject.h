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
		GameObject( Game &_game, Camera& _camera, XMFLOAT3 translate, XMFLOAT3 rotation, float scale);
		~GameObject();
		virtual void Initialize() override;
		XMFLOAT4X4 worldMatrix;
	protected:
		ModelFromFile* model;
		XMFLOAT3 position;
		XMFLOAT3 rotation;
		bool staticObject;
		virtual void Update(const GameTime& gameTime) override;
		virtual void Draw(const GameTime& gameTime) override;

	private:
		void SetPos(XMFLOAT3 _pos, const float scaleFactor, XMFLOAT3 _rot);
		
	};
}

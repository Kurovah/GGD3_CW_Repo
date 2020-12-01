#pragma once

#include "DrawableGameComponent.h"
#include <DirectXCollision.h>

using namespace Library;

namespace Rendering 
{
	//class ModelFromFile;
	class GameObject:public DrawableGameComponent
	{
		//RTTI_DECLARATIONS(GameObject, DrawableGameComponent);
	public:
		GameObject() {

		}
		ModelFromFile* model;
	protected:
		
		XMFLOAT4X4 worldMatrix;

	private:
		void SetPos(const float rotateX, const float rotateY, const float rotateZ, 
			const float scaleFactor, 
			const float translateX, const float translateY, const float translateZ);
		virtual void Update(const GameTime& gameTime) override;
		virtual void Draw(const GameTime& gameTime) override;
	};
}

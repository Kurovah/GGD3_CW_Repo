#include "GameObject.h"
#include"ModelFromFile.h"

namespace Rendering
{
	GameObject::GameObject() {

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


	}

	void GameObject::Draw(const GameTime& gameTime) {

		if (model != nullptr) {
			model->Draw(gameTime);
		}
	}
}

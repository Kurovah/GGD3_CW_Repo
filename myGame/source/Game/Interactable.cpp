#include "Interactable.h"
#include "PlayerObject.h"
#include <math.h> 
namespace Rendering {
	Interactable::Interactable(Game& _game, Camera& _camera, XMFLOAT3 translate, XMFLOAT3 rotation, float scale, std::string _modelPath, std::string _texturePath, PlayerObject* player)
		:GameObject(_game, _camera, translate, rotation, scale, _modelPath, _texturePath)
	{
		mPlayer = player;
		range = 1.0f;
	}

	void Interactable::Update(const GameTime& gameTime)
	{
		float a = mPlayer->GetPos().x - position.x;
		float b = mPlayer->GetPos().z - position.z;
		float distance = (a * a + b * b) / (a * a + b * b);
		if (distance < range) {
			ActivateTrigger();
		}

		GameObject::Update(gameTime);
	}

	void Interactable::ActivateTrigger() {
		mPlayer->boostPow += 5;
		Disable();
		//SetEnabled(false);
	}
}

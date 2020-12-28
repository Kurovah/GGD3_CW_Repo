#pragma once
#include "GameObject.h"
namespace Rendering {
	class PlayerObject;
	class Interactable :
		public GameObject
	{
	public:
		PlayerObject* mPlayer;
		Interactable(Game& _game, Camera& _camera, XMFLOAT3 translate, XMFLOAT3 rotation, float scale, std::string _modelPath, std::string _texturePath, PlayerObject* player);
		//virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime) override;
		//virtual void Draw(const GameTime& gameTime) override;
		virtual void ActivateTrigger();
		float range;
	};
}

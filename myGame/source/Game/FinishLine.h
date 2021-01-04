#pragma once
#include "GameObject.h"
namespace Rendering {
	class RenderingGame;
	class PlayerObject;
	class FinishLine :
		public GameObject
	{
	public:
		XMFLOAT2 triggerScale;
		bool intersecting,lastIn,active;
		int currentState = 0;
		FinishLine(Game& _game, Camera& _camera, XMFLOAT3 translate,XMFLOAT2 scale);
		~FinishLine();
		bool PlayerIsInside();
		virtual void Update(const GameTime& gameTime) override;
	};
}


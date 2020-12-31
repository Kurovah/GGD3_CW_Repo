#include "FinishLine.h"
#include "RenderingGame.h"
#include "PlayerObject.h"
#include "SaveSystem.h"
#include "Timer.h"

namespace Rendering {
	FinishLine::FinishLine(Game& _game, Camera& _camera, XMFLOAT3 translate, XMFLOAT2 scale):GameObject(_game, _camera, translate) {
		triggerScale = scale;
	}
	FinishLine::~FinishLine()
	{
	}

	void FinishLine::Update(const GameTime& gameTime)
	{
		intersecting = PlayerIsInside();
		
		switch (currentState) {
			case 0:
				if (!intersecting && lastIn) {
					currentState = 1;
				}
				break;
			case 1:
				//only activate when you reenter
				if (intersecting && !lastIn) {
					RenderingGame* _g = (RenderingGame*)mGame;
					//only save the time if the current one is less
					if (SaveSystem::GetBestTime(_g->queuedScene - 2) > _g->mTimer->currentTime) 
					{
						SaveSystem::SaveBestTime(_g->mTimer->currentTime, _g->queuedScene - 2);
					}
					_g->queuedScene = 1;
					_g->ChangeRequest = true;
					
					break;
				}
		}
		
		lastIn = intersecting;
	}

	bool FinishLine::PlayerIsInside() {
		RenderingGame* _g = (RenderingGame*)mGame;
		XMFLOAT3 playerPos = _g->playerObj->position;

		return playerPos.x < position.x + triggerScale.x &&
			playerPos.x > position.x - triggerScale.x &&
			playerPos.x > position.y - triggerScale.y &&
			playerPos.x < position.y + triggerScale.y;
		
	}
}
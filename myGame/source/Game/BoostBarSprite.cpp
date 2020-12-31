#include "BoostBarSprite.h"
#include "PlayerObject.h"
#include "RenderingGame.h"
#include "Game.h"
namespace Rendering {
	BoostBarSprite::BoostBarSprite(Game& _game, Camera& _camera, XMFLOAT2 _pos, XMFLOAT2 _scale, std::string _texturePath)
		:Sprite(_game, _camera,  _pos, _scale, _texturePath) 
	{
		origin = XMFLOAT2(0, 0);
	}

	void BoostBarSprite::Update(const GameTime& gameTime) {
		scale = XMFLOAT2(player->boostPow / 100, 1);
	}
}

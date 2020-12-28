#pragma once
#include "Sprite.h"
namespace Rendering{
class BoostBarSprite :
	public Sprite
{
public:
	BoostBarSprite(Game& _game, Camera& _camera, XMFLOAT2 _pos, XMFLOAT2 _scale, std::string _texturePath);
	virtual void Update(const GameTime& gameTime, PlayerObject& player) override;

};
}

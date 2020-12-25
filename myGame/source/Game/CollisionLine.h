#pragma once
#include "DirectXMath.h"
namespace Rendering{
	class CollisionLine
	{
	public:
		CollisionLine(DirectX::XMFLOAT3 p1, DirectX::XMFLOAT3 p2);
		DirectX::XMFLOAT3 point1;
		DirectX::XMFLOAT3 point2;
	};
}


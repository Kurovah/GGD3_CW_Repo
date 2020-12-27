#include "CollisionLine.h"
namespace Rendering{
	CollisionLine::CollisionLine(DirectX::XMFLOAT3 p1, DirectX::XMFLOAT3 p2) {
		point1 = p1;
		point2 = p2;
		normal = DirectX::XMFLOAT3(-(p2.z - p1.z), 0, p2.x - p1.x);
		iNormal = DirectX::XMFLOAT3(p2.z - p1.z, 0, -(p2.x - p1.x));
		
	}
}

#pragma once


#include "OBB.h"
#include "AABB.h"


class Collider {
public:
	
};

class BoxCollider : public Collider
{
public:
	// Axis-aligned bounding boxes
	AABB m_aabb;
	// oriented bounding box
	OBB m_obb;

	BoxCollider();
	BoxCollider(const std::vector<Vertex>& vertices);

	~BoxCollider() {};
};

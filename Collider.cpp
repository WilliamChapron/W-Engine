#include "pch.h"
#include "Collider.h"

BoxCollider::BoxCollider() {
}

BoxCollider::BoxCollider(const std::vector<Vertex>& vertices)
{
	m_aabb.Init(vertices);
	m_obb.Init(vertices);
}


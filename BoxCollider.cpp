#include "pch.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider() {
}

BoxCollider::BoxCollider(std::vector<Vertex>& vertices)
{
	m_aabb.FindMinMaxFromVerticesPack(vertices);
	m_aabb.CalculateData();
}


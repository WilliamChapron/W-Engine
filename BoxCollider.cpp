#include "pch.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider() {
}

BoxCollider::BoxCollider(std::vector<Vertex>& vertices)
{
	m_boundingVolume.FindMinMaxFromVerticesPack(vertices);
	m_boundingVolume.CalculateData();
}


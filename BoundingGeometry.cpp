#include "pch.h"

#include "BoundingGeometry.h"

BoundingGeometry::BoundingGeometry()
    : m_center(Eigen::Vector3d::Zero()),
    m_size(Eigen::Vector3d::Zero()),
    m_rotation(Eigen::Matrix3d::Identity())
{
}

void BoundingGeometry::Init(const std::vector<Vertex>& vertices) {
    ComputeMinMaxForAllVertices(vertices);
    ComputeCenter();
    ComputeSize();
}

void BoundingGeometry::ComputeCenter() {
}

void BoundingGeometry::ComputeSize() {
}

void BoundingGeometry::ComputeMinMaxForAllVertices(const std::vector<Vertex>& vertices) {
}

#include "pch.h"

#include "OBB.h"
#include "RenderStructures.h"

OBB::OBB() {}

std::vector<Eigen::Vector3d>& OBB::GetCorners() {
    return m_corners;
}

void OBB::Init(const std::vector<Vertex>& vertices) {
    ComputeMinMaxForAllVertices(vertices);
    ComputeCenter();
    ComputeSize();
}

void OBB::ComputeCenter() {
    m_center = (min + max) / 2.0;
}

void OBB::ComputeSize() {
    m_size = max - min;
}

void OBB::ComputeMinMaxForAllVertices(const std::vector<Vertex>& vertices) {
    min = Eigen::Vector3d(std::numeric_limits<double>::max(),
        std::numeric_limits<double>::max(),
        std::numeric_limits<double>::max());
    max = Eigen::Vector3d(-std::numeric_limits<double>::max(),
        -std::numeric_limits<double>::max(),
        -std::numeric_limits<double>::max());

    for (const auto& v : vertices) {
        Eigen::Vector3d point(v.position[0], v.position[1], v.position[2]);
        min = min.cwiseMin(point);
        max = max.cwiseMax(point);
    }
}

void OBB::UpdateGlobalBounds(const glm::mat4& world) {
    Eigen::Matrix3d rotationMatrix;

    // Inverse z because of Eigen matrix standards
    rotationMatrix << world[0][0], world[1][0], -world[2][0],
        world[0][1], world[1][1], -world[2][1],
        world[0][2], world[1][2], -world[2][2];

    m_rotation = rotationMatrix * Eigen::Matrix3d::Identity();
    Eigen::Vector3d translation(world[3][0], world[3][1], world[3][2]);

    Eigen::Vector3d halfSize = m_size.cast<double>() / 2.0;

    // Local corners base (before rotation)
    Eigen::Vector3d localCorners[8] = {
        Eigen::Vector3d(-halfSize.x(), -halfSize.y(), -halfSize.z()),
        Eigen::Vector3d(halfSize.x(), -halfSize.y(), -halfSize.z()),
        Eigen::Vector3d(halfSize.x(), -halfSize.y(),  halfSize.z()),
        Eigen::Vector3d(-halfSize.x(), -halfSize.y(),  halfSize.z()),
        Eigen::Vector3d(-halfSize.x(),  halfSize.y(), -halfSize.z()),
        Eigen::Vector3d(halfSize.x(),  halfSize.y(), -halfSize.z()),
        Eigen::Vector3d(halfSize.x(),  halfSize.y(),  halfSize.z()),
        Eigen::Vector3d(-halfSize.x(),  halfSize.y(),  halfSize.z())
    };

    m_corners.clear();
    m_corners.reserve(8);

    for (int i = 0; i < 8; ++i) {
        Eigen::Vector3d rotatedCorner = m_rotation * localCorners[i];
        Eigen::Vector3d globalCorner = m_center + rotatedCorner + translation;
        m_corners.push_back(globalCorner);
    }
}

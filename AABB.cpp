#include "pch.h"

#include "AABB.h"
#include "./RenderStructures.h"

AABB::AABB() {}

void AABB::Init(const std::vector<Vertex>& vertices) {
    min = { std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max() };
    max = { -std::numeric_limits<float>::max(), -std::numeric_limits<float>::max(), -std::numeric_limits<float>::max() };
    ComputeMinMaxForAllVertices(vertices);

    // Compute size
    size[0] = abs(max[0] - min[0]);
    size[1] = abs(max[1] - min[1]);
    size[2] = abs(max[2] - min[2]);

    // Compute center
    center[0] = (min[0] + max[0]) / 2.0f;
    center[1] = (min[1] + max[1]) / 2.0f;
    center[2] = (min[2] + max[2]) / 2.0f;

    // Compute base corners
    bCorners[0] = glm::vec3(bMin[0], bMin[1], bMin[2]);
    bCorners[1] = glm::vec3(bMin[0], bMin[1], bMax[2]);
    bCorners[2] = glm::vec3(bMin[0], bMax[1], bMin[2]);
    bCorners[3] = glm::vec3(bMin[0], bMax[1], bMax[2]);
    bCorners[4] = glm::vec3(bMax[0], bMin[1], bMin[2]);
    bCorners[5] = glm::vec3(bMax[0], bMin[1], bMax[2]);
    bCorners[6] = glm::vec3(bMax[0], bMax[1], bMin[2]);
    bCorners[7] = glm::vec3(bMax[0], bMax[1], bMax[2]);
}

std::vector<Eigen::Vector3d>& AABB::GetCorners() {
    m_corners.reserve(8);
    for (int i = 0; i < 8; ++i) {
        m_corners.emplace_back(transformedCorners[i].x, transformedCorners[i].y, transformedCorners[i].z);
    }
    return m_corners;
}

void AABB::ComputeMinMaxForAllVertices(const std::vector<Vertex>& vertexPack) {
    for (const auto& vertex : vertexPack) {
        min[0] = std::min(min[0], vertex.position[0]);
        min[1] = std::min(min[1], vertex.position[1]);
        min[2] = std::min(min[2], vertex.position[2]);

        max[0] = std::max(max[0], vertex.position[0]);
        max[1] = std::max(max[1], vertex.position[1]);
        max[2] = std::max(max[2], vertex.position[2]);
    }

    // Start pos
    bMin = min;
    bMax = max;
}

void AABB::UpdateGlobalBounds(const glm::mat4& world) {
    Eigen::Matrix3d rotationMatrix;
    rotationMatrix << world[0][0], world[1][0], -world[2][0],
        world[0][1], world[1][1], -world[2][1],
        world[0][2], world[1][2], -world[2][2];

    // Retrieve rotation matrix to allow AABB with OBB collision test
    m_rotation = rotationMatrix * Eigen::Matrix3d::Identity();

    // Subtract translation
    glm::vec3 translate = glm::vec3(world[3]);

    // Subtract scale
    glm::vec3 scale(
        glm::length(world[0]),
        glm::length(world[1]),
        glm::length(world[2])
    );

    // Apply translate & scale on 8 corners
    for (int i = 0; i < 8; ++i) {
        transformedCorners[i] = this->bCorners[i] * scale + translate;
    }

    // Reset min/max
    min[0] = transformedCorners[0].x;
    min[1] = transformedCorners[0].y;
    min[2] = transformedCorners[0].z;
    max[0] = transformedCorners[0].x;
    max[1] = transformedCorners[0].y;
    max[2] = transformedCorners[0].z;

    // Update min/max between 8 corners
    for (int i = 1; i < 8; ++i) {
        min[0] = std::min(min[0], transformedCorners[i].x);
        min[1] = std::min(min[1], transformedCorners[i].y);
        min[2] = std::min(min[2], transformedCorners[i].z);

        max[0] = std::max(max[0], transformedCorners[i].x);
        max[1] = std::max(max[1], transformedCorners[i].y);
        max[2] = std::max(max[2], transformedCorners[i].z);
    }
}

#pragma once

#include "./BoundingGeometry.h"
struct Vertex;

class AABB : public BoundingGeometry {
public:
    AABB();

    void Init(const std::vector<Vertex>& vertices) override;
    void ComputeMinMaxForAllVertices(const std::vector<Vertex>& vertexPack) override;
    void UpdateGlobalBounds(const glm::mat4& world) override;

    std::vector<Eigen::Vector3d>& GetCorners() override;

    // #to protected
    glm::vec3 transformedCorners[8];

    std::array<float, 3> min;
    std::array<float, 3> max;
protected:
    std::array<float, 3> bMin;
    std::array<float, 3> bMax;



    std::array<float, 3> size;
    std::array<float, 3> center;

    glm::vec3 bCorners[8];
};

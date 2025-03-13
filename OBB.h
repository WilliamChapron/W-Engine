#pragma once


#include "./BoundingGeometry.h"
struct Vertex;

class OBB : public BoundingGeometry {
public:
    OBB();

    std::vector<Eigen::Vector3d>& GetCorners() override;
    void Init(const std::vector<Vertex>& vertices) override;
    void ComputeCenter() override;
    void ComputeSize() override;
    void ComputeMinMaxForAllVertices(const std::vector<Vertex>& vertices) override;
    void UpdateGlobalBounds(const glm::mat4& world) override;

private:
    Eigen::Vector3d min, max;
};


#pragma once

struct Vertex;

class BoundingGeometry {
public:
    BoundingGeometry();
    virtual ~BoundingGeometry() = default;

    virtual void Init(const std::vector<Vertex>& vertices);
    virtual void ComputeCenter();
    virtual void ComputeSize();
    virtual void ComputeMinMaxForAllVertices(const std::vector<Vertex>& vertices);
    virtual void UpdateGlobalBounds(const glm::mat4& world) = 0;

    virtual std::vector<Eigen::Vector3d>& GetCorners() = 0;

    // #to protected
    Eigen::Matrix3d m_rotation;

protected:
    Eigen::Vector3d m_center;
    Eigen::Vector3d m_size;

    std::vector<Eigen::Vector3d> m_corners;
};

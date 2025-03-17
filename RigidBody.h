#include <Eigen/Dense>
#include <glm/glm.hpp>

#pragma once
class Transform;

class RigidBody {
public:
    RigidBody(Transform* transform, float mass);

    void ApplyForce(const Eigen::Vector3d& force, const Eigen::Vector3d& point = Eigen::Vector3d(0.0, 0.0, 0.0));
    void ApplyTorque(const Eigen::Vector3d& torqueToApply);

    void Update(float deltaTime);

    Eigen::Vector3d velocity;
    Eigen::Vector3d acceleration;
    Eigen::Vector3d angularVelocity; 
    Eigen::Vector3d torque; 
    Eigen::Matrix3d inertia; 
    float mass;
    Transform* m_transform;

    glm::vec3 EigenToGLM(const Eigen::Vector3d& eigenVec) const;
    Eigen::Vector3d GLMToEigen(const glm::vec3& glmVec) const;

private:
};

#include "pch.h"
#include "RigidBody.h"
#include "Transform.h"
#include <Eigen/Dense>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>  // Pour utiliser des quaternions si nécessaire

RigidBody::RigidBody(Transform* transform, float mass) :
    m_transform(transform),
    mass(mass),
    velocity(Eigen::Vector3d(0.0, 0.0, 0.0)),
    acceleration(Eigen::Vector3d(0.0, 0.0, 0.0)),
    angularVelocity(Eigen::Vector3d(0.0, 0.0, 0.0)),
    torque(Eigen::Vector3d(0.0, 0.0, 0.0)),
    inertia(Eigen::Matrix3d::Identity())  
{
}

void RigidBody::ApplyForce(const Eigen::Vector3d& force, const Eigen::Vector3d& point) {

    acceleration += force / mass;

    //
    Eigen::Vector3d r = point - GLMToEigen(m_transform->GetPosition()); // Vecteur de position relatif
    torque += r.cross(force);  // Couple = r x F / Moment of force by the force and application point
}

void RigidBody::ApplyTorque(const Eigen::Vector3d& torqueToApply) {
    torque += torqueToApply; 
}

void RigidBody::Update(float deltaTime) {

    velocity += acceleration * deltaTime;
    glm::vec3 velocityGLM = EigenToGLM(velocity);
    glm::vec3 newPosition = m_transform->GetPosition() + velocityGLM * deltaTime;
    m_transform->SetPosition(newPosition);
    acceleration = Eigen::Vector3d(0.0, 0.0, 0.0);


    glm::vec3 forcePosition = m_transform->GetPosition(); 
    glm::vec3 forceGLM = EigenToGLM(torque); 
    glm::vec3 torqueGLM = glm::cross(forcePosition, forceGLM);
    Eigen::Vector3d torque = GLMToEigen(torqueGLM);  


    Eigen::Vector3d angularAcceleration = inertia.inverse() * torque;  // angular acceleration : I^-1 * torque
    angularVelocity += angularAcceleration * deltaTime; 
    glm::vec3 angularVelocityGLM = glm::vec3(angularVelocity.x(), angularVelocity.y(), angularVelocity.z());

    glm::mat4 rotationDelta = glm::rotate(glm::mat4(1.0f), glm::length(angularVelocityGLM) * deltaTime, glm::normalize(angularVelocityGLM));
    glm::mat4 worldMatrix = m_transform->GetWorldMatrix();
    glm::mat3 rotationMatrix = glm::mat3(worldMatrix);
    rotationMatrix = rotationMatrix * glm::mat3(rotationDelta);

    //torque += angularVelocity;
    //m_transform->SetRotation(glm::vec3(torque.x(), torque.y(), torque.z()));

}

glm::vec3 RigidBody::EigenToGLM(const Eigen::Vector3d& eigenVec) const {
    return glm::vec3(static_cast<float>(eigenVec.x()), static_cast<float>(eigenVec.y()), static_cast<float>(eigenVec.z()));
}

Eigen::Vector3d RigidBody::GLMToEigen(const glm::vec3& glmVec) const {
    return Eigen::Vector3d(
        static_cast<double>(glmVec.x), 
        static_cast<double>(glmVec.y),
        static_cast<double>(glmVec.z)
    );
}
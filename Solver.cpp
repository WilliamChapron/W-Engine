#include "pch.h"

#include "RigidBody.h"
#include "Transform.h"
#include "./Solver.h"

void Solver::ResolveCollision(RigidBody& rb1, RigidBody& rb2, CollisionInfo& collisionInfo) {
    if (!collisionInfo.hasCollision) return;

    const float restitution = 0.5f; 

    Eigen::Vector3d normal1 = collisionInfo.bestAxis1;
    Eigen::Vector3d normal2 = collisionInfo.bestAxis2;

    Eigen::Vector3d relativeVelocity = rb2.velocity - rb1.velocity;
    float velocityAlongNormal = relativeVelocity.dot(normal1);

    if (velocityAlongNormal > 0) return;

    // loi de restitution de Newton
    float j = -(1 + restitution) * velocityAlongNormal;
    j /= (1 / rb1.mass) + (1 / rb2.mass);

    Eigen::Vector3d impulse = j * normal1;

    rb1.velocity -= impulse / rb1.mass;
    rb2.velocity += impulse / rb2.mass;

    const float percent = 0.8f;
    Eigen::Vector3d correction = percent * collisionInfo.penetrationDepth * normal1 / (1 / rb1.mass + 1 / rb2.mass);

    glm::vec3 position1 = rb1.m_transform->GetPosition();
    glm::vec3 position2 = rb2.m_transform->GetPosition();


    rb1.m_transform->SetPosition(position1 - glm::vec3(correction.x(), correction.y(), correction.z()) * (1 / rb1.mass));
    rb2.m_transform->SetPosition(position2 + glm::vec3(correction.x(), correction.y(), correction.z()) * (1 / rb2.mass));
}



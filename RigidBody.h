#pragma once
#include "Transform.h"
#include <glm/glm.hpp>

class RigidBody {
public:
    RigidBody(Transform* transform, float mass);

    void ApplyForce(const glm::vec3& force);
    void Update(float deltaTime);

    glm::vec3 velocity;
    glm::vec3 acceleration;
    float mass;

private:
    Transform* transform;
};
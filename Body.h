#pragma once

#include "Transform.h"

class Body {
public:
    Body();
    Body(const float velocity[3], float mass);

    // Getters
    glm::vec3 GetPosition() const;
    const float* GetVelocity() const;
    float GetMass() const;
    inline Transform* GetTransform() { return m_Transform; }

    // Setters
    void SetVelocity(const float velocity[3]);

    void ApplyForce(const float force[3]);
    void Update(float deltaTime);

private:
    Transform* m_Transform;   
    float m_Velocity[3];      
    float m_Mass;              
};

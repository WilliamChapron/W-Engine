#include "pch.h"

#include "Body.h"
#include "Body.h"

Body::Body() : m_Mass(0.0005f) { 
    m_Transform = new Transform();

    m_Velocity[0] = 0.0f; 
    m_Velocity[1] = 0.0f; 
    m_Velocity[2] = 0.0f; 
}

Body::Body(const float velocity[3], float mass)
    : m_Mass(mass) {
    m_Transform = new Transform();
    SetVelocity(velocity);
}

glm::vec3 Body::GetPosition() const {
    return m_Transform->GetPosition();
}
const float* Body::GetVelocity() const {
    return m_Velocity;
}
float Body::GetMass() const {
    return m_Mass;
}

void Body::SetVelocity(const float velocity[3]) {
    for (int i = 0; i < 3; ++i) {
        m_Velocity[i] = velocity[i];
    }
}

void Body::ApplyForce(const float force[3]) {

    for (int i = 0; i < 3; ++i) {
        m_Velocity[i] += force[i] * m_Mass; 
    }
}

void Body::Update(float deltaTime) {
    float force[3] = { 0.0f, -1.0f, 0.0f }; 
    ApplyForce(force); 

    glm::vec3 newPosition = m_Transform->GetPosition();
    for (int i = 0; i < 3; ++i) {
        newPosition[i] += m_Velocity[i] * deltaTime; 
    }
    m_Transform->SetPosition(newPosition); 
}
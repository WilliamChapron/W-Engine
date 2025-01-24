#include "pch.h"
#include "RigidBody.h"

RigidBody::RigidBody(Transform* transform, float mass)  : transform(transform), mass(mass), velocity(0.0f), acceleration(0.0f) {
}

void RigidBody::ApplyForce(const glm::vec3& force) {
    acceleration += force / mass;  // F = m * a  -> a = F / m
}

void RigidBody::Update(float deltaTime) {
    velocity += acceleration * deltaTime;  // Intégration de l'accélération
    transform->SetPosition(transform->GetPosition() + velocity * deltaTime);  // Mise à jour de la position
    acceleration = glm::vec3(0.0f);  // Réinitialisation de l'accélération après chaque frame
}

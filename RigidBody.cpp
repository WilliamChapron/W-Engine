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

// CALCULONS LES MOMENT ET MATRICE D'INERTIE INDEPENDANTE POUR CHAQUE COMPOSANT D'UN ENSEMBLE, ajoutons en plus du add force la possibilité de rotate 
//add torque peut etre qui modifiera la rotation mais sa sera l'ensemble total qui en ser le declencheur

// LA MATRICE TOTALE ET LES DEPLACEMENTS TOTALS SERONT GERE PAR UN CONTROLLER QUI S'apellera CollectivePhysicEnsemble qui calculera les elements pour un ensembles d'objets associé 
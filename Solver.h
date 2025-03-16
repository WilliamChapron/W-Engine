#pragma once

class RigidBody;
#include "PhysicSystem.h"

class Solver {
public:
    static void ResolveCollision(RigidBody& rb1, RigidBody& rb2, CollisionInfo& collisionInfo);
};
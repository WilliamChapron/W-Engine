#pragma once

struct OBB;

class PhysicSystem
{
public:
    PhysicSystem() {};

    void CheckCollision();
    void ResolveCollision();
    bool OBB_Collision(const OBB& obb1, const OBB& obb2);
};


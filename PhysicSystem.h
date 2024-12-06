#pragma once

struct OBB;

class PhysicSystem
{
public:
    PhysicSystem() {};

    void CheckCollision();
    void ResolveCollision();


    bool OBB_Collision(OBB& obb1, OBB& obb2);

    //bool ProjectCornerOnAxisAndCheckCollision();
};


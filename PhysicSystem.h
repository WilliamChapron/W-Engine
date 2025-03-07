#pragma once

struct OBB;
struct AABB;

//#include "BoxCollider.h"

class PhysicSystem {
public:
    //check collision
    bool OBB_Collision(OBB& obb1, OBB& obb2);






    // ******** Collision Only ********
    bool TestOBBvsOBB_CollisionOnly(OBB& obb1, OBB& obb2);
    bool TestAABBvsAABB_CollisionOnly(AABB& aabb1, AABB& aabb2);
    //Not Implemented
    //bool TestAABBvsOBB_CollisionOnly(OBB& obb1, AABB& obb2);
    //

    // ******** Collision With Points Implicated ********
    bool TestOBBvsOBB_CollisionWithPoints(OBB& obb1, OBB& obb2,
        std::vector<Eigen::Vector3d>& collisionPointsOBB1,
        std::vector<Eigen::Vector3d>& collisionPointsOBB2);
    


    // ******** Collision With Faces Implicated ********



private:
    // part of check collision
    void SearchReceiverInplicatedFace(OBB& obb, const std::vector<Eigen::Vector3d>& collisionPoints, std::vector<std::string>& implicatedFaces);

    //intermediate
    std::vector<Eigen::Vector3d> GenerateAxes(const OBB& obb1, const OBB& obb2);
    void ProjectCornersOnAxis(const std::vector<Eigen::Vector3d>& corners, const Eigen::Vector3d& axis, double& min, double& max);
    bool TestCornerOnAxes(const Eigen::Vector3d& corner, const std::vector<Eigen::Vector3d>& axes, const OBB& obb);

};
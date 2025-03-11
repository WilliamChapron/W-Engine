#pragma once


struct BoundingGeometry;
struct OBB;
struct AABB;

class PhysicSystem {
public:
    //check collision
    bool OBB_Collision(BoundingGeometry& bg1, BoundingGeometry& bg2);






    // ******** Collision Only ********
    bool TestOBBvsOBB_CollisionOnly(BoundingGeometry& bg1, BoundingGeometry& bg2);
    bool TestAABBvsAABB_CollisionOnly(AABB& aabb1, AABB& aabb2);
    //Not Implemented
    bool TestAABBvsOBB_CollisionOnly(BoundingGeometry& bg1, BoundingGeometry& bg2);
    //

    // ******** Collision With Points Implicated ********
    bool TestOBBvsOBB_CollisionWithPoints(BoundingGeometry& bg1, BoundingGeometry& bg2, std::vector<Eigen::Vector3d>& collisionPointsOBB1, std::vector<Eigen::Vector3d>& collisionPointsOBB2);
    bool TestAABBvsAABB_CollisionWithPoints(); // Not implemented


    // ******** Collision With Points & Faces Implicated ********





private:
    // Faces
    void SearchReceiverInplicatedFace(BoundingGeometry& bg, const std::vector<Eigen::Vector3d>& collisionPoints, std::vector<std::string>& implicatedFaces);

    // SAT Algorithm
    std::vector<Eigen::Vector3d> GenerateAxes(BoundingGeometry& bg1, BoundingGeometry& bg2);
    void ProjectCornersOnAxis(std::vector<Eigen::Vector3d>& corners, const Eigen::Vector3d& axis, double& min, double& max);
    bool TestCornerOnAxes(const Eigen::Vector3d& corner, const std::vector<Eigen::Vector3d>& axes, BoundingGeometry& bg);

};
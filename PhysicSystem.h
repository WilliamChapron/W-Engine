#pragma once


struct BoundingGeometry;
struct OBB;
struct AABB;

class PhysicSystem {
public:
    // ******** Collision Only ********
    bool TestOBBvsOBB_CollisionOnly(BoundingGeometry& bg1, BoundingGeometry& bg2);
    bool TestAABBvsAABB_CollisionOnly(AABB& aabb1, AABB& aabb2);
    //Not Implemented
    bool TestAABBvsOBB_CollisionOnly(BoundingGeometry& bg1, BoundingGeometry& bg2);
    //

    // ******** Collision With Points Implicated ********
    bool TestOBBvsOBB_CollisionWithCorners(BoundingGeometry& bg1, BoundingGeometry& bg2, std::vector<Eigen::Vector3d>& collisionPointsOBB1, std::vector<Eigen::Vector3d>& collisionPointsOBB2);
    bool TestAABBvsAABB_CollisionWithCorners(); // Not implemented


    // ******** Collision Faces Implicated ********
    bool TestOBBvsOBB_CollisionWithFaces(BoundingGeometry& bg1, BoundingGeometry& bg2);



    // Contacts Points / Normals & Penetration
    bool TestOBBvsOBB_CollisionWithContactPoints(BoundingGeometry& bg1, BoundingGeometry& bg2);







private:
    // SAT Algorithm
    // 
    // Projection
    std::vector<Eigen::Vector3d> GenerateAxes(BoundingGeometry& bg1, BoundingGeometry& bg2);
    void ProjectCornersOnAxis(std::vector<Eigen::Vector3d>& corners, const Eigen::Vector3d& axis, double& min, double& max);
    bool TestCornerOnAxes(const Eigen::Vector3d& corner, const std::vector<Eigen::Vector3d>& axes, BoundingGeometry& bg);

    // Face
    void SearchReceiverInplicatedFace(BoundingGeometry& bg, const std::vector<Eigen::Vector3d>& collisionPoints, std::vector<std::string>& implicatedFaces);

    // ContactsPoint & Penetration
    Eigen::Vector3d ComputeCollisionNormal(BoundingGeometry& receiver, const std::vector<Eigen::Vector3d>& collisionPoints, const std::vector<std::string>& implicatedFaces);

    // #todo will be used by search face
    Eigen::Vector3d GetFaceNormal(const std::string& faceName, const std::vector<Eigen::Vector3d>& corners);

};
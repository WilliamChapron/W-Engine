#pragma once

struct OBB;

class PhysicSystem {
public:
    //check collision
    bool OBB_Collision(OBB& obb1, OBB& obb2);

private:
    // part of check collision
    void SearchReceiverInplicatedFace(OBB& obb, const std::vector<Eigen::Vector3d>& collisionPoints, std::vector<std::string>& implicatedFaces);

    //intermediate
    std::vector<Eigen::Vector3d> GenerateAxes(const OBB& obb1, const OBB& obb2);
    void ProjectCornersOnAxis(const std::vector<Eigen::Vector3d>& corners, const Eigen::Vector3d& axis, double& min, double& max);
    bool TestCornerOnAxes(const Eigen::Vector3d& corner, const std::vector<Eigen::Vector3d>& axes, const OBB& obb);

};
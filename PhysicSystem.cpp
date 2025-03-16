#include "pch.h"


#include "PhysicSystem.h"

#include "AABB.h"
#include "OBB.h"

#include "./RenderStructures.h"




#pragma region UsualFunctions
// returns a list of potential separating axes for the Separating Axis Theorem (SAT) collision test (15 axes in worst case)
std::vector<Eigen::Vector3d> PhysicSystem::GenerateAxes(BoundingGeometry& bg1, BoundingGeometry& bg2) {
    std::vector<Eigen::Vector3d> axes;

    // Normal of faces (from rotation matrix)
    for (int i = 0; i < 3; ++i) {
        axes.push_back(bg1.m_rotation.col(i));
        axes.push_back(bg2.m_rotation.col(i));
    }

    // Cross axis
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {

            Eigen::Vector3d crossAxis = bg1.m_rotation.col(i).cross(bg2.m_rotation.col(j));

            // Avoid null cross axes
            if (crossAxis.norm() > 1e-6) {

                Eigen::Vector3d normalizedAxis = crossAxis.normalized();

                // if nothing find, nothing identic
                if (std::find(axes.begin(), axes.end(), normalizedAxis) == axes.end()) {
                    axes.push_back(normalizedAxis);
                }
            }
        }
    }

    return axes;
}


void PhysicSystem::ProjectCornersOnAxis(std::vector<Eigen::Vector3d>& corners, const Eigen::Vector3d& axis, double& min, double& max) {
    min = std::numeric_limits<double>::max();
    max = -std::numeric_limits<double>::max();

    Eigen::Vector3d normalizedAxis = axis.normalized();

    for (const auto& corner : corners) {
        double projection = normalizedAxis.dot(corner);
        min = std::min(min, projection);
        max = std::max(max, projection);
    }
}

bool PhysicSystem::TestCornerOnAxes(const Eigen::Vector3d& corner, const std::vector<Eigen::Vector3d>& axes, BoundingGeometry& bg) {
    for (const auto& axis : axes) {
        double min, max;

        ProjectCornersOnAxis(bg.GetCorners(), axis, min, max);

        double projection = axis.dot(corner);
        if (projection < min || projection > max) {
            return false; // No collision on axis
        }
    }
    return true;
}


#pragma endregion









Eigen::Vector3d PhysicSystem::GetFaceNormal(const std::string& faceName, const std::vector<Eigen::Vector3d>& corners) {
    auto it = faces.find(faceName);
    if (it == faces.end()) {
        std::cerr << "Erreur : Face non trouvée." << std::endl;
        return Eigen::Vector3d::Zero();
    }

    const auto& indices = it->second;  

    Eigen::Vector3d v1 = corners[indices[1]] - corners[indices[0]];
    Eigen::Vector3d v2 = corners[indices[2]] - corners[indices[0]];

    Eigen::Vector3d normal = v1.cross(v2);

    return normal.normalized();
}

Eigen::Vector3d PhysicSystem::ComputeCollisionNormal(
    BoundingGeometry& receiver,
    const std::vector<Eigen::Vector3d>& collisionPoints,
    const std::vector<std::string>& implicatedFaces)
{
    Eigen::Vector3d normal(0, 0, 0);
    //if (collisionPoints.empty() || implicatedFaces.empty()) return normal;

    //// Trouver la face la plus proche du centre de masse du receveur
    //double minDist = std::numeric_limits<double>::max();
    //for (const auto& face : implicatedFaces) {
    //    Eigen::Vector3d faceNormal = GetFaceNormal(face, receiver.GetCorners());

    //    for (const auto& point : collisionPoints) {
    //        double dist = std::abs((point - receiver.m_center).dot(faceNormal));
    //        if (dist < minDist) {
    //            minDist = dist;
    //            normal = faceNormal;
    //        }
    //    }
    //}
    return normal.normalized();
}



















#pragma region CollisionOnly
bool PhysicSystem::TestOBBvsOBB_CollisionOnly(BoundingGeometry& bg1, BoundingGeometry& bg2) {
    std::vector<Eigen::Vector3d> axes = GenerateAxes(bg1, bg2);

    std::vector<Eigen::Vector3d>& c1 = bg1.GetCorners();
    std::vector<Eigen::Vector3d>& c2 = bg2.GetCorners();

    for (const auto& axis : axes) {
        double min1, max1, min2, max2;

        // Project 2 OBB corners on this axis
        ProjectCornersOnAxis(c1, axis, min1, max1);
        ProjectCornersOnAxis(c2, axis, min2, max2);

        // No overlap of max with min => no collision
        if (max1 < min2 || max2 < min1) {
            std::cout << "Pas de collision, séparation détectée sur un axe.\n";
            return false;
        }
    }

    std::cout << "Collision détectée entre les OBB.\n";
    return true;
}

bool PhysicSystem::TestAABBvsAABB_CollisionOnly(AABB& aabb1, AABB& aabb2)
{
    // x
    bool collisionX = aabb1.max[0] >= aabb2.min[0] && aabb2.max[0] >= aabb1.min[0];
    // y
    bool collisionY = aabb1.max[1] >= aabb2.min[1] && aabb2.max[1] >= aabb1.min[1];
    // z
    bool collisionZ = aabb1.max[2] >= aabb2.min[2] && aabb2.max[2] >= aabb1.min[2];

    return collisionX && collisionY && collisionZ;
}

bool PhysicSystem::TestAABBvsOBB_CollisionOnly(BoundingGeometry& bg1, BoundingGeometry& bg2)
{
    std::vector<Eigen::Vector3d> axes = GenerateAxes(bg1, bg2);
    bool isColliding = false;

    std::vector<Eigen::Vector3d>& c1 = bg1.GetCorners();
    std::vector<Eigen::Vector3d>& c2 = bg2.GetCorners();


    if (isColliding) {
        std::cout << "Collision detectee entre les OBB.\n";
    }
    else {
        std::cout << "Aucune collision detectee.\n";
    }

    return isColliding;
}


#pragma endregion




#pragma region CollisionWithPoints
bool PhysicSystem::TestOBBvsOBB_CollisionWithCorners(BoundingGeometry& bg1, BoundingGeometry& bg2, std::vector<Eigen::Vector3d>& collisionPointsbg1, std::vector<Eigen::Vector3d>& collisionPointsbg2)
{
    std::vector<Eigen::Vector3d> axes = GenerateAxes(bg1, bg2);

    std::vector<Eigen::Vector3d>& c1 = bg1.GetCorners();
    std::vector<Eigen::Vector3d>& c2 = bg2.GetCorners();

    // test bg1 corners on axes
    for (size_t i = 0; i < c1.size(); ++i) {
        const auto& c = c1[i];
        if (TestCornerOnAxes(c, axes, bg2)) {
            collisionPointsbg1.push_back(c);
            std::cout << "Coin 1 (Droite) index: " << i << ", Color: " << colors[i] << "\n";
        }
    }

    // test bg2 corners on axes
    for (size_t i = 0; i < c2.size(); ++i) {
        const auto& c = c2[i];
        if (TestCornerOnAxes(c, axes, bg1)) {
            collisionPointsbg2.push_back(c);
            std::cout << "Coin 2 (Gauche) index: " << i << ", Color: " << colors[i] << "\n";
        }
    }
    return !collisionPointsbg1.empty() || !collisionPointsbg2.empty();
}
#pragma endregion



#pragma region CollisionWithFaces

bool PhysicSystem::TestOBBvsOBB_CollisionWithFaces(BoundingGeometry& bg1, BoundingGeometry& bg2) {
    std::vector<Eigen::Vector3d>& c1 = bg1.GetCorners(); // Coins de l'OBB 1
    std::vector<Eigen::Vector3d>& c2 = bg2.GetCorners(); // Coins de l'OBB 2
    std::vector<Eigen::Vector3d> axes = GenerateAxes(bg1, bg2); // Générer les axes de séparation

    std::vector<std::string> implicatedFaces1;
    std::vector<std::string> implicatedFaces2;

    return true;
}

#pragma endregion


CollisionInfo PhysicSystem::TestOBBvsOBB_CollisionWithContactPoints(BoundingGeometry& bg1, BoundingGeometry& bg2) {
    std::vector<Eigen::Vector3d>& c1 = bg1.GetCorners();
    std::vector<Eigen::Vector3d>& c2 = bg2.GetCorners();
    std::vector<Eigen::Vector3d> axes = GenerateAxes(bg1, bg2);

    CollisionInfo collisionInfo;
    collisionInfo.hasCollision = false;
    collisionInfo.penetrationDepth = std::numeric_limits<double>::max();

    for (auto& axis : axes) {
        double min1, max1, min2, max2;
        ProjectCornersOnAxis(c1, axis, min1, max1);
        ProjectCornersOnAxis(c2, axis, min2, max2);

        if (max1 < min2 || max2 < min1) {
            std::cout << "Pas de collision sur l'axe : " << axis.transpose() << std::endl;
            return collisionInfo; // Pas de collision
        }

        double overlap = std::min(max1, max2) - std::max(min1, min2);
        if (overlap < collisionInfo.penetrationDepth) {
            collisionInfo.penetrationDepth = overlap;
            collisionInfo.bestAxis1 = axis;
        }

        if (overlap > 0) {
            Eigen::Vector3d contactPoint = (axis * (std::max(min1, min2) + overlap / 2));
            collisionInfo.contactPoints1.push_back(contactPoint);
            collisionInfo.contactPoints2.push_back(contactPoint);
        }
    }

    collisionInfo.hasCollision = true;
    collisionInfo.bestAxis2 = -collisionInfo.bestAxis1;

    std::cout << "Collision détectée !" << std::endl;
    std::cout << "Pénétration : " << collisionInfo.penetrationDepth << std::endl;
    std::cout << "Meilleure direction de collision : " << collisionInfo.bestAxis1.transpose() << std::endl;

    std::cout << "Points de contact pour OBB1 : " << std::endl;
    for (const auto& point : collisionInfo.contactPoints1) {
        std::cout << "OBB1 - " << point.transpose() << std::endl;
    }

    std::cout << "Points de contact pour OBB2 : " << std::endl;
    for (const auto& point : collisionInfo.contactPoints2) {
        std::cout << "OBB2 - " << point.transpose() << std::endl;
    }

    std::cout << "---------FRAME--------- : " << "\n" << std::endl;

    return collisionInfo;
}
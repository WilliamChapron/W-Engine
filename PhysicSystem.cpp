#include "pch.h"


#include "PhysicSystem.h"

#include "AABB.h"
#include "OBB.h"

#include "./RenderStructures.h"




#pragma region UsualFunctions
// returns a list of potential separating axes for the Separating Axis Theorem (SAT) collision test.
std::vector<Eigen::Vector3d> PhysicSystem::GenerateAxes(BoundingGeometry& bg1, BoundingGeometry& bg2) {
    std::vector<Eigen::Vector3d> axes;

    // Ajouter les normales des faces
    for (int i = 0; i < 3; ++i) {
        axes.push_back(bg1.m_rotation.col(i));
        axes.push_back(bg2.m_rotation.col(i));
    }

    // Ajouter les axes croisés
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            Eigen::Vector3d crossAxis = bg1.m_rotation.col(i).cross(bg2.m_rotation.col(j));
            if (crossAxis.norm() > 1e-6) {
                Eigen::Vector3d normalizedAxis = crossAxis.normalized();
                if (std::find(axes.begin(), axes.end(), normalizedAxis) == axes.end()) {
                    axes.push_back(normalizedAxis);
                }
            }
        }
    }

    return axes;
}

// Projette les coins sur un axe et retourne les min/max
void PhysicSystem::ProjectCornersOnAxis(std::vector<Eigen::Vector3d>& corners, const Eigen::Vector3d& axis, double& min, double& max) {
    min = std::numeric_limits<double>::max();
    max = -std::numeric_limits<double>::max();

    for (const auto& corner : corners) {
        double projection = axis.dot(corner);
        min = std::min(min, projection);
        max = std::max(max, projection);
    }
}

// Teste si un coin se trouve dans tous les axes projetés de l'autre OBB

// bg -> bounding geometry
bool PhysicSystem::TestCornerOnAxes(const Eigen::Vector3d& corner, const std::vector<Eigen::Vector3d>& axes, BoundingGeometry& bg) {
    for (const auto& axis : axes) {
        double min, max;
        ProjectCornersOnAxis(bg.GetCorners(), axis, min, max);

        double projection = axis.dot(corner);
        if (projection < min || projection > max) {
            return false; // Pas de collision sur cet axe
        }
    }
    return true;
}


void PhysicSystem::SearchReceiverInplicatedFace(BoundingGeometry& bg, const std::vector<Eigen::Vector3d>& collisionPoints, std::vector<std::string>& implicatedFaces) {
    implicatedFaces.clear();

    // Parcourir les points de collision
    for (const auto& point : collisionPoints) {
        double minDistance = std::numeric_limits<double>::max();
        std::string closestFace;

        // Parcourir toutes les faces
        for (const auto& pair : faces) {
            const std::string& faceName = pair.first;    
            const std::vector<int>& indices = pair.second; 


            // Get corners
            std::vector<Eigen::Vector3d>& c = bg.GetCorners();
            // Calculer la normale de la face
            Eigen::Vector3d v1 = c[indices[1]] - c[indices[0]];
            Eigen::Vector3d v2 = c[indices[3]] - c[indices[0]];
            Eigen::Vector3d normal = v1.cross(v2).normalized();

            // Calculer la distance entre le point et le plan de la face
            Eigen::Vector3d faceCenter = Eigen::Vector3d::Zero();
            for (int index : indices) {
                faceCenter += c[index];
            }
            faceCenter /= indices.size();

            double distanceToPlane = (point - faceCenter).dot(normal);

            // Si la distance est plus proche que la précédente
            if (std::abs(distanceToPlane) < minDistance) {
                minDistance = std::abs(distanceToPlane);
                closestFace = faceName;
            }
        }

        // Ajouter la face impliquée
        if (!closestFace.empty() && std::find(implicatedFaces.begin(), implicatedFaces.end(), closestFace) == implicatedFaces.end()) {
            implicatedFaces.push_back(closestFace);
        }
    }
}
#pragma endregion


#pragma region CollisionOnly
bool PhysicSystem::TestOBBvsOBB_CollisionOnly(BoundingGeometry& bg1, BoundingGeometry& bg2) {
    std::vector<Eigen::Vector3d> axes = GenerateAxes(bg1, bg2);
    bool isColliding = false;

    std::vector<Eigen::Vector3d>& c1 = bg1.GetCorners();
    std::vector<Eigen::Vector3d>& c2 = bg2.GetCorners();

    for (size_t i = 0; i < c1.size(); ++i) {
        const auto& corner1 = c1[i];
        if (TestCornerOnAxes(corner1, axes, bg2)) {
            isColliding = true;
        }
    }

    for (size_t i = 0; i < c2.size(); ++i) {
        const auto& corner2 = c2[i];
        if (TestCornerOnAxes(corner2, axes, bg1)) {
            isColliding = true;
        }
    }

    if (isColliding) {
        std::cout << "Collision detectee entre les OBB.\n";
    }
    else {
        std::cout << "Aucune collision detectee.\n";
    }

    return isColliding;
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

    for (size_t i = 0; i < c1.size(); ++i) {
        const auto& corner1 = c1[i];
        if (TestCornerOnAxes(corner1, axes, bg2)) {
            isColliding = true;
        }
    }

    for (size_t i = 0; i < c2.size(); ++i) {
        const auto& corner2 = c2[i];
        if (TestCornerOnAxes(corner2, axes, bg1)) {
            isColliding = true;
        }
    }

    if (isColliding) {
        std::cout << "Collision detectee entre les OBB.\n";
    }
    else {
        std::cout << "Aucune collision detectee.\n";
    }

    return isColliding;
}

#pragma endregion



















// RETRIEVE IMPLICATED POINTS
bool PhysicSystem::TestOBBvsOBB_CollisionWithPoints(BoundingGeometry& bg1, BoundingGeometry& bg2, std::vector<Eigen::Vector3d>& collisionPointsbg1, std::vector<Eigen::Vector3d>& collisionPointsbg2)
{
    std::vector<Eigen::Vector3d> axes = GenerateAxes(bg1, bg2);

    std::vector<Eigen::Vector3d>& c1 = bg1.GetCorners();
    std::vector<Eigen::Vector3d>& c2 = bg2.GetCorners();

    // Tester les coins de bg1
    for (size_t i = 0; i < c1.size(); ++i) {
        const auto& corner1 = c1[i];
        if (TestCornerOnAxes(corner1, axes, bg2)) {
            collisionPointsbg1.push_back(corner1);
            std::cout << "Coin 1 (Droite) index: " << i << ", Color: " << colors[i] << "\n";
        }
    }

    // Tester les coins de bg2
    for (size_t i = 0; i < c2.size(); ++i) {
        const auto& corner2 = c2[i];
        if (TestCornerOnAxes(corner2, axes, bg1)) {
            collisionPointsbg2.push_back(corner2);
            std::cout << "Coin 2 (Gauche) index: " << i << ", Color: " << colors[i] << "\n";
        }
    }

    return !collisionPointsbg1.empty() || !collisionPointsbg2.empty();
}

bool PhysicSystem::OBB_Collision(BoundingGeometry& bg1, BoundingGeometry& bg2) {
    std::vector<Eigen::Vector3d> axes = GenerateAxes(bg1, bg2);
    std::vector<Eigen::Vector3d> collisionPointsbg1;
    std::vector<Eigen::Vector3d> collisionPointsbg2;

    std::vector<Eigen::Vector3d>& c1 = bg1.GetCorners();
    std::vector<Eigen::Vector3d>& c2 = bg2.GetCorners();

    // Tester les coins de bg1
    for (size_t i = 0; i < c1.size(); ++i) {
        const auto& corner1 = c1[i];
        if (TestCornerOnAxes(corner1, axes, bg2)) {
            collisionPointsbg1.push_back(corner1);
            std::cout << "Coin 1 (Droite) index: " << i << ", Color: " << colors[i] << "\n";
        }
    }

    // Tester les coins de bg2
    for (size_t i = 0; i < c2.size(); ++i) {
        const auto& corner2 = c2[i];
        if (TestCornerOnAxes(corner2, axes, bg1)) {
            collisionPointsbg2.push_back(corner2);
            std::cout << "Coin 2 (Gauche) index: " << i << ", Color: " << colors[i] << "\n";
        }
    }

    // Résultat final
    if (!collisionPointsbg1.empty() || !collisionPointsbg2.empty()) {
        //std::cout << "Total collision points bg1: " << collisionPointsbg1.size() << "\n";
        //std::cout << "Total collision points bg2: " << collisionPointsbg2.size() << "\n";

        //std::cout << "Searching implicated faces...\n";
        std::cout << "--------------------------------\n";

        if (!collisionPointsbg2.empty()) {
            std::vector<std::string> implicatedFaces1;
            // bg1 is the receiver, collisionPointsbg2 are the collision points of the penetrator
            SearchReceiverInplicatedFace(bg1, collisionPointsbg2, implicatedFaces1);

            if (!implicatedFaces1.empty()) {
                std::cout << "Impacted faces bg1 (right) (receiver): ";
                for (const auto& face : implicatedFaces1) {
                    auto it = faceColors.find(face);
                    if (it != faceColors.end()) {
                        std::cout << "Face: " << face << " - Color: " << it->second << "\n";
                    }
                }
                std::cout << "\n";
            }
            else {
                std::cout << "No implicated faces for bg1 (right) (receiver).\n";
            }
        }

        if (!collisionPointsbg1.empty()) {
            std::vector<std::string> implicatedFaces2;
            // bg2 is the receiver, collisionPointsbg1 are the collision points of the penetrator
            SearchReceiverInplicatedFace(bg2, collisionPointsbg1, implicatedFaces2);

            if (!implicatedFaces2.empty()) {
                std::cout << "Impacted faces bg2 (left) (receiver): ";
                for (const auto& face : implicatedFaces2) {
                    auto it = faceColors.find(face);
                    if (it != faceColors.end()) {
                        std::cout << "Face: " << face << " - Color: " << it->second << "\n";
                    }
                }
                std::cout << "\n";
            }
            else {
                std::cout << "No implicated faces for bg2 (left) (receiver).\n";
            }
        }
    }

    std::cout << "---------------CHANGING FRAME-----------------\n";

    return !collisionPointsbg1.empty() || !collisionPointsbg2.empty();
}
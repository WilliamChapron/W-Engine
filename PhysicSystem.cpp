#include "pch.h"
#include "PhysicSystem.h"


#include "BoxCollider.h"

std::vector<Eigen::Vector3d> PhysicSystem::GenerateAxes(const OBB& obb1, const OBB& obb2) {
    std::vector<Eigen::Vector3d> axes;

    // Ajouter les normales des faces
    for (int i = 0; i < 3; ++i) {
        axes.push_back(obb1.rotation.col(i));
        axes.push_back(obb2.rotation.col(i));
    }

    // Ajouter les axes croisés
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            Eigen::Vector3d crossAxis = obb1.rotation.col(i).cross(obb2.rotation.col(j));
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
void PhysicSystem::ProjectCornersOnAxis(const std::vector<Eigen::Vector3d>& corners, const Eigen::Vector3d& axis, double& min, double& max) {
    min = std::numeric_limits<double>::max();
    max = -std::numeric_limits<double>::max();

    for (const auto& corner : corners) {
        double projection = axis.dot(corner);
        min = std::min(min, projection);
        max = std::max(max, projection);
    }
}

// Teste si un coin se trouve dans tous les axes projetés de l'autre OBB
bool PhysicSystem::TestCornerOnAxes(const Eigen::Vector3d& corner, const std::vector<Eigen::Vector3d>& axes, const OBB& obb) {
    for (const auto& axis : axes) {
        double min, max;
        ProjectCornersOnAxis(obb.corners, axis, min, max);

        double projection = axis.dot(corner);
        if (projection < min || projection > max) {
            return false; // Pas de collision sur cet axe
        }
    }
    return true;
}

std::map<std::string, std::vector<int>> faces = {
    {"Front", {0, 1, 2, 3}},
    {"Back", {4, 5, 6, 7}},
    {"Left", {0, 3, 7, 4}},
    {"Right", {1, 2, 6, 5}},
    {"Top", {2, 3, 7, 6}},
    {"Bottom", {0, 1, 5, 4}}
};

std::map<std::string, std::string> faceColors = {
    {"Front", "Jaune"},
    {"Back", "Vert"},
    {"Left", "Bleu"},
    {"Right", "Rouge"},
    {"Top", "Cyan"},
    {"Bottom", "Magenta"}
};

void PhysicSystem::SearchInplicatedFace(OBB& obb, const std::vector<Eigen::Vector3d>& collisionPoints, std::vector<std::string>& implicatedFaces) {
    implicatedFaces.clear();

    // Parcourir les points de collision
    for (const auto& point : collisionPoints) {
        double minDistance = std::numeric_limits<double>::max();
        std::string closestFace;

        // Parcourir toutes les faces
        for (const auto& pair : faces) {
            const std::string& faceName = pair.first;    
            const std::vector<int>& indices = pair.second; 

            // Calculer la normale de la face
            Eigen::Vector3d v1 = obb.corners[indices[1]] - obb.corners[indices[0]];
            Eigen::Vector3d v2 = obb.corners[indices[3]] - obb.corners[indices[0]];
            Eigen::Vector3d normal = v1.cross(v2).normalized();

            // Calculer la distance entre le point et le plan de la face
            Eigen::Vector3d faceCenter = Eigen::Vector3d::Zero();
            for (int index : indices) {
                faceCenter += obb.corners[index];
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



bool PhysicSystem::OBB_Collision(OBB& obb1, OBB& obb2) {
    std::vector<Eigen::Vector3d> axes = GenerateAxes(obb1, obb2);
    std::vector<Eigen::Vector3d> collisionPointsOBB1; 
    std::vector<Eigen::Vector3d> collisionPointsOBB2; 

    // Tester les coins de obb1
    for (size_t i = 0; i < obb1.corners.size(); ++i) {
        const auto& corner1 = obb1.corners[i];
        if (TestCornerOnAxes(corner1, axes, obb2)) {
            collisionPointsOBB1.push_back(corner1);
            std::cout << "Coin 1 (Droite) index: " << i << ", Color: " << colors[i] << "\n";
        }
    }

    // Tester les coins de obb2
    for (size_t i = 0; i < obb2.corners.size(); ++i) {
        const auto& corner2 = obb2.corners[i];
        if (TestCornerOnAxes(corner2, axes, obb1)) {
            collisionPointsOBB2.push_back(corner2);
            std::cout << "Coin 2 (Gauche) index: " << i << ", Color: " << colors[i] << "\n";
        }
    }

    // Résultat final
    if (!collisionPointsOBB1.empty() || !collisionPointsOBB2.empty()) {
        //std::cout << "Total collision points OBB1: " << collisionPointsOBB1.size() << "\n";
        //std::cout << "Total collision points OBB2: " << collisionPointsOBB2.size() << "\n";

        //std::cout << "Searching implicated faces...\n";
        std::cout << "--------------------------------\n";

        if (!collisionPointsOBB2.empty()) {
            std::vector<std::string> implicatedFaces1;
            // obb1 is the receiver, collisionPointsOBB2 are the collision points of the penetrator
            SearchInplicatedFace(obb1, collisionPointsOBB2, implicatedFaces1);

            if (!implicatedFaces1.empty()) {
                std::cout << "Impacted faces OBB1 (right) (receiver): ";
                for (const auto& face : implicatedFaces1) {
                    auto it = faceColors.find(face);
                    if (it != faceColors.end()) {
                        std::cout << "Face: " << face << " - Color: " << it->second << "\n";
                    }
                }
                std::cout << "\n";
            }
            else {
                std::cout << "No implicated faces for OBB1 (right) (receiver).\n";
            }
        }

        if (!collisionPointsOBB1.empty()) {
            std::vector<std::string> implicatedFaces2;
            // obb2 is the receiver, collisionPointsOBB1 are the collision points of the penetrator
            SearchInplicatedFace(obb2, collisionPointsOBB1, implicatedFaces2);

            if (!implicatedFaces2.empty()) {
                std::cout << "Impacted faces OBB2 (left) (receiver): ";
                for (const auto& face : implicatedFaces2) {
                    auto it = faceColors.find(face);
                    if (it != faceColors.end()) {
                        std::cout << "Face: " << face << " - Color: " << it->second << "\n";
                    }
                }
                std::cout << "\n";
            }
            else {
                std::cout << "No implicated faces for OBB2 (left) (receiver).\n";
            }
        }
    }

    std::cout << "---------------CHANGING FRAME-----------------\n";

    return !collisionPointsOBB1.empty() || !collisionPointsOBB2.empty();
}

#include "pch.h"
#include "PhysicSystem.h"


#include "BoxCollider.h"

std::map<std::string, std::vector<int>> faces = {
    {"Front", {0, 1, 2, 3}},
    {"Back", {4, 5, 6, 7}},
    {"Left", {0, 3, 7, 4}},
    {"Right", {1, 2, 6, 5}},
    {"Top", {2, 3, 7, 6}},
    {"Bottom", {0, 1, 5, 4}}
};



//bool PhysicSystem::OBB_Collision(OBB & obb1, OBB & obb2) {
//    std::vector<Eigen::Vector3d> axes;
//    axes.push_back(obb1.rotation.col(0));
//    axes.push_back(obb1.rotation.col(1));
//    axes.push_back(obb1.rotation.col(2));
//    axes.push_back(obb2.rotation.col(0));
//    axes.push_back(obb2.rotation.col(1));
//    axes.push_back(obb2.rotation.col(2));
//
//    // Ajouter les axes croisés
//    for (int i = 0; i < 3; ++i) {
//        for (int j = 0; j < 3; ++j) {
//            Eigen::Vector3d crossAxis = obb1.rotation.col(i).cross(obb2.rotation.col(j));
//            if (crossAxis.norm() > 1e-6) {
//                Eigen::Vector3d normalizedAxis = crossAxis.normalized();
//                if (std::find(axes.begin(), axes.end(), normalizedAxis) == axes.end()) {
//                    axes.push_back(normalizedAxis);
//                }
//            }
//        }
//    }
//
//    std::vector<Eigen::Vector3d> collisionPoints;
//
//    // Tester les coins sur tous les axes
//    for (size_t i = 0; i < obb1.corners.size(); ++i) {
//        const auto& corner1 = obb1.corners[i];
//        bool collisionOnAllAxes = true;
//
//        for (const auto& axis : axes) {
//            double min2 = std::numeric_limits<double>::max(), max2 = -std::numeric_limits<double>::max();
//
//            // Projeter tous les coins de obb2 sur cet axe
//            for (const auto& corner2 : obb2.corners) {
//                double projection = axis.dot(corner2);
//                min2 = std::min(min2, projection);
//                max2 = std::max(max2, projection);
//            }
//
//            // Projeter le coin de obb1
//            double projection1 = axis.dot(corner1);
//            if (projection1 < min2 || projection1 > max2) {
//                collisionOnAllAxes = false;
//                break; // Pas de collision pour ce coin sur cet axe
//            }
//        }
//
//        if (collisionOnAllAxes) {
//            collisionPoints.push_back(corner1);
//            // Afficher l'index et la couleur du coin
//            std::cout << "Coin 1 index: " << i << ", Color: " << colors[i] << "\n";
//        }
//    }
//
//    // Tester les coins de OBB2 sur tous les axes (symétriquement)
//    for (size_t i = 0; i < obb2.corners.size(); ++i) {
//        const auto& corner2 = obb2.corners[i];
//        bool collisionOnAllAxes = true;
//
//        for (const auto& axis : axes) {
//            double min1 = std::numeric_limits<double>::max(), max1 = -std::numeric_limits<double>::max();
//
//            // Projeter tous les coins de obb1 sur cet axe
//            for (const auto& corner1 : obb1.corners) {
//                double projection = axis.dot(corner1);
//                min1 = std::min(min1, projection);
//                max1 = std::max(max1, projection);
//            }
//
//            // Projeter le coin de obb2
//            double projection2 = axis.dot(corner2);
//            if (projection2 < min1 || projection2 > max1) {
//                collisionOnAllAxes = false;
//                break; // Pas de collision pour ce coin sur cet axe
//            }
//        }
//
//        if (collisionOnAllAxes) {
//            collisionPoints.push_back(corner2);
//            // Afficher l'index et la couleur du coin
//            std::cout << "Coin 2 index: " << i << ", Color: " << colors[i] << "\n";
//        }
//    }
//
//    // Afficher les résultats de la collision
//    if (collisionPoints.size() > 0) {
//        std::cout << "Total collision points: " << collisionPoints.size() << "\n" << std::endl;
//    }
//
//    std::cout << "----------------" << collisionPoints.size() << "\n" << std::endl;
//
//    return !collisionPoints.empty();
//}
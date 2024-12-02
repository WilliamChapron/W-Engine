#include "pch.h"
#include "PhysicSystem.h"


#include "BoxCollider.h"


bool PhysicSystem::OBB_Collision(const OBB& obb1, const OBB& obb2) {
    // Axes à tester : les 3 axes locaux de chaque OBB + leurs produits vectoriels
    std::vector<Eigen::Vector3d> axes;
    axes.push_back(obb1.rotation.col(0));
    axes.push_back(obb1.rotation.col(1));
    axes.push_back(obb1.rotation.col(2));
    axes.push_back(obb2.rotation.col(0));
    axes.push_back(obb2.rotation.col(1));
    axes.push_back(obb2.rotation.col(2));

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            Eigen::Vector3d crossAxis = obb1.rotation.col(i).cross(obb2.rotation.col(j));
            if (crossAxis.norm() > 1e-6) {
                axes.push_back(crossAxis.normalized());
            }
        }
    }

    std::vector<Eigen::Vector3d> collisionPoints;

    for (const auto& axis : axes) {
        double min1 = std::numeric_limits<double>::max(), max1 = -std::numeric_limits<double>::max();
        for (const auto& corner : obb1.corners) {
            double projection = axis.dot(corner);
            min1 = std::min(min1, projection);
            max1 = std::max(max1, projection);
        }

        double min2 = std::numeric_limits<double>::max(), max2 = -std::numeric_limits<double>::max();
        for (const auto& corner : obb2.corners) {
            double projection = axis.dot(corner);
            min2 = std::min(min2, projection);
            max2 = std::max(max2, projection);
        }

        if (max1 < min2 || max2 < min1) {
            return false;
        }

        if (max1 >= min2 && max2 >= min1) {
            double overlap = std::min(max1 - min2, max2 - min1);
            Eigen::Vector3d direction = axis.normalized();

            // Boucle à travers les coins pour déterminer les véritables points de contact
            for (size_t i = 0; i < obb1.corners.size(); ++i) {
                const Eigen::Vector3d& corner1 = obb1.corners[i];
                Eigen::Vector3d point1 = corner1 - direction * overlap * 0.5;
                // Vérifier si ce point se trouve dans le volume d'OBB1
                if (obb1.isPointInsideOBB(point1, obb1)) {
                    collisionPoints.push_back(point1);
                    std::cout << "Collision with OBB1 at corner index " << i << ": " << corner1.transpose() << std::endl;
                }
            }

            for (size_t j = 0; j < obb2.corners.size(); ++j) {
                const Eigen::Vector3d& corner2 = obb2.corners[j];
                Eigen::Vector3d point2 = corner2 + direction * overlap * 0.5;
                // Vérifier si ce point se trouve dans le volume d'OBB2
                if (isPointInsideOBB(point2, obb2)) {
                    collisionPoints.push_back(point2);
                    std::cout << "Collision with OBB2 at corner index " << j << ": " << corner2.transpose() << std::endl;
                }
            }
        }
    }

    if (!collisionPoints.empty()) {
        for (const auto& point : collisionPoints) {
            std::cout << "Collision point: " << point.transpose() << std::endl;
        }
        return true;
    }

    return false;
}



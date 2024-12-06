#include "pch.h"
#include "PhysicSystem.h"


#include "BoxCollider.h"


bool PhysicSystem::OBB_Collision(OBB& obb1, OBB& obb2) {
    // Liste des coins de l'OBB1 et OBB2
    std::vector<Eigen::Vector3d> corners1 = obb1.corners; // Coins de l'OBB1
    std::vector<Eigen::Vector3d> corners2 = obb2.corners; // Coins de l'OBB2

    // Liste pour enregistrer les coins de l'OBB1 qui sont dans l'intervalle de l'OBB2
    std::vector<Eigen::Vector3d> collisionPoints;

    int cornerNbr = 0;
    for (const auto& corner1 : corners1) {
        bool collisionDetected = true;

        // Vérifier chaque axe (X, Y, Z)
        for (int i = 0; i < 3; ++i) {
            // Trouver les projections min et max pour l'OBB2 sur cet axe
            double min2 = std::numeric_limits<double>::max();
            double max2 = -std::numeric_limits<double>::max();

            for (const auto& corner2 : corners2) {
                double projection = corner2[i]; // Projection sur l'axe i (X, Y, Z)
                min2 = std::min(min2, projection);
                max2 = std::max(max2, projection);
            }

            // Vérifier si le coin1 est à l'intérieur de l'intervalle [min2, max2]
            double projection1 = corner1[i]; // Projection de corner1 sur l'axe i
            if (projection1 < min2 || projection1 > max2) {
                collisionDetected = false; // Pas de collision si le coin1 est en dehors de l'intervalle
                break;
            }
        }


        if (collisionDetected) {
            collisionPoints.push_back(corner1); 
            //std::cout << "Collision detected at corner : " << cornerNbr << " " << colors[cornerNbr] << std::endl;
            std::cout << "Collision detected at corner: " << corner1.transpose() << std::endl;
        }

        cornerNbr++;
    }
    return !collisionPoints.empty();
}
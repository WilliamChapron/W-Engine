#pragma once

#include "./RenderStructures.hpp"


struct Vertex;

struct OBB{
	Eigen::Vector3d center;  // Centre de l'OBB en Eigen
	Eigen::Vector3d size;    // Taille de l'OBB (dimensions) en Eigen
	Eigen::Matrix3d rotation; // Matrice de rotation des axes principaux (PCA)
	Eigen::Vector3d min, max; // Min et Max de l'OBB après rotation

	std::vector<Vertex> vertices; // Liste des vertices

	std::vector<Eigen::Vector3d> corners; // Liste des coins de l'OBB après transformation

	// Fonction pour mettre à jour les coins de l'OBB après rotation
	void UpdateCorners() {
		// Définir la taille en double
		Eigen::Vector3d halfSize = size.cast<double>() / 2.0;

		// Définir les coins locaux avec Eigen::Vector3d
		Eigen::Vector3d localCorners[8] = {
			Eigen::Vector3d(-halfSize.x(), -halfSize.y(), -halfSize.z()), // Coin 0
			Eigen::Vector3d(halfSize.x(), -halfSize.y(), -halfSize.z()),  // Coin 1
			Eigen::Vector3d(halfSize.x(), -halfSize.y(), halfSize.z()),   // Coin 2
			Eigen::Vector3d(-halfSize.x(), -halfSize.y(), halfSize.z()),  // Coin 3
			Eigen::Vector3d(-halfSize.x(), halfSize.y(), -halfSize.z()),  // Coin 4
			Eigen::Vector3d(halfSize.x(), halfSize.y(), -halfSize.z()),   // Coin 5
			Eigen::Vector3d(halfSize.x(), halfSize.y(), halfSize.z()),    // Coin 6
			Eigen::Vector3d(-halfSize.x(), halfSize.y(), halfSize.z())    // Coin 7
		};

		// Convertir la rotation en double
		Eigen::Matrix3d rotationD = rotation.cast<double>();

		// Convertir le centre en double
		Eigen::Vector3d centerD = center.cast<double>();

		// Effacer et préparer la liste des coins globaux
		corners.clear();
		corners.reserve(8); // Préallouer l'espace pour optimiser

		// Appliquer la rotation et ajouter les coins globaux
		for (int i = 0; i < 8; ++i) {
			Eigen::Vector3d rotatedCorner = rotationD * localCorners[i];
			Eigen::Vector3d globalCorner = centerD + rotatedCorner;
		}
	}


	// Méthode pour afficher les coins
	//void PrintCorners() {
	//	for (size_t i = 0; i < corners.size(); ++i) {
	//		std::cout << "Corner " << i << ": ("
	//			<< corners[i].x() << ", "
	//			<< corners[i].y() << ", "
	//			<< corners[i].z() << ")\n";
	//	}
	//}

	void ComputeMinMax() {
		min = Eigen::Vector3d(std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
		max = Eigen::Vector3d(-std::numeric_limits<double>::max(), -std::numeric_limits<double>::max(), -std::numeric_limits<double>::max());

		for (const auto& v : vertices) {
			Eigen::Vector3d point(v.position[0], v.position[1], v.position[2]);
			min = min.cwiseMin(point);
			max = max.cwiseMax(point);
		}
	}

	void ComputeCenter() {
		center = (min + max) / 2.0;
	}

	void ComputeSize() {
		size = max - min;
	}

	void ComputeRotationMatrix() {
		// Moyen
		Eigen::Vector3d mean(0, 0, 0);
		for (const auto& v : vertices) {
			mean += Eigen::Vector3d(v.position[0], v.position[1], v.position[2]);
		}
		mean /= vertices.size();

		// Centrer les points par rapport à la moyenne
		Eigen::MatrixXd centered(vertices.size(), 3);
		for (size_t i = 0; i < vertices.size(); ++i) {
			Eigen::Vector3d centeredPoint(vertices[i].position[0], vertices[i].position[1], vertices[i].position[2]);
			centeredPoint -= mean; // Centrer
			centered.row(i) = centeredPoint.transpose();
		}

		// Calculer la matrice de covariance
		Eigen::MatrixXd covariance = (centered.transpose() * centered) / double(vertices.size() - 1);

		// Calculer les vecteurs propres (axes principaux) et les valeurs propres
		Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver(covariance);
		Eigen::Matrix3d eigenVectors = solver.eigenvectors().real(); // Axes principaux

		// La matrice de rotation est la matrice des vecteurs propres
		rotation = eigenVectors;
	}

	// Fonction pour appliquer une transformation à l'OBB
	void ApplyTransformation(const glm::mat4& world) {
		// Appliquer la rotation et la mise à l'échelle à la matrice de rotation de l'OBB
		Eigen::Matrix3d scaleRotationMatrix;
		scaleRotationMatrix << world[0][0], world[0][1], world[0][2],
							  world[1][0], world[1][1], world[1][2],
							  world[2][0], world[2][1], world[2][2];

		// Mettre à jour la matrice de rotation avec la transformation
		rotation = scaleRotationMatrix * rotation;

		// Appliquer la translation au centre de l'OBB
		center.x() += world[3][0];
		center.y() += world[3][1];
		center.z() += world[3][2];

		// Mettre à jour les min et max de l'OBB après transformation
		ComputeMinMax();
		ComputeCenter();
		ComputeSize();
		Print();
	}

	void InitializeOBB(const std::vector<Vertex>& vertices) {
		this->vertices = vertices; // Assigner les vertices
		ComputeMinMax();
		ComputeCenter();
		ComputeSize();
		ComputeRotationMatrix();
		Print();
	}

	void Print() const {
		std::cout << "Center: (" << center.x() << ", " << center.y() << ", " << center.z() << ")\n";
		std::cout << "Size: (" << size.x() << ", " << size.y() << ", " << size.z() << ")\n";
		std::cout << "Rotation Matrix:\n";
		std::cout << rotation << "\n";
		std::cout << "Min: (" << min.x() << ", " << min.y() << ", " << min.z() << ")\n";
		std::cout << "Max: (" << max.x() << ", " << max.y() << ", " << max.z() << ")\n";
	}
};

struct AABB {
	// Local base position (without transformation)
	std::array<float, 3> bMin;
	std::array<float, 3> bMax;

	// Move position
	std::array<float, 3> min;
	std::array<float, 3> max;

	std::array<float, 3> size;

	std::array<float, 3> center;

	glm::vec3 bCorners[8];

	glm::vec3 transformedCorners[8];

	AABB() {
		min = { std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max() };
		max = { -std::numeric_limits<float>::max(), -std::numeric_limits<float>::max(), -std::numeric_limits<float>::max() };
	}

	// Update from vertex pack
	void FindMinMaxFromVerticesPack(std::vector<Vertex>& vertexPack) {
		for (const auto& vertex : vertexPack) {
			//Float3Display(vertex);
			min[0] = std::min(min[0], vertex.position[0]);
			min[1] = std::min(min[1], vertex.position[1]);
			min[2] = std::min(min[2], vertex.position[2]);

			max[0] = std::max(max[0], vertex.position[0]);
			max[1] = std::max(max[1], vertex.position[1]);
			max[2] = std::max(max[2], vertex.position[2]);
		}

		// Start pos
		bMin = min;
		bMax = max;

	}

	void SetMinMax(std::array<float, 3>& min3, std::array<float, 3>& max3) {
		min = min3;
		max = max3;
		bMin = min3;
		bMax = max3;

	}

	// request to have recorded min and max beforehand
	void CalculateData() {
		size[0] = abs(max[0] - min[0]);
		size[1] = abs(max[1] - min[1]);
		size[2] = abs(max[2] - min[2]);

		center[0] = (min[0] + max[0]) / 2.0f;
		center[1] = (min[1] + max[1]) / 2.0f;
		center[2] = (min[2] + max[2]) / 2.0f;


		bCorners[0] = glm::vec3(bMin[0], bMin[1], bMin[2]);
		bCorners[1] = glm::vec3(bMin[0], bMin[1], bMax[2]);
		bCorners[2] = glm::vec3(bMin[0], bMax[1], bMin[2]);
		bCorners[3] = glm::vec3(bMin[0], bMax[1], bMax[2]);
		bCorners[4] = glm::vec3(bMax[0], bMin[1], bMin[2]);
		bCorners[5] = glm::vec3(bMax[0], bMin[1], bMax[2]);
		bCorners[6] = glm::vec3(bMax[0], bMax[1], bMin[2]);
		bCorners[7] = glm::vec3(bMax[0], bMax[1], bMax[2]);
	}

	void UpdateAABBWithTransform(glm::mat4& world) {
		// Extraire la translation
		glm::vec3 translate = glm::vec3(world[3]);

		// Extraire l'échelle en calculant la norme des vecteurs des colonnes de la matrice (les facteurs d'échelle)
		glm::vec3 scale(
			glm::length(world[0]),  // Longueur de la colonne X (échelle en X)
			glm::length(world[1]),  // Longueur de la colonne Y (échelle en Y)
			glm::length(world[2])   // Longueur de la colonne Z (échelle en Z)
		);

		// Appliquer uniquement la translation et l'échelle (pas de rotation)
		for (int i = 0; i < 8; ++i) {
			// Appliquer l'échelle et la translation
			transformedCorners[i] = this->bCorners[i] * scale + translate;
		}

		// Réinitialiser min et max
		min[0] = transformedCorners[0].x;
		min[1] = transformedCorners[0].y;
		min[2] = transformedCorners[0].z;
		max[0] = transformedCorners[0].x;
		max[1] = transformedCorners[0].y;
		max[2] = transformedCorners[0].z;

		for (int i = 1; i < 8; ++i) {
			min[0] = std::min(min[0], transformedCorners[i].x);
			min[1] = std::min(min[1], transformedCorners[i].y);
			min[2] = std::min(min[2], transformedCorners[i].z);

			max[0] = std::max(max[0], transformedCorners[i].x);
			max[1] = std::max(max[1], transformedCorners[i].y);
			max[2] = std::max(max[2], transformedCorners[i].z);
		}
	}

};

class BoxCollider
{
public:
	AABB m_boundingVolume;

	BoxCollider();
	BoxCollider(std::vector<Vertex>& vertices);

	~BoxCollider() {};


};


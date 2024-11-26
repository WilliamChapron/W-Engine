#pragma once

#include "./RenderStructures.hpp"


struct Vertex;

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


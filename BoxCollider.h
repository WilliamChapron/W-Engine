#pragma once

#include "./RenderStructures.hpp"


struct Vertex;

struct OBB {
	// Local base position (without transformation)
	std::array<float, 3> bMin;
	std::array<float, 3> bMax;

	// Move position
	std::array<float, 3> min;
	std::array<float, 3> max;

	std::array<float, 3> size;

	std::array<float, 3> center;

	glm::vec3 corners[8];

	OBB() {
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


		corners[0] = glm::vec3(bMin[0], bMin[1], bMin[2]);
		corners[1] = glm::vec3(bMin[0], bMin[1], bMax[2]);
		corners[2] = glm::vec3(bMin[0], bMax[1], bMin[2]);
		corners[3] = glm::vec3(bMin[0], bMax[1], bMax[2]);
		corners[4] = glm::vec3(bMax[0], bMin[1], bMin[2]);
		corners[5] = glm::vec3(bMax[0], bMin[1], bMax[2]);
		corners[6] = glm::vec3(bMax[0], bMax[1], bMin[2]);
		corners[7] = glm::vec3(bMax[0], bMax[1], bMax[2]);

		//std::cout << "Size: (" << size[0] << ", " << size[1] << ", " << size[2] << ")\n";
		//std::cout << "Center: (" << center[0] << ", " << center[1] << ", " << center[2] << ")\n";
		//std::cout << "------------------------------------------\n";

		std::cout << "Min: (" << bMin[0] << ", " << bMin[1] << ", " << bMin[2] << ")\n";
		std::cout << "Max: (" << bMax[0] << ", " << bMax[1] << ", " << bMax[2] << ")\n";
	}

	void UpdateAABBWithTransform(glm::mat4& world) {
		glm::vec3 transformedCorners[8];

		for (int i = 0; i < 8; ++i) {
			transformedCorners[i] = glm::vec3(world * glm::vec4(this->corners[i], 1.0f));
		}

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

		//std::cout << "Min: (" << min[0] << ", " << min[1] << ", " << min[2] << ")\n";
		//std::cout << "Max: (" << max[0] << ", " << max[1] << ", " << max[2] << ")\n";
		//std::cout << "Size: (" << size[0] << ", " << size[1] << ", " << size[2] << ")\n";
		//std::cout << "Center: (" << center[0] << ", " << center[1] << ", " << center[2] << ")\n";
		std::cout << "------------------------------------------\n";

	}



};

class BoxCollider
{
public:
	OBB m_boundingVolume;

	BoxCollider();
	BoxCollider(std::vector<Vertex>& vertices);

	~BoxCollider() {};


};


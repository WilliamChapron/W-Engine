#pragma once


#include "./BoundingGeometry.h"
struct Vertex;

class OBB : public BoundingGeometry {
public:
    OBB();

    std::vector<Eigen::Vector3d>& GetCorners() override;
    void Init(const std::vector<Vertex>& vertices) override;
    void ComputeCenter() override;
    void ComputeSize() override;
    void ComputeMinMaxForAllVertices(const std::vector<Vertex>& vertices) override;
    void UpdateGlobalBounds(const glm::mat4& world) override;

private:
    Eigen::Vector3d min, max;
};




//struct OBB : public BoundingGeometry {
//
//	Eigen::Vector3d min, max;
//
//	OBB() {
//
//	}
//
//	std::vector<Eigen::Vector3d>& GetCorners() override
//	{
//		return m_corners;
//	};
//
//	// Initialize OBB
//	void Init(const std::vector<Vertex>& vertices) override {
//
//		ComputeMinMaxForAllVertices(vertices);
//		ComputeCenter();
//		ComputeSize();
//	}
//
//	void ComputeCenter() override { m_center = (min + max) / 2.0; }
//	void ComputeSize() override { m_size = max - min; }
//
//	void ComputeMinMaxForAllVertices(const std::vector<Vertex>& vertices) override {
//		min = Eigen::Vector3d(std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
//		max = Eigen::Vector3d(-std::numeric_limits<double>::max(), -std::numeric_limits<double>::max(), -std::numeric_limits<double>::max());
//
//		for (const auto& v : vertices) {
//			Eigen::Vector3d point(v.position[0], v.position[1], v.position[2]);
//			min = min.cwiseMin(point);
//			max = max.cwiseMax(point);
//		}
//	}
//
//	void UpdateGlobalBounds(const glm::mat4& world) override {
//
//		Eigen::Matrix3d rotationMatrix;
//
//		// Inverse z because of Eigen matrix standarts
//		rotationMatrix << world[0][0], world[1][0], -world[2][0],
//			world[0][1], world[1][1], -world[2][1],
//			world[0][2], world[1][2], -world[2][2];
//
//		m_rotation = rotationMatrix * Eigen::Matrix3d::Identity();
//
//		Eigen::Vector3d translation(world[3][0], world[3][1], world[3][2]);
//
//
//		// Is it useful to update that ? 
//		//ComputeMinMaxForAllVertices();
//		//ComputeCenter();
//		//ComputeSize();
//
//
//		Eigen::Vector3d halfSize = m_size.cast<double>() / 2.0;
//
//		// Local corners base (before rotate them)
//		Eigen::Vector3d localCorners[8] = {
//			Eigen::Vector3d(-halfSize.x(), -halfSize.y(), -halfSize.z()), // Coin 0
//			Eigen::Vector3d(halfSize.x(), -halfSize.y(), -halfSize.z()),  // Coin 1
//			Eigen::Vector3d(halfSize.x(), -halfSize.y(), halfSize.z()),   // Coin 2
//			Eigen::Vector3d(-halfSize.x(), -halfSize.y(), halfSize.z()),  // Coin 3
//			Eigen::Vector3d(-halfSize.x(), halfSize.y(), -halfSize.z()),  // Coin 4
//			Eigen::Vector3d(halfSize.x(), halfSize.y(), -halfSize.z()),   // Coin 5
//			Eigen::Vector3d(halfSize.x(), halfSize.y(), halfSize.z()),    // Coin 6
//			Eigen::Vector3d(-halfSize.x(), halfSize.y(), halfSize.z())    // Coin 7
//		};
//
//		m_corners.clear();
//		m_corners.reserve(8);
//
//		for (int i = 0; i < 8; ++i) {
//			Eigen::Vector3d rotatedCorner = m_rotation * localCorners[i];
//			Eigen::Vector3d globalCorner = m_center + rotatedCorner + translation;
//			m_corners.push_back(globalCorner);
//		}
//	}
//};

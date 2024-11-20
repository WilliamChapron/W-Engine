#pragma once

struct AABB {
	float min[3]; 
	float max[3]; 

	AABB() {
		min[0] = min[1] = min[2] = 0.0f;
		max[0] = max[1] = max[2] = 0.0f;
	}

	//AABB(float& Amin[3], float Amax[3]) {
	//	min = 
	//}
};

class BoxCollider
{
public:
	AABB m_boundingVolume;
};


#pragma once

#include <iostream>

#define PRINT(x) std::cout << x << std::endl;

#define Vector3Display(vec) \
    std::cout << "Vector3: (" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;

#define Float3Display(vec) \
    std::cout << "Vector3: (" << vec[0] << ", " << vec[1] << ", " << vec[2] << ")" << std::endl;
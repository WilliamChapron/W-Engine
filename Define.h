#pragma once

#include <iostream>

#define PRINT(x) std::cout << x << std::endl;

#define Vector3Display(vec) \
    std::cout << "Vector3: (" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
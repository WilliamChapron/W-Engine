#pragma once

struct Vertex {
    float position[3];
    float color[4];
    float normal[3];
    float texCoords[2];
};

//
//
//enum class Color {
//    RED,
//    GREEN,
//    BLUE,
//    YELLOW,
//    MAGENTA,
//    CYAN,
//    LIGHT_GRAY,
//    BLACK
//};
//
//
//float* getColor(Color color) {
//    static float colorMap[8][4] = {
//        {1.0f, 0.0f, 0.0f, 1.0f}, // RED
//        {0.0f, 1.0f, 0.0f, 1.0f}, // GREEN
//        {0.0f, 0.0f, 1.0f, 1.0f}, // BLUE
//        {1.0f, 1.0f, 0.0f, 1.0f}, // YELLOW
//        {1.0f, 0.0f, 1.0f, 1.0f}, // MAGENTA
//        {0.0f, 1.0f, 1.0f, 1.0f}, // CYAN
//        {0.8f, 0.8f, 0.8f, 1.0f}, // LIGHT_GRAY
//        {0.0f, 0.0f, 0.0f, 1.0f}  // BLACK
//    };
//
//
//    return colorMap[static_cast<int>(color)];
//}

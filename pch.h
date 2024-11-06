#pragma once

// Standard Libraries
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <cstdint>
#include <variant>
#include <chrono>
#include <memory>
#include <algorithm>

// Containers
#include <array>
#include <map>
#include <vector>
#include <unordered_map>

// System-Specific Headers
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// Filesystem
#include <filesystem>

// Encoding/Locale
#include <codecvt>
#include <locale>

// OpenGL and GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Math Library (GLM)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Linking External Libraries
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")




// Stb image (texture)
#include "extern/stb_image.h" // Inclure ici pour utiliser les fonctions de stb_image

// Assimp
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>  // Important pour les flags de post-traitement
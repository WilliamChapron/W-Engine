#include "pch.h"

//Core
#include "Window.h"

//Render
#include "Mesh.h" 
#include "SubMesh.h" 
#include "Shader.h" 

#include "OpenGL_Context.h"
#include "OpenGL_Renderer.h" 
#include "OpenGL_Shader.h" 
#include "OpenGL_Mesh.h" 
#include "OpenGL_SubMesh.h" 
#include "OpenGL_Texture.h" 
#include "OpenGL_Material.h" 

#include "OpenGL_RenderableEntity.h"
#include "RenderableEntity.h"

#include "GLFWLoader.h"

//Physic
#include "Camera.h" 
#include "Transform.h" 
#include "Body.h"
#include "BoxCollider.h"

#include "Primitive.h"


bool isPaused = false;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Debug console redirection
    FILE* fDummy;
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);

    //Primitive* cubeGeometry = new PrimitiveRectangle(2.2, 2);
    Primitive* cubeGeometry = new Cube();
    cubeGeometry->Init();

    OBB obb;
    obb.InitializeOBB(cubeGeometry->vertices);


    glm::mat4 world = glm::mat4(1.0f); 
    world = glm::rotate(world, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotation autour de Y
    //world = glm::scale(world, glm::vec3(1.5f, 1.5f, 1.5f)); // Échelle

    // Appliquer la transformation
    obb.ApplyTransformation(world);


    while (true) {

    }

    // Cleanup
    //context->Terminate();
    return 0;
}


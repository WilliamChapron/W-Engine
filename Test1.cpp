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

    std::cout << "Bienvenue dans le programme!\n";

    // Create window and initialize context
    OpenGL_Context* context = new OpenGL_Context();
    context->Initialize(SCR_WIDTH, SCR_HEIGHT, "OpenGL WINDOW");
    GLFWwindow* window = context->getWindow();

    // Renderer initialization
    OpenGL_Renderer renderer;
    renderer.Initialize(context);

    // Camera setup
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    // Shaders for pyramid and cube
    Shader* pshader = new OpenGL_Shader();
    if (!pshader->Compile("res\\shaders\\colorV.glsl", "res\\shaders\\colorF.glsl")) {
        std::cerr << "Shader compilation failed!" << std::endl;
    }

    Shader* wireframeShader = new OpenGL_Shader();
    if (!wireframeShader->Compile("res\\shaders\\wireframeV.glsl", "res\\shaders\\wireframeF.glsl")) {
        std::cerr << "Shader compilation failed!" << std::endl;
    }

    // Cube setup
    RenderableEntity* cube = new OpenGL_RenderableEntity();
    Primitive* cubeGeometry = new Cube();
    cubeGeometry->Init();
    OpenGL_SubMesh* cubeSubmesh = new OpenGL_SubMesh();
    cubeSubmesh->Setup(cubeGeometry->vertices, cubeGeometry->indices, 0);

    Material* cubeMaterial = new OpenGL_Material();
    cubeMaterial->SetShader(pshader); // Using same shader as pyramid
    cube->AddMaterial(cubeMaterial);
    cube->AddSubMesh(cubeSubmesh);

    // Transforms and colliders
    Transform* cubeTransform = new Transform();

    BoxCollider* cubeCollider = new BoxCollider(cubeGeometry->vertices);

    //cubeTransform->SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));
    cubeCollider->m_orientedBoundingBox.InitializeOBB(cubeGeometry->vertices);


    float rotate = 0.0f;
    float rotationSpeed = 0.04f; // Angle de rotation par seconde
    // Main loop 
    while (!glfwWindowShouldClose(window))
    {
        rotate += rotationSpeed;
        // Timing
        static float lastFrameTime = 0.0f;
        float currentFrameTime = glfwGetTime();
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        // Matrices for rendering
        glm::mat4 projection = camera.GetProjectionMatrix(90.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        cubeTransform->SetRotation(glm::vec3(rotate, 0.0f, 0.0f));
        //PRINT(cubeTransform->GetRotation().y);
        //cubeTransform->SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));




        // World transforms
        glm::mat4 cubeWorld = cubeTransform->GetTransformMatrix();

        // Update obb
        cubeCollider->m_orientedBoundingBox.UpdateOBBGlobalBounds(cubeWorld);


        // Shader update and rendering
        OpenGL_Shader* shPrimitive = static_cast<OpenGL_Shader*>(pshader);
        OpenGL_Shader* wfsh = static_cast<OpenGL_Shader*>(wireframeShader);

        renderer.Clear();

        // Draw cube
        shPrimitive->UpdateMatrices(cubeWorld, view, projection);
        renderer.Draw(cube);

        // Debug draw for collider
        std::vector<Eigen::Vector3d> corners = cubeCollider->m_orientedBoundingBox.corners;
        std::vector<float> lineVertices;
        for (int i = 0; i < 8; ++i) {
            lineVertices.push_back(corners[i].coeff(0)); // x
            lineVertices.push_back(corners[i].coeff(1)); // y
            lineVertices.push_back(corners[i].coeff(2)); // z
        }

        std::vector<unsigned int> indices = {
            0, 1,  // Arête entre Coin 0 et Coin 1
            1, 2,  // Arête entre Coin 1 et Coin 2
            2, 3,  // Arête entre Coin 2 et Coin 3
            3, 0,  // Arête entre Coin 3 et Coin 0
            4, 5,  // Arête entre Coin 4 et Coin 5
            5, 6,  // Arête entre Coin 5 et Coin 6
            6, 7,  // Arête entre Coin 6 et Coin 7
            7, 4,  // Arête entre Coin 7 et Coin 4
            0, 4,  // Arête entre Coin 0 et Coin 4
            1, 5,  // Arête entre Coin 1 et Coin 5
            2, 6,  // Arête entre Coin 2 et Coin 6
            3, 7   // Arête entre Coin 3 et Coin 7
        };
        glm::mat4 identityMatrix = glm::mat4(1.0f);
        wfsh->UpdateMatrices(identityMatrix, view, projection);
        renderer.DebugColliderDraw(lineVertices, indices, wfsh);

        renderer.Present();

        // Input handling for pause
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            isPaused = !isPaused;  // Toggle pause state
            while (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
                glfwPollEvents();
            }
        }
    }

    // Cleanup
    context->Terminate();
    return 0;
}
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

#include "PhysicSystem.h"
#include "RigidBody.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#include <chrono>
#include <thread>


int it = 0;
// Pause handling
bool isPaused = false;
bool wasSpacePressed = false;
std::chrono::steady_clock::time_point lastToggleTime = std::chrono::steady_clock::now();

void ProcessInput(GLFWwindow* window) {
    bool isSpacePressedNow = (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);
    if (isSpacePressedNow && !wasSpacePressed) {
        isPaused = !isPaused; 
        //std::cout << (isPaused ? "Game Paused" : "Game Resumed") << std::endl;
    }
    wasSpacePressed = isSpacePressedNow;
}


float speed = 1.f;
float lastX = 400.0f;  // Position X initiale de la souris
float lastY = 300.0f;  // Position Y initiale de la souris
bool firstMouse = true; // Flag pour la première capture de la souris
float sensitivity = 0.1f; // Sensibilité de la souris


void ProcessMouseMovement(GLFWwindow* window, Camera& camera) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos); // Récupérer la position actuelle de la souris

    if (firstMouse) { // Si c'est le premier mouvement de souris, on initialise lastX et lastY
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    // Calculer le décalage de la souris (offset) par rapport à la position précédente
    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos; // Inverser yOffset pour un mouvement de souris naturel (haut/bas)
    lastX = xpos;
    lastY = ypos;

    xOffset *= sensitivity;
    yOffset *= sensitivity;

    //PRINT(xOffset, yOffset);

    camera.Rotate(xOffset, yOffset); 
}


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    FILE* fDummy;
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    OpenGL_Context* context = new OpenGL_Context();
    context->Initialize(SCR_WIDTH, SCR_HEIGHT, "OpenGL WINDOW");
    GLFWwindow* window = context->getWindow();
    OpenGL_Renderer renderer;
    renderer.Initialize(context);
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    // Init shader
    Shader* pshader = new OpenGL_Shader();
    if (!pshader->Compile("res\\shaders\\colorV.glsl", "res\\shaders\\colorF.glsl")) {
        std::cerr << "Shader compilation failed!" << std::endl;
    }
    Shader* wireframeShader = new OpenGL_Shader();
    if (!wireframeShader->Compile("res\\shaders\\wireframeV.glsl", "res\\shaders\\wireframeF.glsl")) {
        std::cerr << "Shader compilation failed!" << std::endl;
    }

    PhysicSystem* physicSystem = new PhysicSystem();

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

    // Second cube setup
    RenderableEntity* cube2 = new OpenGL_RenderableEntity();
    Primitive* cube2Geometry = new Cube(); 
    cube2Geometry->Init();
    OpenGL_SubMesh* cube2Submesh = new OpenGL_SubMesh();
    cube2Submesh->Setup(cube2Geometry->vertices, cube2Geometry->indices, 0);

    Material* cube2Material = new OpenGL_Material();
    cube2Material->SetShader(pshader); // Using same shader as pyramid
    cube2->AddMaterial(cube2Material);
    cube2->AddSubMesh(cube2Submesh);

    Transform* cube2Transform = new Transform();
    BoxCollider* cube2Collider = new BoxCollider(cube2Geometry->vertices);
    cube2Collider->m_orientedBoundingBox.InitializeOBB(cube2Geometry->vertices);

    cube2Transform->SetPosition(glm::vec3(2.5f, 0.0f, 0.0f));
    cube2Transform->SetScale(glm::vec3(4.0f, 1.0f, 1.0f));


    // Transforms and colliders
    Transform* cubeTransform = new Transform();
    BoxCollider* cubeCollider = new BoxCollider(cubeGeometry->vertices);


    cubeCollider->m_orientedBoundingBox.InitializeOBB(cubeGeometry->vertices);

    //Camera
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  // Cacher le curseur
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //

    float rotate = 0.0f;
    float rotationSpeed = 0.04f; 
    // Main loop 
    while (!glfwWindowShouldClose(window))
    {
        it++;
        //PRINT(it);

        glfwPollEvents();
        ProcessInput(window);
        if (isPaused) {
            continue;
        }


        rotate += rotationSpeed;
        // Timing
        static float lastFrameTime = 0.0f;
        float currentFrameTime = glfwGetTime();
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;


        // CAMERA HANDLING

        // Entrées utilisateur
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            camera.MoveForward(deltaTime * speed);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            camera.MoveForward(-deltaTime * speed);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            camera.Strafe(-deltaTime * speed);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            camera.Strafe(deltaTime * speed);
        }
        // CAMERA
        ProcessMouseMovement(window, camera);

        // Matrices for rendering
        glm::mat4 projection = camera.GetProjectionMatrix(90.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();



        // Update first cube
        cubeTransform->SetRotation(glm::vec3(rotate, 0.0f, 0.0f));
        glm::mat4 cubeWorld = cubeTransform->GetTransformMatrix();
        cubeCollider->m_orientedBoundingBox.UpdateOBBGlobalBounds(cubeWorld);

        // Update second cube
        cube2Transform->SetRotation(glm::vec3(0.0f, -(rotate*10), 0.0f));
        glm::mat4 cube2World = cube2Transform->GetTransformMatrix();
        cube2Collider->m_orientedBoundingBox.UpdateOBBGlobalBounds(cube2World);


        // Shader update and rendering
        OpenGL_Shader* shPrimitive = static_cast<OpenGL_Shader*>(pshader);
        OpenGL_Shader* wfsh = static_cast<OpenGL_Shader*>(wireframeShader);

        renderer.Clear();

        // SIMPLE RENDER
        shPrimitive->UpdateMatrices(cubeWorld, view, projection);
        renderer.Draw(cube);

        shPrimitive->UpdateMatrices(cube2World, view, projection);
        renderer.Draw(cube2);



        //PRINT(physicSystem->OBB_Collision(cubeCollider->m_orientedBoundingBox, cube2Collider->m_orientedBoundingBox));
        physicSystem->OBB_Collision(cubeCollider->m_orientedBoundingBox, cube2Collider->m_orientedBoundingBox);



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

        // Debug draw for rectangle collider
        std::vector<Eigen::Vector3d> cube2Corners = cube2Collider->m_orientedBoundingBox.corners;
        std::vector<float> rectangleVertices;

        for (int i = 0; i < 8; ++i) {
            rectangleVertices.push_back(cube2Corners[i].coeff(0)); // x
            rectangleVertices.push_back(cube2Corners[i].coeff(1)); // y
            rectangleVertices.push_back(cube2Corners[i].coeff(2)); // z
        }

        // Indices for rectangle edges
        std::vector<unsigned int> rectangleIndices = {
            0, 1,  // Edge 0->1
            1, 2,  // Edge 1->2
            2, 3,  // Edge 2->3
            3, 0,  // Edge 3->0
            4, 5,  // Edge 4->5
            5, 6,  // Edge 5->6
            6, 7,  // Edge 6->7
            7, 4,  // Edge 7->4
            0, 4,  // Edge 0->4
            1, 5,  // Edge 1->5
            2, 6,  // Edge 2->6
            3, 7   // Edge 3->7
        };

        // Draw rectangle collider
        wfsh->UpdateMatrices(identityMatrix, view, projection);
        renderer.DebugColliderDraw(rectangleVertices, rectangleIndices, wfsh);

        renderer.Present();


    }

    // Cleanup
    context->Terminate();
    return 0;
}

// Camera
// Debugger pour connaitre temps d'execution d'une fonction 
// Obb collision


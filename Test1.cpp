#include "pch.h"
//
////Core
//#include "Window.h"
//
////Render
//#include "Mesh.h" 
//#include "SubMesh.h" 
//#include "Shader.h" 
//
//#include "OpenGL_Context.h"
//#include "OpenGL_Renderer.h" 
//#include "OpenGL_Shader.h" 
//#include "OpenGL_Mesh.h" 
//#include "OpenGL_SubMesh.h" 
//#include "OpenGL_Texture.h" 
//#include "OpenGL_Material.h" 
//
//#include "OpenGL_RenderableEntity.h"
//#include "RenderableEntity.h"
//
//#include "GLFWLoader.h"
//
////Physic
//#include "Camera.h" 
//#include "Transform.h" 
//#include "Body.h"
//#include "BoxCollider.h"
//
//#include "Primitive.h"
//
//#include "PhysicSystem.h"
//#include "RigidBody.h"
//
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//
//#include <chrono>
//#include <thread>
//
//
//int it = 0;
//// Pause handling
//bool isPaused = false;
//bool wasSpacePressed = false;
//std::chrono::steady_clock::time_point lastToggleTime = std::chrono::steady_clock::now();
//
//void ProcessInput(GLFWwindow* window) {
//    bool isSpacePressedNow = (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);
//    if (isSpacePressedNow && !wasSpacePressed) {
//        isPaused = !isPaused; 
//        //std::cout << (isPaused ? "Game Paused" : "Game Resumed") << std::endl;
//    }
//    wasSpacePressed = isSpacePressedNow;
//}
//
//
//float speed = 1.f;
//float lastX = 400.0f;  // Position X initiale de la souris
//float lastY = 300.0f;  // Position Y initiale de la souris
//bool firstMouse = true; // Flag pour la première capture de la souris
//float sensitivity = 0.1f; // Sensibilité de la souris
//
//
//void ProcessMouseMovement(GLFWwindow* window, Camera& camera) {
//    double xpos, ypos;
//    glfwGetCursorPos(window, &xpos, &ypos); // Récupérer la position actuelle de la souris
//
//    if (firstMouse) { // Si c'est le premier mouvement de souris, on initialise lastX et lastY
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    // Calculer le décalage de la souris (offset) par rapport à la position précédente
//    float xOffset = xpos - lastX;
//    float yOffset = lastY - ypos; // Inverser yOffset pour un mouvement de souris naturel (haut/bas)
//    lastX = xpos;
//    lastY = ypos;
//
//    xOffset *= sensitivity;
//    yOffset *= sensitivity;
//
//    //PRINT(xOffset, yOffset);
//
//    camera.Rotate(xOffset, yOffset); 
//}
//
//
//int main()
//{
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
//    #ifdef __APPLE__
//        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    #endif
//
//    FILE* fDummy;
//    freopen_s(&fDummy, "CONIN$", "r", stdin);
//    freopen_s(&fDummy, "CONOUT$", "w", stderr);
//    freopen_s(&fDummy, "CONOUT$", "w", stdout);
//    OpenGL_Context* context = new OpenGL_Context();
//    context->Initialize(SCR_WIDTH, SCR_HEIGHT, "OpenGL WINDOW");
//    GLFWwindow* window = context->getWindow();
//    OpenGL_Renderer renderer;
//    renderer.Initialize(context);
//    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//
//    // Init shader
//    Shader* pshader = new OpenGL_Shader();
//    if (!pshader->Compile("res\\shaders\\colorV.glsl", "res\\shaders\\colorF.glsl")) {
//        std::cerr << "Shader compilation failed!" << std::endl;
//    }
//
//    PhysicSystem* physicSystem = new PhysicSystem();
//
//    // Base rocket setup
//    RenderableEntity* cube = new OpenGL_RenderableEntity();
//    Primitive* cubeGeometry = new Cylinder(1,1);
//    cubeGeometry->Init();
//    OpenGL_SubMesh* cubeSubmesh = new OpenGL_SubMesh();
//    cubeSubmesh->Setup(cubeGeometry->vertices, cubeGeometry->indices, 0);
//
//    Material* cubeMaterial = new OpenGL_Material();
//    cubeMaterial->SetShader(pshader); 
//    cube->AddMaterial(cubeMaterial);
//    cube->AddSubMesh(cubeSubmesh);
//
//    // Top setup
//    RenderableEntity* coneRocket = new OpenGL_RenderableEntity();
//    Primitive* coneRocketGeometry = new Cone(1, 2);
//    coneRocketGeometry->Init();
//    OpenGL_SubMesh* coneRocketSubmesh = new OpenGL_SubMesh();
//    coneRocketSubmesh->Setup(coneRocketGeometry->vertices, coneRocketGeometry->indices, 0);
//
//
//    coneRocket->AddMaterial(cubeMaterial);
//    coneRocket->AddSubMesh(coneRocketSubmesh);
//
//
//    // Sub engines
//    RenderableEntity* engines[4];
//    Transform* engineTransforms[4];
//    RigidBody* engineRigidBodies[4];
//
//    float offset = 0.92f; 
//
//    glm::vec3 enginePositions[4] = {
//        glm::vec3(offset, -2.5f,  offset),
//        glm::vec3(-offset, -2.5f,  offset),
//        glm::vec3(offset, -2.5f, -offset),
//        glm::vec3(-offset, -2.5f, -offset)
//    };
//
//    for (int i = 0; i < 4; i++) {
//        engines[i] = new OpenGL_RenderableEntity();
//
//        engines[i]->AddMaterial(cubeMaterial);
//        engines[i]->AddSubMesh(cubeSubmesh);
//
//        engineTransforms[i] = new Transform();
//        engineTransforms[i]->SetPosition(enginePositions[i]);
//        engineTransforms[i]->SetScale(glm::vec3(0.3f, 1.0f, 0.3f)); 
//
//        engineRigidBodies[i] = new RigidBody(engineTransforms[i], 50.0f);
//    }
//
//    //*
//    
//
//
//
//
//
//    //// Transforms and colliders
//    Transform* cubeTransform = new Transform();
//    cubeTransform->SetScale(glm::vec3(1.0f, 5.0f, 1.0f));
//
//    Transform* coneRocketTransform = new Transform();
//    coneRocketTransform->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));
//
//    //Camera
//    glfwMakeContextCurrent(window);
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  // Cacher le curseur
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    //
//
//
//    // Rigid body and rocket physic
//    RigidBody* cubeRigidBody = new RigidBody(cubeTransform, 50.0f);
//    RigidBody* coneRocketRigidBody = new RigidBody(coneRocketTransform, 50.0f);
//
//    float launchTime = 0.1f;
//    bool hasLaunched = false;
//
//    // 
//
//    // Main loop 
//    while (!glfwWindowShouldClose(window))
//    {
//        // Timing
//        static float lastFrameTime = 0.0f;
//        float currentFrameTime = glfwGetTime();
//        float deltaTime = currentFrameTime - lastFrameTime;
//        lastFrameTime = currentFrameTime;
//        it++;
//
//        glfwPollEvents();
//        ProcessInput(window);
//        if (isPaused) {
//            continue;
//        }
//
//        // Update moving logic
//        if (!hasLaunched && currentFrameTime >= launchTime) {
//            glm::vec3 launchForce(0.0f, 50.0f, 0.0f); // Force vers le haut
//            cubeRigidBody->ApplyForce(launchForce);
//            coneRocketRigidBody->ApplyForce(launchForce);
//            for (int i = 0; i < 4; i++) {
//                engineRigidBodies[i]->ApplyForce(launchForce);
//            }
//            hasLaunched = true;
//        }
//        cubeRigidBody->Update(deltaTime);
//        coneRocketRigidBody->Update(deltaTime);
//        for (int i = 0; i < 4; i++) {
//            engineRigidBodies[i]->Update(deltaTime);
//        }
//
//
//
//
//
//
//        // CAMERA HANDLING
//
//        // Entrées utilisateur
//        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
//            camera.MoveForward(deltaTime * speed);
//        }
//        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
//            camera.MoveForward(-deltaTime * speed);
//        }
//        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//            camera.Strafe(-deltaTime * speed);
//        }
//        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//            camera.Strafe(deltaTime * speed);
//        }
//        ProcessMouseMovement(window, camera);
//
//        glm::mat4 projection = camera.GetProjectionMatrix(90.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//
//
//
//
//        glm::mat4 cubeWorld = cubeTransform->GetTransformMatrix();
//        glm::mat4 coneRocketWorld = coneRocketTransform->GetTransformMatrix();
//
//
//
//        OpenGL_Shader* shPrimitive = static_cast<OpenGL_Shader*>(pshader);
//
//        renderer.Clear();
//
//        shPrimitive->UpdateMatrices(cubeWorld, view, projection);
//        renderer.Draw(cube);
//        shPrimitive->UpdateMatrices(coneRocketWorld, view, projection);
//        renderer.Draw(coneRocket);
//
//        for (int i = 0; i < 4; i++) {
//            glm::mat4 engineWorld = engineTransforms[i]->GetTransformMatrix();
//            shPrimitive->UpdateMatrices(engineWorld, view, projection);
//            renderer.Draw(engines[i]);
//        }
//
//        renderer.Present();
//
//
//    }
//
//    context->Terminate();
//    return 0;
//}

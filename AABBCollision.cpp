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
//#include "GLTFLoader.h"
//
////Physic
//#include "Camera.h" 
//#include "Transform.h" 
//#include "BoxCollider.h"
//
//#include "Primitive.h"
//
//#include "PhysicSystem.h"
//
//
//bool isPaused = false;
//
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//int main()
//{
//    // glfw: initialize and configure
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    // Debug console redirection
//    FILE* fDummy;
//    freopen_s(&fDummy, "CONIN$", "r", stdin);
//    freopen_s(&fDummy, "CONOUT$", "w", stderr);
//    freopen_s(&fDummy, "CONOUT$", "w", stdout);
//
//    std::cout << "Bienvenue dans le programme!\n";
//
//    // Create window
//    OpenGL_Context* context = new OpenGL_Context();
//    context->Initialize(SCR_WIDTH, SCR_HEIGHT, "OpenGL WINDOW");
//    GLFWwindow* window = context->getWindow();
//
//    // Renderer initialization
//    OpenGL_Renderer renderer;
//    renderer.Initialize(context);
//
//    // Camera setup
//    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//
//    // Shader for pyramid and cube
//    Shader* pshader = new OpenGL_Shader();
//    if (!pshader->Compile("res\\shaders\\colorV.glsl", "res\\shaders\\colorF.glsl")) {
//        std::cerr << "Shader compilation failed!" << std::endl;
//    }
//
//    // Wireframe
//    Shader* wireframeShader = new OpenGL_Shader();
//    if (!wireframeShader->Compile("res\\shaders\\wireframeV.glsl", "res\\shaders\\wireframeF.glsl")) {
//        std::cerr << "Shader compilation failed!" << std::endl;
//    }
//
//    // Pyramid setup
//    RenderableEntity* pyramid = new OpenGL_RenderableEntity();
//    Primitive* pyramidGeometry = new Cube;
//    pyramidGeometry->Init();
//    OpenGL_SubMesh* pyramidSubmesh = new OpenGL_SubMesh();
//    pyramidSubmesh->Setup(pyramidGeometry->vertices, pyramidGeometry->indices, 0);
//
//    Material* pyramidMaterial = new OpenGL_Material();
//    pyramidMaterial->SetShader(pshader);
//    pyramid->AddMaterial(pyramidMaterial);
//    pyramid->AddSubMesh(pyramidSubmesh);
//
//
//
//    // Cube setup
//    RenderableEntity* cube = new OpenGL_RenderableEntity();
//    Primitive* cubeGeometry = new PrimitiveRectangle(2.2, 2);
//    cubeGeometry->Init();
//    OpenGL_SubMesh* cubeSubmesh = new OpenGL_SubMesh();
//    cubeSubmesh->Setup(cubeGeometry->vertices, cubeGeometry->indices, 0);
//
//    Material* cubeMaterial = new OpenGL_Material();
//    cubeMaterial->SetShader(pshader); 
//    cube->AddMaterial(cubeMaterial);
//    cube->AddSubMesh(cubeSubmesh);
//
//
//    // Transform & Collider
//    Transform* cubeTransform = new Transform();
//    cubeTransform->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f)); 
//    Transform* debugTransform = new Transform();
//    debugTransform->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f)); 
//    BoxCollider* cubeCollider = new BoxCollider(cubeGeometry->vertices); 
//    Transform* pyramidTransform = new Transform();
//    pyramidTransform->SetPosition(glm::vec3(-1.3f, 0.0f, 0.0f)); 
//    BoxCollider* pyramidCollider = new BoxCollider(pyramidGeometry->vertices); 
//
//
//
//
//    // Main loop 
//    float pyramidSpeed = 0.5f; 
//    float cubeRotationSpeed = 45.0f; 
//
//    float dx = 0.0f;
//    float dy = 0.0f;
//
//    PhysicSystem* physicSystem = new PhysicSystem();
//
//    // Main loop
//    while (!glfwWindowShouldClose(window))
//    {
//        cubeTransform->SetRotation(glm::vec3(dx, 0.0f, 90.0f)); 
//        cubeTransform->SetPosition(glm::vec3(dy, 0.0f, 0.0f));
//        cubeTransform->SetScale(glm::vec3(dy, dy, dy)); 
//
//        pyramidTransform->SetPosition(glm::vec3(dy*4, 0.0f, 0.0f)); 
//
//        // Timing
//        static float lastFrameTime = 0.0f;
//        float currentFrameTime = glfwGetTime();
//        float deltaTime = currentFrameTime - lastFrameTime;
//        lastFrameTime = currentFrameTime;
//
//        // Matrices
//        glm::mat4 projection = camera.GetProjectionMatrix(90.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//
//        // World transforms
//        glm::mat4 pyramidWorld = pyramidTransform->GetWorldMatrix();
//        glm::mat4 cubeWorld = cubeTransform->GetWorldMatrix();
//
//        dx += 0.1f;
//        dy += 0.001f;
//
//        pyramidCollider->m_aabb.UpdateAABBWithTransform(pyramidWorld);
//        cubeCollider->m_aabb.UpdateAABBWithTransform(cubeWorld);
//
//
//        if (physicSystem->TestAABBvsAABB_CollisionOnly(pyramidCollider->m_aabb, cubeCollider->m_aabb)) {
//            PRINT("O");
//        }
//        else {
//            PRINT("X");
//        }
//
//        OpenGL_Shader* shPrimitive = static_cast<OpenGL_Shader*>(pshader);
//        OpenGL_Shader* wfsh = static_cast<OpenGL_Shader*>(wireframeShader);
//
//
//        // Render
//        renderer.Clear();
//
//        // Draw pyramid
//        shPrimitive->UpdateMatrices(pyramidWorld, view, projection);
//        renderer.Draw(pyramid);
//        ////pyramidCollider->m_boundingVolume.render();
//        ////renderer.DebugDraw(debugCube1);
//
//        //// Draw cube
//        shPrimitive->UpdateMatrices(cubeWorld, view, projection);
//        renderer.Draw(cube);
//
//
//
//
//        // 
//        glm::vec3* corners = cubeCollider->m_aabb.transformedCorners;
//        std::vector<float> lineVertices;
//        for (int i = 0; i < 8; ++i) {
//            lineVertices.push_back(corners[i].x);
//            lineVertices.push_back(corners[i].y);
//            lineVertices.push_back(corners[i].z);
//        }
//        std::vector<unsigned int> indices = {
//            0, 1, 1, 3, 3, 2, 2, 0, 4, 5, 5, 7, 7, 6, 6, 4,
//            0, 4, 1, 5, 2, 6, 3, 7
//        };
//
//        glm::mat4 identityMatrix = glm::mat4(1.0f);
//
//
//        wfsh->UpdateMatrices(identityMatrix, view, projection);
//
//        // Draw
//        renderer.DrawBoundingBoxCorners(lineVertices, indices, wfsh);
//        renderer.Present();
//
//
//
//        // Input
//        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
//            isPaused = !isPaused; 
//            while (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
//                glfwPollEvents();
//            }
//        }
//    }
//
//    // Cleanup
//    context->Terminate();
//    return 0;
//}

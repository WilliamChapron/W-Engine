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

#include "Primitive.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // debug
    // ------------------------------
    FILE* fDummy;
    freopen_s(&fDummy, "CONIN$", "r", stdin);   
    freopen_s(&fDummy, "CONOUT$", "w", stderr);  
    freopen_s(&fDummy, "CONOUT$", "w", stdout);  


    std::cout << "Bienvenue dans le programme!\n";

    // glfw window creation
    // --------------------
    OpenGL_Context* context = new OpenGL_Context();
    context->Initialize(SCR_WIDTH, SCR_HEIGHT, "OpenGL WINDOW");

    GLFWwindow* window = context->getWindow();

    // renderer
    // --------------------
    OpenGL_Renderer renderer;
    renderer.Initialize(context);

    // camera
    // --------------------
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //

    GLFWLoader loader;
    loader.LoadFile("res/models/dodge/scene.gltf");

    RenderableEntity* renderableEntity = new OpenGL_RenderableEntity();

    Mesh* mesh = new Mesh();
    mesh->SetMaterials(loader.m_materials);
    mesh->SetSubMesh(loader.m_subMeshes);
    renderableEntity->SetMesh(mesh);

    Shader* shader = new OpenGL_Shader();
    if (!shader->Compile("res\\shaders\\vertex.glsl", "res\\shaders\\fragment.glsl")) {
        std::cerr << "Shader compilation failed!" << std::endl;
    }
    renderableEntity->SetShader(shader);
    renderableEntity->SetMesh(mesh);
    

    /*RenderableEntity* pyramid = new OpenGL_RenderableEntity();

    Shader* pshader = new OpenGL_Shader();
    if (!pshader->Compile("res\\shaders\\colorV.glsl", "res\\shaders\\colorF.glsl")) {
        std::cerr << "Shader compilation failed!" << std::endl;
    }

    Primitive* pyramidGeometry = new Pyramid();
    pyramidGeometry->Init();

    Mesh* pyramidmesh = new Mesh();
    OpenGL_SubMesh* submesh = new OpenGL_SubMesh();
    submesh->Setup(pyramidGeometry->vertices, pyramidGeometry->indices, 0);
    Material* material = new OpenGL_Material();
    pyramidmesh->AddSubMesh(submesh);
    pyramidmesh->AddMaterial(material);

    pyramid->SetShader(pshader);
    pyramid->SetMesh(pyramidmesh);*/


    

    float rotationSpeed = 0.0f; 
    float x = 0.0f;
    float scale = 0.0f; 
    float velocity[3] = { 0.0f, 0.0f, 0.0f }; 
    float mass = 0.001f; 
    Body body(velocity, mass);
    const float GRAVITY = -9.81f; 
    float lastFrameTime = glfwGetTime(); 
    Transform* bodyT = body.GetTransform();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // Engine
        // ------
        float currentFrameTime = glfwGetTime(); // Temps actuel
        float deltaTime = currentFrameTime - lastFrameTime; // Delta time
        lastFrameTime = currentFrameTime; // Mettre à jour le temps de la dernière frame
        //body.Update(deltaTime);;
        glm::mat4 projection = camera.GetProjectionMatrix(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        bodyT->SetPosition(glm::vec3(0.f, -0.7f, 0.f));
        bodyT->SetScale(glm::vec3(scale, scale, scale));
        bodyT->SetRotation(glm::vec3(0.f, rotationSpeed, 0.f));
        rotationSpeed += 0.7f;
        x -= 0.005f;
        scale = 0.515f;
        glm::mat4 world = body.GetTransform()->GetTransformMatrix();


        // Rendering
        // ------
        OpenGL_RenderableEntity* glRE = static_cast<OpenGL_RenderableEntity*>(renderableEntity);
        OpenGL_Shader* sh = static_cast<OpenGL_Shader*>(shader);
        sh->UpdateMatrices(world, view, projection);

        renderer.Clear();
        // Bind and draw
        renderer.Draw(renderableEntity);
        renderer.Present();
    }


    context->Terminate();
    return 0;
}
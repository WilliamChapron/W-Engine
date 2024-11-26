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

bool CheckCollision(BoxCollider* box1, BoxCollider* box2) // OBB
{
    AABB volume1 = box1->m_boundingVolume;
    AABB volume2 = box2->m_boundingVolume;

    // x
    bool collisionX = volume1.max[0] >= volume2.min[0] && volume2.max[0] >= volume1.min[0];
    // y
    bool collisionY = volume1.max[1] >= volume2.min[1] && volume2.max[1] >= volume1.min[1];
    // z
    bool collisionZ = volume1.max[2] >= volume2.min[2] && volume2.max[2] >= volume1.min[2];

    return collisionX && collisionY && collisionZ;
}

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

    // Create window
    OpenGL_Context* context = new OpenGL_Context();
    context->Initialize(SCR_WIDTH, SCR_HEIGHT, "OpenGL WINDOW");
    GLFWwindow* window = context->getWindow();

    // Renderer initialization
    OpenGL_Renderer renderer;
    renderer.Initialize(context);

    // Camera setup
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    // Shader for pyramid and cube
    Shader* pshader = new OpenGL_Shader();
    if (!pshader->Compile("res\\shaders\\colorV.glsl", "res\\shaders\\colorF.glsl")) {
        std::cerr << "Shader compilation failed!" << std::endl;
    }

    // Wireframe
    Shader* wireframeShader = new OpenGL_Shader();
    if (!wireframeShader->Compile("res\\shaders\\wireframeV.glsl", "res\\shaders\\wireframeF.glsl")) {
        std::cerr << "Shader compilation failed!" << std::endl;
    }

    // Pyramid setup

    RenderableEntity* pyramid = new OpenGL_RenderableEntity();
    Primitive* pyramidGeometry = new Cube;
    pyramidGeometry->Init();
    OpenGL_SubMesh* pyramidSubmesh = new OpenGL_SubMesh();
    pyramidSubmesh->Setup(pyramidGeometry->vertices, pyramidGeometry->indices, 0);

    Material* pyramidMaterial = new OpenGL_Material();
    pyramidMaterial->SetShader(pshader);
    pyramid->AddMaterial(pyramidMaterial);
    pyramid->AddSubMesh(pyramidSubmesh);



    // Cube setup
    RenderableEntity* cube = new OpenGL_RenderableEntity();
    Primitive* cubeGeometry = new PrimitiveRectangle(2.2, 2);
    cubeGeometry->Init();
    OpenGL_SubMesh* cubeSubmesh = new OpenGL_SubMesh();
    cubeSubmesh->Setup(cubeGeometry->vertices, cubeGeometry->indices, 0);

    Material* cubeMaterial = new OpenGL_Material();
    cubeMaterial->SetShader(pshader); // Utilise le même shader que la pyramide
    cube->AddMaterial(cubeMaterial);
    cube->AddSubMesh(cubeSubmesh);


    // Debug cubes setup



    // Transform

    Transform* cubeTransform = new Transform();
    cubeTransform->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f)); // Position initiale du cube

    Transform* debugTransform = new Transform();
    debugTransform->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f)); // Position initiale du cube
    //cubeTransform->SetScale(glm::vec3(1.0f, 1.0f, 1.0f)); // Position initiale du cube


    BoxCollider* cubeCollider = new BoxCollider(cubeGeometry->vertices); // Collider du cube

    Transform* pyramidTransform = new Transform();
    pyramidTransform->SetPosition(glm::vec3(-1.3f, 0.0f, 0.0f)); // Position initiale de la pyramide


    BoxCollider* pyramidCollider = new BoxCollider(pyramidGeometry->vertices); // Collider de la pyramide




    // Main loop 
    float pyramidSpeed = 0.5f; // Vitesse de déplacement de la pyramide
    float cubeRotationSpeed = 45.0f; // Vitesse de rotation du cube (degrés/sec)

    float dx = 0.0f;
    float dy = 0.0f;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        cubeTransform->SetRotation(glm::vec3(dx, 0.0f, 90.0f)); // Position initiale du cube
        cubeTransform->SetPosition(glm::vec3(dy, 0.0f, 0.0f)); // Position initiale du cube
        cubeTransform->SetScale(glm::vec3(dy, dy, dy)); // Position initiale du cube
        //debugTransform->SetRotation(glm::vec3(dx, 0.0f, 90.0f)); // Position initiale du cube
        
        // Timing
        static float lastFrameTime = 0.0f;
        float currentFrameTime = glfwGetTime();
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        // Update colliders


        // Matrices
        glm::mat4 projection = camera.GetProjectionMatrix(90.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        // World transforms
        glm::mat4 pyramidWorld = pyramidTransform->GetTransformMatrix();
        glm::mat4 cubeWorld = cubeTransform->GetTransformMatrix();

        dx += 0.1f;
        dy += 0.001f;

        //cubeTransform->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

        pyramidCollider->m_boundingVolume.UpdateAABBWithTransform(pyramidWorld);
        cubeCollider->m_boundingVolume.UpdateAABBWithTransform(cubeWorld);


        if (CheckCollision(pyramidCollider, cubeCollider)) {
            PRINT("O");
        }
        else {
            PRINT("X");
        }

        OpenGL_Shader* shPrimitive = static_cast<OpenGL_Shader*>(pshader);
        OpenGL_Shader* wfsh = static_cast<OpenGL_Shader*>(wireframeShader);
        

        // Render
        renderer.Clear();

        // Draw pyramid
        shPrimitive->UpdateMatrices(pyramidWorld, view, projection);
        renderer.Draw(pyramid);
        ////pyramidCollider->m_boundingVolume.render();
        ////renderer.DebugDraw(debugCube1);

        //// Draw cube
        shPrimitive->UpdateMatrices(cubeWorld, view, projection);
        renderer.Draw(cube);




        // Obtenez les coins de la AABB
        glm::vec3* corners = cubeCollider->m_boundingVolume.transformedCorners; 

        // Préparer les vertices
        std::vector<float> lineVertices;
        for (int i = 0; i < 8; ++i) {
            lineVertices.push_back(corners[i].x);  // Ajouter X
            lineVertices.push_back(corners[i].y);  // Ajouter Y
            lineVertices.push_back(corners[i].z/* + 0.1f*/);  // Ajouter Z avec un léger offset

            //std::cout << "Corner " << i << ": ("
            //    << corners[i].x << ", "
            //    << corners[i].y << ", "
            //    << corners[i].z << ")\n";
        }
        std::vector<unsigned int> indices = {
            0, 1,  // Ligne 1 : Coin 0 à Coin 1 (Horizontal, sur la face avant)
            1, 3,  // Ligne 2 : Coin 1 à Coin 3 (Vertical, sur la face avant)
            3, 2,  // Ligne 3 : Coin 3 à Coin 2 (Horizontal, sur la face avant)
            2, 0,  // Ligne 4 : Coin 2 à Coin 0 (Vertical, sur la face avant)

            4, 5,  // Ligne 5 : Coin 4 à Coin 5 (Horizontal, sur la face arrière)
            5, 7,  // Ligne 6 : Coin 5 à Coin 7 (Vertical, sur la face arrière)
            7, 6,  // Ligne 7 : Coin 7 à Coin 6 (Horizontal, sur la face arrière)
            6, 4,  // Ligne 8 : Coin 6 à Coin 4 (Vertical, sur la face arrière)

            0, 4,  // Ligne 9 : Coin 0 à Coin 4 (Vertical, sur la face gauche)
            1, 5,  // Ligne 10 : Coin 1 à Coin 5 (Vertical, sur la face droite)
            2, 6,  // Ligne 11 : Coin 2 à Coin 6 (Vertical, sur la face gauche)
            3, 7   // Ligne 12 : Coin 3 à Coin 7 (Vertical, sur la face droite)
        };

        glm::mat4 identityMatrix = glm::mat4(1.0f); 
        wfsh->UpdateMatrices(identityMatrix, view, projection);
        renderer.DebugColliderDraw(lineVertices, indices, wfsh);

        renderer.Present();



        // Input

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            isPaused = !isPaused;  // Basculer l'état de pause
            while (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
                // Attendre que la touche soit relâchée pour éviter les basculements multiples
                glfwPollEvents();
            }
        }
    }

    // Cleanup
    context->Terminate();
    return 0;
}


// #TODO Collision by distance and then true collision, create bounding box from vertices
// #TODO tableau de transform dans le renderable entity qu'on doit d'ailleur renommer 
// #TODO sort material by id et dessiner les sub mesh en fonction de leur materiau pou ne pas tout mettre a jour pour rien 
// #TODO mettre une matrice world dans chaque submesh mais en mettant un tableau de matrice world dans, mettre un transform dans chaque sub mesh avec un tableau de transform pas dans renderable entity mais dans 
// #TODO Theory collision 



// #TODO Material has shader and can change shader , this the material that needd contain the shader depending on texture that have or other
// Penser a comment eviter de cree un shader different pour chaque contexte mais plutot creer un shader qui conditionne les link
// JE DOIS ENCORE TESTER D'autre objets pour le diffuse et no diffuse

// #AMELIORER le conditionnement en utilisant les octet pour stocker des flags pour material mesh



//int main()
//{
//    // glfw: initialize and configure
//    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
//
//    #ifdef __APPLE__
//        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    #endif
//
//    // debug
//    // ------------------------------
//    FILE* fDummy;
//    freopen_s(&fDummy, "CONIN$", "r", stdin);   
//    freopen_s(&fDummy, "CONOUT$", "w", stderr);  
//    freopen_s(&fDummy, "CONOUT$", "w", stdout);  
//
//
//    std::cout << "Bienvenue dans le programme!\n";
//
//    // glfw window creation
//    // --------------------
//    OpenGL_Context* context = new OpenGL_Context();
//    context->Initialize(SCR_WIDTH, SCR_HEIGHT, "OpenGL WINDOW");
//
//    GLFWwindow* window = context->getWindow();
//
//    // renderer
//    // --------------------
//    OpenGL_Renderer renderer;
//    renderer.Initialize(context);
//
//    // camera
//    // --------------------
//    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//    //
//
//
//    //
//    GLFWLoader loader;
//    loader.LoadFile("res/models/moto/scene.gltf");
//    loader.StoreSceneAllVertices();
// 
//    RenderableEntity* renderableEntity = new OpenGL_RenderableEntity();
//    Shader* shader = new OpenGL_Shader();
//    if (!shader->Compile("res\\shaders\\vertex.glsl", "res\\shaders\\fragment.glsl")) {
//        std::cerr << "Shader compilation failed!" << std::endl;
//    }
//    renderableEntity->SetMaterials(loader.m_materials);
//    for (int i = 0; i < loader.m_materials.size(); i++) {
//        loader.m_materials[i]->SetShader(shader);
//    }
//    renderableEntity->SetSubMesh(loader.m_subMeshes);
//
//
//    BoxCollider* boxCollider1 = new BoxCollider();
//    boxCollider1->m_boundingVolume.SetMinMax(loader.m_min, loader.m_max);
//
//    boxCollider1->m_boundingVolume.CalculateData();
//
//
//    
//    //
//    RenderableEntity* pyramid = new OpenGL_RenderableEntity();
//    Shader* pshader = new OpenGL_Shader();
//    if (!pshader->Compile("res\\shaders\\colorV.glsl", "res\\shaders\\colorF.glsl")) {
//        std::cerr << "Shader compilation failed!" << std::endl;
//    }
//    Primitive* pyramidGeometry = new Pyramid();
//    pyramidGeometry->Init();
//    OpenGL_SubMesh* submesh = new OpenGL_SubMesh();
//    submesh->Setup(pyramidGeometry->vertices, pyramidGeometry->indices, 0);
//    Material* material = new OpenGL_Material();
//    material->SetShader(pshader);
//    pyramid->AddMaterial(material);
//    pyramid->AddSubMesh(submesh);
//
//    BoxCollider* boxCollider2 = new BoxCollider(pyramidGeometry->vertices);
//    //
//
//    // Box collider debug entity
//    RenderableEntity* debugCube = new OpenGL_RenderableEntity();
//    Primitive* cubeGeometry = new Cube();
//    cubeGeometry->Init();
//    OpenGL_SubMesh* submesh2 = new OpenGL_SubMesh();
//    submesh2->Setup(cubeGeometry->vertices, cubeGeometry->indices, 0);
//    Material* material2 = new OpenGL_Material();
//    material2->SetShader(pshader);
//    debugCube->AddMaterial(material2);
//    debugCube->AddSubMesh(submesh2);
//    //
//
//    float rotationSpeed = 0.0f;      // Vitesse de rotation initiale
//    const float ROTATION_INCREMENT = 0.7f;  // La vitesse d'incrémentation de la rotation à chaque frame
//    const float MAX_ROTATION = 360.0f;  // La valeur maximale avant d'enrouler
//
//
//    float x = 0.0f;
//    float scale = 0.0f;
//    float velocity[3] = { 0.0f, 0.0f, 0.0f };
//    float mass = 0.001f;
//    const float GRAVITY = -9.81f;
//    float lastFrameTime = glfwGetTime();
//
//    Body body(velocity, mass);
//    Transform* bodyT = body.GetTransform();  
//
//    Transform* bodyT2 = new Transform();  
//
//
//    bodyT2->SetPosition(glm::vec3(0.5, -0.7f, 0.0f));
//
//    while (!glfwWindowShouldClose(window))
//    {
//        float currentFrameTime = glfwGetTime();
//        float deltaTime = currentFrameTime - lastFrameTime;
//        lastFrameTime = currentFrameTime;
//
//
//        glm::mat4 projection = camera.GetProjectionMatrix(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//
//        rotationSpeed += ROTATION_INCREMENT;
//        if (rotationSpeed >= MAX_ROTATION) {
//            rotationSpeed -= MAX_ROTATION; 
//        }
//
//
//        bodyT->SetPosition(glm::vec3(x, 0.0f, 0.f));
//        bodyT->SetScale(glm::vec3(scale, scale, scale)); 
//        bodyT->SetRotation(glm::vec3(0.f, 0.f, 0.f)); 
//        rotationSpeed += 0.7f; 
//        x += 0.001f;  
//        scale = 0.008f;  
//
//
//        bodyT2->SetPosition(glm::vec3(0.5, -0.0f, 0.0f));
//        //bodyT2->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));  
//        //bodyT2->SetRotation(glm::vec3(0.f, rotationSpeed, 0.f));  
//
//
//
//        glm::mat4 world = bodyT->GetTransformMatrix();  
//        glm::mat4 pyramidWorld = bodyT2->GetTransformMatrix();  
//
//        if (CheckCollision(boxCollider1, boxCollider2)) {
//            PRINT("Collide");
//        }
//
//        boxCollider1->m_boundingVolume.UpdateAABBWithTransform(world);
//        boxCollider2->m_boundingVolume.UpdateAABBWithTransform(pyramidWorld);
//
// 
//        
//
//
//        OpenGL_RenderableEntity* glRE = static_cast<OpenGL_RenderableEntity*>(renderableEntity);
//        OpenGL_Shader* sh = static_cast<OpenGL_Shader*>(shader);
//        OpenGL_RenderableEntity* glPrimitive = static_cast<OpenGL_RenderableEntity*>(pyramid);
//        OpenGL_Shader* shPrimitive = static_cast<OpenGL_Shader*>(pshader);
//
//        //Vector3Display(bodyT2->GetRotation());
//
//
//        renderer.Clear();
//
//
//
//
//
//        sh->UpdateMatrices(world, view, projection);  
//        renderer.Draw(renderableEntity); 
//
//        shPrimitive->UpdateMatrices(pyramidWorld, view, projection);  
//        renderer.Draw(pyramid);  
//
//        renderer.DebugDraw(debugCube);
//
//
//        renderer.Present();
//
//        //Sleep(1500);
//    }
//
//
//    context->Terminate();
//    return 0;
//}
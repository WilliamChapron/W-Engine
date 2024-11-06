#include "pch.h"

//Render
#include "OpenGL_Context.h"
#include "OpenGL_Renderer.h" 
#include "OpenGL_Shader.h" 
#include "OpenGL_Mesh.h" 
#include "OpenGL_Texture.h" 

//Engine
#include "Camera.h" 
#include "Transform.h" 
#include "Body.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void LoadModel(const std::string& filePath, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<std::string>& albedoTextures) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Erreur : " << importer.GetErrorString() << std::endl;
        return;
    }

    // Parcourir tous les sous-maillages pour récupérer les vertices et indices
    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[i];

        // Récupérer les vertices et les coordonnées de texture
        for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
            Vertex vertex;
            vertex.position[0] = mesh->mVertices[j].x;
            vertex.position[1] = mesh->mVertices[j].y;
            vertex.position[2] = mesh->mVertices[j].z;

            if (mesh->mNormals) {
                vertex.normal[0] = mesh->mNormals[j].x;
                vertex.normal[1] = mesh->mNormals[j].y;
                vertex.normal[2] = mesh->mNormals[j].z;
            }

            if (mesh->mTextureCoords[0]) {
                vertex.texCoords[0] = mesh->mTextureCoords[0][j].x;
                vertex.texCoords[1] = mesh->mTextureCoords[0][j].y;
            }
            else {
                vertex.texCoords[0] = 0.0f;
                vertex.texCoords[1] = 0.0f;
            }

            vertices.push_back(vertex);
        }

        // Récupérer les indices
        for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
            aiFace face = mesh->mFaces[j];
            for (unsigned int k = 0; k < face.mNumIndices; k++) {
                indices.push_back(face.mIndices[k]);
            }
        }

        // Récupérer le chemin de la texture albedo pour ce sous-maillage
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        aiString texturePath;
        if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS) {
            albedoTextures.push_back(texturePath.C_Str());
        }
        else {
            albedoTextures.push_back(""); // Ajouter une chaîne vide si pas de texture albedo
        }
    }
}


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

    // build and compile shader
    // ------------------------------------
    OpenGL_Shader shader; 
    if (!shader.Compile("res\\shaders\\vertex.glsl", "res\\shaders\\fragment.glsl")) {
        std::cerr << "Shader compilation failed!" << std::endl;
        return -1; 
    }

    // load textures
    // ------------------------------------


    // vertices
    // ------------------------------------------------------------------
    //std::vector<Vertex> vertices = {
    //    // Sommet de la pyramide (maintenant en haut)
    //    {{ 0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {0.5f, 1.0f}}, // Sommet (blanc)

    //    // Base de la pyramide
    //    {{-0.5f, 0.0f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // Bas gauche arrière (rouge)
    //    {{ 0.5f, 0.0f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}}, // Bas droit arrière (vert)
    //    {{ 0.5f, 0.0f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}}, // Bas droit avant (bleu)
    //    {{-0.5f, 0.0f,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}}  // Bas gauche avant (jaune)
    //};

    //// Indices pour les triangles de la pyramide
    //std::vector<unsigned int> indices = {
    //    // Faces triangulaires
    //    0, 1, 2,  // Face arrière
    //    0, 2, 3,  // Face droite
    //    0, 3, 4,  // Face avant
    //    0, 4, 1,  // Face gauche

    //    // Base (face inférieure)
    //    1, 2, 3,  // Triangle 1 de la base
    //    1, 3, 4   // Triangle 2 de la base
    //};

    OpenGLTexture texture("res\\textures\\scooter\\diffuse.png");


    OpenGL_Mesh mesh;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::string> albedoTextures;

    LoadModel("res/models/moto/scene.gltf", vertices, indices, albedoTextures);
    mesh.Setup(vertices, indices);

    glEnable(GL_DEPTH_TEST);
    


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
        bodyT->SetScale(glm::vec3(scale, scale, scale));
        //bodyT->SetRotation(glm::vec3(rotationSpeed, 0.f, rotationSpeed));
        rotationSpeed += 1.f;
        x -= 0.005f;
        scale = 1.1f;
        glm::mat4 world = body.GetTransform()->GetTransformMatrix();


        // Rendering
        // ------

        shader.UpdateMatrices(world, view, projection);
        renderer.Clear();
        //texture.Bind();
        renderer.Draw(mesh, shader);
        renderer.Present();
    }


    context->Terminate();
    return 0;
}
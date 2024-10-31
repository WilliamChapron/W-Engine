#include "pch.h"

//Render
#include "OpenGL_Context.h"
#include "OpenGL_Renderer.h" 
#include "OpenGL_Shader.h" 
#include "OpenGL_Mesh.h" 

//Engine
#include "Camera.h" 
#include "Transform.h" 



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void LoadModel(const std::string& filePath, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Erreur : " << importer.GetErrorString() << std::endl;
        return;
    }

    // Extraire les meshes
    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[i];

        // Extraire les vertices
        for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
            Vertex vertex;
            vertex.position[0] = mesh->mVertices[j].x;
            vertex.position[1] = mesh->mVertices[j].y;
            vertex.position[2] = mesh->mVertices[j].z;

            vertex.color[0] = mesh->mColors[0] ? mesh->mColors[0][j].r : 0.0f; // Default color to white if no color is provided
            vertex.color[1] = mesh->mColors[0] ? mesh->mColors[0][j].g : 1.0f;
            vertex.color[2] = mesh->mColors[0] ? mesh->mColors[0][j].b : 1.0f;
            vertex.color[3] = 1.0f; // Alpha channel

            if (mesh->mNormals) {
                vertex.normal[0] = mesh->mNormals[j].x;
                vertex.normal[1] = mesh->mNormals[j].y;
                vertex.normal[2] = mesh->mNormals[j].z;
            }
            else {
                // Normale par défaut si aucune normale n'est fournie
                vertex.normal[0] = 0.0f;
                vertex.normal[1] = 0.0f;
                vertex.normal[2] = 1.0f; // Normale pointant vers l'avant
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

        // Extraire les indices
        for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
            aiFace face = mesh->mFaces[j];
            for (unsigned int k = 0; k < face.mNumIndices; k++) {
                indices.push_back(face.mIndices[k]);
            }
        }
    }
}

void PrintGLBContent(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filePath << std::endl;
        return;
    }

    // Lire le contenu du fichier dans un vecteur de caractères
    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Afficher le contenu sous forme binaire (hexadécimal)
    std::cout << "Contenu du fichier " << filePath << " : " << std::endl;
    for (size_t i = 0; i < buffer.size(); ++i) {
        // Affiche les 16 premiers octets en hexadécimal
        if (i % 16 == 0 && i != 0) {
            std::cout << std::endl;
        }
        std::cout << std::hex << (static_cast<int>(buffer[i]) & 0xFF) << " ";
    }
    std::cout << std::dec << std::endl; // Revenir à la base décimale
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
    FILE* fDummy;
    freopen_s(&fDummy, "CONIN$", "r", stdin);   // Pour l'entrée
    freopen_s(&fDummy, "CONOUT$", "w", stderr);  // Pour les erreurs
    freopen_s(&fDummy, "CONOUT$", "w", stdout);  // Pour la sortie

    // Exemple d'utilisation de cout
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

    //camera
    // Créer une caméra
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    // build and compile shader
    // ------------------------------------
    OpenGL_Shader shader; 
    if (!shader.Compile("res\\shaders\\vertex.glsl", "res\\shaders\\fragment.glsl")) {
        std::cerr << "Shader compilation failed!" << std::endl;
        return -1; 
    }


    OpenGL_Mesh mesh;
    // vertices
    // ------------------------------------------------------------------
    std::vector<Vertex> vertices = {
        // Sommet de la pyramide (maintenant en haut)
        {{ 0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {0.5f, 1.0f}}, // Sommet (blanc)

        // Base de la pyramide
        {{-0.5f, 0.0f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // Bas gauche arrière (rouge)
        {{ 0.5f, 0.0f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}}, // Bas droit arrière (vert)
        {{ 0.5f, 0.0f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}}, // Bas droit avant (bleu)
        {{-0.5f, 0.0f,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}}  // Bas gauche avant (jaune)
    };

    // Indices pour les triangles de la pyramide
    std::vector<unsigned int> indices = {
        // Faces triangulaires
        0, 1, 2,  // Face arrière
        0, 2, 3,  // Face droite
        0, 3, 4,  // Face avant
        0, 4, 1,  // Face gauche

        // Base (face inférieure)
        1, 2, 3,  // Triangle 1 de la base
        1, 3, 4   // Triangle 2 de la base
    };

    //std::vector<Vertex> vertices;
    //std::vector<unsigned int> indices;

    // Charge le modèle FBX
    //PrintGLBContent("C:/Users/wchapron/Documents/GitHub/W-Engine/res/models/guitar/source/glb.glb");
    //while (true) {

    //}
    //LoadModel("C:/Users/wchapron/Documents/GitHub/W-Engine/res/models/locker.obj", vertices, indices);
       

    // Configuration du mesh
    mesh.Setup(vertices, indices);

    glEnable(GL_DEPTH_TEST);
    

    // Variables globales
    float rotationSpeed = 0.0f; // Vitesse de rotation en degrés par seconde

    Transform transform; // Créer un objet Transform

    // Configuration initiale
    transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
    transform.SetScale(glm::vec3(0.8f, 0.8f, 0.8f));

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // Calculer le temps écoulé depuis la dernière frame
        // input
        // -----
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render
        // ------
        renderer.Clear();

        // Calculer les matrices
        glm::mat4 projection = camera.GetProjectionMatrix(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        transform.SetRotation(glm::vec3(rotationSpeed, 0.f, rotationSpeed));
        rotationSpeed += 0.1f;

        // Obtenir la matrice de transformation
        glm::mat4 world = transform.GetTransformMatrix();

        // Mettre à jour les matrices dans le shader
        shader.UpdateMatrices(world, view, projection);


        rotationSpeed += 1.f;
        // Dessiner le mesh
        renderer.Draw(mesh, shader);

        // Présenter le buffer
        renderer.Present();
    }


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------

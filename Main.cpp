#include "pch.h"

//Render
#include "OpenGL_Context.h"
#include "OpenGL_Renderer.h" 
#include "OpenGL_Shader.h" 
#include "OpenGL_Mesh.h" 

//Engine
#include "Camera.h" 



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
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

    // Configuration du mesh
    mesh.Setup(vertices, indices);

    glEnable(GL_DEPTH_TEST);
    

    // Variables globales
    float rotationSpeed = 0.0f; // Vitesse de rotation en degrés par seconde

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

        // Position de l'objet
        glm::vec3 position(0.0f, -0.5f, 0.0f);

        // Créer une matrice d'identité
        glm::mat4 world = glm::mat4(1.0f);

        // Appliquer la translation
        world = glm::translate(world, position);

        // Appliquer la rotation
        float angle = rotationSpeed; // Calculer l'angle de rotation en fonction du temps écoulé
        world = glm::rotate(world, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotation autour de l'axe Y

        // Mettre à jour les matrices dans le shader
        shader.UpdateMatrices(world, view, projection); // Appel à UpdateMatrices

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

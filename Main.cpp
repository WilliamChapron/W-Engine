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

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"  // Emplacement des sommets
"layout (location = 1) in vec4 aColor;\n" // Emplacement des couleurs
"uniform mat4 u_World;\n"                 // Matrice du monde
"uniform mat4 u_View;\n"                  // Matrice de vue
"uniform mat4 u_Projection;\n"            // Matrice de projection
"out vec4 vertexColor;\n"                 // Sortie de couleur pour le fragment shader
"void main()\n"
"{\n"
"   gl_Position = u_Projection * u_View * u_World * vec4(aPos, 1.0);\n"  // Appliquer les transformations
"   vertexColor = aColor;\n"          // Passer la couleur au fragment shader
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"                // Récupérer la couleur du vertex shader
"void main()\n"
"{\n"
"   FragColor = vertexColor;\n"         // Utiliser la couleur du vertex
"}\n\0";


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
    if (!shader.Compile(vertexShaderSource, fragmentShaderSource)) {
        std::cerr << "Shader compilation failed!" << std::endl;
        return -1; 
    }


    OpenGL_Mesh mesh;
    // vertices
    // ------------------------------------------------------------------
    std::vector<Vertex> vertices = {
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}}, // Rouge
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}}, // Vert
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}, // Bleu
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, {1.0f, 1.0f, 0.0f, 1.0f}}, // Jaune
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f, 1.0f, 1.0f}}, // Magenta
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f}}, // Cyan
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, {0.5f, 0.5f, 0.5f, 1.0f}}, // Gris
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}, {1.0f, 0.5f, 0.0f, 1.0f}}  // Orange
    };

    // Indices pour les triangles du cube
    std::vector<unsigned int> indices = {
        0, 1, 3,  // Face avant (triangle 1)
        1, 2, 3,  // Face avant (triangle 2)
        4, 5, 7,  // Face arrière (triangle 1)
        5, 6, 7,  // Face arrière (triangle 2)
        0, 4, 7,  // Face gauche (triangle 1)
        0, 3, 7,  // Face gauche (triangle 2)
        1, 5, 6,  // Face droite (triangle 1)
        1, 2, 6,  // Face droite (triangle 2)
        3, 2, 6,  // Face supérieure (triangle 1)
        3, 6, 7,  // Face supérieure (triangle 2)
        0, 1, 5,  // Face inférieure (triangle 1)
        0, 5, 4   // Face inférieure (triangle 2)
    };

    // Configuration du mesh
    mesh.Setup(vertices, indices);
    

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        renderer.Clear();

        // Calculer les matrices
        glm::mat4 projection = camera.GetProjectionMatrix(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        // Position de l'objet
        glm::vec3 position(1.0f, 2.0f, -5.0f);

        // Créer une matrice d'identité
        glm::mat4 world = glm::mat4(1.0f);

        // Appliquer la translation
        world = glm::translate(world, position);

        // Appliquer la rotation (ex. 45 degrés autour de l'axe Y)
        float angle = glm::radians(45.0f); // Convertir les degrés en radians
        world = glm::rotate(world, angle, glm::vec3(0.0f, 1.0f, 0.0f)); // Rotation autour de l'axe Y

        // Mettre à jour les matrices dans le shader
        shader.UpdateMatrices(world, view, projection); // Appel à UpdateMatrices

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

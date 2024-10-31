#include "pch.h"


#include "OpenGL_Shader.h"

OpenGL_Shader::OpenGL_Shader() : m_programID(0) {}

OpenGL_Shader::~OpenGL_Shader() {
    if (m_programID != 0) {
        glDeleteProgram(m_programID);
    }
}

std::string OpenGL_Shader::LoadShaderSource(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier shader : " << filePath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf(); 
    return buffer.str();    
}

bool OpenGL_Shader::Compile(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexSource = LoadShaderSource(vertexPath);
    std::string fragmentSource = LoadShaderSource(fragmentPath);

    if (vertexSource.empty() || fragmentSource.empty()) {
        return false; 
    }

    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource.c_str());
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());

    if (vertexShader == 0 || fragmentShader == 0) {
        return false; // Si la compilation échoue
    }

    // Création et liaison du programme shader
    m_programID = glCreateProgram();
    glAttachShader(m_programID, vertexShader);
    glAttachShader(m_programID, fragmentShader);
    glLinkProgram(m_programID);

    int success;
    char infoLog[512];
    glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_programID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

void OpenGL_Shader::Use() const {
    glUseProgram(m_programID);
}

unsigned int OpenGL_Shader::GetProgramID() const {
    return m_programID;
}

unsigned int OpenGL_Shader::CompileShader(unsigned int type, const std::string& source) {
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(shader); // Supprime le shader en cas d’échec
        return 0;
    }
    return shader;
}

void OpenGL_Shader::UpdateMatrices(const glm::mat4& world, const glm::mat4& view, const glm::mat4& projection) {
    Use();

    GLuint worldLoc = glGetUniformLocation(m_programID, "u_World");
    GLuint viewLoc = glGetUniformLocation(m_programID, "u_View");
    GLuint projectionLoc = glGetUniformLocation(m_programID, "u_Projection");

    glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(world));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}
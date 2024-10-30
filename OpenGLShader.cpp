#include "pch.h"
#include "OpenGLShader.h"

#include "OpenGLShader.h"

OpenGLShader::OpenGLShader() : m_programID(0) {}

OpenGLShader::~OpenGLShader() {
    if (m_programID != 0) {
        glDeleteProgram(m_programID);
    }
}

bool OpenGLShader::Compile(const std::string& vertexSource, const std::string& fragmentSource) {
    // Compilation des shaders vertex et fragment
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

    if (vertexShader == 0 || fragmentShader == 0) {
        return false; // Si la compilation échoue
    }

    // Création et liaison du programme shader
    m_programID = glCreateProgram();
    glAttachShader(m_programID, vertexShader);
    glAttachShader(m_programID, fragmentShader);
    glLinkProgram(m_programID);

    // Vérification des erreurs de liaison
    int success;
    char infoLog[512];
    glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_programID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return false;
    }

    // Nettoyage des shaders (ils sont désormais intégrés au programme)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

void OpenGLShader::Use() const {
    glUseProgram(m_programID);
}

unsigned int OpenGLShader::GetProgramID() const {
    return m_programID;
}

unsigned int OpenGLShader::CompileShader(unsigned int type, const std::string& source) {
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    // Vérification des erreurs de compilation
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
            << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(shader); // Supprime le shader en cas d’échec
        return 0;
    }
    return shader;
}

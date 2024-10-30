#pragma once

#include "Shader.h"

class OpenGL_Shader : public Shader {
public:
    OpenGL_Shader();
    ~OpenGL_Shader() override;

    bool Compile(const std::string& vertexSource, const std::string& fragmentSource) override;
    void Use() const override;
    unsigned int GetProgramID() const override;

    void UpdateMatrices(const glm::mat4& world, const glm::mat4& view, const glm::mat4& projection);

private:
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int m_programID;
};


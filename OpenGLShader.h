#pragma once

#include "Shader.h"

class OpenGLShader : public Shader {
public:
    OpenGLShader();
    ~OpenGLShader() override;

    bool Compile(const std::string& vertexSource, const std::string& fragmentSource) override;
    void Use() const override;
    unsigned int GetProgramID() const override;

private:
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int m_programID;
};


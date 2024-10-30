#pragma once

#include <string>

class Shader {
public:
    virtual ~Shader() = default;


    virtual bool Compile(const std::string& vertexSource, const std::string& fragmentSource) = 0;
    virtual void Use() const = 0;
    virtual unsigned int GetProgramID() const = 0;
};


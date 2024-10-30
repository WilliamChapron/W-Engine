#pragma once

#include "Context.h"

class OpenGLContext : public Context {
public:
    OpenGLContext() {};
    virtual ~OpenGLContext() {};

    bool Initialize(int width, int height, const char* title) override;
    void Terminate() override {};

    inline GLFWwindow* getWindow() const { return m_window; }

private:
    GLFWwindow* m_window;
};
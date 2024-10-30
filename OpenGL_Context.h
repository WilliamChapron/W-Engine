#pragma once

#include "Context.h"

class OpenGL_Context : public Context {
public:
    OpenGL_Context() {};
    virtual ~OpenGL_Context() {};

    bool Initialize(int width, int height, const char* title) override;
    void Terminate() override {};

    inline GLFWwindow* getWindow() const { return m_window; }

private:
    GLFWwindow* m_window;
};
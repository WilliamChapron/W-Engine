#pragma once

class Context {
public:
    virtual ~Context() = default;

    virtual bool Initialize(int width, int height, const char* title) = 0;
    virtual void Terminate() = 0;

protected:
    int m_width;
    int m_height;

    const char* m_title;
};


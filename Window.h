#pragma once

class Window
{
public:
    Window(HINSTANCE hInstance);
    virtual ~Window();
    



    bool Initialize();
    bool Run();

    // Getter
    int  GetClientWidth();
    int  GetClientHeight();
    HWND GetHMainWnd();
    HINSTANCE GetHInstance();

private:

private:


    int        m_width;
    int        m_height;
    HWND*      m_hwnd;
    HINSTANCE* mhInstance;
};
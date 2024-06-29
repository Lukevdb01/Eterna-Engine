#ifndef OS_WINDOW_H
#define OS_WINDOW_H

#include <string>
#include <windows.h>
#include <gl/gl.h>

class Window {
public:
    enum WindowType {
        Windowed,
        Borderless,
        Fullscreen
    };

    Window(const std::wstring& title, int width, int height, WindowType type = Windowed);
    ~Window();

    void Update();
	void Destroy();
    bool IsRunning() const;    

private:
    std::wstring m_Title;
    int m_Width, m_Height;
    WindowType m_Type;

    HWND m_hWnd;
    HINSTANCE m_hInstance;
    HDC m_hDC;
    HGLRC m_hRC;
    WNDCLASS m_wc;
	bool m_Running;

    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    void RegisterWindowClass();
    void CreateAppWindow();
    void CreateOpenGLContext();
    void DestroyOpenGLContext();
    void SwapBuffers();
};

#endif // !OS_WINDOW_H

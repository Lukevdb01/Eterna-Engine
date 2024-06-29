#ifdef _WIN32

#include "OS/window.h"
#include <stdexcept>
#include <iostream>

#include <stdexcept>
#include <iostream>

Window::Window(const std::wstring& title, int width, int height, WindowType type)
    : m_Title(title), m_Width(width), m_Height(height), m_Type(type), m_Running(true), m_hDC(nullptr), m_hRC(nullptr) {
    m_hInstance = GetModuleHandle(nullptr);
    RegisterWindowClass();
    CreateAppWindow();
    CreateOpenGLContext();
}

Window::~Window() {
    DestroyOpenGLContext();
    DestroyWindow(m_hWnd);
    UnregisterClass(m_wc.lpszClassName, m_hInstance);
}

void Window::Update() {
    MSG msg = { 0 };
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
	SwapBuffers();
}

void Window::Destroy()
{
	DestroyOpenGLContext();
	DestroyWindow(m_hWnd);
	UnregisterClass(m_wc.lpszClassName, m_hInstance);
}

bool Window::IsRunning() const
{
    return m_Running;
}

void Window::SwapBuffers() {
    ::SwapBuffers(m_hDC);
}

LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    Window* window = nullptr;

    if (message == WM_CREATE) {
        window = reinterpret_cast<Window*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		std::cout << "Window ptr created" << std::endl;
    }
    else {
        window = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }

    if (window) {
        switch (message) {
        case WM_CLOSE:
            window->m_Running = false;
			std::cout << "Window closed" << std::endl;
            PostQuitMessage(0);
            return 0;

        case WM_DESTROY:
            window->m_Running = false;
			std::cout << "Window destroyed" << std::endl;
            return 0;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

void Window::RegisterWindowClass() {
    m_wc = { 0 };
    m_wc.lpfnWndProc = WindowProc;
    m_wc.hInstance = m_hInstance;
    m_wc.lpszClassName = L"SampleWindowClass";  // Use wide string literal
    if (!RegisterClass(&m_wc)) {
        throw std::runtime_error("Failed to register window class");
    }
}

void Window::CreateAppWindow() {
    DWORD style = WS_OVERLAPPEDWINDOW;
    if (m_Type == Borderless) {
        style = WS_POPUP;
    }
    else if (m_Type == Fullscreen) {
        style = WS_POPUP;
        DEVMODE dm = { 0 };
        dm.dmSize = sizeof(dm);
        dm.dmPelsWidth = m_Width;
        dm.dmPelsHeight = m_Height;
        dm.dmBitsPerPel = 32;
        dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
        ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
    }
    else if (m_Type == Windowed) {
		style = WS_OVERLAPPEDWINDOW | WS_MAXIMIZE;
    }

    m_hWnd = CreateWindowEx(
        0,
        m_wc.lpszClassName,
        m_Title.c_str(),  // Use wide string
        style,
        CW_USEDEFAULT, CW_USEDEFAULT,
        m_Width, m_Height,
        nullptr, nullptr,
        m_hInstance, this
    );

    if (!m_hWnd) {
        throw std::runtime_error("Failed to create window");
    }

    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);
}

void Window::CreateOpenGLContext() {
    m_hDC = GetDC(m_hWnd);
    if (!m_hDC) {
        throw std::runtime_error("Failed to get device context");
    }

    PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR), 1 };
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int pixelFormat = ChoosePixelFormat(m_hDC, &pfd);
    if (!pixelFormat) {
        throw std::runtime_error("Failed to choose pixel format");
    }

    if (!SetPixelFormat(m_hDC, pixelFormat, &pfd)) {
        throw std::runtime_error("Failed to set pixel format");
    }

    m_hRC = wglCreateContext(m_hDC);
    if (!m_hRC) {
        throw std::runtime_error("Failed to create OpenGL context");
    }

    if (!wglMakeCurrent(m_hDC, m_hRC)) {
        throw std::runtime_error("Failed to make OpenGL context current");
    }
}

void Window::DestroyOpenGLContext() {
    if (m_hRC) {
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(m_hRC);
        m_hRC = nullptr;
    }

    if (m_hDC) {
        ReleaseDC(m_hWnd, m_hDC);
        m_hDC = nullptr;
    }
}



#endif // _WIN32

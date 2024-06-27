#ifndef OS_WINDOW_H
#define OS_WINDOW_H

#include <string>

class Window {
public:
	enum WindowType {
		Windowed,
		Borderless,
		Fullscreen
	};

	Window(const std::string& title, int width, int height, Window::WindowType type = Windowed);
	~Window();

	void Update();

private:
	int m_Width = 0, m_Height = 0;
	Window::WindowType m_Type = Windowed;

	void* m_Data = nullptr;
};

#endif // !OS_WINDOW_H

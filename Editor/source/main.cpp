#include <iostream>

#include "engine.h"
#include "OS/events.h"
#include "OS/window.h"

int main(int argc, char* argv[])
{
	Window window(L"Editor", 800, 600, Window::WindowType::Windowed);
	Events events;

	while (window.IsRunning())
	{
		events.Update();

		if (events.Pressed(event::Type::KEY_ESCAPE))
		{
			window.Destroy();
		}

		window.Update();
	}
	return 0;
}
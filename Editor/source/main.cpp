#include <iostream>

#include "engine.h"
#include "OS/events.h"
#include "OS/window.h"
#include <OS/helper.h>

#include <Utils/config.h>

int main(int argc, char* argv[])
{
	ConfigLoader config("config", "config.ini");

	Window window(Helper::stringToWString(config.getString("general", "window_title")), config.GetInteger("general", "window_width"), config.GetInteger("general", "window_height"), Window::WindowType::Windowed);
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
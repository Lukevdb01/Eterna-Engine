#include <iostream>

#include "engine.h"
#include "OS/events.h"

int main(int argc, char* argv[])
{
	Events events;

	std::cout << "Hello, World!" << std::endl;

	bool running = true;
	while (running)
	{
		events.Update();

		if (events.Pressed(event::Type::KEY_ESCAPE))
		{
			running = false;
		}

		if (events.Pressed(event::Type::KEY_SPACE))
		{
			Test();
		}
	}

	std::cout << "Goodbye, World!" << std::endl;
	return 0;
}
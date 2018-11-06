
#define SDL_MAIN_HANDLED
#include "Graphics.h"

#include <iostream>
#include <memory>

int main()
{
	auto graphics = std::make_unique<Graphics>();

	while (true)
	{
		graphics->beforeFrame();

		graphics->update();
		graphics->drawRect(0, 0, 100, 100);
		graphics->drawRect(100, 100, 100, 100);
		graphics->drawRect(200, 200, 100, 100);
		graphics->drawRect(300, 300, 100, 100);
		graphics->drawRect(400, 400, 100, 100);
		graphics->update();

		graphics->afterFrame();
	}

	return 0;
}

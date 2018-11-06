#include "Window.h"
#include <iostream>

Window::Window()
{
	try
	{
		sdlWindow = SDL_CreateWindow("Foxtrot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_OPENGL);
		if (sdlWindow == nullptr)
			throw 0;
	}
	catch (int error)
	{
		std::cout << "Failed to create window!" << std::endl;
	}
}

Window::~Window()
{
	if (sdlWindow != nullptr)
		SDL_DestroyWindow(sdlWindow);
}

SDL_Window* Window::getSdlWindow() const
{
	return sdlWindow;
}

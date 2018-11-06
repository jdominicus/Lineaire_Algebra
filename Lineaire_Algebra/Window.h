#pragma once

#include <SDL2/SDL.h>

class Window
{
	public:
		Window();
		~Window();

	private:
		SDL_Window* sdlWindow;

	public:
		SDL_Window* getSdlWindow() const;
};

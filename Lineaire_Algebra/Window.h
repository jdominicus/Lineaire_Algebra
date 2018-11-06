#pragma once

#include <SDL2/SDL.h>

#define MAX_X 500
#define MAX_Y 500
#define OORSPRONG_X MAX_X/2
#define OORSPRONG_Y MAX_Y/2

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
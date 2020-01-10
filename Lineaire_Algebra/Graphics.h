#pragma once

#include <SDL2/SDL.h>
#include <memory>

class Window;
class Color;
class Sprite;

class Graphics
{
	public:
		Graphics();
		~Graphics();

	private:
		static const int FRAMES_PER_SECOND = 60;
		static const int SCREEN_WIDTH = 600;
		static const int SCREEN_HEIGHT = 600;
		int frameTime;
		int view;	// Top = 0; Front = 1; Side = 2;

		SDL_Renderer* sdlRenderer;
		std::unique_ptr<Window> window;

	public:
		SDL_Renderer* getRenderer() const;

		void beforeFrame();
		void afterFrame() const;
		void clear() const;
		void update() const;
		void drawRect(int x, int y, int width, int height) const;
		void drawVector(int x, int y, int z) const;
		void drawLine(int x_src, int y_src, int z_src, int x_dest, int y_dest, int z_dest, int r = 255, int g = 255, int b = 255) const;
		void drawAxis() const;
		void changeView();
};
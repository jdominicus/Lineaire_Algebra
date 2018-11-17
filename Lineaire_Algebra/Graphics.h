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
		static const int SCREEN_WIDTH = 1280;
		static const int SCREEN_HEIGHT = 720;
		int frameTime;

		SDL_Renderer* sdlRenderer;
		std::unique_ptr<Window> window;

	public:
		SDL_Renderer* getRenderer() const;

		void beforeFrame();
		void afterFrame() const;
		void clear() const;
		void update() const;
		void drawRect(int x, int y, int width, int height) const;
		void drawVector(int x, int y) const;
		void drawLine(int x_src, int y_src, int x_dest, int y_dest, int r, int g, int b) const;
		void drawAxis() const;
};
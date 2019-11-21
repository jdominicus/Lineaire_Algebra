#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include "Window.h"

class Color;
class Sprite;

template <typename T>
class Camera;

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
		void changeView();

		template <typename T>
		void drawAxis(Camera<T>& camera) const
		{
			SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);		//rood
			SDL_RenderDrawLine(sdlRenderer, -camera.getLocation()->getX() + OORSPRONG_X, 0, -camera.getLocation()->getX() + OORSPRONG_X, 600);
			SDL_RenderDrawLine(sdlRenderer, 0, -camera.getLocation()->getY() + OORSPRONG_Y, 600, -camera.getLocation()->getY() + OORSPRONG_Y);
		}
		template <typename T>
		void drawLine(Camera<T>& camera, int x_src, int y_src, int z_src, int x_dest, int y_dest, int z_dest, int r = 255, int g = 255, int b = 255) const
		{
			SDL_SetRenderDrawColor(sdlRenderer, r, g, b, SDL_ALPHA_OPAQUE);

			if (view == 0)
				SDL_RenderDrawLine(sdlRenderer, x_src + -camera.getLocation()->getX() + OORSPRONG_X, OORSPRONG_Z + z_src, -camera.getLocation()->getX() + OORSPRONG_X + x_dest, OORSPRONG_Z + z_dest);

			if (view == 1)
				SDL_RenderDrawLine(sdlRenderer, x_src + -camera.getLocation()->getX() + OORSPRONG_X, -camera.getLocation()->getY() + OORSPRONG_Y - y_src, -camera.getLocation()->getX() + OORSPRONG_X + x_dest, -camera.getLocation()->getY() + OORSPRONG_Y - y_dest);

			if (view == 2)
				SDL_RenderDrawLine(sdlRenderer, OORSPRONG_Z - z_src, -camera.getLocation()->getY() + OORSPRONG_Y - y_src, OORSPRONG_Z - z_dest, -camera.getLocation()->getY() + OORSPRONG_Y - y_dest);
		}
};
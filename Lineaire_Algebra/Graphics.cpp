#include "Graphics.h"
#include "Window.h"

#include <iostream>

Graphics::Graphics()
{
	try
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			throw 0;
	}
	catch (int error)
	{
		std::cout << "Failed to initialise SDL!";
	}
	
	window = std::make_unique<Window>();
	sdlRenderer = SDL_CreateRenderer(window->getSdlWindow(), -1, SDL_RENDERER_ACCELERATED);
}


Graphics::~Graphics()
{
	if (sdlRenderer != nullptr)
		SDL_DestroyRenderer(sdlRenderer);
}

SDL_Renderer* Graphics::getRenderer() const
{
	return sdlRenderer;
}

void Graphics::beforeFrame()
{
	frameTime = SDL_GetTicks();
}

void Graphics::afterFrame() const
{
	if (SDL_GetTicks() - frameTime < 1000 / FRAMES_PER_SECOND)
		SDL_Delay(1000 / FRAMES_PER_SECOND - (SDL_GetTicks() - frameTime));
}

void Graphics::clear() const
{
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(sdlRenderer);
}

void Graphics::update() const
{
	SDL_RenderPresent(sdlRenderer);
}

void Graphics::drawRect(int x, int y, int width, int height) const
{
	SDL_Rect rect{ OORSPRONG_X+x, OORSPRONG_Y-y, width, height };
	SDL_SetRenderDrawColor(sdlRenderer, 0, 255, 0, SDL_ALPHA_OPAQUE);	//groen
	SDL_RenderFillRect(sdlRenderer, &rect);
}

void Graphics::drawLine(int x, int y) const
{
	SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);	//wit
	SDL_RenderDrawLine(sdlRenderer, OORSPRONG_X, OORSPRONG_Y, OORSPRONG_X+x, OORSPRONG_Y-y);
	//"OORSPRONG_X+x, OORSPRONG_Y-y" vanwege de kanteling van het geheel
}

void Graphics::drawAxis() const
{
	SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);		//rood
	SDL_RenderDrawLine(sdlRenderer, OORSPRONG_X, 0, OORSPRONG_X, MAX_Y);
	SDL_RenderDrawLine(sdlRenderer, 0, OORSPRONG_Y, MAX_X, OORSPRONG_Y);
}

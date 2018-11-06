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
	SDL_Rect rect{ x, y, width, height };
	SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(sdlRenderer, &rect);
}
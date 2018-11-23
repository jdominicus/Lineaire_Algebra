#include "EventManager.h"

#include <SDL2/SDL.h>

EventManager::EventManager() = default;

EventManager::~EventManager() = default;

void EventManager::handleEvents() const
{
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		case SDL_QUIT: {
			for (auto& applicationListener : applicationListeners_)
				applicationListener->quit();
			break;
		}
		case SDL_KEYDOWN:
		{
			KeyEvent keyDownEvent{ sdlEvent };
			for (auto& keyListener : keyListeners_)
				keyListener->onKeyDown(keyDownEvent);
			break;
		}
		case SDL_KEYUP:
		{
			KeyEvent keyUpEvent{ sdlEvent };
			for (auto& keyListener : keyListeners_)
				keyListener->onKeyUp(keyUpEvent);
			break;
		}
		}
	}
}

void EventManager::addApplicationListener(ApplicationListener* applicationListener)
{
	applicationListeners_.emplace_back(applicationListener);
}

void EventManager::addKeyListener(KeyListener* keyListener)
{
	keyListeners_.emplace_back(keyListener);
}

void EventManager::removeAllKeyListeners()
{
	keyListeners_.clear();
}

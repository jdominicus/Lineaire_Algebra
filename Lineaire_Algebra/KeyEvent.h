#pragma once
#include "Event.h"
#include <SDL2/SDL.h>

class KeyEvent : public Event
{
public:
	enum Key { Left, Right, Up, Down, Space, Escape, A, W, S, D, P, F1, F2, F3, F4, F5, F6 };

	KeyEvent(const SDL_Event& sdlKeyEvent);
	~KeyEvent();
	KeyEvent(const KeyEvent& other) = delete;
	KeyEvent(KeyEvent&& other) noexcept = delete;
	KeyEvent& operator=(const KeyEvent& other) = delete;
	KeyEvent& operator=(KeyEvent&& other) noexcept = delete;

	Key key() const;
private:
	Key key_;
};


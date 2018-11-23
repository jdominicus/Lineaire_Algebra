#include "KeyEvent.h"

KeyEvent::KeyEvent(const SDL_Event& sdlKeyEvent)
{
	switch (sdlKeyEvent.key.keysym.sym)
	{
		case SDLK_LEFT: key_ = Left; break;
		case SDLK_RIGHT: key_ = Right; break;
		case SDLK_UP: key_ = Up; break;
		case SDLK_DOWN: key_ = Down; break;
		case SDLK_SPACE: key_ = Space; break;
		case SDLK_ESCAPE: key_ = Escape; break;
		case SDLK_p: key_ = P; break;
		case SDLK_F1: key_ = F1; break; 
		case SDLK_F2: key_ = F2; break;
	}
}

KeyEvent::~KeyEvent() = default;

KeyEvent::Key KeyEvent::key() const
{
	return key_;
}

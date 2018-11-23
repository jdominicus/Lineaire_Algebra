#pragma once
#include <vector>
#include <memory>
#include "ApplicationListener.h"
#include "KeyListener.h"

class Event;

class EventManager
{
public:
	EventManager();
	~EventManager();
	EventManager(const EventManager& other) = default;
	EventManager(EventManager&& other) noexcept = default;
	EventManager& operator=(const EventManager& other) = default;
	EventManager& operator=(EventManager&& other) noexcept = default;

	void handleEvents() const;
	void addApplicationListener(ApplicationListener* applicationListener);
	void addKeyListener(KeyListener* keyListener);
	void removeAllKeyListeners();

private:
	std::vector<ApplicationListener*> applicationListeners_;
	std::vector<KeyListener*> keyListeners_;
};


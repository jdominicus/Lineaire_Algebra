#pragma once

class Event
{
public:
	virtual ~Event();
	Event(const Event& other) = delete;
	Event(Event&& other) noexcept = delete;
	Event& operator=(const Event& other) = delete;
	Event& operator=(Event&& other) noexcept = delete;
protected:
	Event();
};


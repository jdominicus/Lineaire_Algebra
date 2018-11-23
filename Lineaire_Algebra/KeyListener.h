#pragma once
#include "KeyEvent.h"

class KeyListener
{
public:
	virtual ~KeyListener() = default;
	KeyListener(const KeyListener& other) = delete;
	KeyListener(KeyListener&& other) noexcept = delete;
	KeyListener& operator=(const KeyListener& other) = delete;
	KeyListener& operator=(KeyListener&& other) noexcept = delete;

	/**
	 * \brief Actions to be taken when a key is pressed down on the keyboard.
	 * \param keyEvent KeyEvent with the key that is pressed down.
	 */
	virtual void onKeyDown(KeyEvent& keyEvent) = 0;

	/**
	 * \brief Actions to be taken when a key is let go on the keyboard.
	 * \param keyEvent KeyEvent with the key that is let go.
	 */
	virtual void onKeyUp(KeyEvent& keyEvent) = 0;

protected:
	KeyListener() = default;
};

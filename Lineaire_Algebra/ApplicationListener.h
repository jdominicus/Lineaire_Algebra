#pragma once

class ApplicationListener
{
	public:
		virtual ~ApplicationListener() = default;
		ApplicationListener(const ApplicationListener& other) = delete;
		ApplicationListener(ApplicationListener&& other) noexcept = delete;
		ApplicationListener& operator=(const ApplicationListener& other) = delete;
		ApplicationListener& operator=(ApplicationListener&& other) noexcept = delete;

		/**
		 * \brief Actions to be taken when the applications quits.
		 */
		virtual void quit() = 0;

	protected:
		ApplicationListener() = default;
};
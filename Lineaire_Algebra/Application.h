#pragma once

#include "ApplicationListener.h"
#include "KeyListener.h"

#include <memory>

class EventManager;
class Graphics;
class Graph;
class Shape;
class Matrix;

class Application : public ApplicationListener, public KeyListener
{
	public:
		Application();
		~Application();
		void start();
		void quit();
		void render();
		void update();

		void onKeyDown(KeyEvent& keyEvent);
		void onKeyUp(KeyEvent& keyEvent);

	private:
		bool running;
		std::unique_ptr<EventManager> eventManager;
		std::unique_ptr<Graphics> graphics;

		std::unique_ptr<Matrix> matrix;
		std::unique_ptr<Graph> graph;
		std::unique_ptr<Shape> s1;

		const double pi = 3.14159265359;
};


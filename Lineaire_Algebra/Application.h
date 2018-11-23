#pragma once

#include "ApplicationListener.h"

#include <memory>

class EventManager;
class Graphics;
class Matrix;
class Graph;

class Application : public ApplicationListener
{
	public:
		Application();
		~Application();
		void start();
		void quit();
		void render();
		void update();

	private:
		bool running;
		std::unique_ptr<EventManager> eventManager;
		std::unique_ptr<Graphics> graphics;

		std::unique_ptr<Matrix> matrix;
		std::unique_ptr<Matrix> matrix_2;
		std::unique_ptr<Matrix> matrix_3;
		std::unique_ptr<Matrix> matrix_4;
		std::unique_ptr<Matrix> matrix_5;

		std::unique_ptr<Graph> graph;
};


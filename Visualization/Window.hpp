#ifndef PHYSICSSANDBOX_WINDOW_HPP
#define PHYSICSSANDBOX_WINDOW_HPP

// STL
#include <iostream>
#include <string>
#include <memory>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "Camera.hpp"
#include "Input.hpp"
#include "Renderer.hpp"

//class Input;

class Window {
	friend class Input; friend class Camera;
public:
	Window(GLuint width, GLuint height, const std::string name, glm::vec4 clearColor);
	bool GameLoop();

	Renderer& getRenderer() {
		return _renderer;
	}

	Camera& getCamera() {
		return _camera;
	}

	bool WindowShouldClose() {
		return static_cast<bool>(glfwWindowShouldClose(_window));
	}

	void CloseWindow() {
		glfwDestroyWindow(_window);
	}

	~Window() {
		glfwTerminate();
	}

private:
	GLuint _width;
	GLuint _height;
	GLFWwindow* _window;
	Camera _camera;
	Input _input;
	Renderer _renderer;
};


#endif //PHYSICSSANDBOX_WINDOW_HPP

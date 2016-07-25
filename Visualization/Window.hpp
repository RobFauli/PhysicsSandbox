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

class Window {
	friend class Input; friend class Camera;
public:
	Window(GLuint width, GLuint height, const std::string name, glm::vec4 clearColor);
    Window() {};
    void setupWindow(GLuint width, GLuint height, const std::string &name, const glm::vec4 &clearColor);

	bool GameLoop();

    void launchWindow() {
        glfwShowWindow(_window.get());
    }

	Renderer& getRenderer() {
		return _renderer;
	}

	Camera& getCamera() {
		return _camera;
	}

	bool WindowShouldClose() {
		return static_cast<bool>(glfwWindowShouldClose(_window.get()));
	}

	void CloseWindow() {
		glfwDestroyWindow(_window.get());
	}

    ~Window() {
        glfwTerminate();
    }

private:
	GLuint _width;
	GLuint _height;
	std::shared_ptr<GLFWwindow> _window;
	Camera _camera;
	Input _input;
	Renderer _renderer;
};


#endif //PHYSICSSANDBOX_WINDOW_HPP

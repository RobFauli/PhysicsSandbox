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

    void ShowWindow() {
        glfwShowWindow(_window.get());
    }
    void ShowWindow(const int x, const int y) {
        glfwSetWindowPos(_window.get(), x, y);
        glfwShowWindow(_window.get());
    }
    void ShowWindow(GLFWmonitor *monitor) {
        int x, y;
        glfwGetMonitorPos(monitor, &x, &y);
        ShowWindow(x, y);
    }
    void ShowWindow(std::string name) {
        int n;
        auto allMonitors = glfwGetMonitors(&n);
        for (auto i = 0; i<n; ++i) {
            if (name == glfwGetMonitorName(allMonitors[i])) {
                ShowWindow(allMonitors[i]);
                return;
            }
            else
            {}
        }
        ShowWindow(glfwGetPrimaryMonitor());
    }

	Renderer& getRenderer() {
		return _renderer;
	}

	Camera& getCamera() {
		return _camera;
	}

    std::shared_ptr<GLFWwindow> getGLFWwindow() {
        return _window;
    }

	bool WindowShouldClose() {
		return static_cast<bool>(glfwWindowShouldClose(_window.get()));
	}

	void HideWindow() {
        glfwHideWindow(_window.get());
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

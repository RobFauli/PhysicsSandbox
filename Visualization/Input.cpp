//
// Created by robertfa on 16.03.16.
//

#include "Input.hpp"
#include "Window.hpp"

bool Input::_keys[1024];
bool Input::_firstMouse = true;
bool Input::_mouseOn = true;
Camera *Input::_camera = nullptr;
std::shared_ptr<GLFWwindow> Input::_GLFWwindow = nullptr;
float Input::_lastX = 0;
float Input::_lastY = 0;
void Input::key_callback(GLFWwindow *window, int key, int scancode, int action,
						 int mode) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if(action == GLFW_PRESS)
			_keys[key] = true;
		else if(action == GLFW_RELEASE)
			_keys[key] = false;
	}
	do_movement();
}

void Input::do_movement()
{
	// Camera controls
	GLfloat cameraSpeed = 0.05f;
	GLfloat cameraHorSpeed = 0.03f;
	GLfloat cameraRotSpeed = 1.3f;
	if(_keys[GLFW_KEY_W])
		_camera->Position += cameraSpeed * _camera->Front;
	if(_keys[GLFW_KEY_S])
		_camera->Position -= cameraSpeed * _camera->Front;
	if(_keys[GLFW_KEY_A])
		_camera->Position -= glm::normalize(glm::cross(_camera->Front, _camera->Up)) * cameraHorSpeed;
	if(_keys[GLFW_KEY_D])
		_camera->Position += glm::normalize(glm::cross(_camera->Front, _camera->Up)) * cameraHorSpeed;
	if(_keys[GLFW_KEY_Q])
		_camera->Up = glm::rotate(_camera->Up, cameraRotSpeed, _camera->Front);
	if(_keys[GLFW_KEY_E])
		_camera->Up = glm::rotate(_camera->Up, -cameraRotSpeed, _camera->Front);
    if(_keys[GLFW_KEY_TAB]) {
        if (!_mouseOn)
            glfwSetInputMode(_GLFWwindow.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        else {
            glfwSetInputMode(_GLFWwindow.get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            _firstMouse = true;
        }
        _mouseOn = !_mouseOn;
    }

}

void Input::scroll_callback(GLFWwindow *window, double xoffset,
							double yoffset) {
	_camera->ProcessMouseScroll(yoffset);
}

void Input::mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (_mouseOn) {
        if (_firstMouse) {
            _lastX = xpos;
            _lastY = ypos;
            _firstMouse = false;
        }

        GLfloat xoffset = xpos - _lastX;
        GLfloat yoffset = _lastY - ypos;  // Reversed since y-coordinates go from bottom to left

        _lastX = xpos;
        _lastY = ypos;

        _camera->ProcessMouseMovement(xoffset, yoffset);
    }
}

void Input::SetCallbacks() {
	glfwSetKeyCallback(_GLFWwindow.get(), key_callback);
	glfwSetCursorPosCallback(_GLFWwindow.get(), mouse_callback);
	glfwSetScrollCallback(_GLFWwindow.get(), scroll_callback);
}

void Input::SetupInputs(Window *window) {
	_GLFWwindow = window->_window;
	_camera = &window->_camera;

	SetCallbacks();
}

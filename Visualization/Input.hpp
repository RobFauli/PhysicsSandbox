#ifndef PHYSICSSANDBOX_INPUT_HPP
#define PHYSICSSANDBOX_INPUT_HPP

#include <functional>
#include <memory>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/gtx/rotate_vector.hpp>

#include "Camera.hpp"

class Camera;

class Window;

class Input {
public:
	void SetupInputs(Window *window);

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void scroll_callback(GLFWwindow *window, double xoffset,
								double yoffset);
	static void mouse_callback(GLFWwindow *window, double xpos, double ypos);
private:
	void SetCallbacks();
	static void do_movement();
	static bool _keys[1024];
	static bool _firstMouse;
	static Camera* _camera;
	static std::shared_ptr<GLFWwindow>_GLFWwindow;
	static float _lastX;
	static float _lastY;
    static bool _mouseOn;
};


#endif //PHYSICSSANDBOX_INPUT_HPP

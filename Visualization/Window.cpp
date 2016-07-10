#include "Window.hpp"

Window::Window(GLuint width, GLuint height, const std::string name, glm::vec4 clearColor)
 : _height(height), _width(width), _input(Input()) {


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//glfwWindowHint(GLFW_SAMPLES, 4);

	_window = glfwCreateWindow(_width, _height, name.c_str(),
                               nullptr, nullptr); // Windowed
	if (_window == nullptr) {
		std::cerr << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(_window);

	_input.SetupInputs(this);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW." << std::endl;
		exit(-1);
	}

	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);

	// Temp:
	_camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	_renderer = Renderer(_window, clearColor);
}

bool Window::GameLoop() {
	if (!glfwWindowShouldClose(_window)) {
		glfwPollEvents();

        _renderer.draw(_width, _height, _camera.GetViewMatrix(), _camera.Zoom);

		glfwSwapBuffers(_window);

		return true;
	}
	else
		return false;
}

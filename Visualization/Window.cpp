#include "Window.hpp"

Window::Window(GLuint width, GLuint height, const std::string name, glm::vec4 clearColor)
 : _height(height), _width(width) {
    setupWindow(width, height, name, clearColor);
}
void Window::setupWindow(GLuint width,
                         GLuint height,
                         const std::string &name,
                         const glm::vec4 &clearColor)
{
    _width = width;
    _height = height;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    //glfwWindowHint(GLFW_SAMPLES, 4);

    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
    _window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(_width, _height, name.c_str(),
                                                nullptr, nullptr), [](GLFWwindow *w) {glfwDestroyWindow(w);}); // Windowed
    if (_window == nullptr) {
		std::cerr << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		exit(-1);
	}

    glfwMakeContextCurrent(_window.get());

    _input.SetupInputs(this);
    glfwSetInputMode(_window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW." << std::endl;
		exit(-1);
	}

    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    // Temp:
    _camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    _renderer = Renderer();
}

bool Window::GameLoop() {
	if (!glfwWindowShouldClose(_window.get())) {
		glfwPollEvents();

        _renderer.draw(_width, _height, _camera.GetViewMatrix(), _camera.Zoom);

		glfwSwapBuffers(_window.get());

		return true;
	}
	else
		return false;
}

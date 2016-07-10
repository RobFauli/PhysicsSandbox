#include "Shader.hpp"

Shader::Shader(const GLchar *vertexPath, const GLchar *geometryPath, const GLchar *fragmentPath)
{
    _program = glCreateProgram();

    auto vertex = compileAndAttachShader(vertexPath, GL_VERTEX_SHADER);
    auto geometry = compileAndAttachShader(geometryPath, GL_GEOMETRY_SHADER);
    auto fragment = compileAndAttachShader(fragmentPath, GL_FRAGMENT_SHADER);

    GLint success;
    GLchar  infoLog[512];
	glLinkProgram(_program);
	glGetProgramiv(_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->_program, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Delete linked shaders:
	glDeleteShader(vertex);
    glDeleteShader(geometry);
	glDeleteShader(fragment);
}

GLuint Shader::compileAndAttachShader(const GLchar *path, GLenum shaderType)
{
    std::string code;
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::badbit);
    try {
        shaderFile.open(path);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        code = shaderStream.str();
    }
    catch(std::ifstream::failure e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const GLchar* shaderCode = code.c_str();

    // Compile shaders:
    GLuint shader;
    GLint success;
    GLchar infoLog[512];
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::" << _glShaderEnums[shaderType] << "::COMPILATION_FAILED\n"
            << infoLog << std::endl;
    };

    glAttachShader(_program, shader);

    return shader;
}

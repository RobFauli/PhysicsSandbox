#ifndef LEARNOPENGL_SHADER_HPP
#define LEARNOPENGL_SHADER_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include <map>

class Shader {
public:
	Shader() { }
	Shader(const GLchar *vertexPath, const GLchar *geometryPath, const GLchar *fragmentPath);

	void Use() const {
		glUseProgram(_program);
	}

    auto getProgram() const {
        return _program;
    }

private:
    GLuint compileAndAttachShader(const GLchar *path, GLenum shaderType);

    GLuint _program;

    std::map<GLenum, std::string> _glShaderEnums{
        {GL_VERTEX_SHADER, "VERTEX"}, {GL_TESS_CONTROL_SHADER, "TESS_CONTROL"},
        {GL_TESS_EVALUATION_SHADER, "TESS_EVALUATION"},
        {GL_GEOMETRY_SHADER, "GEOMETRY"}, {GL_FRAGMENT_SHADER, "FRAGMENT"},
        {GL_COMPUTE_SHADER, "COMPUTE"},
    };
};

#endif //LEARNOPENGL_SHADER_HPP

// Simple vertex shader in GLSL.

#version 330 core

layout (location = 0) in vec3 position;

out VS_OUT {
    vec3 color;
    vec3 fragPos;
    mat4 model;
} vs_out;

uniform vec3 uniColor;

uniform mat4 model;

void main()
{
	gl_Position = model * vec4(position, 1.0f);
	vs_out.color = uniColor;
	vs_out.fragPos = vec3(gl_Position);
	vs_out.model = model;
}

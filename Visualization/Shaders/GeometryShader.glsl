#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec3 color;
    vec3 fragPos;
    mat4 model;
} gs_in[];

out GS_OUT {
    vec3 color;
    vec3 fragPos;
    vec3 normal;
} fs_in;

uniform mat4 projection;
uniform mat4 view;

void main() {

    // Using counterclockwise winding the normal points up from the surface
    vec3 a = vec3(gl_in[1].gl_Position) - vec3(gl_in[0].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[0].gl_Position);
    vec3 N = normalize(cross(b, a));

    for (int i = 0; i<gl_in.length(); ++i) {
        gl_Position = projection * view * gl_in[i].gl_Position;
        fs_in.color = gs_in[0].color;
        fs_in.fragPos = gs_in[0].fragPos;
        fs_in.normal = N;
        EmitVertex();
    }
}

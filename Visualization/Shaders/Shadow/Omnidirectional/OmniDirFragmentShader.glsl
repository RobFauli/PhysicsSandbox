#version 330 core

in vec4 fragPos;

uniform vec3 lightPos;
uniform float far_plane;

void main() {
    // find distance between fragment and light source
    float lightDistance = length(fragPos.xyz - lightPos);

    // map to [0,1] range by dividing by far_plane
    lightDistance = lightDistance / far_plane;

    // Write this as modified depth
    gl_FragDepth = lightDistance;

}

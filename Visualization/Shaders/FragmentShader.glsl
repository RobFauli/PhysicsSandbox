#version 330 core

in GS_OUT {
    vec3 color;
    vec3 fragPos;
    vec3 normal; // Normalized
} fs_in;

out vec4 color;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float ambientFactor;

// Shadow related uniforms
uniform samplerCube depthMap;
uniform float far_plane;

float ShadowCoefficient(vec3 fragPos)
{
    vec3 fragToLight = fragPos - lightPos;
    float closestDepth = texture(depthMap, fragToLight).r;
    closestDepth *= far_plane;
    float currentDepth = length(fragToLight);
    float bias = 0.05;
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    return shadow;
    //return closestDepth;
}

void main() {
    vec3 lightDir = normalize(lightPos - fs_in.fragPos);

    float diff = max(dot(fs_in.normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float shadow = ShadowCoefficient(fs_in.fragPos);
    vec3 result = (ambientFactor + (1.0 - shadow) * diffuse) * fs_in.color;

    color = vec4(result, 1.0f);
    //color = vec4(vec3(shadow / 100e2*far_plane), 1.0f);

    //vec3 fragToLight = fs_in.fragPos - lightPos;
    //color = vec4(texture(depthMap, fragToLight), 1.0);
}

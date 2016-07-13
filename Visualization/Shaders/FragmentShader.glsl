#version 400 core

in GS_OUT {
    vec3 color;
    vec3 fragPos;
    vec3 normal; // Normalized
} fs_in;

out vec4 color;

uniform uint nPointLights;
uniform vec3 pointLightPos[10]; // Maximum 10 point lights
uniform vec3 lightColor;
uniform float ambientFactor;

// Shadow related uniforms
uniform samplerCube depthMaps[10];
uniform float far_plane;

float ShadowCoefficient(vec3 fragPos, vec3 lightPos, samplerCube depthMap)
{
    vec3 fragToLight = fragPos - lightPos;
    float closestDepth = texture(depthMap, fragToLight).r;
    closestDepth *= far_plane;
    float currentDepth = length(fragToLight);
    float bias = 0.5;
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    return shadow;
}

vec3 calculatePointLight(vec3 lightPos, samplerCube depthMap)
{
    vec3 lightDir = normalize(lightPos - fs_in.fragPos);
    float diff = max(dot(fs_in.normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float shadow = ShadowCoefficient(fs_in.fragPos, lightPos, depthMap);

    vec3 result = (ambientFactor + (1.0 - shadow) * diffuse) * fs_in.color;

    return result;
}

void main() {
    vec3 result = vec3(0.0f);
    for (uint i = 0u; i < nPointLights; ++i)
        result += calculatePointLight(pointLightPos[0], depthMaps[i]);
    color = vec4(result, 1.0f);
}

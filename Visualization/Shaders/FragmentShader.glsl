#version 400 core

in GS_OUT {
    vec3 color;
    vec3 fragPos;
    vec3 normal; // Normalized
} fs_in;

out vec4 color;

uniform uint nPointLights;
uniform vec3 pointLightPos[10]; // Maximum 10 point lights
uniform vec3 lightColors[10];
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

vec3 calculatePointLight(uint n)
{
    vec3 lightDir = normalize(pointLightPos[n] - fs_in.fragPos);
    float diff = max(dot(fs_in.normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColors[n];

    float shadow = ShadowCoefficient(fs_in.fragPos, pointLightPos[n], depthMaps[n]);

    vec3 result = (ambientFactor + (1.0 - shadow) * diffuse) * fs_in.color;

    return result;
}

void main() {
    vec3 result = vec3(0.0f);
    if (nPointLights != 0)
        for (uint i = 0u; i < nPointLights; ++i)
            result += calculatePointLight(i);
    else
        result += ambientFactor*fs_in.color;
    color = vec4(result, 1.0f);
}

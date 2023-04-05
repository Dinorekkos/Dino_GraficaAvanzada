#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;

out vec2 fragTexCoord;
out vec3 fragTangentLightPos;
out vec3 fragTangentViewDir;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);

    // Pass the texture coordinates and transformed tangent vector to the fragment shader
    fragTexCoord = texCoord;
    fragTangentLightPos = vec3(view * model * vec4(position, 1.0)) - vec3(view * model * vec4(tangent, 0.0));
    fragTangentViewDir = vec3(view * model * vec4(position, 1.0));
}

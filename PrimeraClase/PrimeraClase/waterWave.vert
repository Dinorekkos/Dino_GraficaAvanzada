#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
out vec3 color;
out vec2 v_texCoord;

void main() {
    vec3 pos = vec3(
        aPos.x + aPos.x,
        aPos.y + aPos.y,
        aPos.z + aPos.z
    );

    gl_Position = vec4(pos, 1.0);

    v_texCoord = aTex;
    color = aColor;
}
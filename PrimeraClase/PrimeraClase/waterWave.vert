#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
out vec3 color;
out vec2 v_texCoord;

void main() {
     gl_Position = vec4(
        aPos.x + aPos.x,
        aPos.y + aPos.y,
        aPos.z + aPos.z, 1.0f);
     
     color = aColor;
    v_texCoord = aTex;
}
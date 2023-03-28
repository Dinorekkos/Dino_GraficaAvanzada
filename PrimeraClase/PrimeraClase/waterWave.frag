#version 330 core

in vec2 v_texCoord;
out vec4 FragColor;

uniform sampler2D inputImageTexture;
uniform float timeWave;
uniform float speed;
uniform float amplitude;
uniform float frequency;

void main()
{
    vec2 uv = v_texCoord;
    uv.y += (sin(uv.x * frequency + timeWave * speed) * amplitude);
    vec4 pixel = texture(inputImageTexture, uv);
    FragColor = pixel;
}

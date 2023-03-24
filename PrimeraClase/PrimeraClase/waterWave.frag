#version 100

in vec2 textureCoordinate;
uniform sampler2D inputImageTexture;
uniform float timeWave;
uniform vec2 resolution;

void main() {

    vec2 uv = textureCoordinate.xy;
    uv.y += sin(uv.x * 10.0 + timeWave) * 0.05;
    vec4 FragColor = texture(inputImageTexture, uv);
    
}
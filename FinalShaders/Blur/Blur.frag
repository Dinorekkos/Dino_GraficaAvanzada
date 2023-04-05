// Frag
#version 330 core
in vec2 v_texCoord;
out vec4 FragColor;

uniform sampler2D tex0;
uniform float blurAmount;
uniform float blurDirY;
uniform float blurDirX;

void main() {

    vec4 color = vec4(0.0);
    vec2 texSize = vec2(textureSize(tex0, 0));

    float blurSize = blurAmount * 5.0f;

    // Calculate the step size for the current direction
    vec2 stepX = vec2(blurDirX, 0.0) / texSize * blurSize;
    vec2 stepY = vec2(0.0, blurDirY) / texSize * blurSize;

    // Perform separable convolution for the horizontal direction
    for (float i = -blurSize; i <= blurSize; i++) {
        vec2 offset = stepX * i;
        color += texture(tex0, v_texCoord + offset) * (1.0 / (2.0 * blurSize + 1.0));
    }
    // Perform separable convolution for the vertical direction
    for (float i = -blurSize; i <= blurSize; i++) {
        vec2 offset = stepY * i;
        color += texture(tex0, v_texCoord + offset) * (1.0 / (2.0 * blurSize + 1.0));
    }
    FragColor = color;
}
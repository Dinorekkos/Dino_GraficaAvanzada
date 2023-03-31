#version 330 core
in vec2 v_texcoord;
out vec4 FragColor;

uniform sampler2D u_texture;
uniform float blurDirY;
uniform float blurDirx;
uniform float blurAmount;

void main() {
    
    vec4 color = vec4(0.0);
    vec2 texSize = vec2(textureSize(u_texture, 0));
    
    float blurSize = blurAmount * 5.0f;

    // Calculate the step size for the current direction
    vec2 stepX = vec2(blurDirx, 0.0) / texSize * blurSize;
    vec2 stepY = vec2(0.0, blurDirY) / texSize * blurSize;

    // Perform separable convolution for the horizontal direction
    for (float i = -blurSize; i <= blurSize; i++) {
        vec2 offset = stepX * i;
        color += texture2D(uTexture, vTexCoord + offset) * (1.0 / (2.0 * blurSize + 1.0));
    }
    // Perform separable convolution for the vertical direction
    for (float i = -blurSize; i <= blurSize; i++) {
        vec2 offset = stepY * i;
        color += texture2D(uTexture, vTexCoord + offset) * (1.0 / (2.0 * blurSize + 1.0));
    }
    FragColor = color;
}
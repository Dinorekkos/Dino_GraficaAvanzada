#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D baseTexture;
uniform sampler2D dissolveTexture;
uniform float dissolveFactor;

void main()
{
    // Muestreamos los colores de las dos texturas en las coordenadas de textura
    vec4 baseColor = texture(baseTexture, TexCoord);
    vec4 dissolveColor = texture(dissolveTexture, TexCoord);

    // Calculamos la cantidad de disolución basada en la textura de disolución
    float dissolveAmount = (dissolveColor.r + dissolveColor.g + dissolveColor.b) / 3.0;
    dissolveAmount = smoothstep(dissolveFactor - 0.1, dissolveFactor + 0.1, dissolveAmount);

    // Mezclamos los colores de las dos texturas basados en la cantidad de disolución
    FragColor = mix(baseColor, dissolveColor, dissolveAmount);
}
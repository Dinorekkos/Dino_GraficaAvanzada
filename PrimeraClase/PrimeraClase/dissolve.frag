#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D baseTexture;
uniform sampler2D dissolveTexture;
uniform float dissolveFactor;
uniform float time;
uniform float amplitude;

void main()
{
    // Calculamos la cantidad de disolución basada en la textura de disolución
    vec4 dissolveColor = texture(dissolveTexture, TexCoord);
    float dissolveAmount = (dissolveColor.r + dissolveColor.g + dissolveColor.b) / 3.0;
    dissolveAmount = smoothstep(dissolveFactor - 0.1, dissolveFactor + 0.1, dissolveAmount);

    // Agregamos una onda sinusoidal para hacer que el efecto sea constante en el tiempo
    float wave = sin(time) * amplitude;
    dissolveAmount += wave;

    // Mezclamos los colores de las dos texturas basados en la cantidad de disolución
    vec4 baseColor = texture(baseTexture, TexCoord);
    FragColor = mix(baseColor, dissolveColor, dissolveAmount);
}

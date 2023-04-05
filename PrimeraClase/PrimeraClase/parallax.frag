#version 330 core

in vec2 fragTexCoord;
in vec3 fragTangentLightPos;
in vec3 fragTangentViewDir;

out vec4 fragColor;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;

uniform float lightPosX;
uniform float lightPosY;
uniform float lightPosZ;
uniform float heightScale;
uniform float parallaxLayers;

void main()
{
    // Get the tangent space normal from the normal map
    vec3 normal = normalize(texture(normalMap, fragTexCoord).rgb * 2.0 - 1.0);

    // Compute the view direction in tangent space
    vec3 viewDir = normalize(fragTangentViewDir);

    // Compute the light direction in tangent space
    vec3 lightDir = normalize(fragTangentLightPos - vec3(lightPosX, lightPosY, lightPosZ));

    // Compute the reflection vector in tangent space
    vec3 reflection = reflect(-lightDir, normal);

    // Compute the texture coordinates for parallax mapping
    float numLayers = parallaxLayers;
    float layerHeight = 1.0 / numLayers;
    float currentLayerHeight = 0.0;
    vec2 deltaTexCoord = heightScale * viewDir.xy / viewDir.z / numLayers;
    vec2 parallaxTexCoord = fragTexCoord;

    // Perform parallax mapping by stepping through the layers
    for (int i = 0; i < 30; i++)
    {
        // Sample the height map to get the height value
        float height = texture(normalMap, parallaxTexCoord).r;

        // Adjust the texture coordinates based on the height value
        parallaxTexCoord -= deltaTexCoord;

        // Update the current layer height
        currentLayerHeight += layerHeight;

        // Exit the loop if the current layer height is greater than the height value
        if (currentLayerHeight > height)
        {
            break;
        }
    }

    // Use the final texture coordinates to sample the diffuse map
    vec3 diffuse = texture(diffuseMap, parallaxTexCoord).rgb;

    // Output the final color
    fragColor = vec4(diffuse, 1.0);
}

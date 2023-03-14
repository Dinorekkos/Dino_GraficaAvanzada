#version 330 core
layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec3 aColor;

out vec3 color;
uniform float scale;


void main()
{
   gl_Position = vec4((aPos.x + aPos.x * scale) * 0.3f, 
					  (aPos.y + aPos.y * scale) * 0.3f, 
                      (aPos.z + aPos.z * scale) * 0.3f, 1.0);
   
   color = aColor;
}
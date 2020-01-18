#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec4 lightColor;

void main()
{
  FragColor = vec4(lightColor * objectColor, 1.0);
}

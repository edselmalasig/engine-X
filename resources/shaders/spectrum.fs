#version 330 core
//in vec2 TexCoord;

out vec4 color;
uniform vec4 incolor;
//uniform sampler2D ourTexture1;
//uniform sampler2D ourTexture2;

void main()
{
    color = incolor; // vec4(1.0f, 0.3f, 0.3f, 1.0f); //mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
}

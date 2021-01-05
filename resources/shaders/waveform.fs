#version 330 core
//in vec2 TexCoord;

out vec4 color;
uniform sampler2D objtexture;
in vec4 f_color;
uniform float sprite;

void main()
{
    if(sprite > 1.0)
        color = f_color;
    else
        color = f_color;
}

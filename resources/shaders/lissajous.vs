#version 330 core
layout (location = 0) in vec3 position;
//layout (location = 2) in vec2 texCoord;

//out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec4 f_color;
uniform lowp float sprite;
in float time;
void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);

    f_color = vec4(sin(time) * position.x / 2.0 + 0.2, sin(time) * position.y / 2.0 + 0.2, 1, 1);
}

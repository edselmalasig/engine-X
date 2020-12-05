

#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    //gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
    gl_Position = projection * view * model * vec4(vertex.xy * vec2(2.0/800,2.0/600) - vec2(1,1), 0.0f, 1.0f);

    TexCoords = vertex.zw;
}

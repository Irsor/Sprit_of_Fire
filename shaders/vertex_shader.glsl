#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec4 outColor;

void main()
{
    gl_Position = vec4(position, 1.0);
    outColor = vec4(color, 1.0f);
}
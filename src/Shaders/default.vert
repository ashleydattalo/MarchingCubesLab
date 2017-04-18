#version 330 core
layout (location = 0) in vec3 pos;

uniform float offset;
uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 ourColor;
out vec3 position;

void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0f);
    gl_PointSize = 2;
}
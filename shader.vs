#version 130

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

in vec2 position;

void main()
{
    gl_Position = proj*view*model*vec4(position, 0.0, 1.0);
}


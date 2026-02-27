#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 object;
void main()
{
   gl_Position = object * vec4(aPos, 1.0);
}
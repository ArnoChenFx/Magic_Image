#version 460 core
out vec4 FragColor;
in vec3 lineColor;
void main()
{
   FragColor = vec4(lineColor,1);
}
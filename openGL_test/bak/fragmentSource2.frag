#version 460 core
//读取闪烁green,读取uniform数据
out vec4 FragColor;
uniform float ourColor;

void main()
{
   FragColor = vec4(0,ourColor,0,1);
}
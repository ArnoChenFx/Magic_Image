#version 460 core
//读取颜色,并赋予给outColor属性,给fragment shader调用
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 ourColor;

void main()
{
   gl_Position = vec4(aPos, 1.0);
   ourColor = aColor;
}
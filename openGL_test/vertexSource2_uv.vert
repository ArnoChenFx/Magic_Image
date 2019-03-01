#version 460 core
//��ȡ��ɫ,�������outColor����,��fragment shader����
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 transform;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;
uniform mat4 model;

out vec3 ourColor;
out vec2 TexCoord;


void main()
{
   gl_Position = projMat * viewMat *model* vec4(aPos, 1.0);
   ourColor = aColor;
   TexCoord = aTexCoord;
}
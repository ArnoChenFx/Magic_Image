#version 460 core
//��ȡ��ɫ,�������outColor����,��fragment shader����
layout (location = 0) in vec3 aPos;
layout (location = 1) in float aCol;
out vec3 lineColor;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;
uniform float Color;

void main()
{
   gl_Position = projMat * viewMat *modelMat* vec4(aPos, 1.0);
  // lineColor = vec3(aCol,aCol,aCol);
  lineColor = vec3(Color,Color,Color);
}
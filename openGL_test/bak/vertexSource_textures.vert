#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec4 aColor;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main()
{
    TexCoords = aTexCoords;    
	gl_Position = projMat * viewMat *modelMat* vec4(aPos, 1.0);
	aColor = vec4(aNormal,1);
}
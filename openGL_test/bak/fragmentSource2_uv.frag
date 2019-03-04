#version 460 core
//读取vertex的属性,根据texture函数读取图像颜色
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;
uniform sampler2D ourTextureA;
uniform sampler2D ourTextureB;

vec4 adgustGamma(vec4 color,float gamma)
{
	float f = 1/gamma;//gamma
	vec4 result = vec4(pow(color.x,f),pow(color.y,f),pow(color.z,f),1);
	return result;
}

void main()
{
	//FragColor = vec4(ourColor, 1.0);
	vec4 a = texture(ourTextureA,TexCoord);
	vec4 b = texture(ourTextureB,TexCoord);

	FragColor = b.w>0 ? a*b*1.2 : a;

}

#version 330

#define PI 3.1415926535897932384626433832795
#define DOUBLE_PI 6.283185307179586476925286766559

in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D bitmap;
uniform float time;

void main()
{
	vec2 uv = texCoord;

	FragColor = texture(bitmap, uv);
}
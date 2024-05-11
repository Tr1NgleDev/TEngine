#version 330

#define PI 3.1415926535897932384626433832795
#define DOUBLE_PI 6.283185307179586476925286766559

in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D bitmap;
uniform vec4 color;
uniform float time;
uniform vec2 flip;

void main()
{
	vec2 uv = texCoord;
	if(flip.x > 0.5)
		uv.x = 1.0 - uv.x;
	if(flip.y > 0.5)
		uv.y = 1.0 - uv.y;

	FragColor = texture(bitmap, uv) * color;
}
#version 330

#define PI 3.1415926535897932384626433832795
#define DOUBLE_PI 6.283185307179586476925286766559

in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D bitmap;
uniform vec4 color;
uniform float time;
uniform vec2 flip;
uniform ivec4 frame;
uniform ivec2 texSize;

float remap(float v, float inMin, float inMax, float outMin, float outMax)
{
	return (v - inMin) * ((outMax - outMin) / (inMax - inMin)) + outMin;
}

void main()
{
	vec2 uv = texCoord;
	if(flip.x > 0.5)
		uv.x = 1.0 - uv.x;
	if(flip.y > 0.5)
		uv.y = 1.0 - uv.y;

	// frame shit
	float minX = float(frame.x) / float(texSize.x);
	float minY = float(frame.y) / float(texSize.y);
	float maxX = minX + float(frame.z) / float(texSize.x);
	float maxY = minY + float(frame.w) / float(texSize.y);
	uv.x = remap(uv.x, 0.0, 1.0, minX, maxX);
	uv.y = remap(uv.y, 0.0, 1.0, minY, maxY);
	
	FragColor = texture(bitmap, uv) * color;
	//FragColor = vec4(uv, 1.0, 1.0);
}
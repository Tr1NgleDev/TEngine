#version 330

vec2 rotate(vec2 v, float a) 
{
	float s = sin(a);
	float c = cos(a);
	mat2 m = mat2(c, s, -s, c);
	return m * v;
}

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;

out vec2 texCoord;

uniform mat4 projection;
uniform mat4 view;
//uniform mat4 transform;

// transform values lol!
uniform vec2 scale;
uniform vec2 offset;
uniform vec2 position;
uniform float angle;
uniform float targetScale;
uniform bool pixelPerfect;

void main()
{
	texCoord = aUV;

	vec2 pos = aPos;

	// translate
	pos *= (!pixelPerfect ? scale : floor(scale));
	pos += (!pixelPerfect ? (offset * scale) : floor(offset * scale));
	if(angle != 0)
	pos = rotate(pos, angle);
	pos += (!pixelPerfect ? position : floor(position));
	pos *= vec2(targetScale);

	gl_Position = projection * view * vec4(pos, 0.0, 1.0);
}
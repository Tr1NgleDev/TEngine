#version 330 core

vec2 rotate(vec2 v, float a) 
{
	float s = sin(a);
	float c = cos(a);
	mat2 m = mat2(c, s, -s, c);
	return m * v;
}

// holy moly
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;
// instancing bs
layout (location = 2) in vec4 scaleOffset;
layout (location = 3) in vec3 positionAngle;
layout (location = 4) in int textureID;
layout (location = 5) in vec4 colorA;
layout (location = 6) in vec2 flipA;
// animSprite
layout(location = 7) in ivec4 frameA;
layout(location = 8) in ivec2 texSizeA;

out vec2 texCoord;
out vec4 color;
out vec2 flip;
out int bitmapID;
out ivec4 frame;
out ivec2 texSize;

// this stuff is per state
uniform mat4 projection;
uniform mat4 view;
uniform float targetScale;
uniform bool pixelPerfect;

void main()
{
	// fragment shader stuff
	bitmapID = textureID;
	color = colorA;
	flip = flipA;
	texCoord = aUV;
	// animSprite
	frame = frameA;
	texSize = texSizeA;
	
	// extract bs from input
	const vec2 scale = scaleOffset.xy;
	const vec2 offset = scaleOffset.zw;
	const vec2 position = positionAngle.xy;
	const float angle = positionAngle.z;

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
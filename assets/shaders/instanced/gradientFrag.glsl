#version 330 core

#define PI 3.1415926535897932384626433832795
#define DOUBLE_PI 6.283185307179586476925286766559

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2DArray bitmaps;

in int bitmapID;
in vec4 color;
uniform float time;
in vec2 flip;

in vec4 colorA;
in vec4 colorB;
in float gScale;
in float gOffset;

void main()
{
	vec2 uv = texCoord;
	if(flip.x > 0.5)
		uv.x = 1.0 - uv.x;
	if(flip.y > 0.5)
		uv.y = 1.0 - uv.y;

	vec4 col = texture(bitmaps, vec3(uv, bitmapID));
	vec4 gradientCol = vec4(mix(colorA.xyz * colorA.w, colorB.xyz * colorB.w, uv.y * gScale + gOffset), mix(colorA.w, colorB.w, uv.y * gScale + gOffset));

	gradientCol.xyz *= col.xyz * col.a;

	FragColor = gradientCol * color;
}
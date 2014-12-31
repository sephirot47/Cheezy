#version 130

uniform float multiplier;
uniform vec4 mec;

attribute vec4 pos;
attribute vec2 uv;
attribute vec4 normal;

varying vec2 uvFrag;
varying vec4 tint;

void main()
{
	vec4 position = pos + vec4(vec3(normal.xyz) * multiplier, 0.0);
	gl_Position = gl_ModelViewProjectionMatrix * position;
	uvFrag = uv;
	tint = mec;
}

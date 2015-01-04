#version 130

attribute vec4 normal;
attribute vec4 pos;
attribute vec2 uv;

uniform vec4 mec;
uniform float multiplier;

varying vec2 uvFrag;
varying vec4 tint;

void main()
{
	vec4 position = pos + vec4(vec3(normal.xyz) * multiplier * 0.5, 0.0);
	gl_Position = gl_ModelViewProjectionMatrix * position;
	uvFrag = uv;
	tint = mec;
}

#version 130

attribute vec4 pos;
attribute vec2 uv;
attribute vec4 normal;

varying vec2 uvFrag;

void main()
{
	vec4 position = pos + vec4(vec3(normal.xyz) * 1.5f, 0.0);
	gl_Position = gl_ModelViewProjectionMatrix * position;
	uvFrag = uv;
}

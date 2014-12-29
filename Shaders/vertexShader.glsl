#version 130

attribute vec2 uv;
attribute vec4 pos;

varying vec2 uvFrag;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * pos;
	uvFrag = uv;
}

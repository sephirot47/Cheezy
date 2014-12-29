#version 130

attribute vec4 pos;
attribute vec2 uv;

varying vec2 uvFrag;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * pos;
	uvFrag = uv;
}

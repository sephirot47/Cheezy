#version 130

uniform sampler2D tex;

attribute vec4 pos;
attribute vec2 uvIn;

varying vec2 uv;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * pos;
	uv = uvIn;
}

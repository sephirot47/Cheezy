#version 130

uniform sampler2D tex;
uniform float mixing;

varying vec2 uvFrag;
varying vec4 tint;
varying float intensity;

void main()
{	
	gl_FragColor = vec4(uvFrag.x, uvFrag.y, 0.0, 1.0) * intensity;
}

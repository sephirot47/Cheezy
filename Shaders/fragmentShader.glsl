#version 130

uniform sampler2D tex;
uniform float mixing;

varying vec2 uvFrag;
varying vec4 tint;

void main()
{	
	gl_FragColor = mix(tint, texture2D(tex, vec2(uvFrag.x, 1.0 - uvFrag.y)), mixing);
	gl_FragColor = vec4(uvFrag.x, uvFrag.y, 0.0, 1.0);
}

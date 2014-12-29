#version 130

uniform sampler2D tex;

varying vec2 uvFrag;

void main()
{	
	gl_FragColor = texture2D(tex, vec2(uvFrag.x, 1.0 - uvFrag.y));
}

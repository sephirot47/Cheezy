#version 130

varying vec2 uvFrag;

void main()
{	
	gl_FragColor = vec4(sin(uvFrag.x), cos(uvFrag.y), 0, 1);
}

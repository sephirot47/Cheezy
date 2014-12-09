#version 130

in vec2 uv;

out vec4 colorOut;

void main()
{
	//colorOut = vec4(sin(gl_FragCoord.x/300), cos(gl_FragCoord.y/300), cos(gl_FragCoord.x/300), 1.0);

	colorOut = vec4(uv.x, 0, 0, 1);
}

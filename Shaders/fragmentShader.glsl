#version 130
 
void main()
{
	gl_FragColor = vec4(sin(gl_FragCoord.x/300), cos(gl_FragCoord.y/300), cos(gl_FragCoord.x/300), 1.0);
}

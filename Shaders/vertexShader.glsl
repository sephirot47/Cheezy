#version 130

in vec4 pos; //0
in vec2 uv;  //1

out vec2 uvOut;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * pos;
	uvOut = uv;
}

#version 130

uniform sampler2D tex;

varying vec2 uv;

void main()
{
	vec4 texel = texture2D(tex, uv);
	gl_FragColor = vec4(texel.r, texel.g, texel.b, 1);
}

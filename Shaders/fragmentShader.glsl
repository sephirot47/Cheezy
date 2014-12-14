#version 130

uniform sampler2D tex;
varying vec2 uv;

void main()
{	
	vec2 nUv;
	nUv.x = uv.x;
	nUv.y = 1.0 - uv.y;

	vec4 texel = texture2D(tex, nUv);
	gl_FragColor = vec4(texel.r, texel.g, texel.b, 1);
}

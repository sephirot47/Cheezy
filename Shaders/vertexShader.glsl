#version 130

attribute vec4 normal;
attribute vec4 pos;
attribute vec2 uv;

uniform vec4 mec;
uniform float multiplier;

varying vec2 uvFrag;
varying vec4 tint;
varying float intensity;

void main()
{
	vec3 lightPos = vec3(10.0, 10.0, 10.0);
	vec3 toLight = normalize(lightPos - vec3(pos.x, pos.y, pos.z));
	intensity = clamp(dot(vec3(pos.x, pos.y, pos.z), toLight), 0, 1); 

	vec4 position = pos + vec4(vec3(normal.xyz) * multiplier * 0.5, 0.0);
	gl_Position = gl_ModelViewProjectionMatrix * position;
	uvFrag = uv;
	tint = mec;
}

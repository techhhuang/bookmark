#version 100
precision mediump float;   

uniform float time;
varying vec4 v_color;
#define WAVES 1.0

void main (void)
{
  vec2 uv =  vec2(gl_FragCoord.xy/vec2(800.0,600.0));

	float t = time * 0.05;
	
	vec3 color = vec3(0.0);

	for (float i=0.0; i<WAVES + 1.0; i++) {
		float freq = 0.1 * 7.0;

		vec2 p = vec2(uv);

		p.x += i * 0.04 + freq * 0.03;
		p.y += sin(p.x * 10.0 + t) * cos(p.x * 2.0) * freq * 0.2 * ((i + 1.0) / WAVES);
		float intensity = abs(0.01 / p.y) * clamp(freq, 0.35, 2.0);
		color += vec3(1.0 * intensity * (i / 5.0), 0.5 * intensity, 1.75 * intensity) * (3.0 / WAVES);
	}

	gl_FragColor = vec4(color, 1.0);
}
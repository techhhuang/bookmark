#version 100 
precision mediump float;   
uniform float time;
vec4 line_color = vec4(1.0, 1.0, 1.0, 1.0);
float border = 0.01;
varying vec4 v_color;
void main (void)
{
  vec2 uv = 2.0*vec2(gl_FragCoord.xy/vec2(800.0,600.0)) -1.0;
  float y = 0.2*sin(20.0*uv.x+time/50.0);
  
  float a = 1.0 + smoothstep(uv.y, uv.y+border, y)-smoothstep(uv.y-border,uv.y,y);

  gl_FragColor= mix(v_color,line_color,a);

}
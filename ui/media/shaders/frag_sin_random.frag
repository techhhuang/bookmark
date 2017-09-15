#version 100 
precision mediump float;   
uniform float time;
vec4 line_color = vec4(1.0, 1.0, 1.0, 1.0);
float border = 0.01;
varying vec4 v_color;
void main (void)
{
  vec2 uv = 2.0*vec2(gl_FragCoord.xy/vec2(800.0,600.0)) -1.0;
  float y,a=0.0;
  for(float i=1.0; i<4.0;i++){
    y = i*0.2*sin(10.0*i*uv.x+time/50.0+i);
    a += smoothstep(uv.y-border,uv.y,y)-smoothstep(uv.y, uv.y+border, y);
  }

  gl_FragColor= mix(v_color,line_color,a);

}
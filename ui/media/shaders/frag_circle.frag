  #version 100 
precision mediump float;   
float border=0.01;
float circle_radius=0.1;
vec4 circle_color = vec4(1.0, 1.0, 1.0, 1.0);
vec2 circle_center = vec2(0.5, 0.5);
varying vec4 v_color;
void main (void)
{
    vec2 uv = vec2(gl_FragCoord.xy/vec2(800.0,600.0));
    uv -= circle_center;
    float dist =  length(uv);
    float a = smoothstep(circle_radius,circle_radius+border,dist);

    gl_FragColor = mix(circle_color,v_color,a);

  
}

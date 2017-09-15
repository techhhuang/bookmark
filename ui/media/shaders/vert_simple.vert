#version 100
precision mediump float;
uniform float time;
attribute vec4 position;
attribute vec4 color;
varying vec4 v_color;
float M_PI = 3.14159265358;

mat4 rotate(float time){
  float angle = time* M_PI / 180.0;
  mat4 rotation=mat4(1);
  rotation[0][0] = cos(angle);
  rotation[0][2] = sin(angle);
  rotation[2][0] = -sin(angle);
  rotation[2][2] = cos(angle);
  return rotation;
}

mat4 move(float time){
  mat4 rotation=mat4(1);
  rotation[3][0] = time/360.0;
  return rotation;
}


void main() {
  
  gl_Position =position;
  v_color = color;
}


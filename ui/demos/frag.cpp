#include <LoadShaders.h>
#include <SmartPlatform.h>
#include <assert.h>
#include <stdio.h>
#include <sys/time.h>

GLuint uniform_time;
void draw() {
  static const GLfloat verts[4][2] = {
      {-1.0, 1.0}, {-1.0, -1.0}, {1.0, -1.0}, {1.0, 1.0}};
  static const GLfloat colors[4][3] = {
      {1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 0, 1}};

  long long time = 0;
  struct timeval tv;
  gettimeofday(&tv, NULL);
  time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
  time = (time / 5) % 36000;
  printf("time:%lld\n", time);
  glUniform1f(uniform_time, (GLfloat)time);

  glViewport(0, 0, WIDTH, HEIGHT);
  glClearColor(0.0, 0.0, 0.0, 0.5);
  glClear(GL_COLOR_BUFFER_BIT);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, verts);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

void init_gl() {
  printf("init gl start\n");

  ShaderInfo shaders[] = {
      {GL_VERTEX_SHADER, "media/shaders/vert_simple.vert"},
      {GL_FRAGMENT_SHADER, "media/shaders/frag_sin_random.frag"},
      {GL_NONE, NULL}};

  GLuint program = LoadShaders(shaders);
  assert(program);

  glUseProgram(program);

  glBindAttribLocation(program, 0, "position");
  glBindAttribLocation(program, 1, "color");

  uniform_time = glGetUniformLocation(program, "time");

  printf("init gl end\n");
}

int main(int argc, char **argv) {
  smart_platform_init();
  init_gl();

  while (!smart_platform_shoud_close()) {
    draw();
    smart_platform_swap_buffer();
  }
  smart_platform_terminate();
}

#include <SmartPlatform.h>
#include <assert.h>
#include <stdio.h>

#include <GLES2/gl2.h>
#define NANOVG_GLES2_IMPLEMENTATION  // Use GL2 implementation.
#include "nanovg.h"
#include "nanovg_gl.h"
// #include "nanovg_gl_utils.h"
struct NVGcontext* vg;

#include <SmartUI.h>

void init_gl() {
  glViewport(0, 0, WIDTH, HEIGHT);
  glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);
}
void draw() {
  init_gl();
  nvgBeginFrame(vg, WIDTH, HEIGHT, 1);

  nvgBeginPath(vg);
  // nvgRect(vg, 200, 200, 120, 120);
  // nvgCircle(vg, 160, 160, 30);
  // // nvgPathWinding(vg, NVG_HOLE);  // Mark circle as a hole.
  // nvgFillColor(vg, nvgRGBA(255, 192, 0, 255));
  // nvgFill(vg);
  nvgMoveTo(vg, 300, 300);
  nvgLineTo(vg, 400, 300);
  nvgArcTo(vg, 500, 300, 500, 400, 70);
  nvgStrokeColor(vg, nvgRGBA(255, 192, 0, 255));
  nvgArc(vg, 200, 200, 20, 0, 0.5 * 3.14, NVG_CW);
  nvgStroke(vg);
  nvgEndFrame(vg);
}

int main(int argc, char** argv) {
  smart_platform_init();
  vg = nvgCreateGLES2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
  while (!smart_platform_shoud_close()) {
    draw();
    smart_platform_swap_buffer();
  }
  smart_platform_terminate();
}

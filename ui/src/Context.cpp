#include <Context.h>
#include <Log.h>

#include <GLES2/gl2.h>
#define NANOVG_GLES2_IMPLEMENTATION  // Use GLES2 implementation.
#include "nanovg.h"
#include "nanovg_gl.h"
// #include "nanovg_gl_utils.h"

namespace SmartUI {

Context::Context() {
  // TRACE("context construct...\n");
  ctx = nvgCreateGLES2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
}
void Context::open(int w, int h, float ratio) {
  // TRACE("context open...\n");
  nvgBeginFrame(ctx, w, h, ratio);
  nvgBeginPath(ctx);
}
void Context::close() {
  // TRACE("context close...\n");
  nvgEndFrame(ctx);
}
void Context::beginPath() {
  // TRACE("context begin path...\n");
  nvgBeginPath(ctx);
}
void Context::save() {
  // TRACE("context save...\n");
  nvgSave(ctx);
}
void Context::restore() {
  // TRACE("context restore...\n");
  nvgRestore(ctx);
}
void Context::rect(int x, int y, int w, int h) {
  TRACE("context rect:%d %d %d %d \n", x, y, w, h);
  nvgRect(ctx, x, y, w, h);
}
void Context::stroke() {
  // TRACE("context stroke...\n");
  nvgStroke(ctx);
}
void Context::fill() {
  // TRACE("context fill...\n");
  nvgFill(ctx);
}

// style
void Context::fillColor(Color color) {
  TRACE("context fillColor...\n");
  nvgFillColor(ctx, nvgRGBA(color.r(), color.g(), color.b(), color.a()));
}

// translate
void Context::translate(int x, int y) {
  TRACE("context translate:%d %d \n", x, y);
  nvgTranslate(ctx, x, y);
}

// clip
void Context::clip(int x, int y, int w, int h) {
  TRACE("context clip:%d %d %d %d \n", x, y, w, h);
  nvgIntersectScissor(ctx, x, y, w, h);
}
}
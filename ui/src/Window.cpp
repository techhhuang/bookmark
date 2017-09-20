#include <Log.h>
#include <Platform.h>
#include <Window.h>

namespace SmartUI {
Window::Window() {
  TRACE("window construct...\n");
  smart_platform_create_window((void*)this);
  mContext = new Context();
}

void Window::draw(Context* ctx) {
  TRACE("window draw...\n");
  ctx->open();
  View::draw(ctx);
  ctx->close();
}

void Window::show() {
  TRACE("window show...\n");
  draw(mContext);
}

void Window::onMouseMove(int x, int y) {
  TRACE("window onMouseMove:%d %d\n", x, y);
}
}
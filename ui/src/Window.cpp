#include <Log.h>
#include <Platform.h>
#include <Window.h>

namespace SmartUI {
Window::Window(int w, int h) {
  mWidth = w;
  mHeight = h;
  TRACE("window construct...\n");
  smart_platform_create_window((void*)this);
  mContext = new Context();
}

void Window::draw(Context* ctx) {
  TRACE("window draw...\n");
  ctx->open(mWidth, mHeight, (float)mWidth / mHeight);
  View::draw(ctx);
  ctx->close();
}

void Window::show() {
  TRACE("window show...\n");
  draw(mContext);
  smart_platform_swap(this);
}
void Window::update() {
  TRACE("window update...\n");
  draw(mContext);
  smart_platform_swap(this);
}

void Window::mouseMoveCallback(int x, int y) {
  // TRACE("window onMouseMove:%d %d\n", x, y);
  mMousePos.setX(x);
  mMousePos.setY(y);
}
void Window::mouseButtonEventCallback(int button, int state,
                                      unsigned int time) {
  TRACE("window mouseButtonEventCallback:%d %d %u\n", button, state, time);
  View* v = findView(mMousePos);
  if (v) {
    TRACE("find view:%d %d %d %d\n", v->x(), v->y(), v->width(), v->height());
    v->onMouseButtonEvent(button, state, time);
    update();
  }
}
void Window::touchDownCallback(int id, int x, int y, unsigned int time) {
  TRACE("window touchDownCallback:%d %d %d %u\n", id, x, y, time);
  View* v = findView(Point<int>(x, y));
  if (v) {
    if (mFocusView == nullptr) {
      mFocusView = v;
      v->setPressed(true);
      update();
    }
  }
}
void Window::touchUpCallback(int id, int x, int y, unsigned int time) {
  TRACE("window touchUpCallback:%d %d %d %u\n", id, x, y, time);
  if (mFocusView != nullptr) {
    mFocusView->setPressed(false);
    update();
    mFocusView = nullptr;
  }
}
void Window::touchMoveCallback(int id, int x, int y, unsigned int time) {
  TRACE("window touchMoveCallback:%d %d %d %u\n", id, x, y, time);
}
//***********************************************************
}
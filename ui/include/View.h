#ifndef _VIEW_H
#define _VIEW_H

#include <Context.h>
#include <Object.h>
#include <Point.h>

#include <vector>

namespace SmartUI {
class View : Object {
 public:
  View();

  View(View *parent);

  const View *parent() const { return mParent; }

  void setParent(View *parent) { mParent = parent; }

  const std::vector<View *> children() const { return mChildren; }

  void addChild(View *child);

  int width() { return mWidth; }

  int height() { return mHeight; }

  int x() { return mPosition.x(); }

  int y() { return mPosition.y(); }

  void setWidth(int width) { mWidth = width; }

  void setHeight(int height) { mHeight = height; }

  void setSize(int width, int height) {
    mWidth = width;
    mHeight = height;
  }

  void setPosition(int x, int y) {
    mPosition.setX(x);
    mPosition.setY(y);
  }

  Color bgColor() { return mBgColor; }

  void setBgColor(Color bgColor) { mBgColor = bgColor; }

  bool visible() { return mVisible; }

  void setVisible(bool visible) { mVisible = visible; }

  bool cliping() { return mCliping; }

  void setCliping(bool cliping) { mCliping = cliping; }

  bool pressed() { return mPressed; }
  void setPressed(bool pressed) { mPressed = pressed; }

  virtual void draw(Context *ctx);

  View *findView(Point<int> p);
  virtual bool contains(Point<int> p) {
    Point<int> offset = p - mPosition;
    return offset.x() >= 0 && offset.x() <= mWidth && offset.y() >= 0 &&
           offset.y() <= mHeight;
  }

  // event
  void mouseButtonEvent(int button, int state, unsigned int time);
  void onMouseMove(int x, int y);
  void onMouseButtonEvent(int button, int state, unsigned int time);
  virtual void onTouchMove(int id, int x, int y, unsigned int time);
  virtual void onTouchUp(int id, int x, int y, unsigned int time);
  virtual void onTouchDown(int id, int x, int y, unsigned int time);

 protected:
  int mWidth, mHeight;
  Point<int> mPosition;
  View *mParent;
  std::vector<View *> mChildren;
  bool mVisible, mCliping, mPressed;
  Color mBgColor, mBgColorPressed;
};
}

#endif
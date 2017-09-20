#ifndef _VIEW_H
#define _VIEW_H

#include <Context.h>
#include <Object.h>
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

  int x() { return mX; }

  int y() { return mY; }

  void setWidth(int width) { mWidth = width; }

  void setHeight(int height) { mHeight = height; }

  void setSize(int width, int height) {
    mWidth = width;
    mHeight = height;
  }

  void setPosition(int x, int y) {
    mX = x;
    mY = y;
  }

  Color bgColor() { return mBgColor; }

  void setBgColor(Color bgColor) { mBgColor = bgColor; }

  bool visible() { return mVisible; }

  void setVisible(bool visible) { mVisible = visible; }

  bool cliping() { return mCliping; }

  void setCliping(bool cliping) { mCliping = cliping; }

  virtual void draw(Context *ctx);

 protected:
  int mX, mY, mWidth, mHeight;
  View *mParent;
  std::vector<View *> mChildren;
  bool mVisible, mCliping;
  Color mBgColor;
};
}

#endif
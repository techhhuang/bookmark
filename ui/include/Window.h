#ifndef _WINDOW_H
#define _WINDOW_H
#include <View.h>
#include <map>

namespace SmartUI {
class Window : public View {
 public:
  Window(int w, int h);
  void show();
  void update();
  virtual void draw(Context *ctx) override;

  virtual void onMouseMove(int x, int y);
  virtual void onMouseButtonEvent(int button, int state, unsigned int time);
  virtual void onTouchMove(int id, int x, int y, unsigned int time) override;
  virtual void onTouchUp(int id, int x, int y, unsigned int time) override;
  virtual void onTouchDown(int id, int x, int y, unsigned int time) override;

 protected:
  Context *mContext;
  Point<int> mMousePos;
  std::map<int, Point<int>> touches;
  View *mFocusView;
};
}

#endif
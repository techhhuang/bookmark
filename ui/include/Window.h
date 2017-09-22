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

  void mouseMoveCallback(int x, int y);
  void mouseButtonEventCallback(int button, int state, unsigned int time);
  void touchMoveCallback(int id, int x, int y, unsigned int time);
  void touchUpCallback(int id, int x, int y, unsigned int time);
  void touchDownCallback(int id, int x, int y, unsigned int time);

 protected:
  Context *mContext;
  Point<int> mMousePos;
  std::map<int, Point<int>> touches;
  View *mFocusView;
};
}

#endif
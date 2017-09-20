#ifndef _WINDOW_H
#define _WINDOW_H
#include <View.h>

namespace SmartUI {
class Window : public View {
 public:
  Window(int w, int h);
  void show();
  void update();
  virtual void draw(Context *ctx) override;
  void onMouseMove(int x, int y);
  void onMouseButtonEvent(int button, int state, unsigned int time);

 protected:
  Context *mContext;
  Point<int> mMousePos;
};
}

#endif
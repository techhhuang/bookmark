#ifndef _WINDOW_H
#define _WINDOW_H
#include <View.h>

namespace SmartUI {
class Window : public View {
 public:
  Window();
  void show();
  virtual void draw(Context *ctx) override;
  void onMouseMove(int x, int y);

 protected:
  Context *mContext;
};
}

#endif
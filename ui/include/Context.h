#ifndef _Context_H
#define _Context_H

#include <Color.h>
#include <Object.h>

#include "nanovg.h"

namespace SmartUI {

class Context : Object {
 public:
  Context();

  void open(int w, int h, float ratio);
  void close();

  void save();
  void restore();
  // void reset();

  void rect(int x, int y, int w, int h);

  void stroke();

  void fill();

  void beginPath();

  void translate(int x, int y);
  // style
  void fillColor(Color color);

  void clip(int x, int y, int w, int h);

 protected:
  NVGcontext *ctx;
  bool dirty;
};
}

#endif
#ifndef _COLOR_H
#define _COLOR_H

#include <Object.h>

typedef unsigned char uint8;

namespace SmartUI {
class Color : public Object {
 public:
  Color(uint8 r, uint8 g, uint8 b, uint8 a) {
    mR = r;
    mG = g;
    mB = b;
    mA = a;
  }
  //   Color(const Color& color) : mR(color.mR) {}
  uint8 r() { return mR; }
  uint8 g() { return mG; }
  uint8 b() { return mB; }
  uint8 a() { return mA; }
  static Color white() { return Color(255, 255, 255, 255); }

 protected:
  uint8 mR, mG, mB, mA;
};
}

#endif
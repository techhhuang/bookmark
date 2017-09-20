#ifndef _UTIL_H
#define _UTIL_H
#include <Color.h>
#include <cstdlib>

namespace SmartUI {
class Util {
 public:
  static Color getRandomColor() {
    return Color(rand() % 255, rand() % 255, rand() % 255, 255);
  }
};
}

#endif
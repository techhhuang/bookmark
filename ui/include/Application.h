#ifndef _APPLICATION_H
#define _APPLICATION_H
#include <Platform.h>

namespace {
class Application {
 public:
  Application() { smart_platform_init(); }
  Application(int argc, char** argv) { smart_platform_init(); }
  ~Application();
  int exec() { smart_platform_loop(); }
};
}
#endif